// Chapter 14 - Project 13: Temporary Class Objects
// ==================================================
// Key concepts:
//   - A temporary (unnamed) object is created with ClassName{args}.
//   - It exists only for the duration of the single full expression.
//   - Useful for:
//       * Passing to functions without creating a named variable
//       * Returning from functions
//       * One-off computations
//   - Objects returned by value are temporaries at the call site.

#include <iostream>
#include <string>

class Color
{
public:
    Color(int r, int g, int b)
        : m_r{r}, m_g{g}, m_b{b}
    {
    }

    void print() const
    {
        std::cout << "Color(" << m_r << ", " << m_g << ", " << m_b << ")";
    }

    int red() const { return m_r; }
    int green() const { return m_g; }
    int blue() const { return m_b; }

private:
    int m_r{};
    int m_g{};
    int m_b{};
};

// Takes a Color by const reference - works with temporaries and named objects
void displayColor(const Color &c)
{
    std::cout << "Displaying: ";
    c.print();
    std::cout << '\n';
}

// Returns a Color - the returned object is a temporary at the call site
Color mixColors(const Color &a, const Color &b)
{
    return Color{
        (a.red() + b.red()) / 2,
        (a.green() + b.green()) / 2,
        (a.blue() + b.blue()) / 2}; // returns a temporary
}

int main()
{
    // --- Passing a temporary directly to a function ---
    std::cout << "=== Temporary passed to function ===\n";
    displayColor(Color{255, 0, 0}); // temporary: no named variable needed
    displayColor(Color{0, 255, 0});
    // The temporaries are destroyed at the semicolons.

    // --- Named object for comparison ---
    Color blue{0, 0, 255};
    displayColor(blue); // named object

    // --- Returned value is a temporary ---
    std::cout << "\n=== Temporary from function return ===\n";
    Color red{255, 0, 0};
    Color mixed = mixColors(red, blue); // returned temporary (elided into 'mixed')
    std::cout << "Mixed: ";
    mixed.print();
    std::cout << '\n';

    // --- Using a temporary's member function directly ---
    std::cout << "\n=== Calling member on temporary ===\n";
    std::cout << "Red component: " << Color{128, 64, 32}.red() << '\n';
    // The temporary Color is created, .red() is called, then it's destroyed.

    // --- Temporary in an expression ---
    std::cout << "\n=== Temporary in expression ===\n";
    displayColor(mixColors(Color{255, 255, 0}, Color{0, 0, 255}));
    // Three temporaries here: two argument Colors + the returned Color.
    // All destroyed at the semicolon.

    std::cout << "\n-- Takeaway --\n"
              << "Temporaries are unnamed objects that live for one expression.\n"
              << "Great for one-off use - no need to name everything.\n";

    return 0;
}
