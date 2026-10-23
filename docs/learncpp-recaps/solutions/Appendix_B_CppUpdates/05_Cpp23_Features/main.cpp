// Appendix B - C++ Updates: Project 05 - C++23 Features
// C++23 continues to modernize C++ with quality-of-life improvements.
// Some features require very recent compilers (MSVC 17.7+, GCC 13+, Clang 17+).
// We use #if checks to gracefully handle unavailable features.

#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <cmath>
#include <utility> // std::to_underlying (C++23)
#include <numeric>

// ============================================================================
// Feature detection: Check what C++23 features are available
// ============================================================================

// Check for std::print support (<print> header)
#if __has_include(<print>)
#include <print>
#define HAS_STD_PRINT 1
#else
#define HAS_STD_PRINT 0
#endif

// Check C++ standard version
#if defined(_MSVC_LANG)
#define CPP_VERSION _MSVC_LANG
#else
#define CPP_VERSION __cplusplus
#endif

// ============================================================================
// 1. std::to_underlying
// ============================================================================
// Before C++23: Converting a scoped enum to its underlying type required:
//   static_cast<std::underlying_type_t<MyEnum>>(value)
// Way too verbose! Now: std::to_underlying(value) does the same thing.

enum class Severity : int
{
    Low = 1,
    Medium = 5,
    High = 10,
    Critical = 100
};
enum class Color : unsigned char
{
    Red = 0,
    Green = 1,
    Blue = 2
};
enum class Permission : unsigned int
{
    Read = 0b001,
    Write = 0b010,
    Execute = 0b100
};

// ============================================================================
// 2. constexpr improvements - more functions are constexpr in C++23
// ============================================================================
// C++23 makes many more standard library functions constexpr, including
// some <cmath> functions and std::unique_ptr operations.

// constexpr math: compile-time absolute value and power
constexpr double constexprAbs(double x)
{
    return x < 0 ? -x : x;
}

constexpr double constexprPow(double base, int exp)
{
    double result = 1.0;
    bool negative = exp < 0;
    if (negative)
        exp = -exp;
    for (int i = 0; i < exp; ++i)
        result *= base;
    return negative ? 1.0 / result : result;
}

// Compile-time check: verify computation at compile time
constexpr double piApprox = 3.14159265358979;
static_assert(constexprAbs(-42.0) == 42.0, "constexpr abs should work at compile time");
static_assert(constexprPow(2.0, 10) == 1024.0, "constexpr pow should work at compile time");

// ============================================================================
// 3. if consteval (C++23)
// ============================================================================
// Before C++23: Inside a constexpr function, there was no standard way to detect
// whether you were actually executing at compile time vs runtime.
// Now: 'if consteval { ... }' runs one branch at compile time, another at runtime.

#if CPP_VERSION >= 202302L
constexpr double safeSqrt(double x)
{
    if consteval
    {
        // Compile-time path: use our own implementation
        // (We can't call non-constexpr std::sqrt at compile time)
        if (x < 0)
            return -1.0; // Signal error
        double guess = x / 2.0;
        for (int i = 0; i < 50; ++i)
            guess = (guess + x / guess) / 2.0; // Newton's method
        return guess;
    }
    else
    {
        // Runtime path: use the optimized standard library version
        return std::sqrt(x);
    }
}
#endif

// ============================================================================
// 4. Deducing this (C++23) - explicit object parameter
// ============================================================================
// Before C++23: To write a member function that works with both const and
// non-const objects, you had to duplicate the function (const and non-const
// overloads). With CRTP, you needed ugly casting.
// Now: 'this' can be an explicit parameter, enabling deduction.

#if CPP_VERSION >= 202302L
struct TextBuffer
{
    std::string content = "Hello, deducing this!";

    // Single function handles both const and non-const access
    // 'self' is deduced as const TextBuffer& or TextBuffer& based on caller
    auto &&getText(this auto &&self)
    {
        return std::forward<decltype(self)>(self).content;
    }
};
#endif

// ============================================================================
// 5. Multidimensional subscript operator (C++23)
// ============================================================================
// Before C++23: matrix[i][j] required operator[] to return a proxy object.
// Or you used matrix(i,j) with operator(). Neither was ideal.
// Now: operator[] can take multiple arguments: matrix[i, j]

