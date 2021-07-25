// compile: g++ -Wall -Wextra main.cpp SU2.cpp Gaugeconfig.cpp getStaple.cpp -o main
// execute: ./main
#include <ctime> // to log the time of execution
#include <fstream> // to log things to file
#include <iostream>
#include <random> // for the random generator
#include <sys/time.h> // to measure the computation time
#include <vector>

#include "analysis.h"
#include "Gaugeconfig.h"
#include "getStaple.h"
#include "su2sweep.h"
#include "SU2.h"
#include "vector_operations.h"
#include "wilsonLoops.h"


int main()
{

    // for random number genration:
    std::random_device rd {}; // to generate the seed for...
    std::mt19937 engine { rd() }; // Mersenne twister generator

    // lattice parameters
    const std::size_t timeSize { 10 };
    const std::size_t spaceSize { 10 };
    const double deltaInit { 0. };

    // initial configuration:
    Gaugeconfig U { hotStart(timeSize, spaceSize, engine, deltaInit) };

    // sweep parameters:
    const double beta { 2.3 };
    const double delta { .1 };
    const std::size_t numberOfSweeps { 24 };
    const std::size_t iterationsPerSight { 10 };

    // to save observables:
    const std::string dataDir { "../data/" };
    const std::string filename { "wilson2xt.txt" };
    std::vector<std::vector<double>> results;

    // for the Wilson loops:
    std::vector<size_t> M {1,2,3,4,5,6,7,8,9}; // time dim
    std::vector<size_t> N {2,2,2,2,2,2,2,2,2}; // space dim
    results.push_back(std::vector<double>(M.begin(), M.end()));
    results.push_back(std::vector<double>(N.begin(), N.end()));

    // to measure the time:
    struct timeval tStart, tEnd;
    gettimeofday(&tStart, NULL);

    std::cout << "warming up..." << std::endl;
    for (std::size_t i {0}; i < 1000; i++)
    {
        sweep(U, beta, delta, iterationsPerSight, engine);
    }

    std::cout << "performing " << numberOfSweeps << " sweeps..." << std::flush;

#pragma omp declare reduction (merge : std::vector<std::vector<double>> : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))
#pragma omp parallel for reduction(merge: results), num_threads(2)
    for (std::size_t i=0; i < numberOfSweeps; i++)
    {
        results.push_back(getLoopTraces(U, 0, 1, M, N));
        results.push_back(getLoopTraces(U, 0, 2, M, N));
        results.push_back(getLoopTraces(U, 0, 3, M, N));
        sweep(U, beta, delta, iterationsPerSight, engine);
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

//    std::cout << "zero if writing successful: ";
//    std::cout << write_2d(results, dataDir + std::to_string(usec) + filename, ',') << '\n';
//    // (the usec is there to make the filename unique)
//
//    // log the parameters:
//    std::ofstream log;
//    log.open(dataDir + "allSimulations.log", std::ios::app); // append mode
//    log<< "# ";
//    log<< "deltaInit = " << deltaInit << ", ";
//    log<< "delta = " << delta << ", ";
//    log<< "beta = " << beta << ", ";
//    log<< "numberOfSweeps = " << numberOfSweeps << ", ";
//    log<< "iterationsPerSight = " << iterationsPerSight << ", ";
//    log<< "timeSize = " << timeSize << ", ";
//    log<< "spaceSize = " << spaceSize << ", ";
//    log<< "filename: " << filename << ", ";
//    log << "duration: " << hour << 'h' << min << "min" << sec + 1.e-6*usec << "s, ";
//    const time_t now { std::time(0) };
//    log << std::ctime(&now);
//    log.close();
}
