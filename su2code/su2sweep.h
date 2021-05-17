#include "deltaS.h"
#include "gaugeconfig.h"
#include "SU2.h"

/* performs a whole sweep through a given lattice and
updates it following the Metropolis algorithm: At each
sight, and for each parallel transport, a new version
is generated randomly (and close to the original,
controlled by delta). The lattice is updated if the 
action is lowered by doing so or with the
probability exp(-\Delta S) if \Delta S > 0.
*/
template<class URNG> Gaugeconfig<SU2matrix>
sweep(const Gaugeconfig<SU2matrix>&, const double beta,
	const std::size_t iterationsPerSight, URNG&);