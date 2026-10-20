// Chapter 13 - Project 08: Designated Initializers (C++20)
// Demonstrates: named member initialization with .member = value syntax,
//               skipping members, and rules/restrictions.
//
// Requires: C++20 or later

#include <iostream>
#include <string>

struct Config
{
    int width{800};
    int height{600};
    bool fullscreen{false};
    std::string title{"My App"};
};

void printConfig(const Config &cfg)
{
    std::cout << "Title:      " << cfg.title << '\n';
    std::cout << "Resolution: " << cfg.width << 'x' << cfg.height << '\n';
    std::cout << "Fullscreen: " << (cfg.fullscreen ? "yes" : "no") << '\n';
}

int main()
{
    // ========================================================================
    // 1. Basic designated initializers
    // ========================================================================
    // You explicitly name which members to initialize.
    // Members not listed use their default member initializer.
    std::cout << "=== Designated Initializers ===\n";
    Config cfg1{.width = 1920, .height = 1080, .fullscreen = true, .title = "Game"};
    printConfig(cfg1);

    // ========================================================================
    // 2. Skipping members - they keep their defaults
    // ========================================================================
    std::cout << "\n=== Skipping Members ===\n";
    // Only set title; width, height, fullscreen keep defaults.
    Config cfg2{.title = "Editor"};
    printConfig(cfg2);

    // ========================================================================
    // 3. Mixing: set some, skip others
    // ========================================================================
    std::cout << "\n=== Selective Initialization ===\n";
    Config cfg3{.width = 1280, .height = 720};
    // fullscreen defaults to false, title to "My App"
    printConfig(cfg3);

    // ========================================================================
    // 4. Rules for designated initializers
    // ========================================================================
    // a) Designators MUST be in declaration order.
    //    Config bad{ .title = "X", .width = 100 }; // ERROR: wrong order

    // b) You cannot mix designated and non-designated initializers.
    //    Config bad{ 1920, .title = "X" }; // ERROR: mixed styles

    // c) Each member can only be designated once.
    //    Config bad{ .width = 100, .width = 200 }; // ERROR: duplicate

    // ========================================================================
    // 5. Designated initializers with assignment
    // ========================================================================
    std::cout << "\n=== Re-assignment with Designated Init ===\n";
    cfg1 = {.width = 3840, .height = 2160, .title = "4K App"};
    printConfig(cfg1);

    return 0;
}
