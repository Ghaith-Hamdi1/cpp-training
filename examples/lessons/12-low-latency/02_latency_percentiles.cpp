// Lesson 16: why averages hide tail latency. A synthetic sample set (deterministic) shows mean versus percentiles;
// the timing helper at the end shows how a real measurement is taken (its numbers vary run to run, so none are printed).
// Compile with -std=c++20.
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

// nearest-rank percentile on an already sorted vector
std::uint64_t percentile(const std::vector<std::uint64_t>& sorted, double p)
{
    const std::size_t rank = static_cast<std::size_t>(p / 100.0 * static_cast<double>(sorted.size()));
    return sorted[std::min(rank, sorted.size() - 1)];
}

struct Lcg {                                                    // tiny deterministic random generator
    std::uint64_t s = 12345;
    std::uint64_t next() { s = s * 6364136223846793005ULL + 1442695040888963407ULL; return s >> 33; }
};

int main()
{
    // 1,000,000 "operations": about 200 ns each, except one in a thousand takes 80 microseconds (an allocation, a
    // context switch, a page fault...). The slow ones are rare, so the average barely moves.
    Lcg rng;
    std::vector<std::uint64_t> ns;
    ns.reserve(1000000);
    for (int i = 0; i < 1000000; ++i)
        ns.push_back(i % 1000 == 999 ? 80000 + rng.next() % 5000 : 180 + rng.next() % 40);

    std::uint64_t sum = 0;
    for (auto x : ns) sum += x;
    std::sort(ns.begin(), ns.end());

    std::cout << "mean   " << sum / ns.size() << " ns\n";
    std::cout << "p50    " << percentile(ns, 50) << " ns\n";
    std::cout << "p99    " << percentile(ns, 99) << " ns\n";
    std::cout << "p99.9  " << percentile(ns, 99.9) << " ns\n";
    std::cout << "p99.99 " << percentile(ns, 99.99) << " ns\n";
    std::cout << "max    " << ns.back() << " ns\n";

    // How a real measurement is taken: steady_clock is monotonic. Record every sample, sort afterwards, and keep the
    // recording itself cheap (a vector reserved in advance, no printing inside the timed region).
    std::vector<std::uint64_t> samples;
    samples.reserve(1000);
    volatile std::uint64_t sink = 0;                            // stops the compiler from deleting the loop body
    for (int i = 0; i < 1000; ++i) {
        const auto t0 = std::chrono::steady_clock::now();
        for (int k = 0; k < 100; ++k) sink = sink + static_cast<std::uint64_t>(k);
        const auto t1 = std::chrono::steady_clock::now();
        samples.push_back(static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count()));
    }
    std::sort(samples.begin(), samples.end());
    std::cout << "real samples taken: " << samples.size() << " (values vary between runs)\n";
}
