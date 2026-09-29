# Functions

- Reusable sequence of statements to do a particular job
  - Organize source code
  - Increase readability
  - Facilitate maintenance of code

[Diagram — extracted labels: "Function header", "Function body" (illustration of a function's signature vs. its body)]

- Function can call other functions
- Nested functions are not legal in C++

## Function return value

- Not returning value (`void`) — no return value
- Returning a type (`int`, `char`, `float`, ...)
  - `return` literal value
  - `return` variable value
- A returning function should always have a return value in every exit point, otherwise we will have undefined behavior

## Function arguments

- Need to pass data to and from functions:
  - Pass arguments by value
  - Pass arguments by address
  - Pass arguments by reference

[Diagram — extracted labels: "argument passed by value", "argument passed by value, but need to change an argument value" (illustrating pass-by-value vs. the need for pass-by-address/reference when mutation is required)]

## Special functions: Lambdas

- Anonymous functions that can be created inside another function (nesting function)

```cpp
[ captureClause ] ( parameters ) -> returnType {
    statements;
}
```

- The capture clause can be empty if no captures are needed.
- The parameter list can be empty if no parameters are required.
- The return type is optional, and if omitted, `auto` will be assumed
- Can be assigned to a variable (give a name to the lambda)
- A lambda call creates a new instance of that lambda

### Generic lambda

- Return type deduction: must have the same return type as the first return statement

### Captures

- Captures allow using variables from surrounding scope
- Capture types:
  - By constant value: `[ = ]` or `[var1, var2, .. varn]` — all the scope specific variables
  - By mutable value: `[ = ] () mutable {}` — all the object scope / all the surrounding scope specific variables
  - By reference or address: `[ this ]` or `[ & ]` or `[&var1, pointer ... &varn]`

### Lambda pitfalls

- Be careful! Dangling passed variables by reference
- Copy of lambda

## Reference example: lambdas and functions, `Examples/01_CPP_Basics/06_functions/06_functions_lambda.cpp`

```cpp
#include <iostream>
#include <functional>

int func(std::function<bool (int, float)> test_fn)
{
    if (test_fn(2, 2.0f) == true)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void myInvoke(const std::function<void()>& fn){
    fn();
}
auto sayHello(const std::string& hello) {
    // Capture name by reference and return the lambda.
    int i{0};
    auto lambda = [&]() {
        std::cout << "Say " << hello << i << '\n'; // Undefined behavior
    };
    lambda();
    i = 10;
    lambda();
    return lambda;
}

int main(){

    int a{0};
    float b{2.0f};

    std::cout << "First lambda call " << func([=](int x, float y) -> bool {
        if (x == a || y == b) {
            return true;
        }
        else {
            return false;
        }
    }) << std::endl;

    auto lambda = [&a, b] (int x, float y) -> bool {

        if (x == a || y == b) {
            a++; // a can be modified
            return true;
        }
        else {
            return false;
        }
    };

    std:: cout << "Second call " << func(lambda) << " new a value " << a << std::endl;

    int i{ 0 };
    // Increments and prints its local copy of @i.
    auto count{ [i]() mutable {
        std::cout << ++i << '\n';
    } };

    myInvoke(std::ref(count));
    myInvoke(std::ref(count));
    myInvoke(std::ref(count));

    auto sayHelloRet{ sayHello("Hello") };

    // Call the lambda function that sayHello returned.
    sayHelloRet();

    return 0;
}
```

---

