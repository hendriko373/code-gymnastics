#ifndef  str_INC
#define  str_INC

#include <iostream>
#include "vec.hpp"

class Str {
    friend std::istream& operator>>(std::istream&, Str&);
public:
    typedef Vec<char>::SizeType SizeType;

    Str() : nullChar_(0){}
    Str(SizeType n, char c) : data_(n, c), nullChar_(0){};
    Str(const char*); // this constructor also define automatic conversion
    template <class In> Str(In, In);
    // note that we do not define a copy constructor, assignment operator
    // or destructor, because the defaults do exactly what we want.
    // We do however add to the destructor to destroy a dynamically allocated
    // nullChar_, a null terminated array of char.
    ~Str();

    explicit operator bool() const;  // use Str object as condition; introducing
    // this conversion without the explicit specifier leads to ambiguities
    // for the operator+ becomes overloaded.
    // The problem is that char* + Str may be intepreted also as a char* + int,
    // because their is an implicit conversion Str -> bool -> int.
    // This is resolved by specifying the explicit keyword, because it allows
    // for implicit conversion only in certain contexts such as within a
    // conditional statement. (see contextually convertible to bool)
    
    SizeType getSize() const;
    char& operator[](SizeType);
    const char& operator[](SizeType) const;
    Str& operator+=(const Str&);

    const char* c_str();
    SizeType copy(char*, SizeType) const;

private:
    Vec<char> data_;
    char* nullChar_;
};

std::ostream& operator<<(std::ostream&, const Str&);
Str operator+(const Str&, const Str&);

bool operator==(const Str&, const Str&);
bool operator!=(const Str&, const Str&);
bool operator<(const Str&, const Str&);
bool operator<=(const Str&, const Str&);
bool operator>(const Str&, const Str&);
bool operator>=(const Str&, const Str&);

#endif   /* ----- #ifndef str_INC  ----- */
