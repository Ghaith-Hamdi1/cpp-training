// Lesson 20: array-of-structs versus struct-of-arrays, and cache-line padding. The sums are identical; what differs is
// how many bytes each loop drags through the cache. Compile with -std=c++23.
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <new>
#include <vector>

// Array of structs: one record per key, every field together.
struct ReadingAos {
    std::int64_t lo;
    std::int64_t hi;
    std::uint32_t loCount;
    std::uint32_t hiCount;
    std::uint64_t lastUpdateNs;
    char name[8];
};                                                              // 40 bytes

// Struct of arrays: one array per field. A loop that only needs lows touches only the low array.
struct ReadingsSoa {
    std::vector<std::int64_t> lo, hi;
    std::vector<std::uint32_t> loCount, hiCount;
    std::vector<std::uint64_t> lastUpdateNs;
};

static_assert(sizeof(ReadingAos) == 40);

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
    std::vector<ReadingAos> aos(N);
    ReadingsSoa soa;
    soa.lo.resize(N); soa.hi.resize(N); soa.loCount.resize(N); soa.hiCount.resize(N); soa.lastUpdateNs.resize(N);
    for (std::size_t i = 0; i < N; ++i) {
        aos[i].lo = soa.lo[i] = static_cast<std::int64_t>(1000000 + i);
        aos[i].hi = soa.hi[i] = static_cast<std::int64_t>(1000100 + i);
    }

    std::int64_t sumAos = 0, sumSoa = 0;
    for (const auto& q : aos) sumAos += q.lo;             // uses 8 of every 40 bytes: 80% of each cache line is wasted
    for (auto b : soa.lo) sumSoa += b;                    // uses every byte it loads
    std::cout << "sum of lows, AoS: " << sumAos << ", SoA: " << sumSoa << ", equal: " << std::boolalpha << (sumAos == sumSoa) << '\n';
    std::cout << "bytes streamed to read all lows: AoS " << N * sizeof(ReadingAos) << ", SoA " << N * sizeof(std::int64_t) << '\n';
    std::cout << "records per 64-byte cache line: AoS " << 64 / sizeof(ReadingAos) << ", SoA (lows) " << 64 / sizeof(std::int64_t) << '\n';
    std::cout << "sizeof Unpadded " << sizeof(Unpadded) << " (both counters on one line), sizeof Padded " << sizeof(Padded)
              << " (one line each, alignof " << alignof(Padded) << ")\n";
}
