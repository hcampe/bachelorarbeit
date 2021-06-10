#include <iostream>
#include <vector>

#include "Gaugeconfig.h"
#include "SU2.h"

int main()
{
    std::cout << "\n/////////// testing default constructor /////////////\n";
    Gaugeconfig U {};
    std::cout << "first U initialised!\n";

    std::cout << "\n////////// testing trivial constructor and access with () ///////////\n";
    U = Gaugeconfig(5, 2);
    std::cout << "timeSize, spaceSize: " << U.getTimeSize() << ", " << U.getSpaceSize() << '\n';
    std::cout << "accessing first element: U({0,0,0,0}, 0) = " << U({0,0,0,0}, 0) << '\n';

    std::cout << "setting that element to iPauliX: ";    
    U({0,0,0,0}, 0) = iPauliX();

    std::cout << "\n//////////// testing cold start //////////\n";
    U = coldStart(5,2);
    std::cout << "accessing first element: U({0,0,0,0}, 0) = " << U({0,0,0,0}, 0) << '\n';
    std::cout << "U({0,0,0,0}, 0) = " << U({0,0,0,0}, 0) << '\n';
    std::cout << "U({4,1,1,1}, 3) = " << U({4,1,1,1}, 3) << std::endl;

    std::cout << "\n////////// testing hot start /////////////\n";
    std::random_device rd {}; // to generate the seed for...
    std::mt19937 engine { rd() }; // Mersenne twister generator
    U = hotStart(5,3,engine,.01);
    std::cout << "U({0,0,0,0}, 0) = " << U({0,0,0,0}, 0) << '\n';

    std::cout << "\n///////// testing periodic boundary conditions: //////////\n";
    std::cout << "U({0,0,0,0}, 0) = " << U({0,0,0,0}, 0) << '\n';
    std::cout << "U({5,3,3,3}, 0) = " << U({5,3,3,3}, 0) << '\n';
    std::cout << "U({-1,-1,-1,-1}, 0) = " << U({-1,-1,-1,-1}, 0) << '\n';
    std::cout << "U({4,2,2,2}, 0) = " << U({4,2,2,2}, 0) << '\n';
    std::cout << "U({1,1,1,1}, 1) = " << U({1,1,1,1}, 1) << std::endl;
    std::cout << "U({6,4,4,4}, 1) = " << U({6,4,4,4}, 1) << std::endl;

    return 0;
}
