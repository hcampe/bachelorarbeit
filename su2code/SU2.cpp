#include <cmath> // for sqrt(), acos()
#include <iostream> // for testing

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
	const double normaliser { sqrt(norm(upperRow[0] +
									norm(upperRow[1]))) };
    //std::cout << "determinant = " << normaliser*normaliser << std::endl;
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


SU2matrix operator*(const SU2matrix& a, const SU2matrix& b)
{
	return SU2matrix({a[0]*b[0] - a[1]*conj(b[1]),
					  a[0]*b[1] + a[1]*conj(b[0])});
}


SU2matrix operator+(const SU2matrix& a, const SU2matrix& b)
{
	return SU2matrix({a[0] + b[0], a[1] + b[1]});
}


SU2matrix operator-(const SU2matrix& a, const SU2matrix& b)
{
	return SU2matrix({a[0] - b[0], a[1] - b[1]});
}


void operator+=(SU2matrix& a, const SU2matrix& b)
{
	a.setUpperRow({a[0] + b[0], a[1] + b[1]});
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

