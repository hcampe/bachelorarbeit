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
	std::vector<long int> x(Gaugeconfig::numSpacetimeDim, 0);
	long int timeSize { static_cast<long int>(U.getTimeSize()) };
	long int spaceSize { static_cast<long int>(U.getSpaceSize()) };

	for (x[0] = 0; x[0] < timeSize; x[0]++)
	{
		for (x[1] = 0; x[1] < spaceSize; x[1]++)
		{
			for (x[2] = 0; x[1] < spaceSize; x[1]++)
			{
				for (x[3] = 0; x[1] < spaceSize; x[1]++)
				{
					for (std::size_t nu { 1 }; nu < Gaugeconfig::numSpacetimeDim; nu++)
					{
						for (std::size_t mu { 0 }; mu < nu; mu++)
						{
							energy += real(trace(getPlaquette(U, x, mu, nu)));
						}
					}
				}
			}
		}
	}

	return energy;
}
