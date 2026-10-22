// Lesson 19: array-of-structs versus struct-of-arrays, and cache-line padding. The sums are identical; what differs is
// how many bytes each loop drags through the cache. Compile with -std=c++20.
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <new>
#include <vector>

// Array of structs: one record per instrument, every field together.
struct QuoteAos {
    std::int64_t bidTicks;
    std::int64_t askTicks;
    std::uint32_t bidQty;
    std::uint32_t askQty;
    std::uint64_t lastUpdateNs;
    char name[8];
};                                                              // 40 bytes

// Struct of arrays: one array per field. A loop that only needs bids touches only the bid array.
struct QuotesSoa {
    std::vector<std::int64_t> bidTicks, askTicks;
    std::vector<std::uint32_t> bidQty, askQty;
    std::vector<std::uint64_t> lastUpdateNs;
};

static_assert(sizeof(QuoteAos) == 40);

// Two counters written by two threads: without padding they share a 64-byte cache line (false sharing).
struct Unpadded { std::uint64_t a; std::uint64_t b; };
struct Padded {
    alignas(64) std::uint64_t a;
    alignas(64) std::uint64_t b;
};
static_assert(sizeof(Unpadded) == 16);
static_assert(sizeof(Padded) == 128 && alignof(Padded) == 64);

int main()
{
    constexpr std::size_t N = 1000;
    std::vector<QuoteAos> aos(N);
    QuotesSoa soa;
    soa.bidTicks.resize(N); soa.askTicks.resize(N); soa.bidQty.resize(N); soa.askQty.resize(N); soa.lastUpdateNs.resize(N);
    for (std::size_t i = 0; i < N; ++i) {
        aos[i].bidTicks = soa.bidTicks[i] = static_cast<std::int64_t>(1000000 + i);
        aos[i].askTicks = soa.askTicks[i] = static_cast<std::int64_t>(1000100 + i);
    }

    std::int64_t sumAos = 0, sumSoa = 0;
    for (const auto& q : aos) sumAos += q.bidTicks;             // uses 8 of every 40 bytes: 80% of each cache line is wasted
    for (auto b : soa.bidTicks) sumSoa += b;                    // uses every byte it loads
    std::cout << "sum of bids, AoS: " << sumAos << ", SoA: " << sumSoa << ", equal: " << std::boolalpha << (sumAos == sumSoa) << '\n';
    std::cout << "bytes streamed to read all bids: AoS " << N * sizeof(QuoteAos) << ", SoA " << N * sizeof(std::int64_t) << '\n';
    std::cout << "records per 64-byte cache line: AoS " << 64 / sizeof(QuoteAos) << ", SoA (bids) " << 64 / sizeof(std::int64_t) << '\n';
    std::cout << "sizeof Unpadded " << sizeof(Unpadded) << " (both counters on one line), sizeof Padded " << sizeof(Padded)
              << " (one line each, alignof " << alignof(Padded) << ")\n";
}
