// Lesson 4: shallow vs deep copy, Rule of Five, and how declaring a destructor silently turns moves into copies.
#include <iostream>
#include <utility>

class Buffer {
    int* data_;
public:
    explicit Buffer(int v) : data_(new int(v)) {}
    ~Buffer() { delete data_; }
    Buffer(const Buffer& o) : data_(new int(*o.data_)) { std::cout << "  copy ctor (deep)\n"; }
    Buffer& operator=(const Buffer& o) {
        std::cout << "  copy assign\n";
        if (this != &o) *data_ = *o.data_;
        return *this;
    }
    Buffer(Buffer&& o) noexcept : data_(o.data_) { o.data_ = nullptr; std::cout << "  move ctor (steal)\n"; }
    Buffer& operator=(Buffer&& o) noexcept {
        std::cout << "  move assign\n";
        if (this != &o) { delete data_; data_ = o.data_; o.data_ = nullptr; }
        return *this;
    }
    int value() const { return data_ ? *data_ : -1; }
};

// Declaring ONLY a destructor: moves are no longer generated, so "moving" falls back to copying.
struct Quiet {
    int v = 1;
    Quiet() = default;
    Quiet(const Quiet& o) : v(o.v) { std::cout << "  Quiet copied\n"; }
};
struct Logged {
    Quiet q;
    ~Logged() { std::cout << ""; }    // user-declared destructor: no implicit move constructor
};

int main() {
    std::cout << "a(7); Buffer b = a;\n";
    Buffer a(7);
    Buffer b = a;                     // deep copy: b owns its own int
    std::cout << "  a=" << a.value() << " b=" << b.value() << '\n';

    std::cout << "Buffer c = std::move(a);\n";
    Buffer c = std::move(a);          // steals the pointer
    std::cout << "  a=" << a.value() << " (moved-from, valid but empty) c=" << c.value() << '\n';

    std::cout << "Logged l1; Logged l2 = std::move(l1);   // wanted a move, got a copy\n";
    Logged l1;
    Logged l2 = std::move(l1);
    (void)l2;
}
