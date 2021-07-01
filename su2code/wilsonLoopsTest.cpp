#include <iostream>
#include <vector>

#include "analysis.h"
#include "Gaugeconfig.h"
#include "wilsonLoops.h"

int main()
{
    // for random number genration:
    std::random_device rd {}; // to generate the seed for...
    std::mt19937 engine { rd() }; // Mersenne twister generator

    Gaugeconfig U { hotStart(5, 5, engine, .1) };

    std::cout << "\n////////// first test by comparison to plaquette ////////////\n";
    std::cout << "as planar loop:" << getPlanarLoop(U, {0,0,0,0}, 0, 1, 1, 1) << std::endl;
    std::cout << "as plaquette:  " << getPlaquette(U, {0,0,0,0}, 0, 1) << std::endl;

    return 0;
}
