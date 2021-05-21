// compile: g++ -Wall -Wextra main.cpp SU2.cpp Gaugeconfig.cpp getStaple.cpp -o main
// execute: ./main
#include <iostream>
#include <random>

#include "analysis.h"
#include "Gaugeconfig.h"
#include "getStaple.h"
#include "su2sweep.h"
#include "SU2.h"
#include "vector_operations.h"


int main()
{
	// for random number genration:
	std::random_device rd {}; // to generate the seed for...
	std::mt19937 engine { rd() }; // Mersenne twister generator

	// lattice parameters
	const std::size_t timeSize { 16 };
	const std::size_t spaceSize { 8 };
	const double deltaInit { .1 };
	// initial configuration:
	Gaugeconfig U { hotStart(timeSize, spaceSize, engine, deltaInit) };

	// sweep parameters:
	const double beta { 4.5 };
	const double delta { .1 };
	const std::size_t numberOfSweeps { 200 };
	const std::size_t iterationsPerSight { 10 };

	// to save observables:
	const std::string dataDir { "../data/" };
	std::vector<double> energy(numberOfSweeps, 0.);

	std::cout << "performing " << numberOfSweeps << " sweeps: ";
	for (std::size_t i {0}; i < numberOfSweeps; i++)
	{
		std::cout << "#" << std::flush;
		U = sweep(U, beta, delta, iterationsPerSight, engine);
		energy[i] = gaugeEnergy(U);
	}
	std::cout << '\n';


	std::cout << "zero if writing successful: " << writeVector(energy, dataDir + "firstTest.txt") << '\n';
}