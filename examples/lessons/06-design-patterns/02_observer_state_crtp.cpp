// Lesson 13: Observer (safe against detaching while notifying), State with std::variant + std::visit, CRTP.
#include <algorithm>
#include <functional>
#include <iostream>
#include <variant>
#include <vector>

class Observer {
public:
    virtual void update(double value) = 0;
    virtual ~Observer() = default;
};

class Subject {
    std::vector<Observer*> observers_;
    double value_ = 0;
public:
    void attach(Observer* o) { observers_.push_back(o); }
    void detach(Observer* o) { observers_.erase(std::remove(observers_.begin(), observers_.end(), o), observers_.end()); }
    void set(double v) {
        value_ = v;
        auto copy = observers_;                         // iterate a COPY: an observer may detach itself in update()
        for (auto* o : copy) o->update(v);
    }
};

struct Display : Observer {
    void update(double v) override { std::cout << "  Display shows " << v << '\n'; }
};
struct OneShot : Observer {                             // detaches itself during notification
    Subject& s;
    explicit OneShot(Subject& s) : s(s) {}
    void update(double v) override { std::cout << "  OneShot saw " << v << " and detaches\n"; s.detach(this); }
};

// State machine: each state is a type; std::visit makes the compiler check every state is handled.
struct Locked {};
struct Unlocked {};
using State = std::variant<Locked, Unlocked>;

struct Turnstile {
    State s = Locked{};
    void coin() { s = Unlocked{}; }
    void push() {
        std::visit([this](auto&& st) {
            using T = std::decay_t<decltype(st)>;
            if constexpr (std::is_same_v<T, Unlocked>) { std::cout << "  pass through, locks again\n"; s = Locked{}; }
            else std::cout << "  ALARM: push while locked\n";
        }, s);
    }
};

template <typename Derived>                             // CRTP: compile-time polymorphism, no vtable
struct ShapeBase {
    double area() const { return static_cast<const Derived*>(this)->areaImpl(); }
};
struct Circle : ShapeBase<Circle> {
    double r = 1;
    double areaImpl() const { return 3.14159 * r * r; }
};

int main() {
    Subject subject;
    Display d;
    OneShot once(subject);
    subject.attach(&d);
    subject.attach(&once);
    std::cout << "set(21.5):\n";
    subject.set(21.5);
    std::cout << "set(30):   (OneShot is gone)\n";
    subject.set(30);

    std::vector<std::function<void(double)>> listeners;  // modern, lighter: observers as callbacks
    listeners.push_back([](double t) { std::cout << "callback temp = " << t << '\n'; });
    for (auto& l : listeners) l(25);

    Turnstile t;
    std::cout << "push, coin, push, push:\n";
    t.push(); t.coin(); t.push(); t.push();

    std::cout << "CRTP area " << Circle{}.area() << '\n';
}
