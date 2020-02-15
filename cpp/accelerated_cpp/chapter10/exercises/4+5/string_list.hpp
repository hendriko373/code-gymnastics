#ifndef STRING_LIST_HPP
#define STRING_LIST_HPP

#include <string>
#include <cstddef>

class StringList {
    private:
        class Node {
            public:
                Node();
                Node(std::string);

                std::string value_;
                Node* previous_;
                Node* next_;
        };
        std::size_t size_;
        Node* firstNode_;
        Node* lastNode_;

    public:
        class Iterator {
            private:
                Node* node_;

            public:
                Iterator();
                Iterator(Node*);

                std::string& operator*();
                Iterator& operator++();
                Iterator& operator--();
                Iterator operator++(int);
                Iterator operator--(int);
                bool operator==(const Iterator&) const;
                bool operator!=(const Iterator&) const;
        };
        StringList();

        std::size_t getSize() const;

        void pushBack(std::string);
        void popFront();
        void clearMemory();
        void printList() const;
        bool isEmpty() const;
        
        Iterator begin() const;
        Iterator end() const;
};

#endif
