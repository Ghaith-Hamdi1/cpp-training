# Metaprogramming

- In C++, metaprogramming refers to the use of templates to perform calculation at compile time
- It will consist then in generating code during compilation
- We will use for this purpose:
  - Templates resolution
  - Enumerations
  - Ternary operator: ( cond ? if_true : if_false; )

- For example, let's see the famous factorial function: f(x) = f(x-1) * x with f(0) = 1
  - Annotation on the example: *"The value of x is calculated by generating code during compile time"*
- Limitation: many compilers allow a maximum number of recursion depth

```cpp
// Representative example (examples/04-templates-and-design-patterns/03-metaprogramming/63_metaprogramming.cpp)
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

int main()
{
    constexpr int x = Fact<10>::value;
    std::cout << "Precompiled value for factorial of 10 = " << x << std::endl;
    return 0;
}
```
