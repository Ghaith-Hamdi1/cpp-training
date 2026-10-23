// Project 10: Overloading the Function Call Operator () - Functors
// =================================================================
// operator() MUST be a member function. It can take any number and type
// of parameters. This makes instances callable like functions.
// Functors (function objects) are classes that overload operator() -
// they can store state in member variables, unlike regular functions.

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

// --- Example 1: 2D Matrix indexing with operator() ---
// operator() is useful for multidimensional array access because
// operator[] only takes one parameter.

class Matrix
{
private:
    static constexpr int rows{3};
    static constexpr int cols{3};
    double m_data[rows][cols]{};

public:
    // operator() for 2D indexing: matrix(row, col)
    double &operator()(int row, int col)
    {
        return m_data[row][col];
    }

    const double &operator()(int row, int col) const
    {
        return m_data[row][col];
    }

    void print() const
    {
        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < cols; ++c)
                std::cout << m_data[r][c] << '\t';
            std::cout << '\n';
        }
    }
};

// --- Example 2: Functor - a callable object with STATE ---
// Unlike a regular function, a functor can remember things between calls.

class Accumulator
{
private:
    int m_total{0};

public:
    // operator() adds a value to the running total and returns the new total
    int operator()(int value)
    {
        m_total += value;
        return m_total;
    }

    int getTotal() const { return m_total; }

    void reset() { m_total = 0; }
};

// --- Example 3: Functor used with standard algorithms ---
// std::sort can take a functor as a custom comparator.

class DescendingOrder
{
public:
    // Compares two ints - returns true if a should come before b (descending)
    bool operator()(int a, int b) const
    {
        return a > b;
    }
};

// --- Example 4: Configurable functor ---
// A functor whose behavior depends on its stored state.

class GreaterThan
{
private:
    int m_threshold{};

public:
    explicit GreaterThan(int threshold) : m_threshold{threshold} {}

    bool operator()(int value) const
    {
        return value > m_threshold;
    }
};

int main()
{
    // --- Matrix indexing ---
    std::cout << "=== Matrix with operator() ===\n";
    Matrix m;
    m(0, 0) = 1.0;
    m(0, 1) = 2.0;
    m(1, 1) = 5.0;
    m(2, 2) = 9.0;
    m.print();

    // --- Accumulator functor with state ---
    std::cout << "\n=== Accumulator Functor ===\n";
    Accumulator acc;
    std::cout << "Add 10: running total = " << acc(10) << '\n';
    std::cout << "Add 20: running total = " << acc(20) << '\n';
    std::cout << "Add 30: running total = " << acc(30) << '\n';
    // The functor remembers the running total between calls!

    // --- Functor as comparator for std::sort ---
    std::cout << "\n=== Sorting with Functor ===\n";
    std::vector<int> nums{5, 2, 8, 1, 9, 3};

    std::cout << "Before sort: ";
    for (int n : nums)
        std::cout << n << ' ';
    std::cout << '\n';

    std::sort(nums.begin(), nums.end(), DescendingOrder{});

    std::cout << "After sort (descending): ";
    for (int n : nums)
        std::cout << n << ' ';
    std::cout << '\n';

    // --- Configurable functor with std::count_if ---
    std::cout << "\n=== Configurable Functor (GreaterThan) ===\n";
    std::vector<int> values{1, 5, 12, 3, 18, 7, 25, 2};

    GreaterThan gt10{10};
    auto count = std::count_if(values.begin(), values.end(), gt10);
    std::cout << "Values greater than 10: " << count << '\n';

    GreaterThan gt5{5};
    count = std::count_if(values.begin(), values.end(), gt5);
    std::cout << "Values greater than 5:  " << count << '\n';

    // Key points:
    // 1. operator() must be a member function
    // 2. It can take any number/type of parameters
    // 3. Functors = classes with operator() - callable objects with state
    // 4. Functors can be passed to STL algorithms as comparators/predicates

    return 0;
}
