#include <iostream>

#include "getStaple.h"
#include "Gaugeconfig.h"
#include "SU2.h"

int main()
{
	std::cout << "\n////////////// testing getStaple ///////////////\n";
	auto U = coldStart(3,3);
	std::vector<long int> x {0,0,0,0};
	std::size_t mu { 0 };
	std::cout << "the Gaugeconfig U is filled with unity matrices -> expect 6 * 1 as staple:\n";
	std::cout << "getStaple(U,x,mu=" << mu << ") = " << getStaple(U, x, mu) << '\n';  


	return 0;
}
