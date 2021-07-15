#include <iostream>
#include <vector>

#include "analysis.h"
#include "Gaugeconfig.h"
#include "wilsonLoops.h"

int main()
{
    // for random number genration:
    std::random_device rd {}; // to generate the seed for...
    std::mt19937 engine { rd() }; // Mersenne twister generator

    Gaugeconfig U { hotStart(5, 5, engine, .1) };

    std::cout << "\n////////// test of the straight line/////////\n";
    std::cout << " put iX, iY, iZ, iX, ... in a straight line. /////////\n";
    U({0,0,0,0}, 0) = iPauliX();
    U({1,0,0,0}, 0) = iPauliY();
    U({2,0,0,0}, 0) = iPauliZ();
    U({3,0,0,0}, 0) = iPauliX();
    U({4,0,0,0}, 0) = iPauliY();
    std::cout << "1: " << getStraightLine(U, {0,0,0,0}, 0, 1) << std::endl;
    std::cout << "2: " << getStraightLine(U, {0,0,0,0}, 0, 2) << std::endl;
    std::cout << "3: " << getStraightLine(U, {0,0,0,0}, 0, 3) << std::endl;
    std::cout << "4: " << getStraightLine(U, {0,0,0,0}, 0, 4) << std::endl;
    std::cout << "5: " << getStraightLine(U, {0,0,0,0}, 0, 5) << std::endl;

    std::cout << "\n////////// test of the loop by comparison to plaquette ////////////\n";
    std::cout << "as planar loop:" << getPlanarLoop(U, {0,0,0,0}, 0, 1, 1, 1) << std::endl;
    std::cout << "as plaquette:  " << getPlaquette(U, {0,0,0,0}, 0, 1) << std::endl;

    std::cout << "\n///////// more interesting test of the planar loop /////////\n";
    std::cout << "put iX, iY, iZ, iX, ... on a 3 x 4 rectangle in dim. 1, 2" << std::endl;
    U = hotStart(5, 5, engine, .1); // "resetting" the configuration

    U({0,0,0,0}, 1) = iPauliX();
    U({0,1,0,0}, 1) = iPauliY();
    U({0,2,0,0}, 1) = iPauliZ();

    U({0,3,0,0}, 2) = iPauliX();
    U({0,3,1,0}, 2) = iPauliY();
    U({0,3,2,0}, 2) = iPauliZ();
    U({0,3,3,0}, 2) = iPauliX();

    U({0,2,4,0}, 1) = iPauliY().dagger();
    U({0,1,4,0}, 1) = iPauliZ().dagger();
    U({0,0,4,0}, 1) = iPauliX().dagger();

    U({0,0,3,0}, 2) = iPauliY().dagger();
    U({0,0,2,0}, 2) = iPauliZ().dagger();
    U({0,0,1,0}, 2) = iPauliX().dagger();
    U({0,0,0,0}, 2) = iPauliY().dagger();

    std::cout << "should get -iZ: ";
    std::cout << getPlanarLoop(U, {0,0,0,0}, 1, 2, 3, 4) << std::endl;

    std::cout << "put iX, iY, iZ, iX, ... on a 3 x 3 rectangle in dim. 1, 2" << std::endl;
    U = hotStart(5, 5, engine, .1); // "resetting" the configuration

    U({0,0,0,0}, 1) = iPauliX();
    U({0,1,0,0}, 1) = iPauliY();
    U({0,2,0,0}, 1) = iPauliZ();

    U({0,3,0,0}, 2) = iPauliX();
    U({0,3,1,0}, 2) = iPauliY();
    U({0,3,2,0}, 2) = iPauliZ();

    U({0,2,3,0}, 1) = iPauliX();
    U({0,1,3,0}, 1) = iPauliY();
    U({0,0,3,0}, 1) = iPauliZ();

    U({0,0,2,0}, 2) = iPauliX();
    U({0,0,1,0}, 2) = iPauliY();
    U({0,0,0,0}, 2) = iPauliZ();

    std::cout << "should get unity: ";
    std::cout << getPlanarLoop(U, {0,0,0,0}, 1, 2, 3, 3) << std::endl;

    std::cout << "put iX, iY, iZ, iX,... on a 1 x 2 rectangle in dim. 0, 3\n";
    U = hotStart(5, 5, engine, .1); // "resetting" the configuration

    U({2,2,2,2}, 0) = iPauliX();

    U({3,2,2,2}, 3) = iPauliY();
    U({3,2,2,3}, 3) = iPauliZ();

    U({2,2,2,4}, 0) = iPauliX().dagger();

    U({2,2,2,3}, 3) = iPauliY().dagger();
    U({2,2,2,2}, 3) = iPauliZ().dagger();

    std::cout << "should get unity: ";
    std::cout << getPlanarLoop(U, {2,2,2,2}, 0, 3, 1, 2) << std::endl;
    return 0;
}
