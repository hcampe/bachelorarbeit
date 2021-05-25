#include "su2sweep.h"

#include <cmath> // for exp

#include "Gaugeconfig.h"
#include "getStaple.h"
#include "SU2.h"

#ifndef SU2SWEEP_IMPL
#define SU2SWEEP_IMPL

template<class URNG> Gaugeconfig
sweep(const Gaugeconfig& input, const double beta, const double delta,
   	const std::size_t iterationsPerSight, URNG& engine)
{
	Gaugeconfig U { input };
	std::vector<long int> x(Gaugeconfig::numSpacetimeDim, 0);
	long int timeSize { static_cast<long int>(U.getTimeSize()) };
	long int spaceSize { static_cast<long int>(U.getSpaceSize()) };
	SU2matrix R; // R stands for "random"^^
	double deltaS;
	std::uniform_real_distribution<double> rDist {0., 1.};


	for (x[0] = 0; x[0] < timeSize; x[0]++)
	{
		for (x[1] = 0; x[1] < spaceSize; x[1]++)
		{
			for (x[2] = 0; x[2] < spaceSize; x[2]++)
			{
				for (x[3] = 0; x[3] < spaceSize; x[3]++)
				{
					for (std::size_t mu { 0 }; mu < Gaugeconfig::numSpacetimeDim; mu++)
					{
						for (std::size_t i { 0 }; i < iterationsPerSight; i++)
						{
							R = randomSU2(engine, delta);
							deltaS = -.5 * beta * real(trace((U(x, mu)*R - U(x, mu))*getStaple(U, x, mu)));
							if (deltaS < 0. or (rDist(engine) < exp(-deltaS)))
							{
								U(x, mu) = (U(x, mu)*R).renormalise();
							}
						}
					}
				}
			}
		}
	}

	return U;
}


#endif