#if CPP_VERSION >= 202302L
class Matrix
{
    std::vector<double> data;
    std::size_t rows, cols;

public:
    Matrix(std::size_t r, std::size_t c)
        : data(r * c, 0.0), rows{r}, cols{c} {}

    // C++23: multi-dimensional subscript
    double &operator[](std::size_t r, std::size_t c)
    {
        return data[r * cols + c];
    }
    double operator[](std::size_t r, std::size_t c) const
    {
        return data[r * cols + c];
    }

    std::size_t numRows() const { return rows; }
    std::size_t numCols() const { return cols; }
};
#endif

int main()
{
    std::cout << "=== Appendix B: C++23 Features ===\n\n";

    // Print which standard we're compiling with
    std::cout << "Compiler C++ standard version: " << CPP_VERSION << '\n';
    if (CPP_VERSION >= 202302L)
        std::cout << "Status: Full C++23 support detected!\n\n";
    else if (CPP_VERSION >= 202002L)
        std::cout << "Status: C++20 mode - some C++23 features may be unavailable.\n\n";
    else
        std::cout << "Status: Pre-C++20 - most C++23 features will be skipped.\n\n";

    // ========================================================================
    // 1. std::print (C++23)
    // ========================================================================
    std::cout << "--- 1. std::print ---\n";
#if HAS_STD_PRINT
    // std::print uses Python-like format strings with {} placeholders.
    // Before C++23: std::cout << "x = " << x << ", y = " << y << '\n';
    // Now: std::print("x = {}, y = {}\n", x, y);  - much cleaner!
    std::print("  std::print is available! This is {} {}\n", "C++23", "magic!");
    std::print("  Formatted: int={}, double={:.2f}, string=\"{}\"\n", 42, 3.14159, "hello");
    std::println("  std::println adds a newline automatically");

    // Positional and fill/alignment
    std::print("  Padded: [{:>10}] [{:<10}] [{:^10}]\n", "right", "left", "center");
#else
    std::cout << "  std::print is NOT available (need <print> header, C++23 compiler).\n";
    std::cout << "  It provides Python-like formatting: std::print(\"x = {}\", 42);\n";
    std::cout << "  Replaces verbose std::cout << chains with clean format strings.\n";
    std::cout << "  Also: std::println() adds a newline automatically.\n";
#endif
    std::cout << '\n';

    // ========================================================================
    // 2. std::to_underlying
    // ========================================================================
    std::cout << "--- 2. std::to_underlying ---\n";

    Severity sev = Severity::High;
    Color col = Color::Blue;

    // Before C++23 (verbose way):
    auto sevOld = static_cast<std::underlying_type_t<Severity>>(sev);
    std::cout << "  Old way: static_cast<underlying_type_t<Severity>>(High) = " << sevOld << '\n';

    // C++23 way - clean and concise:
    auto sevNew = std::to_underlying(sev);
    auto colVal = std::to_underlying(col);
    std::cout << "  New way: std::to_underlying(Severity::High)  = " << sevNew << '\n';
    std::cout << "  std::to_underlying(Color::Blue)     = " << static_cast<int>(colVal) << '\n';

    // Practical use: combining flag enums
    auto readWrite = std::to_underlying(Permission::Read) | std::to_underlying(Permission::Write);
    std::cout << "  Read|Write permissions = 0b";
    // Print binary representation
    for (int i = 2; i >= 0; --i)
        std::cout << ((readWrite >> i) & 1);
    std::cout << " (" << readWrite << ")\n";
    std::cout << '\n';

    // ========================================================================
    // 3. constexpr math (compile-time computation)
    // ========================================================================
    std::cout << "--- 3. constexpr math ---\n";

    // These computations happen entirely at compile time
    constexpr double abs_result = constexprAbs(-3.14);
    constexpr double pow_result = constexprPow(2.0, 10);
    constexpr double pow_neg = constexprPow(2.0, -3);

    std::cout << "  constexprAbs(-3.14)  = " << abs_result << " (compile-time)\n";
    std::cout << "  constexprPow(2, 10)  = " << pow_result << " (compile-time)\n";
    std::cout << "  constexprPow(2, -3)  = " << pow_neg << " (compile-time)\n";

    // Proof it's compile-time: use in a constexpr context
    constexpr int lookupSize = static_cast<int>(constexprPow(2, 8)); // 256
    std::cout << "  Array size (compile-time): " << lookupSize << '\n';

    // C++23 extends constexpr to more <cmath> functions
    std::cout << "  C++23 adds constexpr to std::abs, std::ceil, std::floor, etc.\n";
    std::cout << '\n';

    // ========================================================================
    // 4. if consteval
    // ========================================================================
    std::cout << "--- 4. if consteval ---\n";
#if CPP_VERSION >= 202302L
    // At runtime, safeSqrt uses std::sqrt (fast, hardware-accelerated)
    double runtimeResult = safeSqrt(144.0);
    std::cout << "  safeSqrt(144.0) at runtime = " << runtimeResult << '\n';

    // At compile time, safeSqrt uses Newton's method
    constexpr double compileResult = safeSqrt(144.0);
    std::cout << "  safeSqrt(144.0) at compile-time = " << compileResult << '\n';
    std::cout << "  (Compile-time used Newton's method; runtime used std::sqrt)\n";
#else
    std::cout << "  'if consteval' requires C++23.\n";
    std::cout << "  It lets constexpr functions detect whether they're running\n";
    std::cout << "  at compile time or runtime, and choose different code paths.\n";
    std::cout << "  Example: Use Newton's method at compile time, std::sqrt at runtime.\n";
#endif
    std::cout << '\n';

    // ========================================================================
    // 5. Deducing this
    // ========================================================================
    std::cout << "--- 5. Deducing this (explicit object parameter) ---\n";
#if CPP_VERSION >= 202302L
    TextBuffer buf;
    std::cout << "  Mutable access: " << buf.getText() << '\n';

    const TextBuffer constBuf;
    std::cout << "  Const access:   " << constBuf.getText() << '\n';
    std::cout << "  One function handles both const and non-const!\n";
#else
    std::cout << "  'Deducing this' requires C++23.\n";
    std::cout << "  Syntax: auto&& getText(this auto&& self) { return self.content; }\n";
    std::cout << "  Eliminates the need for const/non-const overload pairs.\n";
    std::cout << "  Also simplifies CRTP and recursive lambdas.\n";
#endif
    std::cout << '\n';

    // ========================================================================
    // 6. Multidimensional operator[]
    // ========================================================================
    std::cout << "--- 6. Multidimensional operator[] ---\n";
#if CPP_VERSION >= 202302L
    Matrix mat(3, 3);
    // C++23: natural matrix syntax with multiple subscript arguments
    mat[0, 0] = 1.0;
    mat[0, 1] = 2.0;
    mat[0, 2] = 3.0;
    mat[1, 0] = 4.0;
    mat[1, 1] = 5.0;
    mat[1, 2] = 6.0;
    mat[2, 0] = 7.0;
    mat[2, 1] = 8.0;
    mat[2, 2] = 9.0;

    std::cout << "  3x3 Matrix:\n";
    for (std::size_t r = 0; r < mat.numRows(); ++r)
    {
        std::cout << "    ";
        for (std::size_t c = 0; c < mat.numCols(); ++c)
            std::cout << mat[r, c] << ' ';
        std::cout << '\n';
    }
#else
    std::cout << "  Multidimensional operator[] requires C++23.\n";
    std::cout << "  Before: matrix(i, j) using operator() or proxy objects.\n";
    std::cout << "  Now:    matrix[i, j] is valid - operator[] accepts multiple args.\n";
    std::cout << "  Makes matrix and tensor classes feel natural.\n";
#endif
    std::cout << '\n';

    // ========================================================================
    // 7. OTHER C++23 HIGHLIGHTS
    // ========================================================================
    std::cout << "--- 7. Other C++23 highlights ---\n";
    std::cout << "  std::expected<T,E>:  Like optional but carries error info on failure.\n";
    std::cout << "  std::flat_map:       Cache-friendly sorted associative container.\n";
    std::cout << "  std::generator:      Coroutine-based lazy sequence generator.\n";
    std::cout << "  std::stacktrace:     Programmatic access to the call stack.\n";
    std::cout << "  std::mdspan:         Multidimensional view over contiguous memory.\n";
    std::cout << "  Literal suffixes:    uz for size_t: auto x = 42uz;\n";
    std::cout << "  constexpr growth:    More <cmath>, <algorithm> functions are constexpr.\n";
    std::cout << "  Ranges improvements: zip, chunk, slide, cartesian_product views.\n";

    std::cout << "\n=== C++23 demo complete ===\n";

    return 0;
}
