#ifndef MEDIAN_HPP
#define MEDIAN_HPP

#include <vector>
#include <stdexcept>
#include <algorithm>

template <class T, class RandomIt>
T median(RandomIt b, RandomIt e)
{
    std::vector<T> v(b, e);

    typedef typename std::vector<T>::size_type VecSz;
    VecSz size = v.size();

    if (size == 0)
        throw std::domain_error("median of an empty vector");

    std::sort(v.begin(), v.end());

    VecSz mid = size/2;
    return size%2 == 0 ? (v[mid-1] + v[mid])/2 : v[mid];
}

#endif
