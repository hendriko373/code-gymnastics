#ifndef Handle_hpp
#define Handle_hpp

#include <stdexcept>

// Smart pointer class
template <class T>
class Handle
{
public:
    Handle() : p_(nullptr) {};
    Handle(const Handle& h) : p_(nullptr)
    {
        if (h.p_)
            p_ = h.p_->clone();
    }
    ~Handle()
    {
        delete p_;
    }
    Handle& operator=(const Handle& h)
    {
        if (this != &h) {
            delete p_;
            p_ = h.p_ ? h.p_->clone() : nullptr;
        }
        return *this;
    }

    Handle(const T* p) : p_(p) {}

    operator bool() const
    {
        return p_;
    }
    T& operator*()
    {
        if (p_)
            return *p_;
        throw std::runtime_error("Unbound Handle object");
    }
    const T& operator*() const
    {
        if (p_)
            return *p_;
        throw std::runtime_error("Unbound Handle object");
    }
    T* operator->()
    {
        if (p_)
            return p_;
        throw std::runtime_error("Unbound Handle object");
        /* If a user-defined operator-> is provided, the operator-> is called
         * again on the value that it returns, recursively, until an operator->
         * is reached that returns a plain pointer. After that, built-in semantics
         * are applied to that pointer.
         */
    }
    const T* operator->() const
    {
        if (p_)
            return p_;
        throw std::runtime_error("Unbound Handle object");
    }

private:
    T* p_;
};

#endif
