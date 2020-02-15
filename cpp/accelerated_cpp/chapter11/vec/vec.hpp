#ifndef  VEC_HPP
#define  VEC_HPP

#include <cstddef>
#include <memory>
#include <algorithm>

template <class T>
class Vec {
public: // interface -- what users of our class see and can use
    // types:    
    typedef T ValueType;
    typedef T& Reference;
    typedef const T& ConstReference;
    typedef T* Iterator;
    typedef const T* ConstIterator;
    typedef std::ptrdiff_t DifferenceType;
    typedef std::size_t SizeType;

    // constructors:
    Vec();
    explicit Vec(SizeType, const T& = T());
    Vec(const Vec&);

    ~Vec();

    // functions:
    Vec& operator=(const Vec&);
    SizeType getSize() const;
    T& operator[](SizeType);
    const T& operator[](SizeType) const;
    Iterator begin();
    ConstIterator begin() const;
    Iterator end();
    ConstIterator end() const;

    void pushBack(const T&);

private: // implementation -- hidden to users of our class
    Iterator data_;
    Iterator avail_;
    Iterator limit_;

    std::allocator<T> alloc_;

    void create();
    void create(SizeType, const T&);
    void create(Iterator, Iterator);
    void uncreate();

    void grow();
    void uncheckedAppend(const T&);
};

// implementation of member functions

template <class T>
Vec<T>::Vec()
{
    create();
}

template <class T>
Vec<T>::Vec(SizeType n, const T& value)
{
    create(n, value);
}

template <class T>
Vec<T>::Vec(const Vec& v)
{
    create(v.begin(), v.end());
}

template <class T>
Vec<T>::~Vec()
{
    uncreate();
}

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& v)
{
    if (this != &v) {
        uncreate();
        create(v.begin(), v.end());
    }
    return *this;
}

template <class T>
typename Vec<T>::SizeType Vec<T>::getSize() const
{
    return avail_ - data_;
}

template <class T>
T& Vec<T>::operator[](SizeType i)
{
    return data_[i];
}

template <class T>
const T& Vec<T>::operator[](SizeType i) const
{
    return data_[i];
}

template <class T>
typename Vec<T>::Iterator Vec<T>::begin()
{
    return data_;
}

template <class T>
typename Vec<T>::ConstIterator Vec<T>::begin() const
{
    return data_;
}

template <class T>
typename Vec<T>::Iterator Vec<T>::end()
{
    return avail_;
}

template <class T>
typename Vec<T>::ConstIterator Vec<T>::end() const
{
    return avail_;
}

template <class T>
void Vec<T>::pushBack(const T& element)
{
    if (avail_ == limit_)
        grow();
    uncheckedAppend(element);
}

template <class T>
void Vec<T>::create()
{
    data_ = limit_ = avail_ = 0;
}

template <class T>
void Vec<T>::create(SizeType n, const T& element)
{
    data_ = alloc_.allocate(n);
    avail_ = limit_ = data_ + n;
    std::uninitialized_fill(data_, avail_, element);
}

template <class T>
void Vec<T>::create(Iterator b, Iterator e)
{
    data_ = alloc_.allocate(e - b);
    avail_ = limit_ = std::uninitialized_copy(b, e, data_);
}

template <class T>
void Vec<T>::uncreate()
{
    if (data_ != 0) {
        Iterator i = avail_;
        while (i != data_)
            alloc_.destroy(--avail_);

        alloc_.deallocate(data_, limit_ - data_);
    }
    data_ = avail_ = limit_;
}

template <class T>
void Vec<T>::grow()
{
    SizeType size = std::max(2*(limit_ - data_), std::ptrdiff_t(1));

    Iterator tempData = alloc_.allocate(size);
    Iterator tempAvail = std::uninitialized_copy(data_, avail_, tempData);

    data_ = tempData;
    avail_ = tempAvail;
    limit_ = data_ + size;
}

template <class T>
void Vec<T>::uncheckedAppend(const T& element)
{
    alloc_.construct(avail_++, element);
}

#endif   /* ----- #ifndef VEC_HPP  ----- */
