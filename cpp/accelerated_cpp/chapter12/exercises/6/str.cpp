#include <cstring>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cctype>
#include <cstring>
#include "str.hpp"
#include "vec.hpp"

using namespace std;

Str::Str(const char* p) : nullChar_(0)
{
    const char* temp = p;
    while (temp != p + strlen(p)) {
        data_.pushBack(*temp);
        ++temp;
    }
}

template <class In> Str::Str(In b, In e) : nullChar_(0) 
{
    while(b != e) {
        data_.pushBack(*b);
        ++b;
    }
}

Str::~Str()
{
    delete[] nullChar_;
}

Str::operator bool() const // see comment in header str.hpp
{
    if (getSize() == 0)
        return false;
    else return true;
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

const char* Str::c_str()
{
    delete[] nullChar_;
    nullChar_ = new char[getSize()+1];
    Str::SizeType i = 0;
    while ( i != getSize()) {
        nullChar_[i] = (*this)[i];
        ++i;
    }
    nullChar_[i] = '\0';
    return nullChar_;
}

Str::SizeType Str::copy(char* p, SizeType n) const
{
    SizeType i = 0;
    while (i != getSize() && i != n) {
        *p = (*this)[i];
        ++p;
        ++i;
    }
    return i;
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

bool operator==(const Str& lhs, const Str& rhs)
{
    Str lhsTemp = lhs;
    Str rhsTemp = rhs;
    if (strcmp(lhsTemp.c_str(), rhsTemp.c_str()) == 0)
        return true;
    else return false;
}

bool operator!=(const Str& lhs, const Str& rhs)
{
    return !(lhs == rhs);
}

bool operator<(const Str& lhs, const Str& rhs)
{
    Str lhsTemp = lhs;
    Str rhsTemp = rhs;
    if (strcmp(lhsTemp.c_str(), rhsTemp.c_str()) < 0)
        return true;
    else return false;
}

bool operator<=(const Str& lhs, const Str& rhs)
{
    return (lhs < rhs || lhs == rhs);
}

bool operator>(const Str& lhs, const Str& rhs)
{
    return !(lhs <= rhs);
}

bool operator>=(const Str& lhs, const Str& rhs)
{
    return !(lhs < rhs);
}
