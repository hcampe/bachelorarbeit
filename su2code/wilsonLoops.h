#ifndef WILSON_LOOPS_H
#define WILSON_LOOPS_H

#include "Gaugeconfig.h"
#include "SU2.h"

/*
returns the product of n parallel transports along a straight
line in direction mu and length m, starting frm x.
L_\mu(x, m) = \product_{i = 0}^{m-1} U_\mu(x + i*\mu)
*/
SU2matrix getStraightLine(const Gaugeconfig& U, const std::vector<long int> x,
    const size_t mu, const size_t m);


/*
The Wilson loop implemented here is to be understood as a
rectangle in spacetime. The following function will return
the real part of the trace of the parallel transports of
such a loop along the two axes specified by mu and nu.
V_{\mu \nu}(x, m, n) = L_\mu(x, m) * L_\nu(x + m\mu, n)
                      *L_\mu^\dag(x + n\nu, m) * L_\nu^\dag(x, n)
*/
SU2matrix getPlanarLoop(const Gaugeconfig& U, const std::vector<long int> x,
    const size_t mu, const size_t nu, const size_t a, const size_t b);

#endif