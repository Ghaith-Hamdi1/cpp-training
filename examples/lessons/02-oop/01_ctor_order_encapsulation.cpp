// Lesson 4: encapsulation with an invariant, member initializer list, construction/destruction order.
#include <iostream>
#include <string>

class BankAccount {
public:
    explicit BankAccount(double opening) : balance_(opening) {}
    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance_) return false;   // invariant protected
        balance_ -= amount;
        return true;
    }
    double balance() const { return balance_; }
private:
    double balance_;
};

struct Vehicle {
    Vehicle() { std::cout << "Vehicle()\n"; }
    virtual ~Vehicle() { std::cout << "~Vehicle()\n"; }
};
struct Engine {
    Engine() { std::cout << "Engine()\n"; }
    ~Engine() { std::cout << "~Engine()\n"; }
};
struct Car : Vehicle {
    Engine e;
    Car() { std::cout << "Car()\n"; }
    ~Car() { std::cout << "~Car()\n"; }
};

int main() {
    BankAccount acc{100.0};
    std::cout << std::boolalpha << acc.withdraw(30) << ' ' << acc.withdraw(500) << ' ' << acc.balance() << '\n';
    // acc.balance_ = 1e9;            // ERROR: private

    std::cout << "--- construct and destroy a Car ---\n";
    {
        Car c;                        // base first, then members, then the derived body
    }                                 // destruction runs in exact reverse
}
