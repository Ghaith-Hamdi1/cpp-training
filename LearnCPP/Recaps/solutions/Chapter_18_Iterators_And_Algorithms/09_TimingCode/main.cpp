// Chapter 18 - Project 9: Timing Your Code with std::chrono
// ============================================================
// The <chrono> library (C++11) provides tools to measure code execution time.
//
// Key ideas:
//   - std::chrono::steady_clock - a monotonic clock ideal for measuring durations
//   - Wrap it in a simple Timer class for convenience
//   - Benchmarking tips:
//       * Always use RELEASE builds (debug can be 30×+ slower)
//       * Minimize background processes
//       * Take at least 3 measurements
//       * Focus on relative comparisons, not absolute timings
//       * Control for randomness (use the same input across tests)

#include <algorithm> // std::sort
#include <chrono>
#include <iostream>
#include <numeric> // std::iota
#include <random>
#include <vector>

// A reusable Timer class wrapping std::chrono::steady_clock
class Timer
{
private:
    // Type aliases for readability
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using Duration = std::chrono::duration<double>; // seconds as a double

    TimePoint m_start{};

public:
    Timer() : m_start{Clock::now()}
    {
    }

    void reset()
    {
        m_start = Clock::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<Duration>(Clock::now() - m_start).count();
    }
};

// Hand-written selection sort for comparison
void selectionSort(std::vector<int> &arr)
{
    int length{static_cast<int>(arr.size())};
    for (int i{0}; i < length - 1; ++i)
    {
        int smallest{i};
        for (int j{i + 1}; j < length; ++j)
        {
            if (arr[j] < arr[smallest])
                smallest = j;
        }
        std::swap(arr[i], arr[smallest]);
    }
}

// Generate a random vector of given size
std::vector<int> generateRandomVector(int size)
{
    std::vector<int> v(size);
    std::iota(v.begin(), v.end(), 1); // Fill with 1, 2, 3, ..., size

    // Shuffle using a random engine
    std::mt19937 rng{std::random_device{}()};
    std::shuffle(v.begin(), v.end(), rng);

    return v;
}

int main()
{
    constexpr int smallSize{10'000};
    constexpr int largeSize{100'000};

    // --- 1) Benchmark selection sort ---
    std::cout << "=== Benchmarking selection sort (" << smallSize << " elements) ===\n";
    {
        auto data{generateRandomVector(smallSize)};
        Timer t;
        selectionSort(data);
        std::cout << "Selection sort: " << t.elapsed() << " seconds\n";
    }

    // --- 2) Benchmark std::sort on the same size ---
    std::cout << "\n=== Benchmarking std::sort (" << smallSize << " elements) ===\n";
    {
        auto data{generateRandomVector(smallSize)};
        Timer t;
        std::sort(data.begin(), data.end());
        std::cout << "std::sort:      " << t.elapsed() << " seconds\n";
    }

    // --- 3) std::sort on a larger data set ---
    std::cout << "\n=== Benchmarking std::sort (" << largeSize << " elements) ===\n";
    {
        auto data{generateRandomVector(largeSize)};
        Timer t;
        std::sort(data.begin(), data.end());
        std::cout << "std::sort:      " << t.elapsed() << " seconds\n";
    }

    // --- 4) Multiple measurements ---
    std::cout << "\n=== 3 measurements of std::sort (" << largeSize << " elements) ===\n";
    for (int run{1}; run <= 3; ++run)
    {
        auto data{generateRandomVector(largeSize)};
        Timer t;
        std::sort(data.begin(), data.end());
        std::cout << "  Run " << run << ": " << t.elapsed() << " seconds\n";
    }

    std::cout << "\nTip: For accurate benchmarks, compile with optimizations enabled!\n";
    std::cout << "  MSVC:      cl /O2 /std:c++20 main.cpp\n";
    std::cout << "  GCC/Clang: g++ -O2 -std=c++20 main.cpp\n";

    return 0;
}
