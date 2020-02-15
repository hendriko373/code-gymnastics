#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <utility>

template <class InputIt1, class InputIt2>
bool equal(InputIt1 b, InputIt1 e, InputIt2 b2)
{
    while (b != e) {
        if (*b == *b2) {
            ++b;
            ++b2;
        }
        else return false;
    }
    return true;
}

template <class InputIt, class T>
InputIt find(InputIt b, InputIt e, const T& t)
{
    while (b != e) {
        if (*b == t)
            return b;
        ++b;
    }
    return e;
}

template <class InputIt, class UnitaryPred> 
InputIt find_if(InputIt b, InputIt e, UnitaryPred pred)
{
    while (b != e) {
        if (pred(*b))
            return b;
        ++b;
    }
    return e;
}

// Function arguments must be forward iterators since there are multiple passes
template <class ForwardIt1, class ForwardIt2>
ForwardIt1 search(ForwardIt1 b, ForwardIt1 e, ForwardIt2 b2, ForwardIt2 e2)
{
    while (b != e) {
        ForwardIt1 it = b;
        ForwardIt2 it2 = b2;
        while (*it == *it2) {
            ++it;
            ++it2;
            if (it2 == e2)
                return b;
            if (it == e)
                return e;
        }
        ++b;
    }
    return e;
}

template <class InputIt, class OutputIt>
OutputIt copy(InputIt b, InputIt e, OutputIt d)
{
    while (b != e) {
        *d = *b;
        ++d;
        ++b;
    }
    return d;
}

template <class InputIt, class OutputIt, class T>
OutputIt remove_copy(InputIt b, InputIt e, OutputIt d, const T& t)
{
    while (b != e) {
        if (*b != t) {
            *d = *b;
            ++d;
        }
        ++b;
    }
    return d;
}

template <class InputIt, class OutputIt, class UnitaryPred>
OutputIt remove_copy_if(InputIt b, InputIt e, OutputIt d, UnitaryPred pred)
{
    while (b != e) {
        if (!pred(*b)) {
            *d = *b;
            ++d;
        }
        ++b;
    }
    return d;
}

template <class ForwardIt, class T>
ForwardIt remove(ForwardIt b, ForwardIt e, const T& t)
{
    ForwardIt it = b;
    while (b != e) {
        if (*b != t) {
            *it = *b;
            ++it;
        }
        ++b;
    }
    return it;
}

template <class InputIt, class OutputIt, class UnitaryOp>
OutputIt transform(InputIt b, InputIt e, OutputIt d, UnitaryOp f)
{
    while (b != e) {
        *d = f(*e);
        ++d;
        ++b;
    }
    return d;
} 

template <class ForwardIt, class UnitaryPred>
ForwardIt partition (ForwardIt b, ForwardIt e, UnitaryPred p)
{
    ForwardIt it = b;
    while (b != e) {
        if (p(*b)) {
            std::swap(*it, *b);
            ++it;
        }
        ++b;
    }
    return it;
}

template <class InputIt, class T>
T accumulate(InputIt b, InputIt e, T t)
{
    while (b != e) {
        t += *b;
        ++b;
    }
    return t;
}

#endif
