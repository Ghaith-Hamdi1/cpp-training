// Exercise 10: a minimal String class that owns its memory (the Rule of Five).
//
// MyString stores a heap-allocated, '\0'-terminated copy of its text. Implement every member:
//   MyString(const char*)   copy the text (nullptr means empty)
//   copy constructor        deep copy: the two strings must not share memory
//   copy assignment         deep copy; must be safe for  s = s
//   move constructor        steal the pointer, leave the source EMPTY (size 0, c_str() == "")
//   move assignment         same, and safe for  s = std::move(s)
//   destructor              free the memory
//   size(), c_str()         c_str() never returns nullptr (an empty string gives "")
//   append(other)           add other's text to the end; must be safe for  s.append(s)
// Hints: keep the invariant "data_ is nullptr or points to size_ + 1 bytes ending in '\0'".
//        Allocate the new buffer BEFORE deleting the old one. Mark the moves noexcept.
#include <cstddef>
#include <cstring>
#include <type_traits>
#include <utility>
#include "../check.h"

class MyString {
    char* data_;
    std::size_t size_;
public:
    MyString(const char* s = "");
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);
    MyString(MyString&& other) noexcept;
    MyString& operator=(MyString&& other) noexcept;
    ~MyString();
    std::size_t size() const;
    const char* c_str() const;
    MyString& append(const MyString& other);
};

MyString::MyString(const char* s)
{
    const char* p = s ? s : "";
    size_ = std::strlen(p);
    data_ = new char[size_ + 1];
    std::memcpy(data_, p, size_ + 1);
}

MyString::MyString(const MyString& other)
    : data_(new char[other.size_ + 1]), size_(other.size_)
{
    std::memcpy(data_, other.c_str(), size_ + 1);
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other) {
        char* fresh = new char[other.size_ + 1];       // allocate first: if new throws, *this is unchanged
        std::memcpy(fresh, other.c_str(), other.size_ + 1);
        delete[] data_;
        data_ = fresh;
        size_ = other.size_;
    }
    return *this;
}

MyString::MyString(MyString&& other) noexcept
    : data_(other.data_), size_(other.size_)
{
    other.data_ = nullptr;                             // leave the source valid and empty
    other.size_ = 0;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
    if (this != &other) {
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

MyString::~MyString()
{
    delete[] data_;
}

std::size_t MyString::size() const
{
    return size_;
}

const char* MyString::c_str() const
{
    return data_ ? data_ : "";
}

MyString& MyString::append(const MyString& other)
{
    const std::size_t n = other.size_;                 // read other BEFORE touching our buffer: s.append(s) works
    char* fresh = new char[size_ + n + 1];
    std::memcpy(fresh, c_str(), size_);
    std::memcpy(fresh + size_, other.c_str(), n + 1);
    delete[] data_;
    data_ = fresh;
    size_ += n;
    return *this;
}

int main()
{
    MyString a("hello");
    CHECK(a.size() == 5 && std::strcmp(a.c_str(), "hello") == 0);
    MyString empty;
    CHECK(empty.size() == 0 && std::strcmp(empty.c_str(), "") == 0);
    MyString fromNull(nullptr);
    CHECK(fromNull.size() == 0);

    MyString b(a);                                     // copy constructor
    CHECK(std::strcmp(b.c_str(), "hello") == 0);
    CHECK(b.c_str() != a.c_str());                     // deep copy: different memory
    b.append(" world");
    CHECK(std::strcmp(b.c_str(), "hello world") == 0 && b.size() == 11);
    CHECK(std::strcmp(a.c_str(), "hello") == 0);       // a is unaffected

    MyString c("x");
    c = a;                                             // copy assignment
    CHECK(std::strcmp(c.c_str(), "hello") == 0 && c.c_str() != a.c_str());
    MyString& cref = c;
    c = cref;                                          // self-assignment must not break anything
    CHECK(std::strcmp(c.c_str(), "hello") == 0);

    MyString d(std::move(a));                          // move constructor
    CHECK(std::strcmp(d.c_str(), "hello") == 0);
    CHECK(a.size() == 0 && std::strcmp(a.c_str(), "") == 0);   // moved-from: valid and empty

    MyString e("old");
    e = std::move(d);                                  // move assignment
    CHECK(std::strcmp(e.c_str(), "hello") == 0);
    CHECK(d.size() == 0 && std::strcmp(d.c_str(), "") == 0);

    MyString f("ab");
    f.append(f);                                       // self-append
    CHECK(std::strcmp(f.c_str(), "abab") == 0 && f.size() == 4);

    static_assert(std::is_nothrow_move_constructible<MyString>::value, "mark the move constructor noexcept");
    static_assert(std::is_nothrow_move_assignable<MyString>::value, "mark the move assignment noexcept");
    return finish("10 MyString (Rule of Five)");
}
