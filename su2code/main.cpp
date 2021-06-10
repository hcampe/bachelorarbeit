// compile: g++ -Wall -Wextra main.cpp SU2.cpp Gaugeconfig.cpp getStaple.cpp -o main
// execute: ./main
#include <ctime> // to log the time of execution
#include <fstream> // to log things to file
#include <iostream>
#include <random> // for the random generator
#include <sys/time.h> // to measure the computation time

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

    // sweep parameters:
    const double beta { 1. };
    const double delta { .1 };
    const std::size_t numberOfSweeps { 10 };
    const std::size_t iterationsPerSight { 10 };

    // to save observables:
    const std::string dataDir { "../data/" };
    const std::string filename { "maxPrecisionDoubles.txt" };
    std::vector<double> energy(numberOfSweeps, 0.);

    // to measure the time:
    struct timeval tStart, tEnd;
    gettimeofday(&tStart, NULL);

    // just for testing:
//    std::cout << "performing " << numberOfSweeps << " sweeps." << std::endl;
//    for (std::size_t i {0}; i < numberOfSweeps; i++)
//    {
//        energy[i] = gaugeEnergy(U);
//        std::cout << "P[" << i << "] = " << energy[i]/(6 * 2 * timeSize * spaceSize*spaceSize*spaceSize) << std::endl;
//        sweep(U, beta, delta, iterationsPerSight, engine);
//    }

    // 'serious run' with progress bar
    std::cout << "performing " << numberOfSweeps << " sweeps: " << std::flush;
    for (std::size_t i {0}; i < numberOfSweeps; i++)
    {
        energy[i] = gaugeEnergy(U);
        sweep(U, beta, delta, iterationsPerSight, engine);
        if (!(i%1000))
        {
            std::cout << i / 1000 << std::flush;
        }
        else if (!(i%100))
        {
            std::cout << '#' << std::flush;
        }
    }

    std::cout << '\n';
    gettimeofday(&tEnd, NULL);

    const double totalSec {static_cast<double>(tEnd.tv_sec - tStart.tv_sec) };
    const double usec { static_cast<double>(tEnd.tv_usec - tStart.tv_usec) };
    const int hour { static_cast<int>(totalSec) / 3600 };
    const int min { static_cast<int>(totalSec) / 60 - hour*60 };
    const int sec { static_cast<int>(totalSec) % 60 };

    std::cout << numberOfSweeps << " sweeps took ";
    std::cout << hour << "h, ";
    std::cout << min << "min, ";
    std::cout << sec + 1.e-6*usec << "s." << std::endl;

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
    log << "duration: " << hour << 'h' << min << "min" << sec + 1.e-6*usec << "s, ";
    const time_t now { std::time(0) };
    log << std::ctime(&now);
    log.close();
}
