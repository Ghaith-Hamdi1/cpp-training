# Atomic variables

- Race condition is a common issue faced on multi threading systems
- It occurs when many threads try to access the same resource at the same time
- Atomic variables are created to be protected from data races
- `std::atomic<T>` where `T` is the type of atomic variable
- Type aliases are defined in the standard library, like `std::atomic_bool` ~ `std::atomic<bool>`

```cpp
// Source: Examples/03_CPP_Standard_Library/11_multithreading_and_synchronization/54_atomic.cpp
#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

class Test
{
public:
    Test() : atomic_counter{0}, counter{0} 
    {
    }

    void run()
    {
        for (int i = 0; i < 1000; i++)
        {
            atomic_counter++;
            counter++;
        }
    }
    int getAtomicCounter() const
    {
        return atomic_counter;
    }

    int getCounter() const 
    {
        return counter;
    }
private:
    std::atomic_int atomic_counter;
    int counter;
};

struct A
{
    int x;
    void print()
    {
        std::cout << "Print from A" << std::endl;
    }
};

int main()
{
    std::vector<std::thread> vect;
    Test test;
    std::atomic<A> aA;

    for (int i = 0; i < 10; i++)
    {
        vect.emplace_back(&Test::run, &test);
    }

    for (int i = 0; i < 10; i++)
    {
        vect[i].join();
    }

    std::cout << "Atomic counter " << test.getAtomicCounter() << " and non atomic counter is " << test.getCounter() << std::endl;
    aA.load().print();
    return 0;
}
```

