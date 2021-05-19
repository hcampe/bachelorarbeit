#include <vector>

#include "Gaugeconfig.h"
#include "SU2.h"


SU2matrix getStaple(const Gaugeconfig& U,
					const std::vector<size_t> x,
					const std::size_t mu)
{
	SU2matrix staple { {{0., 0.}, {0., 0.}} };

	std::vector<size_t> xPlusMu { x };
	xPlusMu[mu]++;

	std::vector<size_t> xPlusNu { x };
	std::vector<size_t> xMinusNu { x };
	std::vector<size_t> xPlusMuMinusNu { xPlusMu };

	for (std::size_t nu {0}; nu < Gaugeconfig::numSpacetimeDim; nu++)
	{
		if (nu == mu) continue;

		xPlusNu[nu]++;
		xPlusMuMinusNu[nu]--;
		xMinusNu[nu]--;

		staple += U(xPlusMu, nu) * U(xPlusNu, mu).dagger() * U(x, nu).dagger()
			+ U(xPlusMuMinusNu, nu).dagger() * U(xMinusNu, mu).dagger() * U(xMinusNu, nu);

		xMinusNu[nu]++;
		xPlusMuMinusNu[nu]++;
		xPlusNu[nu]--;
	}

	return staple;
}