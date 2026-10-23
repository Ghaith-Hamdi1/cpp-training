// Chapter 22 - Project 02: R-value References
// R-value references (`&&`) bind only to r-values (temporaries / literals).
// They are the foundation of move semantics.
//
// Key points:
//   - `int& x`  is an l-value reference  (binds to named objects)
//   - `int&& x` is an r-value reference  (binds to temporaries)
//   - A *named* r-value reference variable is itself an l-value in expressions.
//   - Function overloads can distinguish l-value vs r-value arguments.

#include <iostream>
#include <string>

// -----------------------------------------------------------------------
// 1. Basic binding rules
// -----------------------------------------------------------------------
void demonstrateBinding()
{
    std::cout << "=== 1. Binding rules ===\n";

    int x = 5;

    int &lref = x; // OK: l-value ref binds to l-value
    // int& lref2 = 5;    // ERROR: l-value ref cannot bind to r-value (literal 5)

    const int &clref = 5; // OK: const l-value ref CAN bind to r-values

    int &&rref = 5; // OK: r-value ref binds to r-value (literal 5)
    // int&& rref2 = x;   // ERROR: r-value ref cannot bind to l-value

    std::cout << "lref  = " << lref << '\n';
    std::cout << "clref = " << clref << '\n';
    std::cout << "rref  = " << rref << '\n';

    // r-value references can modify the temporary they extend
    rref = 10;
    std::cout << "rref after modification = " << rref << '\n';
}

// -----------------------------------------------------------------------
// 2. Named r-value references are l-values
// -----------------------------------------------------------------------
void takeByRvalueRef(int &&val)
{
    // Even though 'val' was declared as int&&, it has a name,
    // so inside this function it is treated as an l-value.
    std::cout << "  Inside takeByRvalueRef: val = " << val << '\n';

    // This would NOT compile because 'val' is an l-value here:
    // int&& another = val;   // ERROR
}

void demonstrateNamedRvalueIsLvalue()
{
    std::cout << "\n=== 2. Named r-value ref is an l-value ===\n";
    takeByRvalueRef(42); // 42 is an r-value, binds to int&&
}

// -----------------------------------------------------------------------
// 3. Overloading on l-value vs r-value
// -----------------------------------------------------------------------
void process(const std::string &s)
{
    std::cout << "  process(const string&): received l-value \"" << s << "\"\n";
}

void process(std::string &&s)
{
    std::cout << "  process(string&&):      received r-value \"" << s << "\"\n";
}

void demonstrateOverloading()
{
    std::cout << "\n=== 3. Overloading l-value vs r-value ===\n";

    std::string name = "Alice";
    process(name);                   // calls const string& overload (l-value)
    process("Bob");                  // calls string&& overload   (r-value)
    process(std::string("Charlie")); // calls string&& overload   (r-value)
    process(std::move(name));        // calls string&& overload   (std::move casts to r-value)

    // After std::move, 'name' is in a valid but indeterminate state.
    // We can still reassign it safely:
    name = "Dave";
    std::cout << "  name after reassignment: \"" << name << "\"\n";
}

// -----------------------------------------------------------------------
// 4. R-value references extend the lifetime of temporaries
// -----------------------------------------------------------------------
std::string makeGreeting()
{
    return "Hello, World!"; // returns a temporary
}

void demonstrateLifetimeExtension()
{
    std::cout << "\n=== 4. Lifetime extension ===\n";

    // The temporary returned by makeGreeting() would normally die
    // at the end of the expression, but binding it to an r-value ref
    // extends its lifetime to the scope of 'greeting'.
    std::string &&greeting = makeGreeting();
    std::cout << "  greeting = \"" << greeting << "\" (still alive!)\n";
}

// -----------------------------------------------------------------------
int main()
{
    demonstrateBinding();
    demonstrateNamedRvalueIsLvalue();
    demonstrateOverloading();
    demonstrateLifetimeExtension();

    std::cout << "\nDone.\n";
    return 0;
}
