// Lesson 10: Meyers Singleton, Factory returning unique_ptr (with a registry), Strategy as class / lambda / template.
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>

class Logger {
public:
    static Logger& instance() {
        static Logger inst;                             // built the first time control passes here (thread-safe since C++11)
        return inst;
    }
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    void log(const std::string& msg) { std::cout << "[log] " << msg << '\n'; }
private:
    Logger() { std::cout << "Logger constructed\n"; }
};

struct Shape {
    virtual double area() const = 0;
    virtual ~Shape() = default;
};
struct Circle : Shape { double r; explicit Circle(double r) : r(r) {} double area() const override { return 3.14159 * r * r; } };
struct Square : Shape { double s; explicit Square(double s) : s(s) {} double area() const override { return s * s; } };

enum class Kind { Circle, Square };
std::unique_ptr<Shape> makeShape(Kind k, double size) {
    switch (k) {
        case Kind::Circle: return std::make_unique<Circle>(size);
        case Kind::Square: return std::make_unique<Square>(size);
    }
    return nullptr;
}

// Registry: adding a type does not mean editing the factory (Open/Closed principle).
using Maker = std::function<std::unique_ptr<Shape>(double)>;
std::map<std::string, Maker>& registry() {
    static std::map<std::string, Maker> r;
    return r;
}

struct PricingStrategy {                                // 1. classic: interface + implementations
    virtual double apply(double price) const = 0;
    virtual ~PricingStrategy() = default;
};
struct Regular : PricingStrategy { double apply(double p) const override { return p; } };
struct Member : PricingStrategy { double apply(double p) const override { return p * 0.90; } };
class Checkout {
    std::unique_ptr<PricingStrategy> strategy_;
public:
    explicit Checkout(std::unique_ptr<PricingStrategy> s) : strategy_(std::move(s)) {}
    double total(double price) const { return strategy_->apply(price); }
};

class Checkout2 {                                       // 2. modern: the strategy IS a callable
    std::function<double(double)> pricing_;
public:
    explicit Checkout2(std::function<double(double)> f) : pricing_(std::move(f)) {}
    double total(double price) const { return pricing_(price); }
};

template <typename Pricing>                             // 3. compile time: policy-based design, zero overhead
struct Checkout3 {
    double total(double price) const { return Pricing{}(price); }
};
struct HalfOff { double operator()(double p) const { return p * 0.5; } };

int main() {
    Logger::instance().log("hello");
    Logger& a = Logger::instance();
    Logger& b = Logger::instance();
    std::cout << "same object: " << std::boolalpha << (&a == &b) << '\n';

    auto s = makeShape(Kind::Circle, 2.0);              // the caller sees only Shape
    std::cout << "factory area " << s->area() << '\n';

    registry()["square"] = [](double x) { return std::make_unique<Square>(x); };
    std::cout << "registry area " << registry()["square"](3.0)->area() << '\n';

    std::cout << Checkout(std::make_unique<Regular>()).total(100) << ' '
              << Checkout(std::make_unique<Member>()).total(100) << ' '
              << Checkout2([](double p) { return p * 0.70; }).total(100) << ' '
              << Checkout3<HalfOff>().total(100) << '\n';
}
