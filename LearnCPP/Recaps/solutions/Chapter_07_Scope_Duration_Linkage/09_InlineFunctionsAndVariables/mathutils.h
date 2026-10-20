// mathutils.h - Inline functions and variables defined in a header
// Both main.cpp and other.cpp include this header.
// Without 'inline', the linker would complain about multiple definitions.

#ifndef MATHUTILS_H
#define MATHUTILS_H

namespace MathUtils
{
    // -------------------------------------------------
    // Inline variable - one shared instance across all translation units
    // -------------------------------------------------
    // C++17: 'inline' on a variable means the linker will keep only one copy,
    // even though every .cpp that includes this header has its own "definition."
    inline constexpr double pi{3.14159265358979};

    // -------------------------------------------------
    // Inline function - one shared definition across all translation units
    // -------------------------------------------------
    // 'inline' tells the linker that multiple definitions (one per .cpp)
    // are intentional and identical - keep just one.
    inline int square(int x)
    {
        return x * x;
    }

    // Functions defined inside a class body are implicitly inline.
    // Standalone functions in headers need the 'inline' keyword explicitly.
    inline int cube(int x)
    {
        return x * x * x;
    }

} // namespace MathUtils

#endif
