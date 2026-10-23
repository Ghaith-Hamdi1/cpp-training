// Chapter 27 - Project 12: std::move_if_noexcept
// =================================================
// std::move_if_noexcept(x) returns:
//   - An rvalue reference (enabling move) if x's move constructor is noexcept
//   - An lvalue reference (forcing copy) if x's move constructor could throw
//
// Why? To preserve the strong exception guarantee:
//   - If we're moving elements (e.g., during vector reallocation) and a move
//     fails midway, the source objects are in a moved-from state - we can't
//     recover. The operation has partially succeeded.
//   - If we copy instead, a failure leaves the originals intact - we can
//     roll back cleanly.
//
// The standard library (std::vector::resize, push_back, etc.) uses
// std::move_if_noexcept internally to pick the safest + fastest strategy.

#include <iostream>
#include <string>
#include <utility> // std::move_if_noexcept
#include <vector>
#include <type_traits>

// --- Class with a noexcept move constructor ---
class SafeMover
{
    std::string m_name;

public:
    SafeMover(const std::string &name) : m_name{name} {}

    // Copy constructor
    SafeMover(const SafeMover &other) : m_name{other.m_name}
    {
        std::cout << "  SafeMover COPIED: " << m_name << '\n';
    }

    // Move constructor - noexcept!
    SafeMover(SafeMover &&other) noexcept : m_name{std::move(other.m_name)}
    {
        std::cout << "  SafeMover MOVED: " << m_name << '\n';
    }

    const std::string &name() const { return m_name; }
};

// --- Class with a potentially-throwing move constructor ---
class UnsafeMover
{
    std::string m_name;

public:
    UnsafeMover(const std::string &name) : m_name{name} {}

    // Copy constructor
    UnsafeMover(const UnsafeMover &other) : m_name{other.m_name}
    {
        std::cout << "  UnsafeMover COPIED: " << m_name << '\n';
    }

    // Move constructor - NOT noexcept (could throw)
    UnsafeMover(UnsafeMover &&other) : m_name{std::move(other.m_name)}
    {
        std::cout << "  UnsafeMover MOVED: " << m_name << '\n';
    }

    const std::string &name() const { return m_name; }
};

int main()
{
    std::cout << std::boolalpha;

    // --- Check noexcept traits ---
    std::cout << "=== noexcept move constructor checks ===\n";
    std::cout << "SafeMover   is_nothrow_move_constructible: "
              << std::is_nothrow_move_constructible_v<SafeMover> << '\n';
    std::cout << "UnsafeMover is_nothrow_move_constructible: "
              << std::is_nothrow_move_constructible_v<UnsafeMover> << '\n';

    // --- std::move_if_noexcept behavior ---
    std::cout << "\n=== std::move_if_noexcept behavior ===\n";

    SafeMover safe{"safe_object"};
    UnsafeMover unsafe{"unsafe_object"};

    // For SafeMover: move_if_noexcept returns rvalue ref → MOVE happens
    std::cout << "\nUsing move_if_noexcept on SafeMover:\n";
    SafeMover s2{std::move_if_noexcept(safe)};

    // For UnsafeMover: move_if_noexcept returns lvalue ref → COPY happens
    std::cout << "\nUsing move_if_noexcept on UnsafeMover:\n";
    UnsafeMover u2{std::move_if_noexcept(unsafe)};

    // --- Impact on std::vector ---
    std::cout << "\n=== std::vector reallocation with SafeMover ===\n";
    std::cout << "(vector MOVES elements because move ctor is noexcept)\n\n";
    {
        std::vector<SafeMover> vec;
        vec.reserve(2);
        vec.emplace_back("A");
        vec.emplace_back("B");
        std::cout << "-- Reallocation triggered: --\n";
        vec.emplace_back("C"); // existing A and B are MOVED
    }

    std::cout << "\n=== std::vector reallocation with UnsafeMover ===\n";
    std::cout << "(vector COPIES elements because move ctor may throw)\n\n";
    {
        std::vector<UnsafeMover> vec;
        vec.reserve(2);
        vec.emplace_back("X");
        vec.emplace_back("Y");
        std::cout << "-- Reallocation triggered: --\n";
        vec.emplace_back("Z"); // existing X and Y are COPIED (not moved!)
    }

    // --- Key takeaway ---
    std::cout << "\n=== Takeaway ===\n";
    std::cout << "Always mark move constructors noexcept.\n";
    std::cout << "This lets the standard library use move instead of copy,\n";
    std::cout << "giving you both safety (strong exception guarantee)\n";
    std::cout << "and performance (move is typically O(1)).\n";

    return 0;
}
