#include <iostream>

template<int N>
struct Fact
{
    enum
    {
        value = Fact<N-1>::value * N
    };
};

template<>
struct Fact<0>
{
    enum 
    {
        value = 1
    };
};

template<int N>
struct NumericTest
{
    enum 
    {
        IsPair = N % 2 == 0 ? true : false,
        IsZero = N == 0 ? true : false
    };
};

int main()
{
    constexpr int x = Fact<10>::value;
    std::cout << "Precompiled value for factorial of 10 = " << x << std::endl;

    std::cout  << "3 is pair ? " << (NumericTest<3>::IsPair ? "true" : "false") << std::endl;
    return 0;
}