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
    std::vector<long int> x(Gaugeconfig::numSpacetimeDim, 0);

    for (x[0] = 0; x[0] < U.getTimeSize(); x[0]++)
    {
        for (x[1] = 0; x[1] < U.getSpaceSize(); x[1]++)
        {
            for (x[2] = 0; x[2] < U.getSpaceSize(); x[2]++)
            {
                for (x[3] = 0; x[3] < U.getSpaceSize(); x[3]++)
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
