#include <iostream>

#include "vector_operations.h"

int main()
{
	std::cout << "writing a range frm 0 to 9 to 'testFile.txt'" << std::endl;
	std::vector<double> test(10, 0.);
	for (std::size_t i {0}; i < test.size(); i++)
	{
		test[i] = i;
	}

	std::cout << "zero if writing successful:";
	std::cout << writeVector(test, "testFile.txt") << std::endl;
	return 0;
}