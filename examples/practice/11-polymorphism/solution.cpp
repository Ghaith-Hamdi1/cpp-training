// Exercise 11: polymorphism and virtual destructors.
//
// Rectangle and Circle (below) are finished. Each owns a Tracker so the test can see whether its
// destructor ran. YOUR job is the base class and one function:
//   - Shape: an abstract base class (cannot be instantiated) with a pure virtual
//     `double area() const` and a destructor that makes `delete basePointer` safe.
//   - totalArea: the sum of area() over a vector of owning pointers to shapes.
// Think about WHY the destructor must be virtual: with a plain destructor, deleting a Circle
// through a Shape* skips ~Circle(), so the Tracker is never destroyed.
#include <cmath>
#include <memory>
#include <type_traits>
#include <vector>
#include "../check.h"

struct Tracker {                                       // counts live objects
    static int alive;
    Tracker() { ++alive; }
    Tracker(const Tracker&) { ++alive; }
    ~Tracker() { --alive; }
};
int Tracker::alive = 0;

struct Shape {
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

struct Rectangle : Shape {
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
private:
    double w_, h_;
    Tracker t_;
};

struct Circle : Shape {
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14159265358979 * r_ * r_; }
private:
    double r_;
    Tracker t_;
};

double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    double sum = 0;
    for (const auto& s : shapes) sum += s->area();
    return sum;
}

static bool near(double a, double b) { return std::fabs(a - b) < 1e-6; }

int main()
{
    CHECK(std::is_abstract<Shape>::value);             // Shape cannot be instantiated
    CHECK(std::has_virtual_destructor<Shape>::value);  // deleting through Shape* is safe

    {
        std::vector<std::unique_ptr<Shape>> v;
        v.push_back(std::make_unique<Rectangle>(2, 5));
        v.push_back(std::make_unique<Circle>(2));
        CHECK(Tracker::alive == 2);
        CHECK(near(totalArea(v), 10 + 3.14159265358979 * 4));
    }
    CHECK(Tracker::alive == 0);                        // both destructors ran through the base pointer

    std::unique_ptr<Shape> p = std::make_unique<Circle>(1);
    CHECK(near(p->area(), 3.14159265358979));
    p.reset();
    CHECK(Tracker::alive == 0);
    return finish("11 polymorphism");
}
