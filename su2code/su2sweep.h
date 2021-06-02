#include "Gaugeconfig.h"
#include "getStaple.h"
#include "SU2.h"

#ifndef SU2SWEEP_H
#define SU2SWEEP_H

/* performs a whole sweep through a given lattice and
updates it following the Metropolis algorithm: At each
sight, and for each parallel transport, a new version
is generated randomly (close to the original,
controlled by delta). The lattice is updated if the 
action is lowered by doing so or with the
probability exp(-\Delta S) if \Delta S > 0.
*/
template<class URNG> void 
sweep(const Gaugeconfig&, const double beta, const double delta,
	const std::size_t iterationsPerSight, URNG&);

// the implementation is done in a HEADER file:
#include "su2sweepImplementation.h"

#endif
