// Lesson 6 (RAII and exceptions): a scope guard, the strong exception guarantee by copy-and-swap, why noexcept moves
// matter to std::vector, and returning errors without exceptions. Compile with -std=c++20.
#include <charconv>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// ---- a scope guard: RAII for "run this when the scope ends" ------------------------------------------------------------
template <typename F>
class ScopeExit {
    F f_;
    bool active_ = true;
public:
    explicit ScopeExit(F f) : f_(std::move(f)) {}
    ScopeExit(const ScopeExit&) = delete;
    ScopeExit& operator=(const ScopeExit&) = delete;
    void release() { active_ = false; }                          // commit: the cleanup is no longer needed
    ~ScopeExit() { if (active_) f_(); }
};

void transfer(bool fail)
{
    std::cout << "  begin transaction\n";
    ScopeExit rollback([] { std::cout << "  ROLLBACK (guard ran)\n"; });
    if (fail) throw std::runtime_error("step failed");
    std::cout << "  all steps done\n";
    rollback.release();                                          // success: do not roll back
    std::cout << "  COMMIT\n";
}

// ---- strong guarantee: build the new state aside, then swap (which cannot throw) -------------------------------------
struct Thrower {                                                 // throws on the Nth copy after arm(N)
    static int budget;
    static void arm(int n) { budget = n; }
    std::string s;
    Thrower(std::string v) : s(std::move(v)) {}
    Thrower(const Thrower& o) : s(o.s) { if (budget > 0 && --budget == 0) throw std::runtime_error("copy failed"); }
};
int Thrower::budget = 0;

class Table {
    std::vector<Thrower> rows_;
public:
    Table(std::initializer_list<const char*> init) { for (auto s : init) rows_.emplace_back(s); }
    void replaceAll(const std::vector<Thrower>& fresh)
    {
        std::vector<Thrower> copy(fresh);                        // may throw: *this is still untouched
        rows_.swap(copy);                                        // commit: swap does not throw
    }
    std::size_t size() const { return rows_.size(); }
    const std::string& first() const { return rows_.front().s; }
};

// ---- noexcept moves and std::vector growth --------------------------------------------------------------------------
struct Quiet {                                                    // noexcept move
    static int copies, moves;
    Quiet() = default;
    Quiet(const Quiet&) { ++copies; }
    Quiet(Quiet&&) noexcept { ++moves; }
};
int Quiet::copies = 0, Quiet::moves = 0;
struct Loud {                                                     // move may throw (not marked noexcept)
    static int copies, moves;
    Loud() = default;
    Loud(const Loud&) { ++copies; }
    Loud(Loud&&) { ++moves; }
};
int Loud::copies = 0, Loud::moves = 0;

// ---- errors without exceptions ---------------------------------------------------------------------------------------------
std::optional<int> parseInt(std::string_view s)
{
    int v = 0;
    auto r = std::from_chars(s.data(), s.data() + s.size(), v);
    if (r.ec != std::errc{} || r.ptr != s.data() + s.size()) return std::nullopt;
    return v;
}

int main()
{
    std::cout << "transfer(ok):\n";
    transfer(false);
    std::cout << "transfer(fail):\n";
    try { transfer(true); } catch (const std::exception& e) { std::cout << "  caught: " << e.what() << '\n'; }

    Table t{"a", "b"};
    std::vector<Thrower> fresh{Thrower("x"), Thrower("y"), Thrower("z")};
    Thrower::arm(2);                                             // the next replaceAll will throw on its second copy
    try { t.replaceAll(fresh); } catch (const std::exception& e) { std::cout << "replaceAll threw (" << e.what() << "), table unchanged: size " << t.size() << ", first " << t.first() << '\n'; }

    std::vector<Quiet> q;
    for (int i = 0; i < 100; ++i) q.emplace_back();
    std::vector<Loud> l;
    for (int i = 0; i < 100; ++i) l.emplace_back();
    std::cout << "vector growth with noexcept move: copies " << Quiet::copies << ", moves " << (Quiet::moves > 0 ? "many" : "0") << '\n';
    std::cout << "vector growth with possibly-throwing move: copies " << (Loud::copies > 0 ? "many" : "0") << ", moves " << Loud::moves << '\n';

    for (std::string_view s : {"42", "4x2", ""}) {
        auto v = parseInt(s);
        std::cout << "parseInt(\"" << s << "\") = " << (v ? std::to_string(*v) : "no value") << '\n';
    }
}
