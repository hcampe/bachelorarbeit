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


// SU2matrix& Gaugeconfig::operator()(const std::vector<std::size_t> x,
// 					  			   const std::size_t mu)
// {
// 	return parallelTransports[x[0]][x[1]][x[2]][x[3]][mu];
// }


// const SU2matrix& Gaugeconfig::operator()(const std::vector<std::size_t> x,
// 					  			   const std::size_t mu) const
// {
// 	return parallelTransports[x[0]][x[1]][x[2]][x[3]][mu];
// }


SU2matrix& Gaugeconfig::operator()(const std::vector<long int> x,
					  			   const std::size_t mu)
{
	const long int timeSize { static_cast<long int>(parallelTransports.size()) };
	const long int spaceSize{ static_cast<long int>(parallelTransports[0].size()) };

	return parallelTransports[(x[0] + timeSize) % timeSize]
							 [(x[1] + spaceSize) % spaceSize]
							 [(x[2] + spaceSize) % spaceSize]
							 [(x[3] + spaceSize) % spaceSize]
							 [mu];
}


const SU2matrix& Gaugeconfig::operator()(const std::vector<long int> x,
					  			   const std::size_t mu) const
{
	const long int timeSize { static_cast<long int>(parallelTransports.size()) };
	const long int spaceSize{ static_cast<long int>(parallelTransports[0].size()) };

	return parallelTransports[(x[0] + timeSize) % timeSize]
							 [(x[1] + spaceSize) % spaceSize]
							 [(x[2] + spaceSize) % spaceSize]
							 [(x[3] + spaceSize) % spaceSize]
							 [mu];
}


Gaugeconfig coldStart(const size_t timeSize,
						const size_t spaceSize)
{
	return Gaugeconfig(timeSize, spaceSize);
}

