// Lesson 10: custom comparators and hashes for map keys, heterogeneous lookup, try_emplace, multimap, iterator
// adaptors, std::erase_if and a first look at ranges. Compile with -std=c++20.
#include <algorithm>
#include <cctype>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <ranges>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct NoCase {                                                       // strict weak ordering that ignores case
    bool operator()(const std::string& a, const std::string& b) const {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end(),
            [](unsigned char x, unsigned char y) { return std::tolower(x) < std::tolower(y); });
    }
};

struct Instrument { std::string venue; int id; bool operator==(const Instrument&) const = default; };
struct InstrumentHash {
    std::size_t operator()(const Instrument& i) const {
        std::size_t h = std::hash<std::string>{}(i.venue);
        h ^= std::hash<int>{}(i.id) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);   // combine the two member hashes
        return h;
    }
};

int main()
{
    std::map<std::string, int, NoCase> m;                              // the comparator is part of the TYPE
    m["Alpha"] = 1; m["ALPHA"] = 2; m["beta"] = 3;
    std::cout << "NoCase map: size " << m.size() << ", m[\"alpha\"] = " << m["alpha"] << '\n';

    std::map<std::string, int, std::less<>> t{{"apple", 1}};          // std::less<> is transparent
    std::string_view key = "apple";
    std::cout << "transparent find with a string_view key: " << (t.find(key) != t.end()) << '\n';

    std::unordered_map<Instrument, double, InstrumentHash> px;
    px[{"CME", 7}] = 101.5;
    px[{"CME", 8}] = 99.0;
    std::cout << "custom hash: " << px.size() << " entries, CME/7 -> " << px[{"CME", 7}] << '\n';

    std::map<int, std::string> a{{1, "old"}};
    std::string payload(40, 'p');
    a.try_emplace(1, std::move(payload));                              // key exists: guaranteed to leave the argument alone
    std::cout << "try_emplace on an existing key left the moved argument intact: " << (payload.size() == 40) << ", value kept: " << a[1] << '\n';
    a.try_emplace(2, std::move(payload));                              // new key: the string really is moved in
    std::cout << "try_emplace on a new key moved it: source size " << payload.size() << ", stored size " << a[2].size() << '\n';

    std::multimap<std::string, int> mm{{"ESZ5", 1}, {"ESZ5", 2}, {"NQZ5", 9}};
    auto [lo, hi] = mm.equal_range("ESZ5");
    int cnt = 0, sum = 0;
    for (auto it = lo; it != hi; ++it) { ++cnt; sum += it->second; }
    std::cout << "multimap: key ESZ5 appears " << mm.count("ESZ5") << " times, equal_range sums " << sum << " over " << cnt << '\n';

    std::vector<int> src{3, 1, 2};
    std::vector<int> out;
    std::copy(src.begin(), src.end(), std::back_inserter(out));         // grows the destination instead of overwriting
    std::deque<int> front;
    std::copy(src.begin(), src.end(), std::front_inserter(front));      // each element goes to the front: reverses
    std::set<int> sorted;
    std::copy(src.begin(), src.end(), std::inserter(sorted, sorted.begin()));
    std::cout << "back_inserter: " << out.size() << " elements, front_inserter first: " << front.front() << ", inserter into a set: " << sorted.size() << '\n';

    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
    auto removed = std::erase_if(v, [](int x) { return x % 2 == 0; });  // C++20: erase-remove in one call
    std::cout << "erase_if removed " << removed << ", left " << v.size() << '\n';

    std::vector<int> w{1, 2, 3, 4, 5, 6};
    auto view = w | std::views::filter([](int x) { return x % 2 == 0; })
                  | std::views::transform([](int x) { return x * x; });   // lazy: nothing computed yet
    int total = 0;
    for (int x : view) total += x;
    std::cout << "ranges: sum of squares of the evens = " << total << '\n';
    std::ranges::sort(w, std::greater<>{});
    std::cout << "std::ranges::sort descending: first " << w.front() << '\n';
}
