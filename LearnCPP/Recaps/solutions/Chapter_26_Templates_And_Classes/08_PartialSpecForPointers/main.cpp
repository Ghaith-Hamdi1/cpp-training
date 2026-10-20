// Chapter 26 - Project 8: Partial Specialization for Pointer Types
// ==================================================================
// When a template class like Storage<T> is instantiated with a pointer
// type (e.g. Storage<int*>), it stores the ADDRESS, not a copy of the
// value. This leads to dangling-pointer bugs:
//
//   int x = 5;
//   Storage<int*> s(&x);   // stores pointer to x
//   x = 99;                // s now "sees" 99 - unexpected!
//   // Even worse: if x goes out of scope, s holds a dangling pointer.
//
// Solution: Partially specialize Storage<T*> so that it DEREFERENCES
// the pointer and stores a deep copy of the pointed-to value.

#include <iostream>
#include <memory>

// ---------------------------------------------------------------------------
// Primary template - stores a copy of the value (value semantics)
// ---------------------------------------------------------------------------
template <typename T>
class Storage
{
private:
    T m_value;

public:
    Storage(const T &value) : m_value{value}
    {
        std::cout << "  [primary] Storing value directly\n";
    }

    const T &getValue() const { return m_value; }

    void print() const
    {
        std::cout << "  Value = " << m_value << '\n';
    }
};

// ---------------------------------------------------------------------------
// Partial specialization for pointer types T*
// Dereferences the pointer and stores a COPY of the pointed-to value.
// ---------------------------------------------------------------------------
template <typename T>
class Storage<T *> // matches any pointer type: int*, double*, etc.
{
private:
    // We store a dynamically allocated copy, managed by unique_ptr
    std::unique_ptr<T> m_value;

public:
    Storage(T *value) : m_value{std::make_unique<T>(*value)}
    {
        // *value dereferences the pointer and copies the value
        std::cout << "  [pointer-spec] Deep-copying pointed-to value\n";
    }

    const T &getValue() const { return *m_value; }

    void print() const
    {
        std::cout << "  Value = " << *m_value << '\n';
    }
};

// ---------------------------------------------------------------------------
int main()
{
    // --- Primary template: stores int by value ---
    std::cout << "Creating Storage<int>:\n";
    int a{42};
    Storage<int> s1(a);
    s1.print(); // Value = 42

    a = 999; // changing 'a' does NOT affect s1
    std::cout << "After changing a to 999:\n";
    s1.print(); // Value = 42  (independent copy)

    std::cout << '\n';

    // --- Pointer specialization: deep-copies the int ---
    std::cout << "Creating Storage<int*>:\n";
    int b{100};
    Storage<int *> s2(&b); // partial specialization kicks in
    s2.print();            // Value = 100

    b = 777; // changing 'b' does NOT affect s2 either!
    std::cout << "After changing b to 777:\n";
    s2.print(); // Value = 100  (deep copy, not a dangling ref)

    std::cout << '\n';

    // --- Demonstrate with a scoped variable ---
    std::cout << "Demonstrating safety with scoped variable:\n";
    Storage<int *> *s3{};
    {
        int temp{55};
        s3 = new Storage<int *>(&temp);
        s3->print(); // Value = 55
    }
    // 'temp' is now out of scope, but s3 holds a deep copy
    std::cout << "After temp goes out of scope:\n";
    s3->print(); // Value = 55  (still safe!)
    delete s3;

    return 0;
}
