#include <cmath> // for sqrt(), acos()

#include "SU2.h"

// sadly it's the only way i came up with:
constexpr double PI { acos(-1.) };

const SU2matrix::complex& SU2matrix::operator[](const std::size_t i) const
{
	return upperRow[i];
}

std::complex<double> trace(const SU2matrix& U)
{
	return 2*real(U[0]);
}

SU2matrix SU2matrix::transpose()
{
	return SU2matrix({upperRow[0], -conj(upperRow[1])});
}


SU2matrix SU2matrix::star()
{
	return SU2matrix({conj(upperRow[0]), conj(upperRow[1])});
}


SU2matrix SU2matrix::dagger()
{
	return SU2matrix({conj(upperRow[0]), -upperRow[1]});
}


SU2matrix SU2matrix::renormalise()
{
	// std::complex::norm returns the square of the complex
	// modulus of a complex number
	const double normaliser { sqrt(norm(upperRow[0] +
									norm(upperRow[1]))) };
	return SU2matrix({upperRow[0]/normaliser,
					upperRow[1]/normaliser});
}

std::ostream& operator<<(std::ostream& out, const SU2matrix& U)
{
	out << "(" << U.upperRow[0] << " " << U.upperRow[1] << ")";
	return out;
}

SU2matrix operator*(const SU2matrix& a, const SU2matrix& b)
{
	return SU2matrix({a[0]*b[0] - a[1]*conj(b[1]),
					  a[0]*b[1] + a[1]*conj(b[0])});
}

SU2matrix unity()
{
	return SU2matrix();
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

template<class URNG> SU2matrix randomSU2(URNG& engine, const double delta)
{
	// set up the distributions
	// std::uniform_real_distribution<double> aDist {0., 2*PI*delta};
	// std::uniform_real_distribution<double> bDist {0., 2*PI};
	// std::uniform_real_distribution<double> cosCdist {-1., 1.};

	// // draw the pseudorandom numbers and calculate trigonometric
	// // functions to save some time
	// const double a { aDist(engine) };
	// const double sinA { sin(a) };
	// const double cosA { cos(a) };
	// const double b { bDist(engine) };
	// const double sinB { sin(b) };
	// const double cosB { cos(b) };
	// const double cosC { cosCdist(engine) };
	// const double sinC { sqrt(1 - cosC*cosC)};

	// return SU2matrix({{cosA, sinA * cosC},
	// 			{sinA * sinB * sinC, sinA * cosB * sinC}});

	return SU2matrix();
}

