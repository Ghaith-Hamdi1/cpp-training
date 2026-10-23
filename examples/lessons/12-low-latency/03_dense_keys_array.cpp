// Lesson 20: a table of counts as an array indexed by key, checked against std::map with random operations.
// Compile with -std=c++23.
#include <array>
#include <cstdint>
#include <iostream>
#include <map>

// A table of counts per bucket. Keys are integers inside a bounded range.
class BucketTable {
    static constexpr std::int64_t kBuckets = 4096;
    std::int64_t base_;                                         // key of index 0
    std::array<std::uint64_t, kBuckets> count_{};                  // contiguous: one cache-friendly block, no allocation
    std::int64_t highest_ = -1;                                 // index of the highest non-empty bucket, -1 when empty
public:
    explicit BucketTable(std::int64_t base) : base_(base) {}

    bool inRange(std::int64_t key) const { return key >= base_ && key < base_ + kBuckets; }

    void add(std::int64_t key, std::uint64_t n)
    {
        const std::int64_t i = key - base_;
        count_[static_cast<std::size_t>(i)] += n;
        if (i > highest_) highest_ = i;
    }

    void remove(std::int64_t key, std::uint64_t n)
    {
        const std::int64_t i = key - base_;
        auto& bucket = count_[static_cast<std::size_t>(i)];
        bucket = n >= bucket ? 0 : bucket - n;
        if (bucket == 0 && i == highest_) {                      // the highest bucket vanished: scan down to the next one
            while (highest_ >= 0 && count_[static_cast<std::size_t>(highest_)] == 0) --highest_;
        }
    }

    bool empty() const { return highest_ < 0; }
    std::int64_t highestKey() const { return base_ + highest_; }
    std::uint64_t highestCount() const { return count_[static_cast<std::size_t>(highest_)]; }
};

struct Lcg {
    std::uint64_t s = 99;
    std::uint64_t next() { s = s * 6364136223846793005ULL + 1442695040888963407ULL; return s >> 33; }
};

int main()
{
    const std::int64_t base = 1000000;                          // any starting key
    BucketTable table(base);
    std::map<std::int64_t, std::uint64_t, std::greater<>> ref;   // the textbook alternative, highest key first

    Lcg rng;
    int mismatches = 0, checks = 0;
    for (int step = 0; step < 200000; ++step) {
        const std::int64_t key = base + static_cast<std::int64_t>(rng.next() % 200);   // a narrow band of keys
        const std::uint64_t n = 1 + rng.next() % 50;
        if (rng.next() % 3 != 0) {                              // add
            table.add(key, n);
            ref[key] += n;
        } else {                                                // remove up to n from this bucket, if it exists
            auto it = ref.find(key);
            if (it != ref.end()) {
                table.remove(key, n);
                if (n >= it->second) ref.erase(it); else it->second -= n;
            }
        }
        ++checks;
        const bool sameEmpty = table.empty() == ref.empty();
        if (!sameEmpty || (!ref.empty() && (table.highestKey() != ref.begin()->first || table.highestCount() != ref.begin()->second)))
            ++mismatches;
    }
    std::cout << "compared the highest key after each of " << checks << " operations: " << mismatches << " mismatches\n";
    if (!table.empty())
        std::cout << "final highest key " << table.highestKey() << " count " << table.highestCount() << " (map says "
                  << ref.begin()->first << " count " << ref.begin()->second << ")\n";
    std::cout << "key inside range? 1000100: " << std::boolalpha << table.inRange(1000100)
              << ", 2000000: " << table.inRange(2000000) << '\n';
}
