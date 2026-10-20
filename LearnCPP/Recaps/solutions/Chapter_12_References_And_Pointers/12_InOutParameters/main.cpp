// Chapter 12 - Project 12: In and Out Parameters
// =================================================
// Parameters can serve three roles:
//
//   In parameter     - provides input to the function (pass by value or const&)
//   Out parameter    - returns data back to the caller via a non-const reference
//   In-out parameter - reads AND modifies the caller's object (non-const reference)
//
// Best practices:
//   • Prefer return values over out parameters - out params hide intent and are error-prone
//   • Use non-const reference for in-out params (when modification is the primary purpose)
//   • Document out/in-out parameters clearly

#include <iostream>
#include <string>
#include <cmath>

// ----- In parameters (read-only) -----
// Fundamental types: pass by value
// Class types: pass by const&
double circleArea(double radius) // in parameter (by value)
{
    return 3.14159265 * radius * radius;
}

void printMessage(const std::string &msg) // in parameter (by const&)
{
    std::cout << msg << '\n';
}

// ----- Out parameters (returns data via reference) -----
// Works but is discouraged - prefer return values.
// The caller provides a variable, the function writes into it.
bool divide(double numerator, double denominator, double &result) // 'result' is an out param
{
    if (denominator == 0.0)
        return false; // indicate failure

    result = numerator / denominator;
    return true; // indicate success
}

// Better alternative: return a value (or use std::optional - see Project 14)
// double divide(double a, double b) { return a / b; }

// ----- In-out parameters (read and modify) -----
// The caller provides an initial value, the function modifies it.
void clampToRange(int &value, int low, int high) // 'value' is in-out
{
    if (value < low)
        value = low;
    else if (value > high)
        value = high;
}

void normalizeAngle(double &angleDegrees) // in-out: normalizes to [0, 360)
{
    angleDegrees = std::fmod(angleDegrees, 360.0);
    if (angleDegrees < 0.0)
        angleDegrees += 360.0;
}

int main()
{
    // ----- In parameters -----
    std::cout << "=== In parameters ===\n";
    std::cout << "Area of circle (r=5): " << circleArea(5.0) << '\n';
    printMessage("Hello from an in parameter!");

    // ----- Out parameter -----
    std::cout << "\n=== Out parameter ===\n";
    double result{}; // will be written to by divide()
    if (divide(10.0, 3.0, result))
        std::cout << "10 / 3 = " << result << '\n';
    else
        std::cout << "Division failed.\n";

    if (divide(10.0, 0.0, result))
        std::cout << "10 / 0 = " << result << '\n';
    else
        std::cout << "10 / 0 = division by zero (failed).\n";

    // Note how awkward this is: we pre-declare 'result' and the call
    // doesn't make it obvious that 'result' will be modified.

    // ----- In-out parameters -----
    std::cout << "\n=== In-out parameters ===\n";
    int score{150};
    std::cout << "Before clamp: score = " << score << '\n';
    clampToRange(score, 0, 100);
    std::cout << "After  clamp: score = " << score << '\n'; // 100

    double angle{-45.0};
    std::cout << "\nBefore normalize: angle = " << angle << '\n';
    normalizeAngle(angle);
    std::cout << "After  normalize: angle = " << angle << '\n'; // 315

    return 0;
}
