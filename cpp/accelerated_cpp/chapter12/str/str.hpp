#ifndef  str_INC
#define  str_INC

#include <iostream>
#include "vec.hpp"

class Str {
    friend std::istream& operator>>(std::istream&, Str&);
public:
    typedef Vec<char>::SizeType SizeType;

    Str(){}
    Str(SizeType n, char c) : data_(n, c){};
    Str(const char*); // this constructor also define automatic conversion
    template <class In> Str(In, In);
    // note that we do not define a copy constructor, assignment operator
    // or destructor, because the defaults do exactly what we want.
    
    SizeType getSize() const;
    char& operator[](SizeType);
    const char& operator[](SizeType) const;
    Str& operator+=(const Str&);

private:
    Vec<char> data_;
};

std::ostream& operator<<(std::ostream&, const Str&);
Str operator+(const Str&, const Str&);

#endif   /* ----- #ifndef str_INC  ----- */
