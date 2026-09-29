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
