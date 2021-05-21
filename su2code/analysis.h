#include "Gaugeconfig.h"
#include "SU2.h"

#ifndef ANALYSIS_H
#define ANALYSIS_H

// computes the plaquette at a given point on a lattice
// U_{\mu \nu}(x) = U_\mu(x) * U_\nu(x + \mu) * U_\mu(x + \nu)^\dag * U_\nu(x)^\dag
SU2matrix getPlaquette(const Gaugeconfig& U,
	const std::vector<long int> x, const size_t mu, const size_t nu);


// computes the energy of a given gaugeconfig
// E = sum_x sum_{\mu < \nu} Re Tr (U_{\mu \nu}(x))
double gaugeEnergy(const Gaugeconfig&);


#endif