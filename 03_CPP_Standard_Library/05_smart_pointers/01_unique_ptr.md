# std::unique_ptr\<T\>

- `std::unique_ptr<T>` used to manage allocation and deallocation of object of type `T` that is not shared by multiple objects
- Copy constructor of `unique_ptr` is deleted (can only be moved) so that ownership is moved as well
- Copy assignment is also deleted (can only use move assignment)
- In C++14, we generally use `std::make_unique<T>(constructor_parameters)` to create a `unique_ptr`
- Returning `std::unique_ptr` from function
  - Function `createA()` returns `unique_ptr` by value; if it is not assigned during call, `unique_ptr` will go out of scope. If it is assigned like in the example, it will be moved to `ptr` (since copy is deleted and return is an rvalue)
  - Generally, should not return `unique_ptr` by reference or pointer unless there is a reason (but it is doable, as shown in examples)
- Passing `unique_ptr` to function: generally, we have to pass it by value, since copy is disabled, move semantics should be used by calling `std::move`
- Always be careful about object ownership — a moved `unique_ptr` is no longer valid and may go out of scope and be destroyed

```cpp
// Source: Examples/03_CPP_Standard_Library/05_smart_pointers/46_unique_ptr.cpp
#include <iostream>
#include <memory>

class A
{
public:
    A() : m_x{0}
    {
        std::cout << "A default constructor" << std::endl;
    }
    A(int x) : m_x{x}
    {
        std::cout << "A constructor x=" << m_x << std::endl;
    }
    A (const A& a) : m_x{a.m_x}
    {
        std::cout << "A copy constructor" << std::endl;
    }
    A (A&& a) : m_x{a.m_x}
    {
        a.m_x = 0;
        std::cout << "A move constructor" << std::endl;
    }
    A& operator=(const A& a)
    {
        std::cout << "A copy assignment" << std::endl;
        m_x = a.m_x;
        return *this;
    }
    A& operator=(A&& a)
    {
        std::cout << "A move assignment" << std::endl;
        m_x = a.m_x;
        a.m_x = 0;
        return *this;
    }
    virtual void foo()
    {
        std::cout << "foo from A" << std::endl;
    }
    virtual ~A()
    {
        std::cout << "A destructor" << std::endl;
    }
protected:
    int m_x;
};

class B : public A
{
public:
    B()
    {
        std::cout << "B default constructor" << std::endl;
    }
    B(int x) : A(x)
    {
        std::cout << "B constructor x=" << m_x << std::endl;
    }
    B (const B& b)
    {
        std::cout << "B copy constructor" << std::endl;
    }
    B (B&& b)
    {
        std::cout << "B move constructor" << std::endl;
    }
    B& operator=(const B& b)
    {
        A::operator=(b);
        std::cout << "B copy assignment" << std::endl;
        return *this;
    }
    B& operator=(B&& b)
    {
        A::operator=(std::move(b));
        std::cout << "B move assignment" << std::endl;
        return *this;
    }
    virtual void foo()
    {
        std::cout << "foo from B" << std::endl;
    }
    virtual ~B()
    {
        std::cout << "B destructor" << std::endl;
    }
};

// unique_ptr can be taken by value and returned by moving it back
std::unique_ptr<A> passValue(std::unique_ptr<A> a)
{
    std::cout << "passValue" << std::endl;
    a->foo();
    return a;
}

std::unique_ptr<A>& passValueReference(std::unique_ptr<A>& a)
{
    std::cout << "passValueReference" << std::endl;
    return a;
}

std::unique_ptr<A> passRValueReference(std::unique_ptr<A>&& a)
{
    std::cout << "passRValueReference" << std::endl;
    return std::move(a);
}

int main()
{
    std::unique_ptr<A> adPtr = std::make_unique<B>();
    std::unique_ptr<A> asPtr = std::make_unique<B>(5);

    // it won't work without std::move since copy constructor will be
    // called which is deleted function
    // if returned value is not assigned like done below, adPtr moved in argument
    // will go out of scope
    // when assigned as done below, the move semantic will be employed
    // to transfert resource from return value (rvalue) to variable adPtr
    adPtr = passValue(std::move(adPtr));
    adPtr->foo();

    std::unique_ptr<A> &adPtr2 = passValueReference(adPtr);
    adPtr2->foo();

    adPtr = passRValueReference(std::move(adPtr));
    adPtr->foo();

    // other way for allocation
    std::unique_ptr<B> bPtr = std::unique_ptr<B>(new B(60));
    
    if (bPtr) // calls type cast operator bool() check if allocation success
    {
        bPtr->foo();
        B b = *bPtr; // dereferencing
        b.foo();

        B * bptr = bPtr.get();
        bptr->foo();

        std::cout << "Address of B " << bptr << std::endl;
        bPtr.release();
        std::cout << "Address of B " << bptr << " unique_ptr.get " << bPtr.get() << std::endl;
        bptr->foo();
    }
    std::unique_ptr<B> bPtr2 = std::move(bPtr); // move assignment of unique_ptr
    // bPtr is no longer valid, must not be used any more
    //bPtr2->foo();

    return 0;
}
```

