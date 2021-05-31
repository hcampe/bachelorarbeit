#include <random>

#include "SU2.h"

#ifndef RANDOMSU2IMPLEMENTATION_H
#define RANDOMSU2IMPLEMENTATION_H

// sadly it's the only way i came up with:
constexpr double PI { acos(-1.) };

template<class URNG> SU2matrix randomSU2(URNG& engine, const double delta)
{
	// set up the distributions
	std::uniform_real_distribution<double> aDist {0., 2*PI*delta};
	std::uniform_real_distribution<double> bDist {0., 2*PI};
	std::uniform_real_distribution<double> cosCdist {-1., 1.};

	// draw the pseudorandom numbers and calculate trigonometric
	// functions to save some time
	const double a { aDist(engine) };
	const double sinA { sin(a) };
	const double cosA { cos(a) };
	const double b { bDist(engine) };
	const double sinB { sin(b) };
	const double cosB { cos(b) };
	const double cosC { cosCdist(engine) };
	const double sinC { sqrt(1 - cosC*cosC)};

	SU2matrix U { {{cosA, sinA * cosC},
				{sinA * sinB * sinC, sinA * cosB * sinC}} };
    U = U.renormalise();

    return U;
}

#endif
