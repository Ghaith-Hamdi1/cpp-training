// Chapter 18 - Project 2: Bubble Sort
// =====================================
// Bubble sort repeatedly compares adjacent elements and swaps them
// if they are out of order, "bubbling" the largest value to the end.
//
// Optimization: if no swaps occur during a pass, the array is already
// sorted and we can terminate early. This makes the best case O(n).
//
// Key ideas:
//   - Inner loop compares arr[j] with arr[j+1]
//   - Each outer-loop iteration places one more element in its final position
//   - Early termination via a "swapped" flag

#include <algorithm> // std::swap
#include <iostream>
#include <iterator> // std::size

void bubbleSort(int *arr, int length)
{
    for (int iteration{0}; iteration < length - 1; ++iteration)
    {
        bool swapped{false}; // Track whether any swap happened this pass

        // Each pass puts the next-largest element into place,
        // so the inner loop shrinks by `iteration` each time.
        for (int j{0}; j < length - 1 - iteration; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // Early termination: if no swaps occurred, array is sorted
        if (!swapped)
        {
            std::cout << "(Early exit on iteration " << iteration + 1 << ")\n";
            return;
        }
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
    // Unsorted array
    int arr1[]{6, 3, 8, 1, 5, 2, 7, 4};
    constexpr int len1{static_cast<int>(std::size(arr1))};

    std::cout << "Before bubble sort: ";
    printArray(arr1, len1);

    bubbleSort(arr1, len1);

    std::cout << "After  bubble sort: ";
    printArray(arr1, len1);

    // Already-sorted array - demonstrates early termination
    std::cout << "\n--- Already sorted array ---\n";
    int arr2[]{1, 2, 3, 4, 5};
    constexpr int len2{static_cast<int>(std::size(arr2))};

    std::cout << "Before: ";
    printArray(arr2, len2);

    bubbleSort(arr2, len2);

    std::cout << "After:  ";
    printArray(arr2, len2);

    return 0;
}
