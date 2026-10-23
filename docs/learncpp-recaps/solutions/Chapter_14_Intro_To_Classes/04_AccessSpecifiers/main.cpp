// Chapter 14 - Project 04: Access Specifiers (public / private / protected)
// ==========================================================================
// Key concepts:
//   - public:     anyone can access these members
//   - private:    only other members of the SAME class can access
//   - protected:  members and derived classes (covered in inheritance)
//
//   - Access is per-CLASS, not per-object. A member function of class X
//     can access private members of ANY X object, not just 'this'.
//   - Best practice: declare public members first, then private,
//     to spotlight the interface.
//   - Name private data members with the m_ prefix.

#include <iostream>
#include <string>

class BankAccount
{
    // Public interface - declared first (best practice)
public:
    BankAccount(std::string_view owner, double balance)
        : m_owner{owner}, m_balance{balance}
    {
    }

    // Getter - const because it doesn't modify the object
    double getBalance() const { return m_balance; }

    std::string_view getOwner() const { return m_owner; }

    void deposit(double amount)
    {
        if (amount > 0.0)
            m_balance += amount;
    }

    bool withdraw(double amount)
    {
        if (amount > 0.0 && amount <= m_balance)
        {
            m_balance -= amount;
            return true;
        }
        return false; // insufficient funds or invalid amount
    }

    void print() const
    {
        std::cout << "Account [" << m_owner << "] balance: $" << m_balance << '\n';
    }

    // Access is per-CLASS, not per-object.
    // This member function can access private members of ANOTHER BankAccount.
    void transferTo(BankAccount &other, double amount)
    {
        if (withdraw(amount))
        {
            other.m_balance += amount; // accessing other's PRIVATE member - legal!
            std::cout << "Transferred $" << amount
                      << " from " << m_owner << " to " << other.m_owner << '\n';
        }
        else
        {
            std::cout << "Transfer failed - insufficient funds.\n";
        }
    }

    // Private data - hidden from outside code
private:
    std::string m_owner{};
    double m_balance{};
};

int main()
{
    BankAccount alice{"Alice", 1000.0};
    BankAccount bob{"Bob", 500.0};

    alice.print();
    bob.print();

    // Public interface works fine
    alice.deposit(200.0);
    bob.withdraw(100.0);
    std::cout << "\nAfter deposit/withdraw:\n";
    alice.print();
    bob.print();

    // Per-class access: transferTo accesses ANOTHER object's private members
    std::cout << '\n';
    alice.transferTo(bob, 350.0);
    alice.print();
    bob.print();

    // Direct access is blocked:
    // alice.m_balance = 999999;  // ERROR - m_balance is private

    std::cout << "\n-- Takeaway --\n"
              << "Access is per-CLASS, not per-object.\n"
              << "A member function can touch private members of any object of the same class.\n";

    return 0;
}
