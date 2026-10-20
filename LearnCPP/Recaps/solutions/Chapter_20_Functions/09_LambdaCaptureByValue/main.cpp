// Chapter 20 - Project 09: Lambda Capture By Value
// =================================================
// Demonstrates: capture by value semantics, the 'mutable' keyword,
// and default capture (=).
//
// Key points:
//   - [var] captures 'var' by value - the lambda gets its own COPY.
//   - Captured-by-value variables are const by default inside the lambda.
//   - Adding 'mutable' lets you modify the copy, but the original is unchanged.
//   - [=] is a default capture that captures ALL used variables by value.
//   - Pitfall: expecting the outer variable to change when you modify a
//     captured-by-value copy - it won't.
//   - Pitfall: copies of mutable lambdas have independent state.

#include <functional>
#include <iostream>

int main()
{
    // -------------------------------------------------------
    // 1. Capture by value - the lambda gets a copy
    // -------------------------------------------------------
    int x{10};

    auto printX = [x]()
    {
        std::cout << "Captured x = " << x << '\n';
        // x = 20;  // ERROR: captured by value is const by default
    };

    x = 999;  // change the original AFTER the lambda was created
    printX(); // still prints 10 - the lambda has its own copy

    // -------------------------------------------------------
    // 2. Mutable lambda - can modify the copy
    // -------------------------------------------------------
    int counter{0};

    auto increment = [counter]() mutable
    {
        ++counter; // modifies the lambda's COPY, not the original
        std::cout << "Lambda's counter = " << counter << '\n';
    };

    increment(); // 1
    increment(); // 2
    increment(); // 3

    // The original 'counter' is still 0
    std::cout << "Original counter = " << counter << "\n\n";

    // -------------------------------------------------------
    // 3. Default capture by value [=]
    // -------------------------------------------------------
    int a{5};
    int b{10};

    auto sumAB = [=]()
    {
        // Both 'a' and 'b' captured by value automatically
        return a + b;
    };

    a = 100; // does NOT affect the lambda's copy
    std::cout << "sumAB() = " << sumAB() << " (still 15, not 110)\n\n";

    // -------------------------------------------------------
    // 4. Pitfall: copies of mutable lambdas have independent state
    // -------------------------------------------------------
    int n{0};
    auto counter2 = [n]() mutable
    {
        ++n;
        return n;
    };

    // Each copy of a mutable lambda maintains its own state
    auto copy1 = counter2;
    auto copy2 = counter2;

    std::cout << "counter2(): " << counter2() << '\n'; // 1
    std::cout << "counter2(): " << counter2() << '\n'; // 2
    std::cout << "copy1():    " << copy1() << '\n';    // 1 (independent copy)
    std::cout << "copy2():    " << copy2() << '\n';    // 1 (independent copy)

    // -------------------------------------------------------
    // 5. Pitfall: std::function copies the lambda - independent state
    // -------------------------------------------------------
    std::cout << "\n=== std::function copies the lambda ===\n";
    int count{0};
    auto mutableLambda = [count]() mutable
    {
        return ++count;
    };

    // Wrapping in std::function makes a COPY of the lambda
    std::function<int()> wrapped{mutableLambda};

    std::cout << "mutableLambda(): " << mutableLambda() << '\n'; // 1
    std::cout << "mutableLambda(): " << mutableLambda() << '\n'; // 2
    std::cout << "wrapped():       " << wrapped() << '\n';       // 1 (separate copy)
    std::cout << "wrapped():       " << wrapped() << '\n';       // 2

    // Use std::ref to share state (see Project 10 for reference captures)
    std::function<int()> shared{std::ref(mutableLambda)};
    std::cout << "\nWith std::ref:\n";
    std::cout << "mutableLambda(): " << mutableLambda() << '\n'; // 3
    std::cout << "shared():        " << shared() << '\n';        // 4 (same object!)
    std::cout << "shared():        " << shared() << '\n';        // 5

    return 0;
}
