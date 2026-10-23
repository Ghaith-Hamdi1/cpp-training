# References and pointers

## rvalue vs. lvalue

- lvalue (left value)
  - is an expression that evaluates to an identifiable object or function
  - can be modified (unless constant)
- rvalue (right value)
  - is an expression that is not an lvalue, generally a literal or a return of a called function
  - cannot be modified

## References

- A reference is an alias to an existing object
- Identical to the object being referenced

[Diagram — extracted labels: `x`, `a`, `1234` — illustrating `x` and its alias `a` both referring to the same memory holding `1234`]

```cpp
int x{1234};
int& a = x;
```

- Two types:
  - lvalue reference
  - rvalue reference

## References: lvalue references

- Must have the same type as the value being referenced
- No reference to `void` type

## References: lvalue references returned in functions

- Compile error: reference to local variable

## References: Pass value by reference

- Call to `fun()` will make a copy of the argument: expensive in execution time (pass by value)
- Call to `fun()` won't make a copy (pass by reference):
  - ADVANTAGE 1: gain of time
  - ADVANTAGE 2: modifying the argument in the function will modify the original value
- Pass by const reference:
  - Call to `fun()` won't make a copy
  - ADVANTAGE 1: gain of time
  - ADVANTAGE 2: does not modify the original value
  - ADVANTAGE 3: can be bound to lvalue, const lvalue and rvalue

## References: rvalue references

- Use of rvalue references:
  - Working with move constructor and move assignment (will be seen later)
  - Cannot bind a non-const lvalue reference of type `int&` to an rvalue of type `int` (see provided sample code)
  - Cannot bind an rvalue reference of type `int&&` to an lvalue of type `int` (see provided sample code)

Reference example, `examples/course/01-cpp-basics/11-references-and-pointers/14_references.cpp`:

```cpp
// Trimmed excerpt — full runnable example: examples/course/01-cpp-basics/11-references-and-pointers/14_references.cpp
#include <iostream>

void func1(int& x)
{
    std::cout << "Pass by reference: " << std::endl << x << " -> ";
    x++;
    std::cout << x << std::endl;
}

void func2(const int& x)
{
    std::cout << "Pass by const reference: " << std::endl << x << std::endl;
    // x++; compile error
}

void printReferenceValue(int&& x)
{
    std::cout << x << std::endl;
}

int main(){

    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is now an alias for variable x

    std::cout << x << ref << std::endl; // print 55

    x = 6; // x now has value 6

    std::cout << x << ref << std::endl; // prints 66

    ref = 7; // the object being referenced (x) now has value 7

    std::cout << x << ref <<  std::endl; // prints 77

    func1(x);

    const int y { 100 };
    func2(x); // lvalue
    func2(y); // const lvalue
    func2(500); // rvalue

    // rvalue reference
    int&& rRef { 20 };

    std::cout << "rvalue reference: " << rRef << std::endl;
    rRef = 40;
    std::cout << "rvalue reference changed: " << rRef << "/ " << &rRef << std::endl;

    // This line will generate an error
    // as non-const lvalue reference of
    // type int& to an rvalue of type int
    // int& lref = 10;
    int& lref = rRef; // but this works using rvalue reference

    // This line will generate an error
    // as l-value cannot be assigned
    // to the r-value references
    // printReferenceValue(x);
    printReferenceValue(10); // but this works fine

    return 0;
}
```

## Pointers

- Special object type that contains the address of another object

[Diagram — extracted labels illustrating pointers: "Allocate and free pointer to one element", "Allocate and free pointer to many elements", "Address operator `&`", "Dereferencing operator `*`", with example addresses `x = 0x7ffd052ebcfc` holding value `100`, and `ptr = 0x7ffc81400300` holding address `0x7ffd052ebcfc`]

## Pointers — size

- Size of pointer depends on the address bus size
  - On 32-bit machine → size of pointer 32 bits (4 Bytes)
  - On 64-bit machine → size of pointer 64 bits (8 Bytes)
- Dangling pointers:
  - Holding an address of a no-longer-existing variable or object
  - Pointing to an illegal address and trying to access it (e.g. `0x0`)

## Pointers — best practices

- Always initialize the pointer when declared (`nullptr`, allocate, or point to a variable)
- Always check if it is a null pointer before use
- Promote the use of lvalue references over pointers when possible
- Always check that allocated pointers are freed at every exit point

## Pointers and const keyword

- Different types:
  - Pointer to const
  - Const Pointer
  - Const Pointer to Const

## Pointers: pass by address

- Call to `fun()` will make a copy of the argument: expensive in execution time (pass by value)
- Call to `fun()` won't make a copy (pass by address):
  - ADVANTAGE 1: gain of time
  - ADVANTAGE 2: modifying the argument in the function will modify the original value

Reference example, `examples/course/01-cpp-basics/11-references-and-pointers/13_pointers.cpp`:

```cpp
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
    const int* const cptrc { &x1 }; // a const pointer to a const value

    // compile and see

    return 0;
}
```

## Return by reference

- Making a copy of the returned value is expensive in memory and execution time
- The returned variable by reference should live as long as the returned value is needed

## Return by address

- Almost the same as return by reference
- Advantage: can return `nullptr` when an empty return is needed
- The returned variable by address should point to a valid variable

Reference example, `examples/course/01-cpp-basics/11-references-and-pointers/15_return_address_reference.cpp`:

```cpp
// Trimmed excerpt — full runnable example: examples/course/01-cpp-basics/11-references-and-pointers/15_return_address_reference.cpp
#include <iostream>


const int& getNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return s_x; // and return a reference to it
}

const int* pcGetNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return &s_x; // and return a reference to it
}

int* pGetNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return &s_x; // and return a reference to it
}

int& max(int& x, int& y)
{
    return (x > y) ? x : y;
}

int main()
{
    /********** Return by reference *********/
    const int& id1 { getNextId() }; // id1 is a reference
    const int& id2 { getNextId() }; // id2 is a reference

    std::cout << "Correct handling " << id1 << id2 << std::endl; // displays 22

    const int id3 { getNextId() }; // id3 is not a reference, will make a copy
    const int id4 { getNextId() }; // id4 is not a reference, will make a copy

    std::cout << "Wrong handling " << id3 << id4 << std::endl; // displays 34

    int a{ 5 };
    int b{ 6 };

    max(a, b) = 7; // sets the greater of a or b to 7
    std::cout << "New b value " << b << std::endl;

    /********** Return by address *********/
    int * ptr = pGetNextId();
    const int *cptr = pcGetNextId();

    std::cout << "Return by address " << *ptr << " " << *cptr << std::endl; // displays 1 1

    return 0;
}
```

## Exercise

- Write a function to perform a swap of two integers using pointers, and another one using references: `swap(a, b)`

---

