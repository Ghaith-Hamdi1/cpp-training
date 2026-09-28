#include <iostream>

class A {
public:
    A() : m_ptr{nullptr}
    {
    }
    void createPtr() {
        removePtr();
        m_ptr = new int;
    }
    void removePtr() 
    {
        if (m_ptr != nullptr)
        {
            delete m_ptr;
            m_ptr = nullptr;
        }
    }
    // copy constructor
    A(const A& a)
    {
        std::cout << "Copy constructor" << std::endl;
        if (a.m_ptr != nullptr)
        {
            createPtr();
            *m_ptr = *a.m_ptr;
        }
    }
    // copy assignment
    A& operator=(const A& a)
    {
        std::cout << "Copy assignment operator" << std::endl;
        if (this != &a) // check if it is not self assignment
        {
            createPtr();
        }
        return *this;
    }

    // move constructor 
    A(A&& a) noexcept : m_ptr{a.m_ptr} {
        std::cout << "Move constructor" << std::endl;
        a.m_ptr = nullptr; // ownership moved to this and a is no longer owner, => nullptr
    }

    // move assignment
    A& operator=(A&& a) noexcept 
    {
        std::cout << "Move assignment operator" << std::endl;
        if (this != &a) // check if it is not self assignment
        {
            m_ptr = a.m_ptr;
            a.m_ptr = nullptr;
        }
        return *this;
    } 

    virtual ~A()
    {
        removePtr();
    }
private:
    int * m_ptr;
};

A generateA()
{
    A a;

    return a; // rule in C++, l-value returned 
              // by value will favorize move than copy
}

int main()
{
    A a;
    a = generateA(); // this assignment will invoke the move assignment
    a = A();// this assignment will invoke the move assignment as well

    A a1 = std::move(a); // this will invoke move constructor

    A a2{a};
    a2 = a;
    return 0;
}