// Chapter 20 - Project 10: Lambda Capture By Reference
// =====================================================
// Demonstrates: capture by reference, default reference capture (&),
// mixing value and reference captures, and the dangling-reference pitfall.
//
// Key points:
//   - [&var] captures 'var' by reference - modifications affect the original.
//   - [&] is a default capture that captures ALL used variables by reference.
//   - You can mix: [=, &x] captures x by reference, everything else by value.
//   - CRITICAL pitfall: if the referenced variable goes out of scope before
//     the lambda is called, you get a dangling reference → undefined behavior.

#include <functional>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    // -------------------------------------------------------
    // 1. Capture by reference - modifies the original
    // -------------------------------------------------------
    int total{0};

    auto addToTotal = [&total](int value)
    {
        total += value; // modifies the ORIGINAL 'total'
    };

    addToTotal(10);
    addToTotal(20);
    addToTotal(30);
    std::cout << "total after three adds: " << total << '\n'; // 60

    // -------------------------------------------------------
    // 2. Default capture by reference [&]
    // -------------------------------------------------------
    int a{1};
    int b{2};
    int c{3};

    auto sumAll = [&]()
    {
        return a + b + c; // all captured by reference
    };

    a = 100;
    std::cout << "sumAll() after changing a to 100: " << sumAll() << '\n'; // 105

    // -------------------------------------------------------
    // 3. Mixed capture: some by value, some by reference
    // -------------------------------------------------------
    int multiplier{3};
    int result{0};

    // Capture 'multiplier' by value (fixed at lambda creation time)
    // Capture 'result' by reference (so we can write to it)
    auto compute = [multiplier, &result](int input)
    {
        result = input * multiplier;
    };

    multiplier = 999; // doesn't affect the lambda's copy
    compute(7);
    std::cout << "result = " << result << " (7 * 3, not 7 * 999)\n";

    // -------------------------------------------------------
    // 4. Using reference captures to accumulate in algorithms
    // -------------------------------------------------------
    std::vector<int> nums{1, 2, 3, 4, 5};
    int sum{0};

    std::for_each(nums.begin(), nums.end(), [&sum](int n)
                  { sum += n; });
    std::cout << "\nSum of {1..5}: " << sum << '\n';

    // -------------------------------------------------------
    // 5. Dangling reference pitfall (demonstrated safely)
    // -------------------------------------------------------
    // The function below creates a lambda that captures a local variable
    // by reference.  Once the function returns, that local is destroyed,
    // and calling the lambda would be undefined behavior.

    // std::function<int()> makeDanglingLambda()
    // {
    //     int local{ 42 };
    //     return [&local]() { return local; };  // DANGER: 'local' destroyed on return!
    // }

    // Instead, capture by VALUE to be safe when the lambda outlives the variable:
    auto makeSafeLambda = []() -> std::function<int()>
    {
        int local{42};
        return [local]()
        { return local; }; // SAFE: lambda owns a copy
    };

    auto safeLambda = makeSafeLambda();
    std::cout << "\nSafe lambda returns: " << safeLambda() << " (captured by value)\n";

    // -------------------------------------------------------
    // 6. Capture 'this' by reference (brief demo with a struct)
    // -------------------------------------------------------
    struct Counter
    {
        int count{0};

        auto makeIncrementer()
        {
            // [this] captures the object pointer by value,
            // giving access to member variables by reference.
            return [this]()
            { ++count; };
        }
    };

    Counter ctr;
    auto inc = ctr.makeIncrementer();
    inc();
    inc();
    inc();
    std::cout << "Counter after 3 increments: " << ctr.count << '\n';

    return 0;
}
