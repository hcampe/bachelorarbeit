#include <cmath> // for sqrt(), acos()
#include <iostream>
#include <omp.h>

#include "SU2.h"

std::complex<double> trace(const SU2matrix& U)
{
	return 2*real(U[0]);
}


SU2matrix SU2matrix::transpose() const
{
	return SU2matrix({upperRow[0], -conj(upperRow[1])});
}


SU2matrix SU2matrix::star() const
{
	return SU2matrix({conj(upperRow[0]), conj(upperRow[1])});
}


SU2matrix SU2matrix::dagger() const
{
	return SU2matrix({conj(upperRow[0]), -upperRow[1]});
}


SU2matrix SU2matrix::renormalise() const
{
	// std::complex::norm returns the square of the complex
	// modulus of a complex number
	const double normaliser { sqrt(norm(upperRow[0]) +
									norm(upperRow[1])) };
	return SU2matrix({upperRow[0]/normaliser,
					upperRow[1]/normaliser});
}


const SU2matrix::complex& SU2matrix::operator[](const std::size_t i) const
{
	return upperRow[i];
}


std::ostream& operator<<(std::ostream& out, const SU2matrix& U)
{
	out << "(" << U.upperRow[0] << "," << U.upperRow[1] << ")";
	return out;
}


SU2matrix operator*(const SU2matrix& A, const SU2matrix& B)
{
    std::vector<std::complex<double>> a(4, {0., 0.});
    std::vector<std::complex<double>> b(4, {0., 0.});
    std::vector<std::complex<double>> products(4, {0., 0.});

    #pragma omp parallel for
    for (size_t i = 0; i < 4; i++)
    {
        switch(i)
        {
            case 0:
                products[0] = A[0]*B[0];
                break;
            case 1:
                products[1] = A[1]*conj(B[1]);
                break;
            case 2:
                products[2] = A[0]*B[1];
                break;
            case 3:
                products[3] = A[1]*conj(B[0]);
                break;
        }
    }

    return SU2matrix({products[0] - products[1], products[2] + products[3]});

	// return SU2matrix({A[0]*B[0] - A[1]*conj(B[1]),
	// 				  A[0]*B[1] + A[1]*conj(B[0])});
}


SU2matrix operator+(const SU2matrix& A, const SU2matrix& B)
{
	return SU2matrix({A[0] + B[0], A[1] + B[1]});
}


SU2matrix operator-(const SU2matrix& A, const SU2matrix& B)
{
	return SU2matrix({A[0] - B[0], A[1] - B[1]});
}


void operator+=(SU2matrix& A, const SU2matrix& B)
{
	A.setUpperRow({A[0] + B[0], A[1] + B[1]});
	return;
}

SU2matrix unity()
{
	return SU2matrix({{1., 0}, {0., 0.}});
}

SU2matrix iPauliX()
{
	return SU2matrix({{0., 0.}, {0., 1.}});
}

SU2matrix iPauliY()
{
	return SU2matrix({{0., 0.}, {1., 0}});
}

SU2matrix iPauliZ()
{
	return SU2matrix({{0., 1.}, {0., 0.}});
}

