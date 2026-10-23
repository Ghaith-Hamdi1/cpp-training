// Lesson 16: recursive_mutex (and why it is a smell), timed_mutex with try_lock_for, shared_mutex for a read-mostly
// table, and call_once. Compile with -std=c++20 -pthread.
#include <chrono>
#include <iostream>
#include <map>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <thread>
#include <vector>

class Account {                                                   // public methods call each other: a recursive mutex "fixes" it
    std::recursive_mutex m_;
    int balance_ = 0;
public:
    void deposit(int n) { std::lock_guard<std::recursive_mutex> lk(m_); balance_ += n; }
    void depositTwice(int n) { std::lock_guard<std::recursive_mutex> lk(m_); deposit(n); deposit(n); }   // locks again in the same thread
    int balance() { std::lock_guard<std::recursive_mutex> lk(m_); return balance_; }
};

class PriceTable {                                                // many readers, rare writers
    mutable std::shared_mutex m_;
    std::map<std::string, double> px_;
public:
    void set(const std::string& k, double v) { std::unique_lock lk(m_); px_[k] = v; }                // exclusive
    double get(const std::string& k) const { std::shared_lock lk(m_); auto it = px_.find(k); return it == px_.end() ? -1 : it->second; }   // shared
};

int main()
{
    Account a;
    a.depositTwice(5);
    std::cout << "recursive_mutex: depositTwice(5) locked the same mutex three times in one thread, balance " << a.balance() << '\n';

    std::mutex plain;
    plain.lock();                                                // a plain mutex locked twice by one thread would deadlock; we only try
    std::cout << "try_lock on a mutex we already hold (from another thread): ";
    std::thread([&] { std::cout << std::boolalpha << plain.try_lock() << '\n'; }).join();
    plain.unlock();

    std::timed_mutex tm;
    std::thread holder([&] { tm.lock(); std::this_thread::sleep_for(std::chrono::milliseconds(200)); tm.unlock(); });
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    bool got = tm.try_lock_for(std::chrono::milliseconds(20));  // gives up after 20 ms instead of blocking forever
    std::cout << "timed_mutex: try_lock_for(20 ms) while another thread holds it for 200 ms -> " << got << '\n';
    if (got) tm.unlock();
    holder.join();

    PriceTable t;
    t.set("ESZ5", 5000.25);
    std::vector<std::thread> readers;
    std::vector<double> seen(4);
    for (int i = 0; i < 4; ++i) readers.emplace_back([&, i] { seen[i] = t.get("ESZ5"); });
    for (auto& r : readers) r.join();
    std::cout << "shared_mutex: four readers saw " << seen[0] << ' ' << seen[1] << ' ' << seen[2] << ' ' << seen[3] << '\n';

    std::once_flag flag;
    int initCount = 0;
    std::vector<std::thread> ts;
    for (int i = 0; i < 8; ++i) ts.emplace_back([&] { std::call_once(flag, [&] { ++initCount; }); });
    for (auto& x : ts) x.join();
    std::cout << "call_once from 8 threads ran the initializer " << initCount << " time\n";
}
