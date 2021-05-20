// compile: g++ -Wall -Wextra main.cpp SU2.cpp Gaugeconfig.cpp getStaple.cpp -o main
// execute: ./main
#include <iostream>
#include <random>

#include "Gaugeconfig.h"
#include "getStaple.h"
#include "su2sweep.h"
#include "SU2.h"


int main()
{
	// for random number genration:
	std::random_device rd {}; // to generate the seed for...
	std::mt19937 engine { rd() }; // Mersenne twister generator

	// lattice parameters
	const std::size_t timeSize { 5 };
	const std::size_t spaceSize { 5 };
	const double deltaInit { .1 };
	// initial configuration:
	Gaugeconfig U { hotStart(timeSize, spaceSize, engine, deltaInit) };

	// sweep parameters:
	const double beta { 1. };
	const double delta { .01 };
	const std::size_t numberOfSweeps { 100 };
	const std::size_t iterationsPerSight { 10 };

	std::cout << "performing " << numberOfSweeps << " sweeps: ";
	for (std::size_t i {0}; i < numberOfSweeps; i++)
	{
		std::cout << "#" << std::flush;
		U = sweep(U, beta, delta, iterationsPerSight, engine);
	}
	std::cout << '\n';
}