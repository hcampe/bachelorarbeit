#include <iostream>

#include "deltaS.h"
#include "Gaugeconfig.h"
#include "SU2.h"

int main()
{
	std::cout << "\n////////////// testing getStaple ///////////////\n";
	auto U = Gaugeconfig(3,3);
	std::vector<std::size_t> x {1,1,1,1};
	std::size_t mu { 0 };
	std::cout << "the Gaugeconfig U is filled with unity matrices -> expect 6 * 1 as staple:\n";
	std::cout << "getStaple(U,x,mu=" << mu << ") = " << getStaple(U, x, mu) << '\n';  


	return 0;
}