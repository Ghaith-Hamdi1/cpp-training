// Chapter 3 - Project 04: Validating Code Flow
// ===============================================
//
// KEY CONCEPT:
//   When debugging, it helps to print the name of every function as it is
//   entered. This confirms which functions are actually being called and
//   in what order - your assumptions about control flow may be wrong!
//
//   By tracing execution, you can quickly narrow down WHICH function
//   contains the bug (or which function is never being called at all).
//
// This program has a subtle bug: processOrder() calls calculateTax()
// with the wrong argument. By reading the trace output, you can see
// the unexpected tax value and locate the problem.

#include <iostream>

double getPrice()
{
    std::cerr << "[TRACE] getPrice() called\n";
    return 49.99;
}

int getQuantity()
{
    std::cerr << "[TRACE] getQuantity() called\n";
    return 3;
}

double calculateSubtotal(double price, int qty)
{
    std::cerr << "[TRACE] calculateSubtotal(price=" << price
              << ", qty=" << qty << ") called\n";
    return price * qty;
}

double calculateTax(double amount, double rate)
{
    std::cerr << "[TRACE] calculateTax(amount=" << amount
              << ", rate=" << rate << ") called\n";
    return amount * rate;
}

// BUG: This function passes the wrong value to calculateTax().
// It passes 'price' instead of 'subtotal', so the tax is too low.
void processOrder()
{
    std::cerr << "[TRACE] processOrder() called\n";

    double price{getPrice()};
    int qty{getQuantity()};
    double subtotal{calculateSubtotal(price, qty)};

    // BUG: should be calculateTax(subtotal, 0.08), not calculateTax(price, 0.08)
    double tax{calculateTax(price, 0.08)}; // <-- Wrong! Uses price, not subtotal

    double total{subtotal + tax};

    std::cout << "\n=== Order Summary ===\n";
    std::cout << "Price:    $" << price << '\n';
    std::cout << "Quantity: " << qty << '\n';
    std::cout << "Subtotal: $" << subtotal << '\n';
    std::cout << "Tax:      $" << tax << '\n';
    std::cout << "Total:    $" << total << '\n';

    // With the trace output, you can see that calculateTax() received
    // amount=49.99 instead of amount=149.97. That pinpoints the bug!
}

int main()
{
    std::cerr << "[TRACE] main() called\n";

    std::cout << "=== Validating Code Flow Demo ===\n";
    processOrder();

    std::cerr << "[TRACE] main() returning\n";
    return 0;
}
