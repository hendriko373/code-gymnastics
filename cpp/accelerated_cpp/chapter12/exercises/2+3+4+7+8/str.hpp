#ifndef  str_INC
#define  str_INC

#include <iostream>
#include "vec.hpp"

class Str {
    friend std::istream& operator>>(std::istream&, Str&);
    friend std::istream& getLine(std::istream&, Str&);
public:
    typedef Vec<char>::SizeType SizeType;
    typedef Vec<char>::Iterator Iterator;
    typedef Vec<char>::ConstIterator ConstIterator;
        // Note that Vec<T>::(Const)Iterator is (const) T*, which is already
        // a random access iterator.

    Str() : nullChar_(0){}
    Str(SizeType n, char c) : data_(n, c), nullChar_(0){};
    Str(const char*); // this constructor also define automatic conversion
    template <class In> Str(In, In);
    // note that we do not define a copy constructor, assignment operator
    // or destructor, because the defaults do exactly what we want.
    // We do however add to the destructor to destroy a dynamically allocated
    // nullChar_, a null terminated array of char.
    ~Str();
    
    SizeType getSize() const;
    char& operator[](SizeType);
    const char& operator[](SizeType) const;
    Str& operator+=(const Str&);

    Iterator begin();
    ConstIterator begin() const;
    Iterator end();
    ConstIterator end() const;

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
