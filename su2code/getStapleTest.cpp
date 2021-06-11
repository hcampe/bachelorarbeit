#include <iostream>

#include "getStaple.h"
#include "Gaugeconfig.h"
#include "SU2.h"


int main()
{
    std::cout << "\n////////////// testing getStaple ///////////////\n";
    auto U = coldStart(3,3);
    std::vector<long int> x {0,0,0,0};
    std::size_t mu { 0 };
    std::cout << U(x, mu) << std::endl;
    std::cout << "the Gaugeconfig U is filled with unity matrices -> expect 6 * 1 as staple:\n";
    std::cout << "getStaple(U,x,mu=" << mu << ") = " << getStaple(U, x, mu) << '\n';  
    std::cout << "fill V w/ 0 matrices exept one -> expect 0 as staple:\n";
    Gaugeconfig V(3,3);
    std::cout << "V({0,0,0,0}, 0) = " << V({0,0,0,0}, 0) << std::endl;
    V({1,1,1,1}, 0) = unity();
    std::cout << "getStaple(V,x,mu) = " << getStaple(V,x,mu) << std::endl;


//    std::cout << "fill U w/ random matrices...\n";
//    std::random_device rd {}; // to generate the seed for...
//    std::mt19937 engine { rd() }; // Mersenne twister generator
//    U = hotStart(3, 3, engine, .1);
//    std::cout << "[[[[[";
//    for (x[0] = 0; x[0] < U.getTimeSize(); x[0]++)
//    {
//        for (x[1] = 0; x[1] < U.getSpaceSize(); x[1]++)
//        {
//            for (x[2] = 0; x[2] < U.getSpaceSize(); x[2]++)
//            {
//                for (x[3] = 0; x[3] < U.getSpaceSize(); x[3]++)
//                {
//                    for (size_t mu {0}; mu < 4; mu++)
//                    {
//                        std::cout << U(x, mu);
//                        std::cout << ',';
//                    }
//                    std::cout << "],[";
//                }
//                std::cout << "],[";
//            }
//            std::cout << "],[";
//        }
//        std::cout << "],[";
//    }
//    std::cout << "],[";
//
//    std::cout << std::endl;



    return 0;
}
