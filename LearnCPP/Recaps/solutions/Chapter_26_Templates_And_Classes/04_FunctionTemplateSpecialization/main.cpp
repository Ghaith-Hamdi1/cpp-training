// Chapter 26 - Project 4: Function Template Specialization
// ===========================================================
// When a template function needs different behavior for a specific type,
// you have two options:
//
//   1. **Non-template function overload (PREFERRED)**
//      - Takes highest priority during overload resolution.
//      - Simpler syntax, doesn't need to match the primary template exactly.
//
//   2. **Full template specialization** using `template<>`
//      - Provides a custom implementation for one specific type.
//      - Must match the primary template's signature.
//      - Full specializations are NOT implicitly inline - mark them inline
//        if they appear in a header to avoid ODR violations.
//
// You CANNOT partially specialize function templates. Only classes support
// partial specialization.

#include <iostream>
#include <string>

// ---------------------------------------------------------------------------
// Primary function template
// ---------------------------------------------------------------------------
template <typename T>
void printValue(const T &value)
{
    std::cout << "[generic]      " << value << '\n';
}

// ---------------------------------------------------------------------------
// Option 1 (PREFERRED): Non-template overload for const char*
// ---------------------------------------------------------------------------
// This is a plain function, not a specialization. It takes priority over
// any template match involving const char*.
void printValue(const char *value)
{
    std::cout << "[overload]     \"" << value << "\"\n";
}

// ---------------------------------------------------------------------------
// Option 2: Full template specialization for std::string
// ---------------------------------------------------------------------------
// Note the `template<>` - this tells the compiler we are specializing
// the primary template for T = std::string.
template <>
// In a header this would need `inline` to be ODR-safe:
//   template <> inline void printValue<std::string>(...)
void printValue<std::string>(const std::string &value)
{
    std::cout << "[specialized]  length=" << value.size()
              << "  \"" << value << "\"\n";
}

// ---------------------------------------------------------------------------
int main()
{
    printValue(42);                   // generic (T = int)
    printValue(3.14);                 // generic (T = double)
    printValue("hello");              // overload (const char*)
    printValue(std::string("world")); // specialization (std::string)

    std::cout << "\n--- Resolution order ---\n";
    std::cout << "1. Non-template overload  (highest priority)\n";
    std::cout << "2. Full template specialization\n";
    std::cout << "3. Primary template       (lowest priority)\n";

    // PITFALL: You cannot partially specialize a function template.
    // The following would be illegal:
    //
    //   template <typename T>
    //   void printValue<T*>(T* value) { ... }   // ERROR: partial spec of function
    //
    // Instead, use a non-template overload or partially specialize the
    // enclosing class.

    return 0;
}
