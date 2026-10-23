// Chapter 13 - Project 10: Passing and Returning Structs
// Demonstrates: pass by const reference, return by value,
//               passing temporaries, and returning multiple values via struct.

#include <cmath> // std::sqrt
#include <iostream>
#include <string>

struct Point
{
    double x{};
    double y{};
};

struct Employee
{
    int id{};
    std::string name{};
    double salary{};
};

// ============================================================================
// 1. Pass by const reference - avoids expensive copies
// ============================================================================
// Best practice: pass structs to functions by const reference.
void printPoint(const Point &p)
{
    std::cout << '(' << p.x << ", " << p.y << ')';
}

double distanceFromOrigin(const Point &p)
{
    return std::sqrt(p.x * p.x + p.y * p.y);
}

// ============================================================================
// 2. Return by value - safe and efficient (copy elision)
// ============================================================================
// Returning a struct by value is fine; the compiler typically elides the copy.
Point midpoint(const Point &a, const Point &b)
{
    return Point{(a.x + b.x) / 2.0, (a.y + b.y) / 2.0};
}

// ============================================================================
// 3. Returning multiple values from a function
// ============================================================================
// Structs let a function effectively return multiple values.
struct DivisionResult
{
    int quotient{};
    int remainder{};
};

DivisionResult divide(int dividend, int divisor)
{
    return {dividend / divisor, dividend % divisor};
}

// ============================================================================
// 4. Passing temporary (unnamed) struct objects
// ============================================================================
void printEmployee(const Employee &emp)
{
    std::cout << emp.id << ": " << emp.name << " ($" << emp.salary << ")\n";
}

int main()
{
    // --- Pass by const reference ---
    std::cout << "=== Pass by Const Reference ===\n";
    Point p1{3.0, 4.0};
    std::cout << "p1 = ";
    printPoint(p1);
    std::cout << ", distance from origin = " << distanceFromOrigin(p1) << '\n';

    // --- Return by value ---
    std::cout << "\n=== Return by Value ===\n";
    Point p2{1.0, 2.0};
    Point p3{5.0, 8.0};
    Point mid{midpoint(p2, p3)};
    std::cout << "Midpoint of ";
    printPoint(p2);
    std::cout << " and ";
    printPoint(p3);
    std::cout << " = ";
    printPoint(mid);
    std::cout << '\n';

    // --- Multiple return values ---
    std::cout << "\n=== Multiple Return Values ===\n";
    DivisionResult result{divide(17, 5)};
    std::cout << "17 / 5 = " << result.quotient
              << " remainder " << result.remainder << '\n';

    // --- Passing temporaries (unnamed objects) ---
    std::cout << "\n=== Passing Temporary Structs ===\n";
    // No need to create a named variable - pass the struct directly:
    printEmployee({200, "Temp Worker", 30000.0});

    // You can also pass a temporary to functions expecting const ref:
    std::cout << "Distance from (6,8): "
              << distanceFromOrigin(Point{6.0, 8.0}) << '\n';

    // --- PITFALL: never return a local struct by reference! ---
    // const Point& bad() { Point p{1,2}; return p; } // DANGLING REFERENCE!
    // The local struct is destroyed when the function ends.

    return 0;
}
