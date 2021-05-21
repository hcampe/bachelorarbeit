#include <iostream>

#include "analysis.h"
#include "Gaugeconfig.h"
#include "SU2.h"

int main()
{
	std::cout << "\n////////////// testing getPlaquette: ///////////////\n";
	std::cout << "U is a lattice w/ just one sight. The plaquettes should just be 1:\n";
	const Gaugeconfig U(1, 1);
	std::cout << "U_{00}({0,0,0,0}) = " << getPlaquette(U, {0,0,0,0}, 0, 0) << '\n';

	std::cout << "\n///////////// testing gaugeEnergy: ///////////////////\n";
	std::cout << "the trace of any plaquette will b 2. -> E = " << (1 + 2 + 3) * 2 << '\n';
	std::cout << "gaugeEnergy(U) = " << gaugeEnergy(U) << '\n';

	return 0;
}