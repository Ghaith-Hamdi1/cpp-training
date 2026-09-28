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