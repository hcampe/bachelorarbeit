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
	std::cout << "U({0,0,0,0}, 0) = " << U({0,0,0,0}, 0) << '\n';

	std::cout << "\n////////// testing hot start /////////////\n";
	std::random_device rd {}; // to generate the seed for...
	std::mt19937 engine { rd() }; // Mersenne twister generator
	U = hotStart(5,3,engine,.01);
	std::cout << "U({0,0,0,0}, 0) = " << U({0,0,0,0}, 0) << '\n';

	return 0;
}