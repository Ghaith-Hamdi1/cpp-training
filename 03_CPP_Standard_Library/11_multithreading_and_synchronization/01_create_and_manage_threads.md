# Create and manage threads

- `std::thread` used to create standard threads. It allows running multiple functions concurrently
- Threads begin immediately upon construction
- If an exception is thrown within a thread, `std::terminate` is called
- Promise and Future mechanism is used to communicate with the caller (return value or handled exceptions)
- Mutexes and atomic variables are used to manage concurrent access for shared data
- Important: a thread must be joined by calling `join()` (blocking until processing is finished) OR detached using `detach()` so that the thread remains running separately until self destruction (thread function exits)
- If a thread is detached, the thread handle is no longer valid

```cpp
// Source: Examples/03_CPP_Standard_Library/11_multithreading_and_synchronization/53_multithreading.cpp
#include <iostream>
#include <thread>
#include <chrono>
#include <exception>
#include <csignal>

/// !!! Need to be executed using compile flag -lpthread (to link threads library of linux)

using namespace std::chrono_literals;

void signalHandler( int signum ) {
   std::cout << "Interrupt signal (" << signum << ") received.\n";

   // terminate program  
   std::exit(signum);  
}

class A 
{
public:
    explicit A(int x) : m_x{x} {}

    A(const A& a) : m_x{a.m_x}
    {
        std::cout << "Copy Constructor" << std::endl;
    }
    virtual ~A() = default;
    int getX() const 
    {
        return m_x;
    }
private:
    int m_x;
};

class ThreadHandler
{
public:
    void run()
    {
        std::cout << "Run thread from class member function" << std::endl;
    }
    void operator()()
    {
        std::cout << "Thread with void function" << std::endl;
    }

    void operator()(int x)
    {
        while (x >= 0)
        {
            std::cout << "Running thread with counter " << x << std::endl;
            x--;
            std::this_thread::sleep_for(100ms);
        }
        
    }
    void operator()(int &x, int id)
    {
        while (x >= 0)
        {
            std::cout << "Running thread id=" << id << " with counter " << x << std::endl;
            x--;
            std::this_thread::sleep_for(100ms);
        }
        
    }

    void operator()(const A& a)
    {
        int x = a.getX();
        while (x >= 0)
        {
            std::cout << "Running thread with A reference " << x << std::endl;
            x--;
            std::this_thread::sleep_for(100ms);
        }
    }
};

int main()
{
    int capture{10};
    std::thread th1; // not a thread, just declared
    std::cout << "th1 is " << (th1.joinable() ? "joinable" : "not joinable") << std::endl;
    th1 = std::thread([&capture]() { // use lambda and move assignment operator
        std::cout << "Running thread from lambda with capture value " << capture << std::endl;
        // modify capture should be handled by mutex since it may be shared by another task
        // here we won't use mutexes since it is not shared
        capture = 20;
    });
    std::cout << "th1 is now " << (th1.joinable() ? "joinable" : "not joinable") << " with id=0x" << std::hex << th1.get_id() << std::dec << std::endl;
    if (th1.joinable() == true)
    {
        capture = 30;
        th1.join();
    }
    std::cout << "Capture " << capture << std::endl;
    std::thread th2(ThreadHandler(), 20); // thread created and launched argument passed by value
    A a(10);
    std::thread th3(ThreadHandler(), std::ref(a)); // pass a by reference to the thread

    // execute and see disorder in log display
    if (th2.joinable())
    {
        th2.join();
    }
    if (th3.joinable())
    {
        th3.join();
    }
    ThreadHandler threadHandler;
    std::thread th4(&ThreadHandler::run, &threadHandler); // we have to run thread on an object of ThreadHandler class
    th4.detach(); // no problem since run will exit (no infinite loop)
    std::cout << "th4 is " << (th1.joinable() ? "joinable" : "not joinable") << " after detach" << std::endl;

    // creating two threads from same function
    int x = 8;
    std::thread ths1(ThreadHandler(), std::ref(x), 1);
    std::thread ths2(ThreadHandler(), std::ref(x), 2);
    if (ths1.joinable())
    {
        ths1.join();
    }
    if (ths2.joinable())
    {
        ths2.join();
    }

    // register signals 
    signal(SIGTERM, signalHandler); 
    signal(SIGABRT, signalHandler); 

    // create a thread and throw exception
    std::thread thex([]() { throw std::runtime_error("RUNTIME ERROR!");});
    if (thex.joinable())
    {
        thex.join();
    }
    return 0;
}
```

