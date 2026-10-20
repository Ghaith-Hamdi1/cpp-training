// geometry.cpp - Definitions for geometry functions
// Best practice: include the paired header first to catch mismatches early.

#include "geometry.h"

// We could also #include <cmath> for std::numbers::pi in C++20,
// but a local constexpr keeps this example self-contained.
namespace
{
    constexpr double pi{3.14159265358979323846};
}

double circleArea(double radius)
{
    return pi * radius * radius;
}

double circleCircumference(double radius)
{
    return 2.0 * pi * radius;
}
