// Lesson 19: an order book side as an array indexed by price tick, checked against std::map with random operations.
// Compile with -std=c++20.
#include <array>
#include <cstdint>
#include <iostream>
#include <map>

// One side of a book: quantity at each price level. Prices are integer ticks inside a bounded window.
class BookSide {
    static constexpr std::int64_t kLevels = 4096;
    std::int64_t base_;                                         // price (in ticks) of index 0
    std::array<std::uint64_t, kLevels> qty_{};                  // contiguous: one cache-friendly block, no allocation
    std::int64_t bestIdx_ = -1;                                 // index of the best (highest) level, -1 when empty
public:
    explicit BookSide(std::int64_t base) : base_(base) {}

    bool inWindow(std::int64_t price) const { return price >= base_ && price < base_ + kLevels; }

    void add(std::int64_t price, std::uint64_t q)
    {
        const std::int64_t i = price - base_;
        qty_[static_cast<std::size_t>(i)] += q;
        if (i > bestIdx_) bestIdx_ = i;
    }

    void remove(std::int64_t price, std::uint64_t q)
    {
        const std::int64_t i = price - base_;
        auto& level = qty_[static_cast<std::size_t>(i)];
        level = q >= level ? 0 : level - q;
        if (level == 0 && i == bestIdx_) {                      // the best level vanished: scan down to the next one
            while (bestIdx_ >= 0 && qty_[static_cast<std::size_t>(bestIdx_)] == 0) --bestIdx_;
        }
    }

    bool empty() const { return bestIdx_ < 0; }
    std::int64_t bestPrice() const { return base_ + bestIdx_; }
    std::uint64_t bestQty() const { return qty_[static_cast<std::size_t>(bestIdx_)]; }
};

struct Lcg {
    std::uint64_t s = 99;
    std::uint64_t next() { s = s * 6364136223846793005ULL + 1442695040888963407ULL; return s >> 33; }
};

int main()
{
    const std::int64_t base = 1000000;                          // 100.0000 with 4 decimals
    BookSide arrayBook(base);
    std::map<std::int64_t, std::uint64_t, std::greater<>> mapBook;   // the textbook alternative, highest price first

    Lcg rng;
    int mismatches = 0, checks = 0;
    for (int step = 0; step < 200000; ++step) {
        const std::int64_t price = base + static_cast<std::int64_t>(rng.next() % 200);   // a narrow band of prices
        const std::uint64_t q = 1 + rng.next() % 50;
        if (rng.next() % 3 != 0) {                              // add
            arrayBook.add(price, q);
            mapBook[price] += q;
        } else {                                                // remove up to q from this level, if it exists
            auto it = mapBook.find(price);
            if (it != mapBook.end()) {
                arrayBook.remove(price, q);
                if (q >= it->second) mapBook.erase(it); else it->second -= q;
            }
        }
        ++checks;
        const bool sameEmpty = arrayBook.empty() == mapBook.empty();
        if (!sameEmpty || (!mapBook.empty() && (arrayBook.bestPrice() != mapBook.begin()->first || arrayBook.bestQty() != mapBook.begin()->second)))
            ++mismatches;
    }
    std::cout << "compared best bid after each of " << checks << " operations: " << mismatches << " mismatches\n";
    if (!arrayBook.empty())
        std::cout << "final best bid " << arrayBook.bestPrice() << " qty " << arrayBook.bestQty() << " (map says "
                  << mapBook.begin()->first << " qty " << mapBook.begin()->second << ")\n";
    std::cout << "price inside window? 1000100: " << std::boolalpha << arrayBook.inWindow(1000100)
              << ", 2000000: " << arrayBook.inWindow(2000000) << '\n';
}
