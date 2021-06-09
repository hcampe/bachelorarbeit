#ifdef _USE_OMP_
#include <omp.h>
#endif

#include <vector>
#include "Gaugeconfig.h"
#include "SU2.h"

#ifdef _USE_OMP_ // parallel version:
SU2matrix getStaple(const Gaugeconfig& U,
                    const std::vector<long int> x,
                    const std::size_t mu)
{
    SU2matrix staple {};

    std::vector<long int> xPlusMu { x };
    xPlusMu[mu]++;

    std::vector<long int> xPlusNu { x };
    std::vector<long int> xMinusNu { x };
    std::vector<long int> xPlusMuMinusNu { xPlusMu };

    const int numberOfThreads { omp_get_max_threads() };
    static SU2matrix* stapleOfThread = new SU2matrix[numberOfThreads];
    #pragma omp parallel
    {
        int thread { omp_get_thread_num() };

        #pragma omp for
        for (std::size_t nu = 0; nu < Gaugeconfig::numSpacetimeDim; nu++)
        {
            if (nu == mu) continue;

            xPlusNu[nu]++;
            xPlusMuMinusNu[nu]--;
            xMinusNu[nu]--;

            stapleOfThread[thread] = U(xPlusMu, nu) * U(xPlusNu, mu).dagger() * U(x, nu).dagger()
                + U(xPlusMuMinusNu, nu).dagger() * U(xMinusNu, mu).dagger() * U(xMinusNu, nu);

            xMinusNu[nu]++;
            xPlusMuMinusNu[nu]++;
            xPlusNu[nu]--;
        }
    }

    for (int i {0}; i < numberOfThreads; i++)
    {
        staple += stapleOfThread[i];
    }

    return staple;
}

#else // non parallel version:
SU2matrix getStaple(const Gaugeconfig& U,
                    const std::vector<long int> x,
                    const std::size_t mu)
{
    SU2matrix staple {};

    std::vector<long int> xPlusMu { x };
    xPlusMu[mu]++;

    std::vector<long int> xPlusNu { x };
    std::vector<long int> xMinusNu { x };
    std::vector<long int> xPlusMuMinusNu { xPlusMu };

    for (std::size_t nu = 0; nu < Gaugeconfig::numSpacetimeDim; nu++)
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

#endif
