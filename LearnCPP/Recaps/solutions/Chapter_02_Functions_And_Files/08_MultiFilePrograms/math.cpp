// math.cpp - Definitions of the math functions declared in math.h
//
// This file is compiled separately from main.cpp.
// The linker connects the two object files.
//
// Best practice: #include the paired header ("math.h") so the compiler
// can verify that the declarations match the definitions.

#include "math.h" // Include our own header to catch mismatches early

int add(int x, int y)
{
    return x + y;
}

int multiply(int x, int y)
{
    return x * y;
}
