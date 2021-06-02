#include <iostream>

#include "analysis.h"
#include "Gaugeconfig.h"
#include "SU2.h"

int main()
{
	std::cout << "\n////////////// testing getPlaquette: ///////////////\n";
	std::cout << "U is a 2x2^3 lattice. The plaquettes should just be 1:\n";
	const auto U = coldStart(2, 2);

	std::cout << "U_{00}({0,0,0,0}) = " << getPlaquette(U, {0,0,0,0}, 0, 0) << '\n';
	std::cout << "U_{23}({1,1,0,1}) = " << getPlaquette(U, {1,1,0,1}, 2, 3) << '\n';

	std::cout << "\n///////////// testing gaugeEnergy: ///////////////////\n";
	std::cout << "the trace of any plaquette will b 2. -> E = " << 192 << '\n';
	std::cout << "gaugeEnergy(U) = " << gaugeEnergy(U) << '\n';

	return 0;
}
