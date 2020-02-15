#ifndef GenHandle_hpp
#define GenHandle_hpp

#include <cstddef>
#include <stdexcept>

template <class T>
class GenHandle
{
public:
    GenHandle();
    GenHandle(const GenHandle& handle);
    GenHandle& operator=(const GenHandle& handle);
    ~GenHandle();

    GenHandle(T* p);
    void makeUnique();
    operator bool() const;
    T& operator*() const;
    T* operator->() const;
private:
    T* object_;
    std::size_t* counter_;
};

template <class T>
GenHandle<T>::GenHandle() : object_(nullptr), counter_(new std::size_t(1)) {};

template <class T>
GenHandle<T>::GenHandle(const GenHandle& handle)
        : object_(handle.object_), counter_(handle.counter_)
{
    ++(*counter_);
}

template <class T>
GenHandle<T>& GenHandle<T>::operator=(const GenHandle& handle)
{
    if (this != &handle) {
        --(*counter_);
        if (*counter_ == 0) {
            delete object_;
            delete counter_;
        }
        object_ = handle.object_;
        counter_ = handle.counter_;
        ++(*counter_);
    }
    return *this;
}

template <class T>
GenHandle<T>::~GenHandle()
{
    --(*counter_);
    if (*counter_ == 0) {
        delete object_;
        delete counter_;
    }
}

template <class T>
GenHandle<T>::GenHandle(T* p) : object_(p), counter_(new std::size_t(1)) {}

template <class T>
void GenHandle<T>::makeUnique()
{
    if (*counter_ != 1) {
        --*counter_;
        object_ = object_ ? object_->clone() : nullptr;
        counter_ = new std::size_t(1);
    }
}

template <class T>
GenHandle<T>::operator bool() const
{
    return object_;
}

template <class T>
T& GenHandle<T>::operator*() const
{
    if (object_)
        return *object_;
    throw std::runtime_error("Unbound GenHandle!");
}

template <class T>
T* GenHandle<T>::operator->() const
{
    if (object_)
        return object_;
    throw std::runtime_error("Unbound GenHandle!");
}


#endif
