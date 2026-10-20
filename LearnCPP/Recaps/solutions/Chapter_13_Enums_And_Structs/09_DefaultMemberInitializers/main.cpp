// Chapter 13 - Project 09: Default Member Initializers
// Demonstrates: providing defaults inside the struct definition,
//               explicit initializers overriding defaults,
//               and why you should always provide defaults.

#include <iostream>
#include <string>

// ============================================================================
// 1. Default member initializers
// ============================================================================
// Each member can have a default value right in the struct definition.
// If a member is not explicitly initialized, its default is used.
struct Rectangle
{
    double width{1.0};  // default: 1.0
    double height{1.0}; // default: 1.0
    std::string color{"black"};
};

// ============================================================================
// 2. Struct WITHOUT defaults - dangerous!
// ============================================================================
struct UnsafePoint
{
    double x; // no default - will be uninitialized if no init list provided!
    double y; // no default
};

void printRect(const Rectangle &r)
{
    std::cout << r.width << " x " << r.height
              << " (" << r.color << ")\n";
}

int main()
{
    // ========================================================================
    // Default member initializers in action
    // ========================================================================
    std::cout << "=== Default Member Initializers ===\n";

    // Value initialization - all members get their defaults.
    Rectangle r1{};
    std::cout << "r1 (all defaults): ";
    printRect(r1); // 1 x 1 (black)

    // Partial initialization - provided values override defaults.
    Rectangle r2{5.0, 3.0};
    std::cout << "r2 (partial init):  ";
    printRect(r2); // 5 x 3 (black) - color keeps default

    // Full initialization - all defaults overridden.
    Rectangle r3{10.0, 4.0, "red"};
    std::cout << "r3 (full init):     ";
    printRect(r3); // 10 x 4 (red)

    // ========================================================================
    // Explicit init always overrides default
    // ========================================================================
    std::cout << "\n=== Override Defaults ===\n";
    Rectangle r4{.color = "blue"}; // width and height keep defaults
    std::cout << "r4 (only color set): ";
    printRect(r4); // 1 x 1 (blue)

    // ========================================================================
    // Why defaults matter: UnsafePoint without braces
    // ========================================================================
    std::cout << "\n=== Danger: No Defaults ===\n";

    // UnsafePoint p1;  // default init - x and y are UNINITIALIZED!
    //                   // Reading them is undefined behavior.

    UnsafePoint p2{}; // value init - x and y are zero-initialized (safe)
    std::cout << "p2 (value-init): (" << p2.x << ", " << p2.y << ")\n";

    // LESSON: Always provide default member initializers to prevent
    // uninitialized variables when users forget braces.

    // ========================================================================
    // Re-assignment preserves type; new defaults apply
    // ========================================================================
    std::cout << "\n=== Re-assignment ===\n";
    r1 = {7.0}; // width=7.0, height=1.0 (default), color="black" (default)
    std::cout << "r1 after re-assign: ";
    printRect(r1);

    return 0;
}
