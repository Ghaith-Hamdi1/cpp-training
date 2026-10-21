// Lesson 7: starting threads, std::ref, lambdas, member functions, join on every path (RAII guard), jthread.
// Compile with -pthread. Output order of the two "running" lines can differ between runs.
#include <chrono>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>

std::mutex coutMutex;                                   // one mutex so lines from different threads do not interleave
void say(const std::string& s) { std::lock_guard<std::mutex> lk(coutMutex); std::cout << s << '\n'; }

void hello(int id) { say("worker " + std::to_string(id) + " running"); }
void addOne(int& n) { ++n; }
struct Worker { void run(int n) { say("member function got " + std::to_string(n)); } };

class ThreadGuard {                                     // RAII: join however the scope is left
    std::thread& t_;
public:
    explicit ThreadGuard(std::thread& t) : t_(t) {}
    ~ThreadGuard() { if (t_.joinable()) t_.join(); }
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
};

void mayThrow() { throw std::runtime_error("something failed"); }

int main() {
    std::thread t(hello, 1);                            // starts running immediately
    say("main continues");
    t.join();                                           // wait here until t has finished

    int x = 0;
    std::thread t1(addOne, std::ref(x));                // std::ref: without it this will not even compile
    t1.join();
    std::cout << "x = " << x << '\n';

    std::thread t2([] { say("a lambda works too"); });
    t2.join();

    Worker w;
    std::thread t3(&Worker::run, &w, 5);                // pointer to member, the object, then the arguments
    t3.join();

    try {
        std::thread t4([] { std::this_thread::sleep_for(std::chrono::milliseconds(20)); say("t4 finished"); });
        ThreadGuard g(t4);                              // joins when the scope exits, even by an exception
        mayThrow();
    } catch (const std::exception& e) {
        say(std::string("caught: ") + e.what() + " (t4 was still joined)");
    }

    {
        std::jthread jt([] { say("jthread joins automatically in its destructor"); });   // C++20
    }
    std::cout << "hardware threads: " << std::thread::hardware_concurrency() << '\n';
}
