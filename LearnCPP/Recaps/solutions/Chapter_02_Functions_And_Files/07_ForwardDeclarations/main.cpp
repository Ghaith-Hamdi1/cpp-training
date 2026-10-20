// Chapter 2 - Project 07: Forward Declarations and the ODR
// Concept: Function prototypes, declarations vs. definitions, One Definition Rule
//
// A forward declaration (function prototype) tells the compiler that a
// function exists - its name, return type, and parameter types - WITHOUT
// providing the body.  This lets you call a function before its full
// definition appears in the file.
//
// Syntax:  returnType functionName(parameterTypes);   // note: no body
//
// Declarations vs. Definitions:
//   • Declaration - introduces a name to the compiler (says "this exists").
//   • Definition  - implements/instantiates the entity (provides the body).
//   • All definitions are declarations, but not all declarations are
//     definitions.
//
// One Definition Rule (ODR):
//   1. Within a file, each function/variable can have only one definition.
//   2. Within a program, each function/variable can have only one definition
//      (across all files).  Exceptions: types, templates, inline functions.
//   3. Every function/variable that is used must have exactly one definition
//      somewhere - otherwise you get a linker error.
// -----------------------------------------------------------------------

#include <iostream>

// -----------------------------------------------------------------------
// FORWARD DECLARATIONS (function prototypes)
// We declare these functions here so main() can call them,
// even though their definitions appear BELOW main().
// -----------------------------------------------------------------------
int multiply(int a, int b);      // Forward declaration
void printProduct(int a, int b); // Forward declaration

// Parameter names in prototypes are optional (only types are required).
// These two declarations are equivalent:
//   int multiply(int a, int b);
//   int multiply(int, int);
// Using names improves readability, so prefer including them.

int main()
{
    std::cout << "=== Project 07: Forward Declarations & the ODR ===\n\n";

    // We can call multiply() and printProduct() here because of the
    // forward declarations above - even though their definitions are below.
    std::cout << "multiply(6, 7) = " << multiply(6, 7) << '\n';

    printProduct(4, 5);
    printProduct(8, 3);

    // Without forward declarations, the compiler would emit an error:
    //   "identifier 'multiply' is undefined"
    // because the compiler reads top-to-bottom.

    return 0;
}

// -----------------------------------------------------------------------
// DEFINITIONS - these provide the actual implementations.
// They satisfy the forward declarations above.
// -----------------------------------------------------------------------

int multiply(int a, int b)
{
    return a * b;
}

void printProduct(int a, int b)
{
    std::cout << a << " * " << b << " = " << multiply(a, b) << '\n';
}

// -----------------------------------------------------------------------
// ODR VIOLATION EXAMPLES (commented out - would cause errors)
// -----------------------------------------------------------------------

// VIOLATION 1: Two definitions of the same function in one file.
// int multiply(int a, int b) { return a * b; }  // ERROR: redefinition

// VIOLATION 2: If multiply() were also defined in another .cpp file
// in the same project, the linker would report a "multiple definition"
// error.

// VIOLATION 3: If you declare multiply but never define it, and then
// call it, the linker reports "unresolved external symbol".
