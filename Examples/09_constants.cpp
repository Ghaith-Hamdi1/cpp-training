#include <iostream>

constexpr int greater(int x, int y)
{
    return (x > y ? x : y); // here's our expression
}

constexpr int factorial(int n)
{
    return n <= 1 ? 1 : (n * factorial(n - 1));
}
 
// C++14 constexpr functions may use local variables and loops
#if __cplusplus >= 201402L
constexpr int factorial_cxx14(int n)
{
    int res = 1;
    while (n > 1)
        res *= n--;
    return res;
}
#endif

int main(){
    const int ki { 5 * 3 };
    constexpr int kExpr { ki };
    int i { kExpr };
    // ki = i; not allowed

    constexpr int x{ 5 };
    constexpr int y{ 6 };
    constexpr int g { greater(x, y) }; // will be evaluated at compile-time
    //constexpr int g { greater(i, y) }; // compile error, i not constant

    int g1 { greater(x, y) }; // Constexpr functions can also be evaluated at runtime

    int h { greater(ki, i) };

    std::cout << "g= " << g << " h= " << h << std::endl;

    const long int fac_10 = factorial(10);
#if __cplusplus >= 201402L
    const long int fac_10_cxx14 = factorial_cxx14(10); // faster than without const
#endif
    
    return 0;
}