// Lessons 8 and 14: string and string_view, regex_match vs regex_search, captures, replace, chrono.
#include <chrono>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <thread>

void log(std::string_view msg) { std::cout << "log: " << msg << '\n'; }   // accepts string, literal, substring

int main() {
    using namespace std::chrono_literals;

    std::string s = "hello world";
    log(s);
    log("literal");                                     // no temporary std::string is built
    auto pos = s.find("world");
    if (pos != std::string::npos) std::cout << "found at " << pos << ", view: " << std::string_view(s).substr(pos) << '\n';
    std::cout << "(s.find('z') == npos) = " << (s.find('z') == std::string::npos) << '\n';

    std::regex re("ab+c");
    std::cout << std::boolalpha
              << "match  abbbc   " << std::regex_match("abbbc", re) << '\n'
              << "match  xabbbcx " << std::regex_match("xabbbcx", re) << "   (whole string must fit)\n"
              << "search xabbbcx " << std::regex_search("xabbbcx", re) << "   (found inside)\n";

    std::string line = "temp=21.5C humidity=40%";
    std::regex kv(R"((\w+)=([\d.]+))");                 // raw string: no doubled backslashes
    std::smatch m;
    if (std::regex_search(line, m, kv)) std::cout << "first match: " << m[1] << " is " << m[2] << '\n';
    for (std::sregex_iterator it(line.begin(), line.end(), kv), end; it != end; ++it)
        std::cout << "  " << (*it)[1] << " -> " << (*it)[2] << '\n';
    std::cout << std::regex_replace(line, kv, "$2:$1") << '\n';

    auto t0 = std::chrono::steady_clock::now();         // monotonic clock for measuring intervals
    std::this_thread::sleep_for(50ms);
    auto t1 = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
    std::cout << "slept about " << (ms >= 50 ? "50+" : "less than 50") << " ms\n";

    std::chrono::seconds sec = 90s;
    std::chrono::milliseconds milli = sec;              // implicit: lossless
    auto min = std::chrono::duration_cast<std::chrono::minutes>(sec);   // explicit: truncates
    std::cout << milli.count() << " ms, " << min.count() << " minute(s)\n";
}
