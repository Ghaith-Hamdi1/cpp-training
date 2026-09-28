#include <iostream>

template<typename T, typename U>
class A 
{
public:
    A(T& x);

    A(T&& x);

    virtual U process();
protected:
    T m_x;
};

template<>
class A<char, char>
{
public:
    A(char& x) : m_x(x)
    {
        std::cout << "A template specialization char (& constructor)" << std::endl;
    }

    A(char&& x)
    {
        std::cout << "A template specialization char (&& constructor)" << std::endl;
    }

    virtual char process()
    {
        std::cout << "A template specialization char process" << std::endl;
        return 'X';
    }
protected:
    char m_x;
};

class B : public A<int, int>
{
public:
    B() : A(0) 
    {
        std::cout << "Called B constructor " << m_x << std::endl;
    }
};

template<typename T>
class C : public A<T, int>
{
public:
    C(T& x);

    C(T&& x);
};

template<typename T, typename U>
A<T, U>::A(T& x) : m_x(x)
{
    std::cout << "Called A constructor with lvalue reference " << m_x << std::endl;
}

template<typename T, typename U>
A<T, U>::A(T&& x) : m_x(x)
{
    std::cout << "Called A constructor with rvalue reference " << m_x << std::endl;
}

template<typename T, typename U>
U A<T, U>::process()
{
    return static_cast<U>(m_x);
}

template<typename T>
C<T>::C(T& x): A<T, int>(x)
{
    std::cout << "Called C constructor with lvalue reference " << A<T, int>::m_x << std::endl;
}

template<typename T>
C<T>::C(T&& x): A<T, int>(x)
{
    std::cout << "Called C constructor with rvalue reference " << A<T, int>::m_x << std::endl;
}


template<typename T>
class Test
{
public:
    Test(T& t);

    template<typename U>
    bool testTemplate(T& t, U& u);
};

template<typename T>
Test<T>::Test(T& t)
{
    std::cout << "Called template for type" << std::endl;
}

template<>
Test<int>::Test(int& t)
{
    std::cout << "Called specialization for int" << std::endl;
}
template<typename T>
template<typename U>
bool Test<T>::testTemplate(T& t, U& u)
{
    return (static_cast<T>(u) == t);
}

// partial template specialization
template<typename T>
class DerivedA : public A<T, int>
{
public:
    DerivedA() : A<T, int>(0) {}
    int process()
    {
        std::cout << "DerivedA process function call" << std::endl;
        return 0;
    }
};

int main()
{
    A<int, int> a(2);

    int x1{0};
    uint32_t x2{0};
    Test<int> t1(x1);
    Test<uint32_t> t2(x2);
    // auto deduction is done below when calling testTemplate function
    std::cout << "Result of call of template function in template class " << std::boolalpha << t1.testTemplate(x1, x2) << std::endl;

    // template specialization
    A<char, char> a1('C');
    std::cout << a1.process() << std::endl;
    // partial template specialization
    DerivedA<char> derivedA;
    std::cout << derivedA.process() << std::endl;
    
    return 0;
}

