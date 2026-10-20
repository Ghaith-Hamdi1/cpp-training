// Chapter 17 - Project 11: Multidimensional C-style Arrays
// Topics: 2D arrays, row-major order, nested init, Cartesian mapping
// Compile: g++ -std=c++20 -Wall -Wextra -o program main.cpp

#include <iostream>

int main()
{
    // -----------------------------------------------------------------------
    // 1. Declaration: int arr[rows][cols]
    //    Memory layout is ROW-MAJOR: row 0 elements first, then row 1, etc.
    // -----------------------------------------------------------------------
    std::cout << "--- 1. 2D array declaration ---\n";

    constexpr int rows{3};
    constexpr int cols{4};

    int matrix[rows][cols]{}; // value-initialized (all zeros)

    // Fill with sequential values
    int counter{1};
    for (int r{0}; r < rows; ++r)
        for (int c{0}; c < cols; ++c)
            matrix[r][c] = counter++;

    // Print as a table
    for (int r{0}; r < rows; ++r)
    {
        for (int c{0}; c < cols; ++c)
            std::cout << matrix[r][c] << '\t';
        std::cout << '\n';
    }

    // -----------------------------------------------------------------------
    // 2. Initialization with nested braces
    // -----------------------------------------------------------------------
    std::cout << "\n--- 2. Nested-brace initialization ---\n";

    int grid[2][3]{
        {1, 2, 3}, // row 0
        {4, 5, 6}  // row 1
    };

    for (int r{0}; r < 2; ++r)
    {
        for (int c{0}; c < 3; ++c)
            std::cout << grid[r][c] << ' ';
        std::cout << '\n';
    }

    // -----------------------------------------------------------------------
    // 3. Row-major order - why row should be the OUTER loop
    //    Elements in the same row are contiguous in memory.
    //    Iterating row-first is cache-friendly (sequential access pattern).
    //
    //    Memory layout of grid[2][3]:
    //    [1][2][3] [4][5][6]   (row 0 then row 1, contiguous)
    // -----------------------------------------------------------------------
    std::cout << "\n--- 3. Row-major memory layout ---\n";
    std::cout << "Elements in memory order: ";
    // Casting to int* gives a pointer to the flat storage
    int *flat{&grid[0][0]};
    for (int i{0}; i < 2 * 3; ++i)
        std::cout << flat[i] << ' ';
    std::cout << '\n';

    // -----------------------------------------------------------------------
    // 4. PITFALL: Cartesian {x, y} vs array [row][col]
    //
    //    In a Cartesian coordinate system:
    //      x = column (horizontal), y = row (vertical)
    //
    //    So Cartesian {x, y} maps to array index [y][x]  - NOT [x][y]!
    //
    //    Example: point at Cartesian (2, 1) is at grid[1][2]
    // -----------------------------------------------------------------------
    std::cout << "\n--- 4. Cartesian vs array coordinates ---\n";

    // A 4x3 grid (4 cols, 3 rows in Cartesian terms)
    constexpr int gridRows{3};
    constexpr int gridCols{4};
    int world[gridRows][gridCols]{};

    // Place a marker at Cartesian position {x=2, y=1}
    int cartesianX{2};
    int cartesianY{1};
    world[cartesianY][cartesianX] = 99; // array[y][x]

    std::cout << "Marker at Cartesian (" << cartesianX << ", " << cartesianY << "):\n";
    for (int r{0}; r < gridRows; ++r)
    {
        for (int c{0}; c < gridCols; ++c)
            std::cout << world[r][c] << '\t';
        std::cout << '\n';
    }

    // -----------------------------------------------------------------------
    // 5. Partial initialization - unspecified elements are zero
    // -----------------------------------------------------------------------
    std::cout << "\n--- 5. Partial init ---\n";

    int sparse[3][3]{
        {1},      // {1, 0, 0}
        {0, 2},   // {0, 2, 0}
        {0, 0, 3} // {0, 0, 3}
    };

    for (int r{0}; r < 3; ++r)
    {
        for (int c{0}; c < 3; ++c)
            std::cout << sparse[r][c] << ' ';
        std::cout << '\n';
    }

    // -----------------------------------------------------------------------
    // 6. 3D array - syntax extends naturally
    // -----------------------------------------------------------------------
    std::cout << "\n--- 6. 3D array ---\n";

    int cube[2][2][2]{
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}};

    for (int d{0}; d < 2; ++d)
    {
        std::cout << "Depth " << d << ": ";
        for (int r{0}; r < 2; ++r)
            for (int c{0}; c < 2; ++c)
                std::cout << cube[d][r][c] << ' ';
        std::cout << '\n';
    }

    // -----------------------------------------------------------------------
    // KEY TAKEAWAY:
    //   C++ 2D arrays use row-major order. Iterate with row as the outer
    //   loop for cache efficiency. Remember: Cartesian {x,y} -> arr[y][x].
    // -----------------------------------------------------------------------

    return 0;
}
