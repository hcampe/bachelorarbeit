#include "vector_operations.h"

#include <iomanip> // to manipulate the displayed precision
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

double sum(std::vector<double> input)
{
    double sum = 0;

    for (std::size_t i = 0; i < input.size(); i++)
    {
        sum += input[i];
    }

    return sum;
}


double avg(std::vector<double> input)
{
    return sum(input) / ((double)input.size());
}


double variance(std::vector<double> input)
{
    return avg(map([] (double x) {return x*x;}, input)) - avg(input)*avg(input);
}


int writeVector(const std::vector<double>& arr,
                const std::string& filename)
{
    std::ofstream out(filename);
    out << std::setprecision(15); // to achieve max precision for the doubles

    for (std::size_t i {0}; i < arr.size(); i++)
    {
        out << arr[i] << '\n';
    }

    return 0;
}



int write_2d(
        std::vector<std::vector<double>> arr,
        std::string filename,
        char delimiter)//delimiter = ';') // default param did not work
{
    std::ofstream out(filename);

    for (std::size_t i = 0; i < arr.size(); i++)
    {
        out << arr[i][0]; // no delimiter before the first element
        for (std::size_t j = 1; j < arr[i].size(); j++)
        {
            out << delimiter << arr[i][j];
        }
        out << '\n'; // newline at the end of any row
    }

    return 0;
}


int write_2_cols(
        std::vector<double> col_1,
        std::vector<double> col_2,
        std::string filename,
        char delimiter)
{
    if (col_1.size() != col_2.size())
    {
        std::cout << "Error. Columns have different sizes\n";
        return -1;
    }

    std::ofstream out(filename);

    for (std::size_t i = 0; i < col_1.size(); i++)
    {
        out << col_1[i] << delimiter << col_2[i] << '\n';
    }

    return 0;
}


std::vector<double> map(
        double (*fct)(double),
        std::vector<double> input)
{
    std::vector<double> output (input.size(), 0.);
    for (std::size_t i {0}; i < input.size(); i++)
    {
        output[i] = fct(input[i]);
    }
    
    return output;
}


std::vector<double> zipWith(
        double (*function) (double, double),
        std::vector<double> input1,
        std::vector<double> input2)
{
    if (input1.size() != input2.size())
    {
        std::cout << "Error! Input vectors must b of same length!\n";
        return std::vector<double> {};
    }

    std::vector<double> output (input1.size(), 0.);

    for (std::size_t i {0}; i < input1.size(); i++)
    {
        output[i] = function(input1[i], input2[i]);
    }

    return output;
}


std::vector<double> arange(
        double start,
        double stop,
        double step)
{
    std::vector<double> out;
    for (double x = start; x < stop; x += step)
    {
        out.push_back(x);
    }

    return out;
}


std::vector<double> linspace(
        double start,
        double stop,
        int slices)
{
    std::vector<double> out;
    double step = (stop - start) / slices;
    for (double x = start; x < stop; x += step)
    {
        out.push_back(x);
    }

    return out;
}


