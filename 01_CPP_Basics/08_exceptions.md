# Exceptions

## Why Exceptions?

- Exceptions decouple handling errors from the typical code flow

## Basic mechanism

- To trigger an exception: `throw`
- To handle an exception: `try ... catch ...`

## Exception from a called function

- Stack unwinding: may not happen if no exception handler is found (something to avoid)

## Exception dangers and downsides

- Cleaning up resources: be sure to clean allocated data and resources
- Performance price to pay when an exception is thrown

## "noexcept" specifier

- Used to specify that a given function doesn't throw an exception
- Exception can be handled locally in a `noexcept` function
- `std::terminate` is called if the function throws an exception

## "noexcept" with boolean

- `noexcept(true)`, equivalent to `noexcept`, means not throwing
- `noexcept(false)` means potentially throwing

## When to use "noexcept"

- Specify that a function can be called safely without a try/catch block
- Compiler can optimize `noexcept` functions more

## Optional hint in function declaration

- `void foo() throw()` — function doesn't throw exception
- `void foo() throw(int, std::runtime_error)` — may throw one of the two types mentioned
- `void foo() throw(...)` — may throw any type

## Reference examples

`Examples/01_CPP_Basics/08_exceptions/08_exceptions.cpp`:

```cpp
#include <iostream>
#include <exception>
#include <string>

int main() {

    for (int i = 0; i < 5; i++) {
        try
        {
            // Statements that may throw exceptions you want to handle here
            switch (i)
            {
            case 0:
                throw 1;
            case 1:
            {
                double a{1.0};
                throw a;
            }
            case 2:
                throw std::string("Exception text");
            case 3:
                throw std::runtime_error("Runtime error special exception");
            case 4:
                throw 'a';
            default:
                break;
            }
        }
        catch (int x)
        {
            // Any exceptions of type exception_simple_type1 thrown within the above try block
            std::cerr << "We caught an int exception with value: " << x << std::endl;
        }
        catch (double) // no variable name since we don't use the exception itself in the catch block below
        {
            // Any exceptions of type double thrown within the above try block
            std::cerr << "We caught an exception of type double" << std::endl;
        }
        catch (const std::string&) // catch classes by const reference
        {
            // Any exceptions of type class_name thrown within the above try block
            std::cerr << "We caught an exception of type std::string" << std::endl;
        }
        catch (const std::runtime_error& name) // catch classes by const reference
        {
            // Any exceptions of type class_name2 thrown within the above try block
            std::cerr << "We caught an exception of type runtime_error " << name.what() << std::endl;
        }
        catch (...)
        {
            // Any exceptions of a type not in the list
            std::cerr << "We caught an exception of non handled type" << std::endl;
        }
    }

    return 0;
}
```

`Examples/01_CPP_Basics/08_exceptions/11_stack_unwinding.cpp` (illustrates stack unwinding across nested calls A → B → C → D):

```cpp
#include <iostream>

void D() // called by C()
{
    std::cout << "Start D" << std::endl;
    std::cout << "D throwing int exception" << std::endl;

    throw - 1;

    std::cout << "End D" << std::endl; // skipped over
}

void C() // called by B()
{
    std::cout << "Start C" << std::endl;
    D();
    std::cout << "End C" << std::endl;
}

void B() // called by A()
{
    std::cout << "Start B" << std::endl;

    try
    {
        C();
    }
    catch (double) // not caught: exception type mismatch
    {
        std::cerr << "B caught double exception" << std::endl;
    }

    try
    {
    }
    catch (int) // not caught: exception not thrown within try
    {
        std::cerr << "B caught int exception" << std::endl;
    }

    std::cout << "End B" << std::endl;
}

void A() // called by main()
{
    std::cout << "Start A" << std::endl;

    try
    {
        B();
    }
    catch (int) // exception caught here and handled
                // can change int by char and see that stack is unwound
    {
        std::cerr << "A caught int exception" << std::endl;
    }

    std::cout << "End A" << std::endl;
}

int main()
{
    std::cout << "Start main" << std::endl;

    try
    {
        A();
    }
    catch (int) // not called because exception was handled by A
                // can change int by char and see that stack is unwound
    {
        std::cerr << "main caught int exception" << std::endl;
    }
    std::cout << "End main" << std::endl;

    return 0;
}
```

---

