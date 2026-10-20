// Project 01: Static vs Dynamic Libraries
// =========================================
// Appendix A.1 - Static and dynamic libraries
//
// We can't actually build/link external libraries in a single main.cpp,
// but we CAN demonstrate the *concepts* and the mental model behind them.
//
// Key ideas:
//   - A static library (.lib / .a) is linked at compile time and becomes
//     part of your executable.  Simple distribution, but larger binary and
//     no independent updates.
//
//   - A dynamic library (.dll / .so) is loaded at runtime.  Smaller binary,
//     shared across programs, independently updatable - but requires the
//     library file to be present at runtime.
//
//   - An import library is a thin static library that automates finding
//     and loading a dynamic library's functions.
//
//   - Installing any library involves 4 steps:
//       1. Acquire it (download / package manager / build from source)
//       2. Install it to a known location
//       3. Tell the compiler where its headers are (include path)
//       4. Tell the linker where its binaries are (library path + link name)
//
// This program simulates static and dynamic "linking" with function
// pointers and compile-time vs runtime binding to illustrate the difference.

#include <iostream>
#include <functional>
#include <string>

// -----------------------------------------------------------------------
// "Static library" - the implementation is compiled directly into this
// translation unit.  The code is always available; no runtime lookup needed.
// -----------------------------------------------------------------------
namespace StaticLib
{

    int add(int a, int b)
    {
        return a + b;
    }

    int multiply(int a, int b)
    {
        return a * b;
    }

} // namespace StaticLib

// -----------------------------------------------------------------------
// "Dynamic library" - we simulate runtime binding by using function pointers.
// At "load time" we resolve which function to call.  This mirrors how a
// dynamic linker resolves symbols from a .dll/.so at program start-up.
// -----------------------------------------------------------------------
namespace DynamicLib
{

    // These represent functions that live inside a shared library.
    int subtract(int a, int b)
    {
        return a - b;
    }

    int divide(int a, int b)
    {
        if (b == 0)
        {
            std::cerr << "[DynamicLib] Error: division by zero\n";
            return 0;
        }
        return a / b;
    }

    // Simulate "loading" the library at runtime - returns a function pointer.
    // In real code you'd use LoadLibrary/GetProcAddress (Windows) or
    // dlopen/dlsym (Linux).
    using MathFunc = std::function<int(int, int)>;

    MathFunc loadFunction(const std::string &name)
    {
        std::cout << "[DynamicLib] Resolving symbol '" << name << "' at runtime...\n";
        if (name == "subtract")
            return subtract;
        if (name == "divide")
            return divide;

        std::cerr << "[DynamicLib] Symbol '" << name << "' not found!\n";
        return nullptr;
    }

} // namespace DynamicLib

int main()
{
    std::cout << "=== Static vs Dynamic Libraries (Conceptual Demo) ===\n\n";

    // --- Static linking: call directly, resolved at compile time ----------
    std::cout << "--- Static Library (compile-time binding) ---\n";
    std::cout << "StaticLib::add(10, 5)      = " << StaticLib::add(10, 5) << '\n';
    std::cout << "StaticLib::multiply(10, 5) = " << StaticLib::multiply(10, 5) << '\n';

    // --- Dynamic linking: resolve symbols at "runtime" --------------------
    std::cout << "\n--- Dynamic Library (runtime binding) ---\n";

    auto subtractFunc = DynamicLib::loadFunction("subtract");
    if (subtractFunc)
        std::cout << "subtract(10, 5) = " << subtractFunc(10, 5) << '\n';

    auto divideFunc = DynamicLib::loadFunction("divide");
    if (divideFunc)
        std::cout << "divide(10, 5)   = " << divideFunc(10, 5) << '\n';

    // Attempt to load a symbol that doesn't exist
    auto missingFunc = DynamicLib::loadFunction("modulo");
    if (!missingFunc)
        std::cout << "(symbol 'modulo' was not found - load failed)\n";

    // --- Summary ----------------------------------------------------------
    std::cout << "\n--- Summary ---\n";
    std::cout << "Static linking:  code baked into executable (always available).\n";
    std::cout << "Dynamic linking: code loaded at runtime (must be present on disk).\n";
    std::cout << "Import library:  thin .lib that automates dynamic loading.\n";
    std::cout << "\nLibrary setup steps:\n";
    std::cout << "  1. Acquire the library\n";
    std::cout << "  2. Install it\n";
    std::cout << "  3. Add header include path\n";
    std::cout << "  4. Add library path + link the .lib/.a\n";

    return 0;
}
