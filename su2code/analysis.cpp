#include <omp.h>

#include "Gaugeconfig.h"
#include "SU2.h"

SU2matrix getPlaquette(const Gaugeconfig& U,
	const std::vector<long int> x, const size_t mu, const size_t nu)
{
	SU2matrix plaquette { {{0., 0.}, {0., 0.}} };
	std::vector<long int> xPlusMu { x };
	xPlusMu[mu]++;
	std::vector<long int> xPlusNu { x };
	xPlusNu[nu]++;

	plaquette = U(x, mu)*U(xPlusMu, nu)*U(xPlusNu, mu).dagger()*U(x, nu).dagger();

	return plaquette;
}


double gaugeEnergy(const Gaugeconfig& U)
{
	double energy { 0. };
	long int timeSize { static_cast<long int>(U.getTimeSize()) };
	long int spaceSize { static_cast<long int>(U.getSpaceSize()) };

    #pragma omp parallel for reduction(+:energy)
	for (long int x0 = 0; x0 < timeSize; x0++)
	{
	    for (long int x1 = 0; x1 < spaceSize; x1++)
		{
	        for (long int x2 = 0; x2 < spaceSize; x2++)
			{
	            for (long int x3 = 0; x3 < spaceSize; x3++)
				{
					for (std::size_t nu { 1 }; nu < Gaugeconfig::numSpacetimeDim; nu++)
					{
						for (std::size_t mu { 0 }; mu < nu; mu++)
						{
							energy += real(trace(getPlaquette(U, {x0, x1, x2, x3}, mu, nu)));
						}
					}
				}
			}
		}
	}

	return energy;
}
