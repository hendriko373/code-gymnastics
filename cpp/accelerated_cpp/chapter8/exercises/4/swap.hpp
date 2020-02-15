template <class T>
void swap(T a, T b)
{
    T c = a;
    a = b;
    b = c;
}

// In \S8.2.5/148 one must invoke swap, because there is no way of knowing
// the type of *begin, *end, such that we cannot make a copy of these elements.
// By invoking the template function swap, this problem is resolved since swap
// will know these elements' types at the time when it is called.
