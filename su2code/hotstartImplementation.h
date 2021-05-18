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
	auto output = Gaugeconfig(timeSize, spaceSize);
	std::vector<size_t> x(4, 0);

	for (x[0] = 0; x[0] < timeSize; x[0]++)
		for (x[1] = 0; x[1] < spaceSize; x[1]++)
			for (x[2] = 0; x[2] < spaceSize; x[2]++)
				for (x[3] = 0; x[3] < spaceSize; x[3]++)
					for (size_t mu {0}; mu < Gaugeconfig::numSpacetimeDim; mu++)
					{
						output(x, mu) = randomSU2(engine, delta);
					}
	return output;
}

#endif