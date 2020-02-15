#ifndef RefHandle_hpp
#define RefHandle_hpp

#include <cstddef>
#include <stdexcept>

template <class T>
class RefHandle
{
public:
    RefHandle();
    RefHandle(const RefHandle& handle);
    RefHandle& operator=(const RefHandle& handle);
    ~RefHandle();

    RefHandle(T* p);
    operator bool() const;
    T& operator*() const;
    T* operator->() const;
private:
    T* object_;
    std::size_t* counter_;
};

template <class T>
RefHandle<T>::RefHandle() : object_(nullptr), counter_(new std::size_t(1)) {};

template <class T>
RefHandle<T>::RefHandle(const RefHandle& handle)
        : object_(handle.object_), counter_(handle.counter_)
{
    ++(*counter_);
}

template <class T>
RefHandle<T>& RefHandle<T>::operator=(const RefHandle& handle)
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
RefHandle<T>::~RefHandle()
{
    --(*counter_);
    if (*counter_ == 0) {
        delete object_;
        delete counter_;
    }
}

template <class T>
RefHandle<T>::RefHandle(T* p) : object_(p), counter_(new std::size_t(1)) {}

template <class T>
RefHandle<T>::operator bool() const
{
    return object_;
}

template <class T>
T& RefHandle<T>::operator*() const
{
    if (object_)
        return *object_;
    throw std::runtime_error("Unbound RefHandle!");
}

template <class T>
T* RefHandle<T>::operator->() const
{
    if (object_)
        return object_;
    throw std::runtime_error("Unbound RefHandle!");
}


#endif
