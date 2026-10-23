// ============================================================================
// Chapter 19 - Project 07: Pointers to Pointers and Dynamic 2D Arrays
// ============================================================================
// A pointer to a pointer (int**) stores the address of another pointer.
// This is commonly used to create dynamic 2D arrays.
//
// Key points:
//   - int** ptrptr = &ptr;  - ptrptr points to ptr, which points to an int
//   - **ptrptr dereferences twice to reach the final value
//   - Dynamic 2D arrays: allocate an array of row pointers, then allocate
//     each row separately
//   - Deallocation must happen in REVERSE order: rows first, then the
//     pointer array
//   - Flattening 2D into 1D (row * cols + col) is a simpler alternative
// ============================================================================

#include <iostream>

int main()
{
    // -----------------------------------------------------------------
    // 1. Basic pointer to pointer
    // -----------------------------------------------------------------
    std::cout << "=== Pointer to Pointer Basics ===\n\n";

    int value{42};
    int *ptr{&value};   // ptr points to value
    int **ptrptr{&ptr}; // ptrptr points to ptr

    std::cout << "value       = " << value << '\n';
    std::cout << "*ptr        = " << *ptr << '\n';
    std::cout << "**ptrptr    = " << **ptrptr << '\n';

    // Modifying through the double pointer
    **ptrptr = 100;
    std::cout << "After **ptrptr = 100: value = " << value << '\n';

    // -----------------------------------------------------------------
    // 2. Dynamic 2D array using pointer to pointer
    // -----------------------------------------------------------------
    std::cout << "\n=== Dynamic 2D Array ===\n\n";

    constexpr int rows{3};
    constexpr int cols{4};

    // Step 1: Allocate an array of row pointers
    int **matrix{new int *[rows]};

    // Step 2: For each row, allocate an array of ints
    for (int r{0}; r < rows; ++r)
        matrix[r] = new int[cols]{}; // zero-initialized

    // Fill with sample data: matrix[r][c] = r * cols + c
    for (int r{0}; r < rows; ++r)
        for (int c{0}; c < cols; ++c)
            matrix[r][c] = r * cols + c;

    // Print the 2D array
    std::cout << "Matrix (" << rows << "x" << cols << "):\n";
    for (int r{0}; r < rows; ++r)
    {
        std::cout << "  ";
        for (int c{0}; c < cols; ++c)
            std::cout << matrix[r][c] << '\t';
        std::cout << '\n';
    }

    // Step 3: Deallocate in REVERSE order - rows first, then the pointer array
    for (int r{0}; r < rows; ++r)
        delete[] matrix[r]; // free each row
    delete[] matrix;        // free the array of row pointers
    matrix = nullptr;

    std::cout << "2D array deallocated (rows first, then pointer array).\n";

    // -----------------------------------------------------------------
    // 3. Simpler alternative: flattened 1D array
    // -----------------------------------------------------------------
    std::cout << "\n=== Flattened 1D Alternative ===\n\n";

    // A single contiguous allocation is simpler and cache-friendlier
    int *flat{new int[rows * cols]{}};

    // Access with: flat[row * cols + col]
    for (int r{0}; r < rows; ++r)
        for (int c{0}; c < cols; ++c)
            flat[r * cols + c] = r * cols + c;

    std::cout << "Flat matrix (" << rows << "x" << cols << "):\n";
    for (int r{0}; r < rows; ++r)
    {
        std::cout << "  ";
        for (int c{0}; c < cols; ++c)
            std::cout << flat[r * cols + c] << '\t';
        std::cout << '\n';
    }

    delete[] flat;
    flat = nullptr;
    std::cout << "Flat array deallocated (single delete[]).\n";

    std::cout << "\nAll memory freed correctly.\n";
    return 0;
}
