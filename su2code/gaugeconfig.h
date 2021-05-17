#include <vector>

#include "SU2.h"

#ifndef GAUGECONFIG_H
#define GAUGECONFIG_H

/* The following class is meant as container for the
parallel transports of a 4d spacetime lattice. It is assumed
that the lattice is cubic in space but it may have a 
different "length" in time. For any point in spacetime,
there are four parallel transports (in any spacetime direction)
to be stored. */
template<class parallelTransport> class Gaugeconfig
{
	// we need a 5 dimensional array to store
	// the data.
	using container = 	std::vector<std::vector<
						std::vector<std::vector<
						std::vector<parallelTransport>>>>>;
	// to store the dimensions of the lattice.
	using size = typename container::size_type;

	container parallelTransports {};

public:
	//////// implementation of basic methods /////////
	Gaugeconfig() = default; // default constructor

	// trivial constructor:
	Gaugeconfig(container parallelTransports)
		{ parallelTransports = parallelTransports; }

	// returns the time/space size
	size getTimeSize() { return parallelTransports.size(); }
	size getSpaceSize() { return parallelTransports[0].size(); }

	////////// signatures of more advanced methods /////////

	// for simple access using parantheses. x will denote the
	// spacetime lattice sight, mu the direction of the 
	// parallel transport.
	parallelTransport& operator()(std::vector<std::vector<
						          std::vector<std::vector<size>>>> x,
						          size mu);
};

// two functions to initialise the configuration: for a cold start,
// all parallel transports will be initialised to 1, for a hot
// start, they will be assigned random values close to 1 following
// the generator for random su2matrices.
Gaugeconfig<SU2matrix> coldStart();

Gaugeconfig<SU2matrix> hotStart(const double);

#endif