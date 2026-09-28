#include <iostream>

int main()
{
    int x{100};
    int* ptr{nullptr};
    ptr = &x;

    std::cout << "x value " << x << " from pointer " << *ptr << " x address " << &x;
    std::cout << " " << " from pointer " << ptr << " pointer address " << &ptr << std::endl;

    int y{30};
    ptr = &y; // change ptr to point on y totally valid

    {
        int z{10};

        ptr = &z;
    }
    int z{30};
    std::cout << "Access no longer existing variable " << *ptr << std::endl; // undefined behavior

    const int x1 { 5 }; // x is now const
    // int* ptr { &x1 };   // compile error: cannot convert from const int* to int*
    /// Pointer to const
    const int y1{ 5 };
    const int* ptrc { &y1 }; // okay: ptr is pointing to a "const int"
    // *ptrc = 6; // not allowed: we can't change a const value
    ptrc = &x1; // we can change since pointer is not const (but y was const)
    /// Constant pointer
    int* const cptr { &x }; // okay: the const pointer is initialized to the address of x
    // cptr = &y; // error: once initialized, a const pointer can not be changed.
    *cptr = 6; // okay value is changed and not the pointer
    const int* const ptr { &x1 }; // a const pointer to a const value

    // compile and see

    return 0;
}