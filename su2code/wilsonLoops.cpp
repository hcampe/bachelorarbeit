#include "Gaugeconfig.h"
#include "SU2.h"

SU2matrix getStraightLine(const Gaugeconfig& U, const std::vector<long int> x,
    const size_t mu, const size_t n)
{
    SU2matrix output { unity() };
    std::vector<long int> y { x };    

    for (size_t i {0}; i < n; i++)
    {
        y[mu]++;
        output *= U(y, mu);
    }

    return output;
}

SU2matrix getPlanarLoop(const Gaugeconfig& U, const std::vector<long int> x,
    const size_t mu, const size_t nu, const size_t m, const size_t n)
{
    SU2matrix V { unity() };
    std::vector<long int> y { x };

    V *= getStraightLine(U, y, mu, m);
    y[mu] += m;
    V *= getStraightLine(U, y, nu, n);
    y[mu] -= m;
    y[nu] += n;
    V *= getStraightLine(U, y, mu, m).dagger();
    y[nu] -= n;
    V *= getStraightLine(U, y, nu, n).dagger();

    return V;
}