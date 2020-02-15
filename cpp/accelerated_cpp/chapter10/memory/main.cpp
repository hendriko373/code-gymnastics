#include <iostream>

using namespace std;

// This function returns an invalid pointer, since the allocated memory for
// y, i.e., &y, is deallocated automatically at the end of the function block.
// Deallocation means that the memory becomes unavailable to the program and any
// thing can happen with the values stored at this address. Therefore, the pointer
// &y becomes invalid.
int* invalid_ptr(int x)
{
    int y = x;
    return &y;
}

// The static keyword makes that the memory where y is stored is not deallocated
// at the end of the block.
int* ptr_to_static(int x)
{
    static int y;
    y = x;
    cout << "y equals " << y << endl;
    return &y;
}

int main()
{
    int* p = invalid_ptr(20);
    cout << *p << endl;
    cout << p << endl;
    
    int a = 5;
    cout << &a << endl;
    cout << *p << endl;
    // Here we see that *p has changed, this shows that dereferencing p gives
    // undefined behavior. The memory has been deallocated and we have no clue
    // what the value will be stored in it.

    cout << endl;
    p = ptr_to_static(20);
    cout << *p << endl;
    cout << p << endl;

    int b = 5;
    cout << &b << endl;
    cout << *p << endl;
    // Now *p has not changed, because the memory to which it points has not
    // been deallocated when leaving the function ptr_to_static().

    cout << endl;
    p = ptr_to_static(30);
    cout << *p << endl;
    cout << p << endl;

    return 0;
}

