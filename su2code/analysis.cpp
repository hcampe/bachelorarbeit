#include <omp.h>

#include "Gaugeconfig.h"
#include "SU2.h"

SU2matrix getPlaquette(const Gaugeconfig& U,
	const std::vector<long int> x, const size_t mu, const size_t nu)
{
	std::vector<long int> xPlusMu { x };
	xPlusMu[mu]++;
	std::vector<long int> xPlusNu { x };
	xPlusNu[nu]++;

	return U(x, mu)*U(xPlusMu, nu)*U(xPlusNu, mu).dagger()*U(x, nu).dagger();
}

double gaugeEnergy(const Gaugeconfig& U)
{
	double energy { 0. };

    const int numberOfThreads { omp_get_max_threads() };
    static double* energyOfThread = new double[numberOfThreads];

    #pragma omp parallel
    {
        int thread { omp_get_thread_num() };
        
        #pragma omp for
	    for (long int x0 = 0; x0 < U.getTimeSize(); x0++)
	    {
	        for (long int x1 = 0; x1 < U.getSpaceSize(); x1++)
	    	{
	            for (long int x2 = 0; x2 < U.getSpaceSize(); x2++)
	    		{
	                for (long int x3 = 0; x3 < U.getSpaceSize(); x3++)
	    			{
	    				for (std::size_t nu { 1 }; nu < Gaugeconfig::numSpacetimeDim; nu++)
	    				{
	    					for (std::size_t mu { 0 }; mu < nu; mu++)
	    					{
	    						energyOfThread[thread] = real(trace(getPlaquette(U, {x0, x1, x2, x3}, mu, nu)));
	    					}
	    				}
	    			}
	    		}
	    	}
	    }
    }

    for (int i {0}; i < numberOfThreads; i++)
    {
        energy += energyOfThread[i];
    }

	return energy;
}

double gaugeEnergy2(const Gaugeconfig& U)
{
	double energy { 0. };

    #pragma omp parallel for reduction(+:energy)
	for (long int x0 = 0; x0 < U.getTimeSize(); x0++)
	{
	    for (long int x1 = 0; x1 < U.getSpaceSize(); x1++)
		{
	        for (long int x2 = 0; x2 < U.getSpaceSize(); x2++)
			{
	            for (long int x3 = 0; x3 < U.getSpaceSize(); x3++)
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
