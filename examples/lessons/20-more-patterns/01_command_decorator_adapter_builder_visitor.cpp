// Lesson 15: Command with undo, Decorator, Adapter, Builder, Visitor with std::variant, and a session state machine.
// Compile with -std=c++20.
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

// ---- Command with undo -------------------------------------------------------------------------------------------------
struct Document { std::string text; };
struct Command {
    virtual ~Command() = default;
    virtual void execute(Document&) = 0;
    virtual void undo(Document&) = 0;
};
struct Append : Command {
    std::string s;
    explicit Append(std::string x) : s(std::move(x)) {}
    void execute(Document& d) override { d.text += s; }
    void undo(Document& d) override { d.text.resize(d.text.size() - s.size()); }
};
class Editor {
    Document doc_;
    std::vector<std::unique_ptr<Command>> done_;                       // the history IS the undo stack
public:
    void run(std::unique_ptr<Command> c) { c->execute(doc_); done_.push_back(std::move(c)); }
    void undo() { if (!done_.empty()) { done_.back()->undo(doc_); done_.pop_back(); } }
    const std::string& text() const { return doc_.text; }
};

// ---- Decorator ---------------------------------------------------------------------------------------------------------
struct Sink { virtual ~Sink() = default; virtual std::string write(const std::string&) = 0; };
struct Plain : Sink { std::string write(const std::string& s) override { return s; } };
struct Upper : Sink {                                                  // wraps another Sink and adds behaviour
    std::unique_ptr<Sink> inner;
    explicit Upper(std::unique_ptr<Sink> i) : inner(std::move(i)) {}
    std::string write(const std::string& s) override { std::string r = inner->write(s); for (char& c : r) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c))); return r; }
};
struct Bracket : Sink {
    std::unique_ptr<Sink> inner;
    explicit Bracket(std::unique_ptr<Sink> i) : inner(std::move(i)) {}
    std::string write(const std::string& s) override { return "[" + inner->write(s) + "]"; }
};

// ---- Adapter -----------------------------------------------------------------------------------------------------------
struct LegacyFeed { int priceInCents() const { return 10025; } };       // an interface we cannot change
struct PriceSource { virtual ~PriceSource() = default; virtual double price() const = 0; };   // the one our code expects
struct LegacyAdapter : PriceSource {
    LegacyFeed feed;
    double price() const override { return feed.priceInCents() / 100.0; }
};

// ---- Builder -----------------------------------------------------------------------------------------------------------
struct Order { std::string sym; int qty; double px; bool ioc; };
class OrderBuilder {
    Order o_{"", 0, 0.0, false};
public:
    OrderBuilder& symbol(std::string s) { o_.sym = std::move(s); return *this; }
    OrderBuilder& qty(int q) { o_.qty = q; return *this; }
    OrderBuilder& price(double p) { o_.px = p; return *this; }
    OrderBuilder& immediateOrCancel() { o_.ioc = true; return *this; }
    Order build() const { return o_; }
};

// ---- Visitor with std::variant -----------------------------------------------------------------------------------------
struct Circle { double r; };
struct Rect { double w, h; };
using Shape = std::variant<Circle, Rect>;
struct Area {
    double operator()(const Circle& c) const { return 3.0 * c.r * c.r; }
    double operator()(const Rect& r) const { return r.w * r.h; }
};

// ---- Session state machine ---------------------------------------------------------------------------------------------
struct Disconnected {};
struct LoggedOn { int nextSeq = 1; };
struct Stopped { std::string reason; };
using Session = std::variant<Disconnected, LoggedOn, Stopped>;
Session onEvent(const Session& s, const std::string& ev) {
    return std::visit([&](const auto& st) -> Session {
        using T = std::decay_t<decltype(st)>;
        if constexpr (std::is_same_v<T, Disconnected>) { if (ev == "logon") return LoggedOn{}; }
        else if constexpr (std::is_same_v<T, LoggedOn>) { if (ev == "msg") return LoggedOn{st.nextSeq + 1}; if (ev == "logout") return Stopped{"logout"}; }
        return st;                                                    // events that do not apply leave the state alone
    }, s);
}

int main()
{
    Editor ed;
    ed.run(std::make_unique<Append>("Hello"));
    ed.run(std::make_unique<Append>(", world"));
    std::cout << "after two commands: \"" << ed.text() << "\"";
    ed.undo();
    std::cout << ", after one undo: \"" << ed.text() << "\"\n";

    std::unique_ptr<Sink> s = std::make_unique<Bracket>(std::make_unique<Upper>(std::make_unique<Plain>()));
    std::cout << "decorators stacked: " << s->write("feed") << '\n';

    LegacyAdapter adapter;
    const PriceSource& src = adapter;
    std::cout << "adapter converts cents to dollars: " << src.price() << '\n';

    Order o = OrderBuilder().symbol("ESZ5").qty(10).price(5000.25).immediateOrCancel().build();
    std::cout << "builder: " << o.sym << ' ' << o.qty << " @ " << o.px << (o.ioc ? " IOC" : "") << '\n';

    std::vector<Shape> shapes{Circle{2}, Rect{3, 4}};
    double total = 0;
    for (const auto& sh : shapes) total += std::visit(Area{}, sh);
    std::cout << "visitor over a variant: total area " << total << '\n';

    Session st = Disconnected{};
    for (const char* ev : {"msg", "logon", "msg", "msg", "logout", "msg"}) {
        st = onEvent(st, ev);
        std::cout << ev << " -> " << (std::holds_alternative<Disconnected>(st) ? "Disconnected" : std::holds_alternative<LoggedOn>(st) ? "LoggedOn(next " + std::to_string(std::get<LoggedOn>(st).nextSeq) + ")" : "Stopped") << '\n';
    }
}
