// Exercise 17: an array indexed by key instead of a map.
//
// BucketTable holds a count for each integer key in [base, base + 64). Implement:
//   explicit BucketTable(long long base)
//   bool inRange(long long key) const              is the key inside the range?
//   void add(long long key, unsigned n)            add n to the key's bucket (precondition: in range)
//   void remove(long long key, unsigned n)         subtract n, but never below zero
//   unsigned count(long long key) const
//   bool empty() const                             true when every bucket is zero
//   long long highest() const                      the highest key with a non-zero count (precondition: not empty)
// Every operation except finding a new highest key after the top bucket empties must be O(1):
// track the highest index, and when its bucket empties scan downwards. No std::map.
// Build: g++ -std=c++20 -Wall -Wextra exercise.cpp -o ex && ./ex
#include <array>
#include <map>
#include "../check.h"

class BucketTable {
public:
    explicit BucketTable(long long base) { (void)base; }              // TODO
    bool inRange(long long key) const { (void)key; return false; }    // TODO
    void add(long long key, unsigned n) { (void)key; (void)n; }       // TODO
    void remove(long long key, unsigned n) { (void)key; (void)n; }    // TODO
    unsigned count(long long key) const { (void)key; return 0; }      // TODO
    bool empty() const { return true; }                               // TODO
    long long highest() const { return 0; }                           // TODO
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

    // compare with std::map on a pseudo-random sequence
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
