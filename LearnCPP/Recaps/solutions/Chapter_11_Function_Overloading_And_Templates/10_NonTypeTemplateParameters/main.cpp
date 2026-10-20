// Chapter 11 - Project 10: Non-Type Template Parameters
// ================================================================
// Non-type template parameters hold constexpr VALUES (not types).
// Syntax:  template <int N>   or   template <auto N>  (C++17)
//
// Use cases:
//   - When a compile-time constant is needed inside a template
//   - static_assert with compile-time values
//   - Fixed-size containers (e.g. std::bitset<8>, std::array<int, 5>)
//   - C++20 adds support for floating-point non-type parameters

#include <iostream>
#include <array>
#include <bitset>
#include <cstdint>

// ---------------------------------------------------------------
// Example 1: Non-type template parameter for compile-time size
// ---------------------------------------------------------------
template <int N>
void printSize()
{
    // N is available at compile time - can use in static_assert
    static_assert(N > 0, "N must be positive");
    std::cout << "Size = " << N << '\n';
}

// ---------------------------------------------------------------
// Example 2: Fixed-size stack using non-type parameter
// ---------------------------------------------------------------
template <typename T, int Capacity>
struct FixedStack
{
    std::array<T, Capacity> data{};
    int top{0};

    bool push(const T &value)
    {
        if (top >= Capacity)
            return false; // full
        data[static_cast<std::size_t>(top++)] = value;
        return true;
    }

    bool pop(T &out)
    {
        if (top <= 0)
            return false; // empty
        out = data[static_cast<std::size_t>(--top)];
        return true;
    }

    int size() const { return top; }
};

// ---------------------------------------------------------------
// Example 3: auto non-type parameter (C++17)
// ---------------------------------------------------------------
template <auto Value>
void printValue()
{
    std::cout << "Value = " << Value
              << "  (type: " << typeid(Value).name() << ")\n";
}

// ---------------------------------------------------------------
// Example 4: Non-type parameter for compile-time computation
// ---------------------------------------------------------------
template <int N>
constexpr int factorial()
{
    if constexpr (N <= 1)
        return 1;
    else
        return N * factorial<N - 1>();
}

// ---------------------------------------------------------------
// Example 5: C++20 floating-point non-type parameter
// ---------------------------------------------------------------
template <double Scale>
double scaleValue(double input)
{
    return input * Scale;
}

int main()
{
    std::cout << "=== Example 1: printSize ===\n";
    printSize<5>();
    printSize<100>();
    // printSize<-1>();  // ERROR at compile time: static_assert fails

    std::cout << "\n=== Example 2: FixedStack ===\n";
    FixedStack<int, 3> stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout << "Stack size: " << stack.size() << '\n';
    std::cout << "Push to full stack: " << (stack.push(40) ? "ok" : "failed") << '\n';

    int val{};
    stack.pop(val);
    std::cout << "Popped: " << val << '\n';

    std::cout << "\n=== Example 3: auto non-type parameter (C++17) ===\n";
    printValue<42>();   // int
    printValue<'A'>();  // char
    printValue<true>(); // bool

    std::cout << "\n=== Example 4: Compile-time factorial ===\n";
    constexpr int f5 = factorial<5>();   // 120, computed at compile time
    constexpr int f10 = factorial<10>(); // 3628800
    std::cout << "5!  = " << f5 << '\n';
    std::cout << "10! = " << f10 << '\n';

    std::cout << "\n=== Example 5: Floating-point non-type parameter (C++20) ===\n";
    std::cout << "scaleValue<2.5>(4.0) = " << scaleValue<2.5>(4.0) << '\n';
    std::cout << "scaleValue<0.1>(100.0) = " << scaleValue<0.1>(100.0) << '\n';

    // Standard library examples:
    std::cout << "\n=== Standard library non-type examples ===\n";
    std::bitset<8> bits{0b10110010};
    std::cout << "bitset<8>: " << bits << '\n';

    std::array<int, 4> arr{1, 2, 3, 4};
    std::cout << "array<int,4>: ";
    for (int v : arr)
        std::cout << v << ' ';
    std::cout << '\n';

    return 0;
}
