#include <iostream>


class A 
{
public:
    A(int x) : m_x{x} {}

    int process() const
    {
        return m_x * m_x;
    }

    int process2() const
    {
        return m_x * 2;
    }
private:
    int m_x;
};

class B : public A
{
public:
    B() : A(0) {}
};

template<typename T, typename U>
T function(const U& u)
{
    std::cout << "Called template" << std::endl;
    T t;
    t = u.process();

    return t;
}
// template specialization for function
template<>
int function(const A& a)
{
    std::cout << "Called template speicalization" << std::endl;
    return a.process2();
}

template<typename T>
int functionOverload(T & b)
{
    std::cout << "Called template with B parameter" << std::endl;
    return b.process2();
}

int functionOverload(B& b)
{
    std::cout << "Called overload with B parameter" << std::endl;
    return b.process2();
}

template<typename T>
T min(T& x, T& y)
{
    return (x < y ? x : y);
}

template<typename T>
int processFunction(int in)
{
    T t(in);

    return t.process();
}

int main()
{
    A a(2);
    // A is auto deduced (cannot deduct return type)
    int x = function<int>(a); 
    std::cout << "Template function return " << x << std::endl;

    B b;

    int y = function<int>(b);
    std::cout << "Template function return " << y << std::endl;

    int x1 = min<const int>(4, 5);
    int x2 = processFunction<A>(6);
    std::cout << "The 'processFunction' returned " << x2 << std::endl;
    int z1 = functionOverload<>(b);
    int z2 = functionOverload(b);


    return 0;
}
