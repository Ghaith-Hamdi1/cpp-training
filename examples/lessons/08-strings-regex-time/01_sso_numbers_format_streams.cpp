// Lesson 10: small string optimisation and capacity growth, converting numbers with from_chars/to_chars/stoi,
// std::format, string streams and file streams. Compile with -std=c++23.
#include <charconv>
#include <cstdio>
#include <format>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

int main()
{
    // SSO: short strings live inside the std::string object itself
    std::string small = "hello";
    std::string big(40, 'x');
    auto inside = [](const std::string& s) {
        auto p = reinterpret_cast<const char*>(&s);
        return s.data() >= p && s.data() < p + sizeof(s);
    };
    std::cout << "sizeof(std::string) = " << sizeof(std::string) << ", empty capacity = " << std::string().capacity() << '\n';
    std::cout << "\"hello\" stored inside the object: " << std::boolalpha << inside(small) << ", 40 chars stored inside: " << inside(big) << '\n';

    std::string g;
    std::size_t last = g.capacity();
    int reallocations = 0;
    for (int i = 0; i < 1000; ++i) { g += 'a'; if (g.capacity() != last) { ++reallocations; last = g.capacity(); } }
    std::cout << "appending 1000 chars one by one reallocated " << reallocations << " times; with reserve(1000) first: ";
    std::string r; r.reserve(1000);
    const char* before = r.data();
    for (int i = 0; i < 1000; ++i) r += 'a';
    std::cout << (r.data() == before ? "0 times" : "it moved") << '\n';

    // numbers and text
    int v = 0;
    std::string_view num = "1234";
    auto res = std::from_chars(num.data(), num.data() + num.size(), v);
    std::cout << "from_chars(\"1234\") -> " << v << ", ok " << (res.ec == std::errc{}) << '\n';
    std::string_view bad = "12x4";
    auto res2 = std::from_chars(bad.data(), bad.data() + bad.size(), v);
    std::cout << "from_chars(\"12x4\") stopped at \"" << res2.ptr << "\" and returned " << v << " (no exception)\n";
    try { (void)std::stoi("abc"); } catch (const std::invalid_argument&) { std::cout << "stoi(\"abc\") throws invalid_argument\n"; }
    try { (void)std::stoi("99999999999"); } catch (const std::out_of_range&) { std::cout << "stoi(\"99999999999\") throws out_of_range\n"; }
    char buf[32];
    auto tr = std::to_chars(buf, buf + sizeof(buf), 255, 16);
    std::cout << "to_chars(255, base 16) = " << std::string_view(buf, tr.ptr - buf) << '\n';

    // formatting
    std::cout << std::format("{:>8}|{:<8}|{:^8}|\n", "right", "left", "mid");
    std::cout << std::format("{:08.3f} {:#x} {:#b} {:+d} {}\n", 3.14159, 255, 5, 7, true);
    std::cout << std::format("{1} before {0}\n", "world", "hello");

    // string streams
    std::istringstream in("42 3.5 word");
    int a; double b; std::string w;
    in >> a >> b >> w;
    std::cout << "istringstream parsed: " << a << ' ' << b << ' ' << w << '\n';
    std::ostringstream out;
    out << "id=" << 7 << " px=" << 101.25;
    std::cout << "ostringstream built: " << out.str() << '\n';

    // file streams
    {
        std::ofstream f("strings_demo.tmp");
        f << "first line\nsecond line\n";
    }                                                              // closed by the destructor
    std::ifstream f("strings_demo.tmp");
    std::string line, lastLine;
    int n = 0;
    while (std::getline(f, line)) { ++n; lastLine = line; }        // getline returns false at end of file
    std::cout << "read " << n << " lines with getline; last: " << lastLine << '\n';
    f.close();
    std::remove("strings_demo.tmp");

    // splitting a CSV line with getline
    std::istringstream csv("apple,5000.25,10");
    std::vector<std::string> fields;
    for (std::string x; std::getline(csv, x, ',');) fields.push_back(x);
    std::cout << "split into " << fields.size() << " fields, second is " << fields[1] << '\n';
}
