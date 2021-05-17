#include <complex>
#include <random>
#include <vector>

#ifndef SU2_H
#define SU2_H


// Any matrix U \in SU(2) must fulfill U^\dag * U = U * U^\dag = 1.
// One can make use of this to show that it can be written as 
// U = ((a, b), (-b*, a*)). The following class makes use of that:
// only the upper row of any such matrix will be saved and accessible.
class SU2matrix
{
    // They types for both complex numbers and the container used may
    // be changed later on if necessary.
    using complex = std::complex<double>;
    using container = std::vector<complex>;

    container upperRow {{1., 0.}, {0., 0.}}; // default: unitity

public:
    ///////////// implementations of basic methods ////////////

    SU2matrix() = default; // default constructor
    // constructor by specifying the upper row:
    SU2matrix(container input) { upperRow = input; };
    container getUpperRow() { return upperRow; }
    void setUpperRow(container input) { upperRow = input; }

    //////////// signatures of more advanced methods /////////

    // transposed matrix
    SU2matrix transpose() ;

    // complex conjugate
    SU2matrix star();

    // hermitian conjugate
    SU2matrix dagger();

    // renormalise the matrix: due to the limited precision of the 
    // complex type, every now and then, the matrix should be renormalised
    // s.t. det U = 1. The normalisation factor is given by the square root
    // of the sum of the squares of the moduli of the upper row entries.
    SU2matrix renormalise();


    // overloading [] for easier access to the values using array indexing.
    const complex& operator[](const std::size_t) const;

    // for easier printing: now one can simply write
    // std::cout << U, where U is an SU2matrix
    friend std::ostream& operator<<(std::ostream&, const SU2matrix&);
};


// compute the trace of any SU(2) matrix. This is not a method since 
// trace(U) is closer to the mathematical formulation tr(U) than U.trace()
std::complex<double> trace(SU2matrix);

// overloading the * operator for matrix calculation:
SU2matrix operator*(const SU2matrix&, const SU2matrix&);


// definitions of the three pauli matrices and unity
SU2matrix unity();

SU2matrix iPauliX();

SU2matrix iPauliY();

SU2matrix iPauliZ();


// a generator for random SU(2) matrices close to unity. It makes use of 
// the fact that SU(2) is isomorphic (in fact: homeomorphic) to S_3 via
//         phi: S_3    ->   SU(2),
// (x0, x1, x2, x3) \mapsto x0 * unity + i \sum_j x_j sigma_j
// Thus, x \in S_3 is generated randomly, then the above map is used to 
// produce a SU(2) matrix. The generation of x \in S_3 is done in spherical
// coordinates:
// x0 = cos(a) cos(b) sin(c)
// x1 = sin(a) cos(b) sin(c)
// x2 = sin(a) sin(b) sin(c)
// x3 = sin(a) cos(c)
// a will be drawn from U(0, delta*2pi) w/ delta > 0 but close to 0,
// b will be drawn from U(0, 2pi),
// cos(c) will be drawn from U(-1,1),
// where U(.,.) is the uniform distribution.
// -> for this case, the upper row of the random matrix will contain entries
// cos(a) + i sin(a) cos(c) and sin(a) sin(b) sin(c) + i sin(a) cos(b) sin(c)
// since it should work with any Uniform Random Number Generator, it is
// implemented as a template:
template<class URNG> SU2matrix randomSU2(URNG& engine, const double delta);

#endif