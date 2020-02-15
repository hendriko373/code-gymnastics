#include <vector>
#include <numeric>
#include "average.hpp"

using std::vector;      using std::accumulate;

double average(vector<double> vec)
{
    if (vec.empty())
        return 0.0;
    else
        return accumulate(vec.begin(), vec.end(), 0.0)/vec.size();
}
