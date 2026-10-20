// Chapter 18 - Project 5: Iterator Invalidation
// ================================================
// Iterator invalidation occurs when an iterator becomes dangling because
// the underlying container was modified (elements added or removed).
//
// PITFALL: Modifying a container (push_back, erase, insert) while
//          iterating over it causes undefined behavior.
//
// SOLUTION: Use the return value of erase() to get a valid iterator
//           to the element after the erased one.
//
// Key ideas:
//   - push_back may reallocate the vector, invalidating ALL iterators
//   - erase invalidates the erased iterator and all iterators after it
//   - erase() returns a valid iterator to the next element - use it!
//   - Never modify a container inside a range-based for-loop

#include <iostream>
#include <vector>

void printVector(const std::string &label, const std::vector<int> &v)
{
    std::cout << label;
    for (int val : v)
        std::cout << val << ' ';
    std::cout << '\n';
}

int main()
{
    // =========================================================
    // WRONG WAY - Erasing during iteration (commented out to
    // avoid UB; shown here for educational purposes)
    // =========================================================
    //
    // std::vector<int> data{ 1, 2, 3, 4, 5, 6 };
    // for (auto it = data.begin(); it != data.end(); ++it)
    // {
    //     if (*it % 2 == 0)
    //         data.erase(it);  // BUG: `it` is now invalid!
    //                          // ++it in the loop header is UB
    // }
    //
    // The problem: erase(it) invalidates `it`, then the loop
    // does ++it on an invalid iterator → undefined behavior.

    std::cout << "=== Correct way: erase with iterator revalidation ===\n";

    std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printVector("Before removing evens: ", data);

    // CORRECT: use the return value of erase() to revalidate the iterator
    auto it{data.begin()};
    while (it != data.end())
    {
        if (*it % 2 == 0)
        {
            // erase returns an iterator to the element AFTER the erased one
            it = data.erase(it); // Revalidate iterator
            // Do NOT increment - erase already moved us to the next element
        }
        else
        {
            ++it; // Only advance when we didn't erase
        }
    }

    printVector("After  removing evens: ", data);

    // =========================================================
    // WRONG WAY - push_back during iteration (commented out)
    // =========================================================
    //
    // std::vector<int> nums{ 1, 2, 3 };
    // for (auto val : nums)       // range-based for uses iterators
    // {
    //     nums.push_back(val * 2); // BUG: push_back may reallocate,
    //                              // invalidating ALL iterators
    // }
    //
    // If push_back triggers reallocation, every iterator (including
    // the one the range-based for is using internally) becomes dangling.

    std::cout << "\n=== Safe alternative: collect changes, apply after ===\n";

    std::vector<int> nums{1, 2, 3};
    printVector("Original: ", nums);

    // Collect new values in a separate container
    std::vector<int> toAdd;
    for (auto val : nums)
    {
        toAdd.push_back(val * 10);
    }

    // Apply changes AFTER the loop is done
    for (auto val : toAdd)
    {
        nums.push_back(val);
    }

    printVector("After adding *10 copies: ", nums);

    // =========================================================
    // Using std::erase_if (C++20) - the cleanest approach
    // =========================================================
    std::cout << "\n=== C++20 std::erase_if (cleanest approach) ===\n";

    std::vector<int> values{10, 15, 20, 25, 30, 35, 40};
    printVector("Before removing > 25: ", values);

    // std::erase_if handles iterator management for you
    std::erase_if(values, [](int v)
                  { return v > 25; });

    printVector("After  removing > 25: ", values);

    return 0;
}
