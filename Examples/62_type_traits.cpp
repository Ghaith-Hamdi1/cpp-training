#include <iostream>
#include <type_traits>
#include <string>

template<typename T>
T multiply(T& a, T& b)
{
    static_assert(std::is_integral<T>::value, "Multiplication can only be done using integral type");
    return a * b;
}

class Test
{
public:
    template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
    static void print(const T& t)
    {
        std::cout << "Print an itegral value " << t << std::endl; 
    }

    template<typename T, std::enable_if_t<!std::is_integral<T>::value, bool> = true>
    static void print(const T& t)
    {
        std::cout << "Print a non integral value " << t << std::endl; 
    }
};

class X
{

};

class A
{
public:
    A() {}
    virtual ~A() = default;
};

class B : public A
{
};

int main()
{
    std::cout << "2 * 3 = " << multiply<const int>(2, 3) << std::endl;
    // won't compile due to static_assert
    // multiply<const std::string>("2", "3");

    Test::print<int>(5);
    Test::print<std::string>(std::string("Hello"));

    std::cout << "X is polymorphic " << std::boolalpha << std::is_polymorphic<X>::value << std::endl;
    std::cout << "A is polymorphic " << std::boolalpha << std::is_polymorphic<A>::value << std::endl;

    std::cout << "X is" << (std::is_base_of<A, X>::value == true ? " " : " not ") << "a derived from A" << std::endl;
    std::cout << "B is" << (std::is_base_of<A, B>::value == true ? " " : " not ") << "a derived from A" << std::endl;

    return 0;
}