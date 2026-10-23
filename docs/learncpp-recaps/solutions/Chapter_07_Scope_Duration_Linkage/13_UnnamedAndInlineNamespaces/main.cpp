// Chapter 7 - Project 13: Unnamed and Inline Namespaces
// =======================================================
// UNNAMED NAMESPACES:
//   - Give all their content INTERNAL LINKAGE (file-local)
//   - Modern C++ replacement for 'static' on globals/functions
//   - Also work for types, enums, etc. (which 'static' cannot do)
//
// INLINE NAMESPACES:
//   - Make their content accessible as part of the PARENT namespace
//   - Useful for API versioning - the inline version is the "default"
//   - Can combine with unnamed namespaces for internal-linkage versioned content

#include <iostream>
#include <string_view>

// -------------------------------------------------
// 1. Unnamed namespace - everything inside has internal linkage
// -------------------------------------------------
// These identifiers are only visible in this translation unit.
// Same effect as 'static', but also works for types and enums.
namespace
{
    int secretCounter{0};

    void incrementSecret()
    {
        ++secretCounter;
    }

    // 'static' cannot give internal linkage to a struct/enum,
    // but unnamed namespaces can:
    struct InternalData
    {
        int x{};
        int y{};
    };

    enum class InternalColor
    {
        Red,
        Green,
        Blue
    };
}

// -------------------------------------------------
// 2. Inline namespace - content is part of the parent namespace
// -------------------------------------------------
namespace MyLibrary
{
    // The inline namespace is the "default" version
    inline namespace V2
    {
        std::string_view getVersion()
        {
            return "2.0 (current/default)";
        }

        int compute(int x)
        {
            return x * x; // V2: squares the input
        }
    }

    namespace V1
    {
        std::string_view getVersion()
        {
            return "1.0 (legacy)";
        }

        int compute(int x)
        {
            return x + x; // V1: doubles the input
        }
    }
}

// -------------------------------------------------
// 3. API versioning pattern in practice
// -------------------------------------------------
namespace Graphics
{
    // V1 - original API
    namespace V1
    {
        void render(std::string_view shape)
        {
            std::cout << "    [V1] Rendering " << shape << " (software renderer)\n";
        }
    }

    // V2 - improved API (inline = default)
    inline namespace V2
    {
        void render(std::string_view shape)
        {
            std::cout << "    [V2] Rendering " << shape << " (GPU accelerated)\n";
        }
    }
}

int main()
{
    // -------------------------------------------------
    // 1. Unnamed namespace - internal linkage
    // -------------------------------------------------
    std::cout << "1. Unnamed namespace (internal linkage):\n";
    incrementSecret();
    incrementSecret();
    incrementSecret();
    std::cout << "   secretCounter = " << secretCounter << '\n';

    InternalData data{10, 20};
    std::cout << "   InternalData: x=" << data.x << ", y=" << data.y << '\n';

    InternalColor color{InternalColor::Green};
    std::cout << "   InternalColor::Green = " << static_cast<int>(color) << '\n';
    std::cout << "   (All of these are file-local - invisible to other .cpp files)\n";

    // -------------------------------------------------
    // 2. Inline namespace - default version
    // -------------------------------------------------
    std::cout << "\n2. Inline namespace (default version):\n";

    // MyLibrary::getVersion() resolves to MyLibrary::V2::getVersion()
    // because V2 is the inline (default) namespace
    std::cout << "   MyLibrary::getVersion()     = " << MyLibrary::getVersion() << '\n';
    std::cout << "   MyLibrary::V2::getVersion() = " << MyLibrary::V2::getVersion() << '\n';
    std::cout << "   MyLibrary::V1::getVersion() = " << MyLibrary::V1::getVersion() << '\n';

    std::cout << "\n   MyLibrary::compute(5) (default=V2) = "
              << MyLibrary::compute(5) << '\n'; // 25 (V2: x*x)
    std::cout << "   MyLibrary::V1::compute(5)           = "
              << MyLibrary::V1::compute(5) << '\n'; // 10 (V1: x+x)

    // -------------------------------------------------
    // 3. API versioning in practice
    // -------------------------------------------------
    std::cout << "\n3. API versioning with inline namespaces:\n";

    // Users call Graphics::render() - gets the latest (V2) by default
    Graphics::render("Circle");

    // If they need the old behavior, they can specify V1 explicitly
    Graphics::V1::render("Circle");

    // When V3 is released, change 'inline' from V2 to V3 - all users
    // who call Graphics::render() automatically get the new version.

    // -------------------------------------------------
    // 4. Unnamed namespace vs. static
    // -------------------------------------------------
    std::cout << "\n4. Unnamed namespace vs. static keyword:\n";
    std::cout << "   static int x;       -> internal linkage (variables/functions only)\n";
    std::cout << "   namespace { int x; } -> internal linkage (EVERYTHING: vars, types, enums)\n";
    std::cout << "   Prefer unnamed namespaces in modern C++.\n";

    // -------------------------------------------------
    // Summary
    // -------------------------------------------------
    std::cout << "\n--- Summary ---\n";
    std::cout << "  Unnamed namespace: gives internal linkage to ALL content\n";
    std::cout << "  Inline namespace:  content is part of the parent namespace\n";
    std::cout << "  Use inline ns for API versioning (default version = inline)\n";
    std::cout << "  Users can still access old versions explicitly (NS::V1::func)\n";

    return 0;
}
