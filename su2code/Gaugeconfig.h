#include <vector>

#include "SU2.h"

#ifndef GAUGECONFIG_H
#define GAUGECONFIG_H

/* The following class is meant as container for the
parallel transports of a 4d spacetime lattice. It is assumed
that the lattice is cubic in space but it may have a 
different "length" in time. For any point in spacetime,
there are four parallel transports (one for any spacetime direction)
to be stored. */
class Gaugeconfig
{
	using parallelTransport = SU2matrix;
	// we need a 5 dimensional array to store
	// the data. the innermost index will denote
	// time, then follow the three space dimensions
	// and the outmost index indicates the direction
	// of the parallel transport.
	using container = 	std::vector<std::vector<
						std::vector<std::vector<
						std::vector<parallelTransport>>>>>;
	// to store the lattice lengths
	using size = typename container::size_type;

	container parallelTransports {};

public:
	// number of spacetime dimensions:
	static const size numSpacetimeDim { 4 };

	//////// implementation of basic methods /////////
	Gaugeconfig() = default; // default constructor

	// trivial constructor:
	Gaugeconfig(container input)
		{ parallelTransports = input; }

	// returns the time/space size
	size getTimeSize() const { return parallelTransports.size(); }
	size getSpaceSize() const { return parallelTransports[0].size(); }

	////////// signatures of more advanced methods /////////

	// constructor by specifying space and time size. The 
	// parallel transports will b initialised w/ their default
	// constructor.
	Gaugeconfig(const size timeSize, const size spaceSize);

	// for simple access using parantheses. x will denote the
	// spacetime lattice sight, mu the direction of the 
	// parallel transport.
	SU2matrix& operator()(const std::vector<std::size_t> x,
						  const std::size_t mu);

	const SU2matrix& operator()(const std::vector<std::size_t> x,
						  const std::size_t mu) const;
};

// two functions to initialise the configuration: for a cold start,
// all parallel transports will be initialised to 1, for a hot
// start, they will be assigned random values close to 1 following
// the generator for random su2matrices.
Gaugeconfig coldStart(const size_t, const size_t);

template<class URNG>
Gaugeconfig hotStart(const size_t, const size_t, URNG&, const double);

// this has to be implemented in a HEADER file:
#include "hotstartImplementation.h"

#endif