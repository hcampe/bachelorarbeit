// compile: g++ -Wall -Wextra main.cpp SU2.cpp Gaugeconfig.cpp getStaple.cpp -o main
// execute: ./main
#include <ctime>
#include <fstream>
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
	const double deltaInit { 0. };

	// initial configuration:
	Gaugeconfig U { hotStart(timeSize, spaceSize, engine, deltaInit) };
	// Gaugeconfig U(timeSize, spaceSize);
	std::cout << "initial energy: " << gaugeEnergy(U) << std::endl;

	// sweep parameters:
	const double beta { 4.5 };
	const double delta { .1 };
	const std::size_t numberOfSweeps { 5 };
	const std::size_t iterationsPerSight { 10 };

	// to save observables:
	const std::string dataDir { "../data/" };
	const std::string filename { "frmColdStart.txt" };
	std::vector<double> energy(numberOfSweeps, 0.);

	std::cout << "performing " << numberOfSweeps << " sweeps: ";
	for (std::size_t i {0}; i < numberOfSweeps; i++)
	{
		energy[i] = gaugeEnergy(U);
		U = sweep(U, beta, delta, iterationsPerSight, engine);
		std::cout << "#" << std::flush;
	}
	std::cout << '\n';

	std::cout << "zero if writing successful: ";
	std::cout << writeVector(energy, dataDir + filename) << '\n';

	// log the parameters:
	std::ofstream log;
	log.open(dataDir + "allSimulations.log", std::ios::app); // append mode
	log<< "# ";
	log<< "deltaInit = " << deltaInit << ", ";
	log<< "delta = " << delta << ", ";
	log<< "beta = " << beta << ", ";
	log<< "numberOfSweeps = " << numberOfSweeps << ", ";
	log<< "iterationsPerSight = " << iterationsPerSight << ", ";
	log<< "timeSize = " << timeSize << ", ";
	log<< "spaceSize = " << spaceSize << ", ";
	log<< "filename: " << filename << ", ";
	const time_t now { std::time(0) };
	log << std::ctime(&now);
	log.close();
}