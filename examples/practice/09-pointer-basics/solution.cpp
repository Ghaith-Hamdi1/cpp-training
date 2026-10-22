// Exercise 9: pointers, arrays and function pointers.
//
// maxOf:         the largest of n ints (n >= 1). Walk the array with a pointer.
// swapInts:      swap the two ints the pointers point to.
// reverseInPlace: reverse the array a[0..n) in place, without a second array.
// countIf:       how many of the n ints satisfy pred (pred is a pointer to a function).
#include <cstddef>
#include "../check.h"

int maxOf(const int* a, std::size_t n)
{
    int best = *a;
    for (const int* p = a + 1; p != a + n; ++p)
        if (*p > best) best = *p;
    return best;
}

void swapInts(int* a, int* b)
{
    const int t = *a;
    *a = *b;
    *b = t;
}

void reverseInPlace(int* a, std::size_t n)
{
    if (n < 2) return;
    int* lo = a;
    int* hi = a + n - 1;
    while (lo < hi) swapInts(lo++, hi--);
}

std::size_t countIf(const int* a, std::size_t n, bool (*pred)(int))
{
    std::size_t count = 0;
    for (std::size_t i = 0; i < n; ++i)
        if (pred(a[i])) ++count;
    return count;
}

static bool isEven(int x) { return x % 2 == 0; }

int main()
{
    int a[] = {3, 9, -4, 7, 9, 1};
    CHECK(maxOf(a, 6) == 9);
    int one[] = {-5};
    CHECK(maxOf(one, 1) == -5);
    int neg[] = {-9, -2, -7};
    CHECK(maxOf(neg, 3) == -2);

    int x = 1, y = 2;
    swapInts(&x, &y);
    CHECK(x == 2 && y == 1);

    int r[] = {1, 2, 3, 4, 5};
    reverseInPlace(r, 5);
    CHECK(r[0] == 5 && r[1] == 4 && r[2] == 3 && r[3] == 2 && r[4] == 1);
    int e[] = {1, 2, 3, 4};
    reverseInPlace(e, 4);
    CHECK(e[0] == 4 && e[1] == 3 && e[2] == 2 && e[3] == 1);
    int s1[] = {7};
    reverseInPlace(s1, 1);
    CHECK(s1[0] == 7);

    CHECK(countIf(a, 6, isEven) == 1);
    int evens[] = {2, 4, 6, 7};
    CHECK(countIf(evens, 4, isEven) == 3);
    CHECK(countIf(evens, 0, isEven) == 0);
    return finish("09 pointer basics");
}
