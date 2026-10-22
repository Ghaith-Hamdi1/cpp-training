// Lesson 8: vector growth and invalidation, map::operator[], erase-remove, algorithms, priority_queue.
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
    std::vector<int> v;
    std::size_t last = v.capacity();
    std::cout << "capacity changes while push_back-ing 20 ints: ";
    for (int i = 0; i < 20; ++i) {
        v.push_back(i);
        if (v.capacity() != last) { last = v.capacity(); std::cout << last << ' '; }
    }
    std::cout << "(geometric growth)\n";

    std::vector<int> r;
    r.reserve(100);                                     // capacity 100, size 0
    std::cout << "after reserve(100): size " << r.size() << ", capacity " << r.capacity() << '\n';

    std::map<std::string, int> m;
    if (m["x"] == 0) {}                                 // operator[] INSERTS a default value
    std::cout << "map size after looking up a missing key with []: " << m.size() << '\n';
    std::cout << "contains(\"y\") does not insert: " << std::boolalpha << m.contains("y") << ", size " << m.size() << '\n';

    std::vector<int> e{1, 2, 3, 4, 5, 6};
    e.erase(std::remove_if(e.begin(), e.end(), [](int x) { return x % 2 == 0; }), e.end());   // erase-remove
    for (int x : e) std::cout << x << ' ';
    std::cout << " // evens removed\n";
    std::vector<int> e2{1, 2, 3, 4};
    std::erase_if(e2, [](int x) { return x % 2 == 0; });  // C++20: one call
    std::cout << "erase_if left " << e2.size() << " elements\n";

    std::vector<int> w{1, 2, 3, 4, 5};
    (void)std::remove(w.begin(), w.end(), 3);              // does NOT shrink the container
    std::cout << "size after std::remove alone: " << w.size() << " (still 5)\n";

    std::vector<int> a{5, 2, 9, 2, 7, 4};
    std::sort(a.begin(), a.end());
    auto pos = std::lower_bound(a.begin(), a.end(), 5); // binary search: range must be sorted
    std::cout << "first >= 5 is " << *pos << " at index " << (pos - a.begin()) << '\n';
    std::cout << "sum = " << std::accumulate(a.begin(), a.end(), 0)
              << ", count of 2 = " << std::count(a.begin(), a.end(), 2) << '\n';
    std::transform(a.begin(), a.end(), a.begin(), [](int x) { return x * x; });
    for (int x : a) std::cout << x << ' ';
    std::cout << " // squared\n";

    std::priority_queue<int> maxHeap;
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    for (int x : {5, 1, 8, 3}) { maxHeap.push(x); minHeap.push(x); }
    std::cout << "max-heap top " << maxHeap.top() << ", min-heap top " << minHeap.top() << '\n';

    std::unordered_set<int> seen;
    std::cout << "insert(5) first time: " << seen.insert(5).second << ", second time: " << seen.insert(5).second << '\n';
}
