// Exercise 17: an array indexed by key instead of a map. Worked solution.
// Build: g++ -std=c++20 -Wall -Wextra solution.cpp -o sol && ./sol
#include <array>
#include <map>
#include "../check.h"

class BucketTable {
    static constexpr long long kBuckets = 64;
    long long base_;
    std::array<unsigned, kBuckets> count_{};
    long long highest_ = -1;                                          // index of the highest non-empty bucket, -1 when empty
public:
    explicit BucketTable(long long base) : base_(base) {}
    bool inRange(long long key) const { return key >= base_ && key < base_ + kBuckets; }
    void add(long long key, unsigned n)
    {
        const long long i = key - base_;
        count_[static_cast<std::size_t>(i)] += n;
        if (n > 0 && i > highest_) highest_ = i;                      // O(1)
    }
    void remove(long long key, unsigned n)
    {
        const long long i = key - base_;
        auto& c = count_[static_cast<std::size_t>(i)];
        c = n >= c ? 0 : c - n;
        if (c == 0 && i == highest_)                                  // the top bucket emptied: scan down
            while (highest_ >= 0 && count_[static_cast<std::size_t>(highest_)] == 0) --highest_;
    }
    unsigned count(long long key) const { return count_[static_cast<std::size_t>(key - base_)]; }
    bool empty() const { return highest_ < 0; }
    long long highest() const { return base_ + highest_; }
};

int main()
{
    BucketTable t(100);
    CHECK(t.empty());
    CHECK(t.inRange(100) && t.inRange(163) && !t.inRange(99) && !t.inRange(164));
    t.add(110, 5);
    t.add(105, 2);
    t.add(110, 1);
    CHECK(!t.empty() && t.count(110) == 6 && t.count(105) == 2 && t.count(111) == 0);
    CHECK(t.highest() == 110);
    t.remove(110, 4);
    CHECK(t.count(110) == 2 && t.highest() == 110);
    t.remove(110, 99);                                  // never below zero
    CHECK(t.count(110) == 0);
    CHECK(t.highest() == 105);                          // the top bucket emptied: scan down
    t.remove(105, 2);
    CHECK(t.empty());
    t.add(163, 1);
    CHECK(t.highest() == 163);

    BucketTable a(1000);
    std::map<long long, unsigned> ref;
    unsigned s = 12345;
    bool same = true;
    for (int i = 0; i < 5000; ++i) {
        s = s * 1103515245u + 12345u;
        long long key = 1000 + (s >> 16) % 64;
        unsigned n = 1 + (s >> 8) % 5;
        if ((s >> 4) % 3 != 0) { a.add(key, n); ref[key] += n; }
        else if (ref.count(key)) {
            a.remove(key, n);
            if (n >= ref[key]) ref.erase(key); else ref[key] -= n;
        }
        if (a.empty() != ref.empty()) same = false;
        else if (!ref.empty() && a.highest() != ref.rbegin()->first) same = false;
    }
    CHECK(same);
    return finish("17 BucketTable");
}
