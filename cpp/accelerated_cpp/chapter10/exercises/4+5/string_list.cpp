#include <string>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "string_list.hpp"

using namespace std;

StringList::StringList() : size_(0), firstNode_(NULL), lastNode_(NULL) {}

StringList::Node::Node() : previous_(NULL), next_(NULL) {}

StringList::Node::Node(string s) : value_(s), previous_(NULL), next_(NULL) {}

StringList::Iterator::Iterator() : node_(NULL) {}

StringList::Iterator::Iterator(Node* node) : node_(node) {}

size_t StringList::getSize() const
{
    return size_;
}

// Operator* needs to return a reference to nonconst string so that the
// returned object can be modified. One needs to return by reference instead
// of value, as the latter would return an rvalue.
// Furthermore, the member function is nonconst because if it were const, the
// object (iterator) on which the function is invoked would be passed as a
// pointer to const (i.e., this is a pointer to const), the returned object
// also would be a reference to const, to which the caller would have no write
// access.
string& StringList::Iterator::operator*()
{
    return node_->value_; // (*(*this).node_).value_
}

StringList::Iterator& StringList::Iterator::operator++()
{
    node_ = node_->next_;
    return *this;
}

StringList::Iterator& StringList::Iterator::operator--()
{
    node_ = node_->previous_;
    return *this;
}

StringList::Iterator StringList::Iterator::operator++(int)
{
    Iterator temp = *this;
    node_ = node_->next_;
    return temp;
}

StringList::Iterator StringList::Iterator::operator--(int)
{
    Iterator temp = *this;
    node_ = node_->previous_;
    return temp;
}

// lhs == rhs calls lhs.operator==(rhs) behind the scenes.
bool StringList::Iterator::operator==(const Iterator& rhs) const
{
    return node_ == rhs.node_;
}

bool StringList::Iterator::operator!=(const Iterator& rhs) const
{
    return !(*this == rhs);
}

StringList::Iterator StringList::begin() const
{
    return Iterator(firstNode_);
}

StringList::Iterator StringList::end() const
{
    return Iterator(NULL);
}

bool StringList::isEmpty() const
{
    return begin() == end();
}

void StringList::pushBack(string s)
{
    Node* node = new Node(s);

    // The element previous to *node is the current *lastNode_,
    // after which we set lastNode_ equal to node.
    (*node).previous_ = lastNode_;
    lastNode_ = node;

    // If node is the first element pushed back to the StringList, we set
    // firstElement_ accordingly. Otherwise, we link the previous to the present.
    if (isEmpty())
        firstNode_ = node;
    else
        (*node).previous_->next_ = node;
    ++size_;
}

void StringList::popFront()
{
    if (isEmpty())
        throw out_of_range("The list does not contain any element");
    else if (firstNode_ == lastNode_ && firstNode_ != NULL) {
        delete firstNode_;
        firstNode_ = NULL;
        lastNode_ = NULL;
    }
    else {
        Node* temp = firstNode_;
        firstNode_ = (*temp).next_;
        delete temp;
        firstNode_->previous_ = NULL;
    }
    --size_;
}

void StringList::clearMemory()
{
    while (!isEmpty()) {
        Node* temp = firstNode_;
        firstNode_ = (*temp).next_;
        delete temp;
        --size_;
    }
}

void StringList::printList() const
{
    for (Iterator i = begin(); i != end(); ++i) {
        cout << *i << endl;
    }
}
