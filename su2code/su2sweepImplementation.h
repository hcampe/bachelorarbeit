#include "su2sweep.h"

#include <cmath> // for exp

#include "Gaugeconfig.h"
#include "getStaple.h"
#include "SU2.h"

#ifndef SU2SWEEP_IMPL
#define SU2SWEEP_IMPL

template<class URNG> void 
sweep(Gaugeconfig& U, const double beta, const double delta,
       const std::size_t iterationsPerSight, URNG& engine)
{
    std::vector<long int> x(Gaugeconfig::numSpacetimeDim, 0);
    SU2matrix R; // R stands for "random"^^
    SU2matrix Unew;
    double deltaS;
    std::uniform_real_distribution<double> rDist {0., 1.};


    for (x[0] = 0; x[0] < U.getTimeSize(); x[0]++)
    {
        for (x[1] = 0; x[1] < U.getSpaceSize(); x[1]++)
        {
            for (x[2] = 0; x[2] < U.getSpaceSize(); x[2]++)
            {
                for (x[3] = 0; x[3] < U.getSpaceSize(); x[3]++)
                {
                    for (std::size_t mu { 0 }; mu < Gaugeconfig::numSpacetimeDim; mu++)
                    {
                        for (std::size_t i { 0 }; i < iterationsPerSight; i++)
                        {
                            R = randomSU2(engine, delta);
                            Unew = U(x, mu) * R;
                            deltaS = -.5 * beta * real(trace(
                                        (Unew - U(x, mu))*getStaple(U, x, mu)));
                            if (deltaS < 0. or (rDist(engine) < exp(-deltaS)))
                            {
                                U(x, mu) = Unew;
                            }
                        }
                    }
                }
            }
        }
    }

    return;
}


#endif
