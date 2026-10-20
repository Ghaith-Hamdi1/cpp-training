// Chapter 16 - Project 02: List Constructor vs Length Constructor
// ==============================================================
// One of C++'s most confusing initialization gotchas:
//   std::vector<int> v{ 5 };   // List constructor  → 1 element with value 5
//   std::vector<int> v( 5 );   // Length constructor → 5 elements, all value-initialized to 0
//
// This distinction matters enormously. Getting it wrong means
// your vector has a completely different size and contents.
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>

// Helper: prints all elements of a vector with its size
void printVector(const std::vector<int> &v, const char *label)
{
    std::cout << label << " (size=" << v.size() << "): { ";
    for (std::size_t i{0}; i < v.size(); ++i)
    {
        if (i > 0)
            std::cout << ", ";
        std::cout << v[i];
    }
    std::cout << " }\n";
}

int main()
{
    // --- 1. List constructor: { n } creates ONE element with value n ---
    std::vector<int> listInit{5};
    printVector(listInit, "vector<int>{ 5 }   (list ctor)");
    // Output: size=1, contains { 5 }

    // --- 2. Length constructor: ( n ) creates n value-initialized elements ---
    std::vector<int> lengthInit(5);
    printVector(lengthInit, "vector<int>( 5 )   (length ctor)");
    // Output: size=5, contains { 0, 0, 0, 0, 0 }

    // --- 3. More examples to solidify the distinction ---
    std::vector<int> a{3, 4, 5}; // List: 3 elements → 3, 4, 5
    std::vector<int> b(3);       // Length: 3 elements → 0, 0, 0

    printVector(a, "\nvector<int>{ 3, 4, 5 } (list ctor)");
    printVector(b, "vector<int>( 3 )       (length ctor)");

    // --- 4. Length constructor with a fill value ---
    // ( count, value ) → creates 'count' copies of 'value'
    std::vector<int> filled(4, 99);
    printVector(filled, "\nvector<int>( 4, 99 )   (fill ctor)");
    // Output: size=4, contains { 99, 99, 99, 99 }

    // --- 5. The gotcha with a single value ---
    std::cout << "\n=== THE GOTCHA ===\n";
    std::cout << "vector<int>{ 10 } has " << std::vector<int>{10}.size()
              << " element(s), value = " << std::vector<int>{10}[0] << '\n';
    std::cout << "vector<int>( 10 ) has " << std::vector<int>(10).size()
              << " element(s), all zeros\n";

    return 0;
}
