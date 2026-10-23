// Chapter 22 - Project 07: std::unique_ptr
// std::unique_ptr is the go-to smart pointer for sole-ownership resources.
//
// Key points:
//   - Non-copyable, but movable - ownership can be transferred.
//   - Use std::make_unique<T>(args) to create (C++14+) - safer than raw new.
//   - Automatically deletes the managed object when it goes out of scope.
//   - Pass the raw pointer via get() to functions that don't need ownership.
//   - Return unique_ptr by value from factory functions.
//   - NEVER construct two unique_ptrs from the same raw pointer.

#include <iostream>
#include <memory> // std::unique_ptr, std::make_unique
#include <string>
#include <utility> // std::move

// -----------------------------------------------------------------------
// A simple resource class to observe construction / destruction
// -----------------------------------------------------------------------
class Sensor
{
    std::string m_name;

public:
    explicit Sensor(const std::string &name) : m_name{name}
    {
        std::cout << "  [Sensor] \"" << m_name << "\" created\n";
    }

    ~Sensor()
    {
        std::cout << "  [Sensor] \"" << m_name << "\" destroyed\n";
    }

    const std::string &name() const { return m_name; }
    void read() const { std::cout << "  [Sensor] \"" << m_name << "\" reading: 42.0\n"; }
};

// -----------------------------------------------------------------------
// 1. Basic creation and automatic cleanup
// -----------------------------------------------------------------------
void basicUsage()
{
    std::cout << "=== 1. Basic unique_ptr ===\n";

    // Preferred creation: std::make_unique (exception-safe, no raw 'new')
    auto sensor = std::make_unique<Sensor>("Temperature");

    // Use like a regular pointer
    sensor->read();
    std::cout << "  Name: " << (*sensor).name() << '\n';

    // unique_ptr is destroyed here - Sensor is automatically deleted
}

// -----------------------------------------------------------------------
// 2. Passing raw pointer to non-owning functions
// -----------------------------------------------------------------------
void printSensor(const Sensor *s) // non-owning: takes raw pointer
{
    if (s)
        std::cout << "  printSensor: \"" << s->name() << "\"\n";
}

void passWithoutOwnership()
{
    std::cout << "\n=== 2. Pass raw pointer (no ownership transfer) ===\n";

    auto sensor = std::make_unique<Sensor>("Humidity");

    // Use get() to pass the raw pointer - caller does NOT take ownership
    printSensor(sensor.get());

    std::cout << "  unique_ptr still owns it: " << sensor->name() << '\n';
}

// -----------------------------------------------------------------------
// 3. Transferring ownership with std::move
// -----------------------------------------------------------------------
void transferOwnership()
{
    std::cout << "\n=== 3. Transfer ownership ===\n";

    auto a = std::make_unique<Sensor>("Pressure");
    std::cout << "  a owns: " << a->name() << '\n';

    // Move ownership from a to b
    auto b = std::move(a);

    std::cout << "  a is now: " << (a ? a->name() : "nullptr") << '\n';
    std::cout << "  b owns: " << b->name() << '\n';
}

// -----------------------------------------------------------------------
// 4. Factory function returning unique_ptr
// -----------------------------------------------------------------------
std::unique_ptr<Sensor> createSensor(const std::string &name)
{
    // Returning unique_ptr by value - move is automatic
    return std::make_unique<Sensor>(name);
}

void factoryDemo()
{
    std::cout << "\n=== 4. Factory function ===\n";

    auto sensor = createSensor("Light");
    sensor->read();
}

// -----------------------------------------------------------------------
// 5. unique_ptr with arrays
// -----------------------------------------------------------------------
void arrayDemo()
{
    std::cout << "\n=== 5. unique_ptr with arrays ===\n";

    // unique_ptr<T[]> manages a dynamically allocated array
    auto arr = std::make_unique<int[]>(5);

    for (int i = 0; i < 5; ++i)
        arr[i] = i * 10;

    std::cout << "  Array: ";
    for (int i = 0; i < 5; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';

    // Automatically calls delete[] when arr goes out of scope
}

// -----------------------------------------------------------------------
// 6. Checking for null
// -----------------------------------------------------------------------
void nullCheck()
{
    std::cout << "\n=== 6. Null check ===\n";

    std::unique_ptr<Sensor> ptr; // default constructed - nullptr
    std::cout << "  ptr is " << (ptr ? "not null" : "null") << '\n';

    ptr = std::make_unique<Sensor>("GPS");
    std::cout << "  ptr is " << (ptr ? "not null" : "null") << '\n';

    ptr.reset(); // Explicitly release and delete
    std::cout << "  After reset: ptr is " << (ptr ? "not null" : "null") << '\n';
}

// -----------------------------------------------------------------------
int main()
{
    basicUsage();
    passWithoutOwnership();
    transferOwnership();
    factoryDemo();
    arrayDemo();
    nullCheck();

    std::cout << "\nDone.\n";
    return 0;
}
