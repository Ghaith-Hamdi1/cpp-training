// Chapter 25 - Project 06: Early Binding and Late Binding
// =========================================================
// Early binding (static dispatch):
//   The compiler resolves the function call at COMPILE time - it knows
//   exactly which function to call.  Direct function calls use this.
//
// Late binding (dynamic dispatch):
//   The function call is resolved at RUNTIME through an indirect mechanism
//   such as a function pointer or a virtual table.  This is slightly slower
//   but far more flexible.
//
// Virtual functions use late binding (via the vtable) to achieve polymorphism.

#include <iostream>

// ========== Early binding with direct calls ==========
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

// ========== Late binding with function pointers ==========
// A function-pointer-based calculator - the operation is chosen at runtime.
using ArithmeticFunc = int (*)(int, int); // pointer to function (int,int)->int

int calculate(int a, int b, ArithmeticFunc op)
{
    // 'op' is an indirect call - resolved at runtime (late binding).
    return op(a, b);
}

// ========== Late binding with virtual functions ==========
class Shape
{
public:
    virtual double area() const = 0; // pure virtual
    virtual const char *name() const = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape
{
    double radius;

public:
    explicit Circle(double r) : radius{r} {}
    double area() const override { return 3.14159265 * radius * radius; }
    const char *name() const override { return "Circle"; }
};

class Rectangle : public Shape
{
    double width, height;

public:
    Rectangle(double w, double h) : width{w}, height{h} {}
    double area() const override { return width * height; }
    const char *name() const override { return "Rectangle"; }
};

// Uses late binding: shape.area() is resolved via the vtable.
void printArea(const Shape &shape)
{
    std::cout << shape.name() << " area = " << shape.area() << '\n';
}

// ---------- main ----------
int main()
{
    // --- Early binding ---
    std::cout << "=== Early binding (direct calls) ===\n";
    // The compiler knows at compile time which function to call.
    std::cout << "add(3, 4) = " << add(3, 4) << '\n'; // resolved at compile time
    std::cout << "sub(10, 3) = " << sub(10, 3) << '\n';

    // --- Late binding via function pointers ---
    std::cout << "\n=== Late binding (function pointers) ===\n";
    ArithmeticFunc ops[] = {add, sub, mul};
    const char *labels[] = {"add", "sub", "mul"};

    for (int i = 0; i < 3; ++i)
    {
        // Which function is called depends on the runtime value of ops[i].
        std::cout << labels[i] << "(6, 2) = " << calculate(6, 2, ops[i]) << '\n';
    }

    // --- Late binding via virtual functions ---
    std::cout << "\n=== Late binding (virtual functions / vtable) ===\n";
    Circle c{5.0};
    Rectangle r{4.0, 6.0};

    // printArea receives a Shape& - at runtime the vtable determines
    // which area() and name() to call.
    printArea(c); // Circle area = 78.5398
    printArea(r); // Rectangle area = 24

    std::cout << "\nVirtual function calls have a small overhead (vtable lookup)\n"
              << "but enable powerful runtime flexibility.\n";

    return 0;
}
