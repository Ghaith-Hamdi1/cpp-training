// Chapter 18 - Project 1: Selection Sort
// ========================================
// Selection sort is a simple O(n²) sorting algorithm.
// It works by repeatedly finding the smallest element in the unsorted
// portion of the array and swapping it into the next sorted position.
//
// Key ideas:
//   - Outer loop: marks the boundary between sorted (left) and unsorted (right)
//   - Inner loop: scans the unsorted portion for the smallest element
//   - std::swap: standard utility to swap two values
//   - The outer loop stops at size-1 (not size) because when only one
//     element remains, it's already in the correct position.

#include <algorithm> // std::swap
#include <iostream>
#include <iterator> // std::size

void selectionSort(int *arr, int length)
{
    // Walk through each position that needs to be filled
    for (int startIndex{0}; startIndex < length - 1; ++startIndex)
    {
        // Assume the current position holds the smallest value
        int smallestIndex{startIndex};

        // Scan the rest of the array for a smaller element
        for (int currentIndex{startIndex + 1}; currentIndex < length; ++currentIndex)
        {
            if (arr[currentIndex] < arr[smallestIndex])
                smallestIndex = currentIndex;
        }

        // Swap the smallest found element into the sorted position
        std::swap(arr[startIndex], arr[smallestIndex]);
    }
}

void printArray(const int *arr, int length)
{
    for (int i{0}; i < length; ++i)
        std::cout << arr[i] << ' ';
    std::cout << '\n';
}

int main()
{
    int arr[]{30, 50, 20, 10, 40};
    constexpr int length{static_cast<int>(std::size(arr))};

    std::cout << "Before selection sort: ";
    printArray(arr, length);

    selectionSort(arr, length);

    std::cout << "After  selection sort: ";
    printArray(arr, length);

    // Demonstrate with another array
    int arr2[]{9, 1, 4, 7, 2, 8, 3, 6, 5};
    constexpr int length2{static_cast<int>(std::size(arr2))};

    std::cout << "\nBefore: ";
    printArray(arr2, length2);

    selectionSort(arr2, length2);

    std::cout << "After:  ";
    printArray(arr2, length2);

    return 0;
}
