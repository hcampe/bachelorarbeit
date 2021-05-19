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


const SU2matrix& Gaugeconfig::operator()(const std::vector<std::size_t> x,
					  			   const std::size_t mu) const
{
	return parallelTransports[x[0]][x[1]][x[2]][x[3]][mu];
}


Gaugeconfig coldStart(const size_t timeSize,
						const size_t spaceSize)
{
	return Gaugeconfig(timeSize, spaceSize);
}

