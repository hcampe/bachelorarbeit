#include <vector>

#include "Gaugeconfig.h"
#include "SU2.h"

/* for the computation of the change of the actione
corr. to the change of a certain parallel transport,
we need the staple thereof. It contains all other
parallel transports that will be affected by the
change. A staple corr. to a spacetime point x and
the direction mu is defined as follows:
K_mu(x) = \sum_{\nu \neq \mu}
(U_nu(x + a\mu)U^\dag_mu(x+a\nu)U^\dag_nu(x)
+ U^\dag_\nu(x+a\mu-a\nu)U^\dag_\mu(x-a\nu) U_\nu(x-a\nu))
*/
SU2matrix getStaple(const Gaugeconfig&,
	const std::vector<long int>, const std::size_t);

/* the change of the action then becomes
\Delta S = -\beta/2 Re Tr(\Delta U_mu(x) * K_mu(x))
(NO sum over mu)
*/
double deltaS(const Gaugeconfig&,
	const std::vector<long int>, const std::size_t,
	const SU2matrix&, const double);
