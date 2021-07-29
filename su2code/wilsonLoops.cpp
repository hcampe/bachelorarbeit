#include "Gaugeconfig.h"
#include "SU2.h"

SU2matrix getStraightLine(const Gaugeconfig& U, const std::vector<long int> x,
    const size_t mu, const size_t n)
{
    SU2matrix output { unity() };
    std::vector<long int> y { x };    

    for (size_t i {0}; i < n; i++)
    {
        output *= U(y, mu);
        y[mu]++;
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

std::vector<double> getLoopTraces(const Gaugeconfig& U,
                                  const size_t mu, const size_t nu,
                                  const std::vector<size_t> M,
                                  const std::vector<size_t> N)
{
    std::vector<double> traces(M.size(), 0.);

    for (size_t i {0}; i < traces.size(); i++)
    {
        traces[i] = trace(getPlanarLoop(U, {0,0,0,0}, mu, nu, M[i], N[i]));
    }

    return traces;
}

SU2matrix getSqrt2Loop(const Gaugeconfig& U, const long int t)
{
    SU2matrix result { unity() };
    
    result *= getStraightLine(U, {0,0,0,0}, 0, t);
    result *= U({t,0,0,0}, 1) * U({t,1,0,0}, 2);
    result *= getStraightLine(U, {0,1,1,0}, 0, t).dagger();
    result *= U({0,1,0,0}, 2).dagger() * U({0,0,0,0}, 1).dagger();

    return result;
}

SU2matrix getSqrt3Loop(const Gaugeconfig& U, const long int t)
{
    SU2matrix result { unity() };
    
    result *= getStraightLine(U, {0,0,0,0}, 0, t);
    result *= U({t,0,0,0}, 1) * U({t,1,0,0}, 2) * U({t,1,1,0}, 3);
    result *= getStraightLine(U, {0,1,1,1}, 0, t).dagger();
    result *= U({0,1,1,0}, 3).dagger() * U({0,1,0,0}, 2).dagger() *U({0,0,0,0}, 1).dagger();

    return result;
}

SU2matrix getSqrt6Loop(const Gaugeconfig& U, const long int t)
{
    SU2matrix result { unity() };
    
    result *= getStraightLine(U, {0,0,0,0}, 0, t);
    result *= getStraightLine(U, {t,0,0,0}, 1, 2);
    result *= U({t,2,0,0}, 2) * U({t,2,1,0}, 3);
    result *= getStraightLine(U, {0,2,1,1}, 0, t).dagger();
    result *= U({0,2,1,0}, 3).dagger();
    result *= U({0,2,0,0}, 2).dagger();
    result *= getStraightLine(U, {0,0,0,0}, 1, 2).dagger();

    return result;
}

SU2matrix getSqrt13Loop(const Gaugeconfig& U, const long int t)
{
    SU2matrix result { unity() };
    
    result *= getStraightLine(U, {0,0,0,0}, 0, t);
    result *= getStraightLine(U, {t,0,0,0}, 1, 2);
    result *= getStraightLine(U, {t,2,0,0}, 2, 3);
    result *= getStraightLine(U, {0,2,3,0}, 0, t).dagger();
    result *= getStraightLine(U, {0,2,0,0}, 2, 3).dagger();
    result *= getStraightLine(U, {0,0,0,0}, 1, 2).dagger();

    return result;
}