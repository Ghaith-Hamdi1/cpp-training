// Chapter 17 - Project 12: Multidimensional std::array
// Topics: 2D std::array, alias template, flattening, reversed dimensions
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <array>
#include <iostream>
#include <cstddef> // std::size_t

// -----------------------------------------------------------------------
// PROBLEM: The raw 2D std::array syntax is verbose and dimensions
// appear reversed from what you'd expect:
//
//   std::array<std::array<int, cols>, rows>
//              ^^^^^^^^^^^^^^^^^^^^  ^^^^^
//              inner = one row        outer = number of rows
//
// The inner array represents columns (one row), and the outer array
// represents rows. So cols comes first in the template, but logically
// rows come first when you access arr[row][col].
// -----------------------------------------------------------------------

// -----------------------------------------------------------------------
// SOLUTION: Use an alias template to make it readable.
// -----------------------------------------------------------------------
template <typename T, std::size_t Rows, std::size_t Cols>
using Array2d = std::array<std::array<T, Cols>, Rows>;

// Generic print function for 2D arrays
template <typename T, std::size_t Rows, std::size_t Cols>
void print2d(const Array2d<T, Rows, Cols> &arr)
{
    for (const auto &row : arr)
    {
        for (const auto &elem : row)
            std::cout << elem << '\t';
        std::cout << '\n';
    }
}

int main()
{
    // -----------------------------------------------------------------------
    // 1. Raw syntax (verbose, dimensions look reversed)
    // -----------------------------------------------------------------------
    std::cout << "--- 1. Raw 2D std::array syntax ---\n";

    // 3 rows, 4 columns - but template reads <array<int,4>, 3>
    std::array<std::array<int, 4>, 3> raw{{{{1, 2, 3, 4}},
                                           {{5, 6, 7, 8}},
                                           {{9, 10, 11, 12}}}};

    for (std::size_t r{0}; r < raw.size(); ++r)
    {
        for (std::size_t c{0}; c < raw[0].size(); ++c)
            std::cout << raw[r][c] << '\t';
        std::cout << '\n';
    }

    // -----------------------------------------------------------------------
    // 2. Alias template - clean and readable
    // -----------------------------------------------------------------------
    std::cout << "\n--- 2. Array2d alias template ---\n";

    Array2d<int, 3, 4> grid{{{{10, 20, 30, 40}},
                             {{50, 60, 70, 80}},
                             {{90, 100, 110, 120}}}};

    print2d(grid);

    // -----------------------------------------------------------------------
    // 3. constexpr 2D array
    // -----------------------------------------------------------------------
    std::cout << "\n--- 3. constexpr 2D array ---\n";

    constexpr Array2d<int, 2, 3> constGrid{{{{1, 2, 3}},
                                            {{4, 5, 6}}}};

    static_assert(constGrid[0][0] == 1);
    static_assert(constGrid[1][2] == 6);

    print2d(constGrid);

    // -----------------------------------------------------------------------
    // 4. Flattening alternative - store as 1D, index with [row * cols + col]
    //    Simpler to pass around and avoids nested array verbosity.
    // -----------------------------------------------------------------------
    std::cout << "\n--- 4. Flattened 1D approach ---\n";

    constexpr std::size_t rows{3};
    constexpr std::size_t cols{4};

    std::array<int, rows * cols> flat{};

    // Fill using 2D-style indexing into flat storage
    for (std::size_t r{0}; r < rows; ++r)
        for (std::size_t c{0}; c < cols; ++c)
            flat[r * cols + c] = static_cast<int>(r * cols + c + 1);

    // Print as 2D
    for (std::size_t r{0}; r < rows; ++r)
    {
        for (std::size_t c{0}; c < cols; ++c)
            std::cout << flat[r * cols + c] << '\t';
        std::cout << '\n';
    }

    // -----------------------------------------------------------------------
    // 5. Accessing and modifying individual elements
    // -----------------------------------------------------------------------
    std::cout << "\n--- 5. Element access ---\n";

    Array2d<double, 2, 2> mat{{
        {{1.0, 0.0}},
        {{0.0, 1.0}} // identity matrix
    }};

    std::cout << "Before:\n";
    print2d(mat);

    mat[0][1] = 3.14;
    mat[1][0] = 2.72;

    std::cout << "After modification:\n";
    print2d(mat);

    // -----------------------------------------------------------------------
    // 6. Range-based for on 2D std::array
    // -----------------------------------------------------------------------
    std::cout << "\n--- 6. Range-based for ---\n";

    Array2d<char, 2, 3> letters{{{{'A', 'B', 'C'}},
                                 {{'D', 'E', 'F'}}}};

    for (const auto &row : letters)
    {
        for (char ch : row)
            std::cout << ch << ' ';
        std::cout << '\n';
    }

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   2D std::array syntax is verbose with reversed dimension order.
    //   Use an alias template (Array2d<T, Row, Col>) for clarity.
    //   Flattening into 1D with index math is a simpler alternative.
    //   C++23 std::mdspan provides a standard multidimensional view.
    // -----------------------------------------------------------------------

    return 0;
}
