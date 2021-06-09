#include "Gaugeconfig.h"
#include "SU2.h"

#ifndef HOTSTART_H
#define HOTSTART_H

template<class URNG>
Gaugeconfig hotStart(const size_t timeSize,
                     const size_t spaceSize,
                     URNG& engine,
                     const double delta)
{
    auto U = Gaugeconfig(timeSize, spaceSize);
    std::vector<long int> x(4, 0);

    for (x[0] = 0; x[0] < U.getTimeSize(); x[0]++)
        for (x[1] = 0; x[1] < U.getSpaceSize(); x[1]++)
            for (x[2] = 0; x[2] < U.getSpaceSize(); x[2]++)
                for (x[3] = 0; x[3] < U.getSpaceSize(); x[3]++)
                    for (size_t mu {0}; mu < Gaugeconfig::numSpacetimeDim; mu++)
                    {
                        U(x, mu) = randomSU2(engine, delta);
                    }
    return U;
}

#endif
