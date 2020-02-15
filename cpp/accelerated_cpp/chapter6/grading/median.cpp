#include <vector>
#include <stdexcept>
#include <algorithm>

using std::vector;
using std::sort;
using std::domain_error;

double median(vector<double> vec)
{
    typedef vector<double>::size_type VecSz;
    VecSz size = vec.size();

    if (size == 0)
        throw domain_error("median of an empty vector");

    sort(vec.begin(), vec.end());

    VecSz mid = size/2;
    return size%2 == 0 ? (vec[mid-1] + vec[mid])/2 : vec[mid];
}
