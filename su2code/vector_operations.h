#include <string>
#include <vector>

#ifndef vector_operations
#define vector_operations

// sums up all elements of a given std::vector
// returns: summ of all elements
double sum(std::vector<double> input);               // std::vector 2 b summed up


// calculates the average of the values of a std::vector
// returns: average of the elemts of the std::vector
double avg(std::vector<double> input);               // std::vector 2 b averaged


// calculates the variance of the distribution
// of the elements of a given std::vector
// returns: that variance
double variance(std::vector<double> input);          // input std::vector

// writes a single std::vector to a file,
// returns 0 if successful
int writeVector(const std::vector<double>& arr,
                const std::string& filename);


// writes a 2d std::vector to a file
// returns: 0 if successful
int write_2d(
        std::vector<std::vector<double>> arr,            // std::vector 2 b written 
        std::string filename,                       // name of file to write in
        char delimiter);// = ';')              // delimiter (default param did not work)


// computes a function on all elements of
// an array
std::vector<double> map(
        double (*fct)(double x),                    // function 2 b evaluated
        std::vector<double> x_arr);                 // vector with x values


// inspired by zipWith in the Haskell std library
// if cpp was vectorised, one could simply write
// output = function(input1, input2)
std::vector<double> zipWith(
        double (*function) (double, double),        // function
        std::vector<double> input1,
        std::vector<double> input2);


// works like numpy.arange
std::vector<double> arange(
        double start,
        double stop,
        double step);


// works like numpy.linspace
std::vector<double> linspace(
        double start,
        double stop,
        int slices);

// writes two vectors as colums to a file
int write_2_cols(
        std::vector<double> col_1,
        std::vector<double> col_2,
        std::string filename,
        char delimiter);

#endif
