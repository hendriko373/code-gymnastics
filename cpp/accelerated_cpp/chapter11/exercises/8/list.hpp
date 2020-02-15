#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <memory>
#include <iostream>

template <class T>
class List {
private:
    class Node {
    public:
        T value_;
        Node* previous_;
        Node* next_;

        Node();
        Node(const T&);
    };

public:
    class Iterator {
        friend class List;
    private:
        Node* node_;

    public:
        Iterator();
        Iterator(Node*);

        T& operator*() const;
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
        Iterator& operator++();      // prefix
        Iterator operator++(int);   // postfix
        Iterator& operator--();      // prefix
        Iterator operator--(int);   // postfix
    };

    typedef T ValueType;
    typedef T& Reference;
    typedef const T& ConstReference;
    typedef std::size_t SizeType;

    List();
    List(SizeType, const T& = T());
    List(const List&);
    List& operator=(const List&);
    ~List();

    void create(SizeType, const T&);
    Iterator begin() const;
    Iterator end() const;
    void pushBack(const T&);
    Iterator erase(Iterator);
    Iterator erase(Iterator, Iterator);
    void clear();

private:
    Node* data_;    // first element
    Node* end_;     // off-the-end element
    SizeType size_;
    std::allocator<Node> alloc_;
};

template <class T>
List<T>::List() : size_(0)
{
    data_ = end_ = alloc_.allocate(1);
    alloc_.construct(end_, Node());
}

template <class T>
List<T>::List(SizeType n, const T& val) : size_(0)
{
    data_ = end_ = alloc_.allocate(1);
    alloc_.construct(end_, Node());
    create(n, val); 
}

template <class T>
List<T>::List(const List& lst) : size_(0)
{
    data_ = end_ = alloc_.allocate(1);
    alloc_.construct(end_, Node());
    for (Iterator i = lst.begin(); i != lst.end(); ++i)
        pushBack(*i);
}

template <class T>
List<T>& List<T>::operator=(const List& lst)
{
    if (this != &lst) {
        clear();
        for (Iterator i = lst.begin(); i != lst.end(); ++i)
            pushBack(*i);
    }
    return *this;
}

template <class T>
List<T>::~List()
{
    clear();
    alloc_.destroy(end_);
    alloc_.deallocate(end_, 1);
}

template <class T>
void List<T>::create(SizeType n, const T& val)
{
    for (SizeType i = 0; i !=n; ++i)
        pushBack(val);
}

template <class T>
typename List<T>::Iterator List<T>::begin() const
{
    return Iterator(data_);
}

template <class T>
typename List<T>::Iterator List<T>::end() const
{
    return Iterator(end_);
}

template <class T>
void  List<T>::pushBack(const T& val)
{
    Node newNode(val);
    Node* newNodePtr = alloc_.allocate(1);
    alloc_.construct(newNodePtr, newNode);

    if (size_ == 0) {
        data_ = newNodePtr;
        data_->next_ = end_;
        end_->previous_ = data_;
    } else {
        end_->previous_->next_ = newNodePtr;
        newNodePtr->previous_ = end_->previous_;
        newNodePtr->next_ = end_;
        end_->previous_ = newNodePtr;
    }
    ++size_;
}

template <class T>
typename List<T>::Iterator List<T>::erase(Iterator pos)
{
    if (pos.node_ == data_) {
        data_ = data_->next_;
        data_->previous_ = 0;
    } else {
        pos.node_->previous_->next_ = pos.node_->next_;
        pos.node_->next_->previous_ = pos.node_->previous_;
    }
    Iterator ret(pos.node_->next_);
    alloc_.destroy(pos.node_);
    alloc_.deallocate(pos.node_, 1);
    --size_;
    return ret;
}

template <class T>
typename List<T>::Iterator List<T>::erase(Iterator b, Iterator e)
{
    if (b == e)
        return b;
    
    if (b == begin()) {
        data_ = e.node_;
        data_->previous_ = 0;
    }
    else {
        b.node_->previous_->next_ = e.node_;
        e.node_->previous_ = b.node_->previous_;
    }
    while (b != e) {
        Iterator temp(b.node_->next_);
        alloc_.destroy(b.node_);
        alloc_.deallocate(b.node_, 1);
        b = temp;
        --size_;
    }
    return e;
}

template <class T>
void List<T>::clear()
{
    erase(begin(), end());
}

template <class T>
List<T>::Node::Node() : previous_(0), next_(0) {}

template <class T>
List<T>::Node::Node(const T& val) : previous_(0), next_(0)
{
    value_ = val;
}

template <class T>
List<T>::Iterator::Iterator() : node_(0) {}

template <class T>
List<T>::Iterator::Iterator(Node* val)
{
    node_ = val;
}

template <class T>
T& List<T>::Iterator::operator*() const
{
    return this->node_->value_;
}

template <class T>
bool List<T>::Iterator::operator==(const Iterator& rhs) const
{
    return node_ == rhs.node_;
}

template <class T>
bool List<T>::Iterator::operator!=(const Iterator& rhs) const
{
    return !(*this == rhs);
}

template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
    node_ = node_->next_;
    return *this;
}

template <class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
    Node* temp = node_;
    node_ = node_->next_;
    return temp;
}

template <class T>
typename List<T>::Iterator& List<T>::Iterator::operator--()
{
    node_ = node_->previous_;
    return *this;
}

template <class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int)
{
    Node* temp = node_;
    node_ = node_->previous_;
    return temp;
}

#endif
