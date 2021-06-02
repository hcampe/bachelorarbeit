// g++ -Wall -Wextra SU2.cpp su2tests.cpp -o su2tests
// ./su2tests
#include <cmath> // for M_PI
#include <complex>
#include <iomanip> // to manipulate the displayed precision
#include <iostream>
#include <random>
#include <vector>

#include "SU2.h"

// just for testing:
double determinant(const SU2matrix& U)
{
    return norm(U[0]) + norm(U[1]);
}


int main()
{
	// first test: initialise su2 matrix

	std::cout << "////// testing the constructor /////////\n";
	SU2matrix U {};
    SU2matrix zero {};
	SU2matrix one { unity() };
	SU2matrix iPauliX { {{0., 0.}, {0., 1.}} };
    std::cout << "zero = " << zero << '\n';
	std::cout << "one = " << one << '\n';
	std::cout << "iPauliX = "	<< iPauliX << '\n';

	std::cout << "\n////// testing transpose, complex & hermitian conjugate ////////\n";
	auto iPauliXt = iPauliX.transpose();

	std::cout << "iPauliXt = "	<< iPauliXt << '\n';

	auto iPauliXs = iPauliX.star();
	std::cout << "iPauliXs = "	<< iPauliXs << '\n';

	auto iPauliXd = iPauliX.dagger();
	std::cout << "iPauliXd = "	<< iPauliXd << '\n';

	std::cout << "\n////// testing matrix multiplication /////////\n";
	std::cout << "iPauliX * iPauliY = " << iPauliX * iPauliY() << '\n';
	std::cout << "should be: -PauliZ, PauliZ = " << iPauliZ() << '\n';

	std::cout << "\n//////// intermezzo: finding the best version of pi /////////\n";
	std::cout << std::setprecision(16);
	std::cout << "exact value:		3.14159265358979323846... (Wikipedia)\n";
	std::cout << "M_PI from cmath:	" << M_PI << '\n';
	std::cout << "4*arctan(1):		" << 4*atan(1.) << '\n';
	std::cout << "arccos(-1):		" << acos(-1.) << '\n';
	std::cout << std::setprecision(6);

	std::cout << "\n////////// testing the random SU(2) matrix generator ///////\n";
	std::random_device rd {}; // to generate the seed for...
	std::mt19937 engine { rd() }; // Mersenne twister generator
	std::uniform_real_distribution<double> dist {0., 1.};
	std::cout << "delta = 0.0:		" << randomSU2(engine, 0.0) << '\n';
	std::cout << "delta = 0.001:		" << randomSU2(engine, 0.001) << '\n';
	std::cout << "delta = 0.01:		" << randomSU2(engine, .01) << '\n';
    U = randomSU2(engine, 0.1);
	std::cout << "delta = 0.1:		" << U << '\n';

    std::cout << "\n///////// testing the renormalisation ////////////\n";
    std::cout << "0: U = " << U;
    std::cout << ", sqrt(det(U)) = " << sqrt(determinant(U)) << std::endl;
    U.renormalise();
    std::cout << "1: U = " << U;
    std::cout << ", sqrt(det(U)) = " << sqrt(determinant(U)) << std::endl;
    U.renormalise();
    std::cout << "2: U = " << U;
    std::cout << ", sqrt(det(U)) = " << sqrt(determinant(U)) << std::endl;
    U.renormalise();
    std::cout << "3: U = " << U;
    std::cout << ", sqrt(det(U)) = " << sqrt(determinant(U)) << std::endl;
    U.renormalise();
    std::cout << "4: U = " << U;
    std::cout << ", sqrt(det(U)) = " << sqrt(determinant(U)) << std::endl;


	std::cout << "\n//////////// testing assignment with the = operator ///////////\n";
	std::cout << "newly initialised: " << U << '\n';
	U = iPauliY();
	std::cout << "setting U = iPauliY: " << U << '\n';

	std::cout << "\n////////////// testing addition: ///////////////\n";
	std::cout << "one + iPauliX = " << one + iPauliX << '\n';
	std::cout << "one - iPauliX = " << one - iPauliX << '\n';
	return 0;
}
