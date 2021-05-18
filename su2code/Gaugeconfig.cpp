#include <vector>

#include "Gaugeconfig.h"
#include "SU2.h"

Gaugeconfig::Gaugeconfig(const Gaugeconfig::size timeSize,
						const Gaugeconfig::size spaceSize)
{
	parallelTransports= std::vector<
						std::vector<
						std::vector<
						std::vector<
						std::vector<SU2matrix>>>>>(
						 	timeSize,
						 	std::vector<
						 	std::vector<
						 	std::vector<
						 	std::vector<SU2matrix>>>>(
						 		spaceSize,
						 		std::vector<
						 		std::vector<
						 		std::vector<SU2matrix>>>(
						 			spaceSize,
						 			std::vector<
						 			std::vector<
						 			SU2matrix>>(
						 				spaceSize,
						 				std::vector<SU2matrix>(
						 					Gaugeconfig::numSpacetimeDim,
						 					SU2matrix())))));
}


SU2matrix& Gaugeconfig::operator()(const std::vector<std::size_t> x,
					  			   const std::size_t mu)
{
	return parallelTransports[x[0]][x[1]][x[2]][x[3]][mu];
}


Gaugeconfig coldStart(const size_t timeSize,
						const size_t spaceSize)
{
	return Gaugeconfig();
}


Gaugeconfig hotStart(const size_t timeSize,
					 const size_t spaceSize,
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
					}
	return Gaugeconfig();
}