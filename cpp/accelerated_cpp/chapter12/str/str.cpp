#include <cstring>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cctype>
#include "str.hpp"
#include "vec.hpp"

using namespace std;

Str::Str(const char* p)
{
    const char* temp = p;
    while (temp != p + strlen(p)) {
        data_.pushBack(*temp);
        ++temp;
    }
}

template <class In> Str::Str(In b, In e)
{
    while(b != e) {
        data_.pushBack(*b);
        ++b;
    }
}

char& Str::operator[](SizeType i)
{
    return data_[i];
}

const char& Str::operator[](SizeType i) const
{
    return data_[i];
}

Str::SizeType Str::getSize() const
{
    return data_.getSize();
}

Str& Str::operator+=(const Str& rhs)
{
    Vec<char>::ConstIterator temp = rhs.data_.begin();
    while (temp != rhs.data_.end()) {
        (*this).data_.pushBack(*temp);
        ++temp;
    }
    return *this;
}

ostream& operator<<(ostream& os, const Str& s)
{
    for(Str::SizeType i = 0; i != s.getSize(); ++i)
        os << s[i];
    return os;
}

istream& operator>>(istream& is, Str& s)
{
    s.data_.clear();
    char c;
    while(is.get(c) && isspace(c));

    if (is) {
        do s.data_.pushBack(c);
        while(is.get(c) && !isspace(c));
        if (is)
            is.unget();
    }
    return is;
}

Str operator+(const Str& lhs, const Str& rhs)
{
    Str ret = lhs;
    ret += rhs;
    return ret;
}
