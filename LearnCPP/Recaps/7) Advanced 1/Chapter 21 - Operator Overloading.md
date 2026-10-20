# Chapter 21 Recap - Operator Overloading

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- At least one operand must be a program-defined type.
- Use friend/normal functions for binary ops that don't modify the left operand (+, ==, <<).
- Use member functions for =, [], (), ->, unary ops, and compound assignment (+=, -=).
- Return `*this` by reference from operators that modify the left operand.
- Arithmetic operators that create new values should return by value.
- Implement `==` and `<` first; define others in terms of these (or use `<=>` in C++20).
- Prefix ++/-- is more efficient than postfix (avoids a temporary copy).
- `operator[]` must return a reference; provide both const and non-const versions.

### 3 Tiny Examples

1.

```cpp
Cents operator+(const Cents& c1, const Cents& c2) {
    return Cents{ c1.getCents() + c2.getCents() };
}
```

2.

```cpp
class Cents {
    int m_cents{};
public:
    Cents(int c) : m_cents{c} {}
    friend Cents operator+(const Cents& a, const Cents& b);
};
Cents operator+(const Cents& a, const Cents& b) {
    return Cents{ a.m_cents + b.m_cents };
}
```

3.

```cpp
Cents operator+(const Cents& a, const Cents& b) {
    return Cents{ a.getCents() + b.getCents() }; // uses public getter
}
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Operator overloading** - defining custom behavior for existing operators when used with program-defined types.
- **Three approaches** - friend function (private access, non-member), normal function (public interface only), member function (implicit `*this` left operand).
- **Must-be-member operators** - `=`, `[]`, `()`, `->` must be member functions.
- **Functor** - a class overloading `operator()`, making instances callable like functions while retaining state.
- **Transactional input** - implementing `operator>>` so extraction either fully succeeds or leaves the object unchanged.
- **Shallow copy** - copies pointer addresses, not the pointed-to data (default compiler behavior).
- **Deep copy** - allocates new memory and copies the actual data; required when managing dynamic memory.
- **Rule of Three** - if you need a custom destructor, copy constructor, or copy assignment operator, you likely need all three.
- **`operator<=>`** (C++20) - the spaceship operator; generates all six comparison operators from a single definition.

### Section-by-Section Detail

### 21.1 - Introduction to operator overloading

- **Operator overloading** allows redefining existing operators for **program-defined types** - at least one operand must be user-defined
- You cannot create new operators, change operand count, or alter **precedence/associativity**
- Overloaded operators should behave **intuitively** - `operator+` should add, not subtract → surprising semantics confuse users
- Operators can be implemented as **member functions**, **friend functions**, or **normal functions**, each with different trade-offs
- If the meaning isn't obvious for your type → prefer a **named function** over an operator overload

```cpp
Cents operator+(const Cents& c1, const Cents& c2) {
    return Cents{ c1.getCents() + c2.getCents() };
}
```

→ _See [01_OperatorOverloadingBasics](../solutions/Chapter_21_Operator_Overloading/01_OperatorOverloadingBasics/) for the rules._

### 21.2 - Overloading arithmetic operators using friend functions

- Binary arithmetic operators (`+`, `-`, `*`, `/`) are commonly overloaded as **friend functions** - two explicit parameters with private member access
- When operand types differ (e.g., `Cents + int` vs `int + Cents`) - each ordering requires a **separate overload**; one can delegate to the other
- These operators **return by value** since the result is a new temporary - returning a reference to a local → dangling reference
- Implement **compound assignment** (`+=`) as a member function first, then define `+` in terms of `+=` to reduce redundancy

```cpp
class Cents {
    int m_cents{};
public:
    Cents(int c) : m_cents{c} {}
    friend Cents operator+(const Cents& a, const Cents& b);
};
Cents operator+(const Cents& a, const Cents& b) {
    return Cents{ a.m_cents + b.m_cents };
}
```

→ _See [02_FriendFunctionOverloading](../solutions/Chapter_21_Operator_Overloading/02_FriendFunctionOverloading/) for friend arithmetic overloads._

### 21.3 - Overloading operators using normal functions

- If the class provides sufficient **public getters**, operators can be implemented as non-friend, non-member **normal functions**
- This is the **preferred approach** - minimizes functions touching private members → smaller change surface if internals evolve
- **Normal functions** promote looser coupling between the operator implementation and class internals
- Fall back to **friend functions** only when private access is actually needed

```cpp
Cents operator+(const Cents& a, const Cents& b) {
    return Cents{ a.getCents() + b.getCents() }; // uses public getter
}
```

→ _See [03_NormalFunctionOverloading](../solutions/Chapter_21_Operator_Overloading/03_NormalFunctionOverloading/) for normal function overloads._

### 21.4 - Overloading the I/O operators

- `operator<<` takes `std::ostream&` + your type, returns `std::ostream&` for **chaining** - must be a non-member function
- `operator>>` takes `std::istream&` + a non-const reference to your type for modification
- Use **transactional input** - extract to temporaries first, only update the object if all extractions succeed
- Call `in.setstate(std::ios_base::failbit)` on **invalid input** to signal failure through the stream

```cpp
std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << '(' << p.x << ", " << p.y << ')';
    return out;
}
```

→ _See [04_IOOperatorOverloading](../solutions/Chapter_21_Operator_Overloading/04_IOOperatorOverloading/) for I/O operator patterns._

### 21.5 - Overloading operators using member functions

- The **left operand** becomes `*this` - only the right operand is an explicit parameter
- **Member functions** are best for operators that modify the left operand - `+=`, `-=`, prefix `++`, prefix `--`
- `operator<<` and `operator>>` **cannot be members** of your class - the left operand is a stream, not your type
- The compiler rewrites `a += b` as `a.operator+=(b)` - calling syntax is unchanged

```cpp
Cents& Cents::operator+=(const Cents& rhs) {
    m_cents += rhs.m_cents;
    return *this;
}
```

→ _See [05_MemberFunctionOverloading](../solutions/Chapter_21_Operator_Overloading/05_MemberFunctionOverloading/) for member operator patterns._

**Operator Overload Implementation Approaches:**

| Approach            | Left Operand     | Private Access?   | Best For                                                   |
| ------------------- | ---------------- | ----------------- | ---------------------------------------------------------- |
| **Friend function** | Explicit param   | Yes               | Binary ops with mixed types (`Cents + int`, `int + Cents`) |
| **Normal function** | Explicit param   | No (uses getters) | Binary ops when public interface suffices                  |
| **Member function** | Implicit `*this` | Yes               | `=`, `[]`, `()`, `->`, `+=`, unary ops                     |

### 21.6 - Overloading unary operators +, -, and !

- **Unary operators** as member functions take no explicit parameters - the single operand is `*this`
- `operator-` returns a **new object** with negated values by value - the original is unchanged
- `operator!` returns `true` if the object is in a zero or **default state**
- Mark these operators `const` since they **don't modify** the invoking object

```cpp
Cents Cents::operator-() const {
    return Cents{ -m_cents };
}
```

→ _See [06_UnaryOperatorOverloading](../solutions/Chapter_21_Operator_Overloading/06_UnaryOperatorOverloading/) for unary demos._

### 21.7 - Overloading the comparison operators

- Implement `operator==` and `operator<` first - define the remaining four (`!=`, `>`, `<=`, `>=`) **in terms of those two**
- C++20 introduces `operator<=>` (the **spaceship operator**) - generates all six comparison operators from a **single definition**
- Return type of `<=>` depends on comparison category - `std::strong_ordering`, `std::weak_ordering`, or `std::partial_ordering`
- Defaulting `<=>` with `= default` performs **memberwise comparison** in declaration order - sufficient for most simple types

```cpp
auto operator<=>(const Cents& rhs) const = default; // C++20: all 6 generated
```

→ _See [07_ComparisonOperators](../solutions/Chapter_21_Operator_Overloading/07_ComparisonOperators/) for comparison and spaceship operator._

**C++20 Spaceship Operator Ordering Categories:**

| Ordering Type           | Equality Meaning                      | Incomparable? | Example Types                      |
| ----------------------- | ------------------------------------- | ------------- | ---------------------------------- |
| `std::strong_ordering`  | Substitutable (truly identical)       | No            | `int`, `char`, `std::string`       |
| `std::weak_ordering`    | Equivalent (not substitutable)        | No            | Case-insensitive string comparison |
| `std::partial_ordering` | Equivalent, but some values unordered | Yes (`NaN`)   | `float`, `double`                  |

### 21.8 - Overloading the increment and decrement operators

- **Prefix** (`++x`) takes no dummy parameter, increments in place, returns `*this` by reference - no copy made
- **Postfix** (`x++`) takes a dummy `int` parameter, saves current state, increments, then returns the saved copy **by value**
- Prefix is **more efficient** than postfix - postfix must create a temporary to hold the pre-increment value
- Prefer **prefix** increment/decrement for user-defined types when the return value is unused → avoids the unnecessary copy

```cpp
Digit& Digit::operator++() {       // prefix
    ++m_digit;
    return *this;
}
Digit Digit::operator++(int) {     // postfix (dummy int)
    Digit temp{*this};
    ++(*this);
    return temp;
}
```

→ _See [08_IncrementDecrementOperators](../solutions/Chapter_21_Operator_Overloading/08_IncrementDecrementOperators/) for prefix vs. postfix._

**Prefix vs Postfix Increment:**

| Aspect                 | Prefix (`++x`)       | Postfix (`x++`)                        |
| ---------------------- | -------------------- | -------------------------------------- |
| **Signature**          | `Foo& operator++()`  | `Foo operator++(int)`                  |
| **Dummy parameter**    | None                 | `int` (unused, distinguishes overload) |
| **Returns**            | `*this` by reference | Copy of pre-increment state by value   |
| **Creates temporary?** | No                   | Yes                                    |
| **Performance**        | Faster (no copy)     | Slower (copy overhead)                 |

### 21.9 - Overloading the subscript operator

- `operator[]` **must be a member function** - returns by reference (`int&` for non-const, `const int&` for const)
- Provide **both const and non-const** overloads to support read-only and mutable access
- Use `assert` or bounds checking to catch **out-of-range** indices
- The index type can be anything (`std::string`, `enum`, etc.) - not limited to `int`

```cpp
int& IntArray::operator[](int index) {
    assert(index >= 0 && index < m_size);
    return m_data[index];
}
```

→ _See [09_SubscriptOperator](../solutions/Chapter_21_Operator_Overloading/09_SubscriptOperator/) for const/non-const operator[]._

### 21.10 - Overloading the parenthesis operator

- `operator()` **must be a member function** and can take any number/type of parameters - the most flexible operator to overload
- Commonly used for **multidimensional indexing** (e.g., `matrix(row, col)`) and for creating **functors**
- **Functors** are objects callable like functions that retain **state** across calls via member variables
- Widely used with standard library algorithms like `std::sort` and `std::for_each`
- The same class can provide **multiple overloads** of `operator()` with different signatures

```cpp
struct Accumulator {
    int m_total{0};
    int operator()(int val) { m_total += val; return m_total; }
};
Accumulator acc;
acc(10); acc(20); // m_total == 30
```

→ _See [10_FunctionCallOperator](../solutions/Chapter_21_Operator_Overloading/10_FunctionCallOperator/) for functor examples._

### 21.11 - Overloading typecasts

- **Typecast operators** (e.g., `operator int() const`) have no explicit parameter and no declared return type - the return type is implied by the name
- These conversions let your class **implicitly convert** to another type in assignment or function-argument contexts
- Mark `explicit` to prevent implicit conversions → requires `static_cast` at the call site - do this unless the conversion is truly natural
- Prefer **converting constructors** on the target type over typecast overloads when possible - they are clearer and easier to discover

```cpp
explicit operator int() const { return m_cents; }
// static_cast<int>(myCents) works; implicit conversion blocked
```

→ _See [11_TypecastOverloading](../solutions/Chapter_21_Operator_Overloading/11_TypecastOverloading/) for user-defined conversions._

### 21.12 - Overloading the assignment operator

- **Copy assignment** `operator=` must be a member function - returns `*this` by reference for chaining
- Include a **self-assignment check** (`if (this == &other) return *this;`) for classes managing dynamic memory
- The compiler generates an **implicit memberwise assignment** if you don't define one
- Use `= delete` to **prevent** assignment entirely

```cpp
Foo& Foo::operator=(const Foo& rhs) {
    if (this == &rhs) return *this; // self-assignment guard
    delete[] m_data;
    m_data = new int[rhs.m_size];
    std::copy_n(rhs.m_data, rhs.m_size, m_data);
    m_size = rhs.m_size;
    return *this;
}
```

→ _See [12_CopyAssignmentOperator](../solutions/Chapter_21_Operator_Overloading/12_CopyAssignmentOperator/) for self-assignment guard._

### 21.13 - Shallow vs. deep copying

- Default copy/assignment performs **shallow** (memberwise) copies - pointer addresses are copied, not the pointed-to data
- With dynamic memory, shallow copy → multiple objects share the same block → **double-delete** and dangling pointers
- **Deep copy** allocates new memory and copies the actual data - required when managing dynamic resources
- Follow the **Rule of Three** - if you need a custom destructor → you also need a custom copy constructor and copy assignment operator

```cpp
// Deep copy constructor
MyArray::MyArray(const MyArray& src) : m_size{src.m_size} {
    m_data = new int[m_size];
    std::copy_n(src.m_data, m_size, m_data);
}
```

→ _See [13_ShallowVsDeepCopy](../solutions/Chapter_21_Operator_Overloading/13_ShallowVsDeepCopy/) for shallow vs. deep copy demos._

### 21.14 - Overloading operators and function templates

- **Function templates** using operators (`<`, `+=`, `<<`) work with any type that has those operators defined
- Providing operator overloads for your class **automatically enables** compatibility with existing generic algorithms and templates
- This is **duck typing** in templates - the template doesn't care about type identity, only that it supports the required operations
- Defining `operator<` immediately makes your class usable with `std::sort`, `std::set`, and `std::map`

```cpp
template <typename T>
T max(T a, T b) { return (a < b) ? b : a; } // works with any T that has operator<
```

→ _See [14_OperatorsAndTemplates](../solutions/Chapter_21_Operator_Overloading/14_OperatorsAndTemplates/) for template compatibility._

### Edge Cases and Caveats

❌ Forgetting self-assignment check in `operator=`:

```cpp
Foo& operator=(const Foo& rhs) {
    delete[] m_data;
    m_data = new int[rhs.m_size]; // ❌ if this == &rhs, m_data was just deleted
    // ...
}
```

✅ Check for self-assignment:

```cpp
Foo& operator=(const Foo& rhs) {
    if (this == &rhs) return *this; // ✅ self-assignment guard
    // ...
}
```

---

❌ Returning `std::ostream` by value from `operator<<`:

```cpp
std::ostream operator<<(std::ostream& out, const Foo& f) { // ❌ by value
```

✅ Return by reference:

```cpp
std::ostream& operator<<(std::ostream& out, const Foo& f) { // ✅
```

---

❌ Shallow copying classes with pointers:

```cpp
Foo a;
Foo b = a; // ❌ default copy - both point to same memory → double-delete
```

✅ Implement a deep copy constructor and assignment operator.

---

❌ Overloading `^` for exponentiation:

```cpp
Foo operator^(int exp) { /* power */ } // ❌ ^ has wrong precedence (lower than +)
```

✅ Use a named function like `pow()` instead.

---

❌ `operator[]` on a pointer to an object:

```cpp
Foo* fp = &myFoo;
fp[0]; // ❌ indexes an array of Foo, not myFoo's subscript
```

✅ Dereference first:

```cpp
(*fp)[0]; // ✅ calls myFoo's operator[]
```

---

❌ Partial extraction in `operator>>`:

```cpp
std::istream& operator>>(std::istream& in, Point& p) {
    in >> p.x;     // succeeds
    in >> p.y;     // ❌ fails - p.x already modified
}
```

✅ Use transactional approach (extract to temps first):

```cpp
int x{}, y{};
if (in >> x >> y) { p.x = x; p.y = y; } // ✅ atomic update
```

---

❌ Non-intuitive operator meanings:

```cpp
Foo operator+(const Foo& rhs) { /* subtract?! */ } // ❌ confusing
```

✅ If the operation isn't obvious, use a named function instead.

---

❌ Missing const/non-const `operator[]` pair:

```cpp
int& operator[](int i) { return m_data[i]; } // only non-const version
const Foo f{...};
f[0]; // ❌ compile error - no const overload
```

✅ Provide both:

```cpp
int& operator[](int i) { return m_data[i]; }
const int& operator[](int i) const { return m_data[i]; } // ✅
```

---

❌ Typecast + converting constructor for the same conversion:

```cpp
// Both Foo::operator int() and Bar(Foo) exist ❌ ambiguous
```

✅ Avoid providing both; prefer `explicit` conversions.

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_21_Operator_Overloading/
```

| Project                                                                                                        | Concept                                              |
| -------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------- |
| [01_OperatorOverloadingBasics](../solutions/Chapter_21_Operator_Overloading/01_OperatorOverloadingBasics/)     | Rules, restrictions, and a first overloaded operator |
| [02_FriendFunctionOverloading](../solutions/Chapter_21_Operator_Overloading/02_FriendFunctionOverloading/)     | Overloading +, -, \*, / using friend functions       |
| [03_NormalFunctionOverloading](../solutions/Chapter_21_Operator_Overloading/03_NormalFunctionOverloading/)     | Non-friend, non-member operator overloading          |
| [04_IOOperatorOverloading](../solutions/Chapter_21_Operator_Overloading/04_IOOperatorOverloading/)             | Overloading `<<` and `>>` with transactional input   |
| [05_MemberFunctionOverloading](../solutions/Chapter_21_Operator_Overloading/05_MemberFunctionOverloading/)     | Overloading as member functions (+=, -=, etc.)       |
| [06_UnaryOperatorOverloading](../solutions/Chapter_21_Operator_Overloading/06_UnaryOperatorOverloading/)       | Unary +, -, !                                        |
| [07_ComparisonOperators](../solutions/Chapter_21_Operator_Overloading/07_ComparisonOperators/)                 | ==, !=, <, >, <=, >= and C++20 spaceship operator    |
| [08_IncrementDecrementOperators](../solutions/Chapter_21_Operator_Overloading/08_IncrementDecrementOperators/) | Prefix vs. postfix ++/--                             |
| [09_SubscriptOperator](../solutions/Chapter_21_Operator_Overloading/09_SubscriptOperator/)                     | `operator[]` with const/non-const versions           |
| [10_FunctionCallOperator](../solutions/Chapter_21_Operator_Overloading/10_FunctionCallOperator/)               | `operator()` - functors and stateful callables       |
| [11_TypecastOverloading](../solutions/Chapter_21_Operator_Overloading/11_TypecastOverloading/)                 | User-defined type conversions and `explicit`         |
| [12_CopyAssignmentOperator](../solutions/Chapter_21_Operator_Overloading/12_CopyAssignmentOperator/)           | `operator=` with self-assignment guard               |
| [13_ShallowVsDeepCopy](../solutions/Chapter_21_Operator_Overloading/13_ShallowVsDeepCopy/)                     | Shallow vs. deep copying, Rule of Three              |
| [14_OperatorsAndTemplates](../solutions/Chapter_21_Operator_Overloading/14_OperatorsAndTemplates/)             | Enabling classes in function templates via operators |

### Quick Reference

| Feature         | Syntax                                                 | Notes                          |
| --------------- | ------------------------------------------------------ | ------------------------------ |
| Friend overload | `friend Foo operator+(const Foo&, const Foo&);`        | Non-member with private access |
| Member overload | `Foo operator+(const Foo& rhs) const;`                 | `*this` is left operand        |
| `operator<<`    | `std::ostream& operator<<(std::ostream&, const Foo&);` | Return stream for chaining     |
| `operator>>`    | `std::istream& operator>>(std::istream&, Foo&);`       | Transactional input            |
| Prefix ++       | `Foo& operator++();`                                   | Returns `*this` by ref         |
| Postfix ++      | `Foo operator++(int);`                                 | Dummy int; returns copy        |
| `operator[]`    | `int& operator[](int i);`                              | Must be member; return ref     |
| `operator()`    | `int operator()(int r, int c);`                        | Functor - any params           |
| Typecast        | `explicit operator int() const;`                       | No params, no return type      |
| Copy assign     | `Foo& operator=(const Foo& rhs);`                      | Self-assignment check          |
| Spaceship       | `auto operator<=>(const Foo&) const = default;`        | C++20; generates all 6         |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. Why is a self-assignment check important in `operator=`?

<details>
<summary>Show answer</summary>

**Direct answer:** Without a self-assignment check (`if (this == &other) return *this;`), assigning an object to itself can delete its own resources before copying them corrupting the object. This matters most when the class manages dynamic memory.

**Detailed explanation:**

```cpp
class MyString
{
    char* m_data{};
public:
    MyString& operator=(const MyString& other)
    {
        if (this == &other) return *this;  // self-assignment guard

        delete[] m_data;                    // free old data
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);       // deep copy
        return *this;
    }
};
```

Without the check, `a = a;` would delete `m_data`, then try to copy from the now-deleted memory undefined behavior.

</details>

2. Why must `operator<<` return `std::ostream&` by reference?

<details>
<summary>Show answer</summary>

**Direct answer:** Returning `std::ostream&` enables chaining: `std::cout << a << b << c;`. Each `<<` call returns the same stream object so the next `<<` can use it. Streams are non-copyable, so returning by value wouldn't compile.

**Detailed explanation:**

```cpp
class Point
{
    int m_x{}, m_y{};
public:
    Point(int x, int y) : m_x{x}, m_y{y} {}
    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << '(' << p.m_x << ", " << p.m_y << ')';
        return out;  // enables chaining
    }
};

// Without returning ostream&, this wouldn't work:
std::cout << Point{1, 2} << " and " << Point{3, 4};
```

`operator<<` must be a non-member (usually friend) because the left operand is `std::ostream`, not your class.

</details>

3. What is the difference between shallow copy and deep copy?

<details>
<summary>Show answer</summary>

**Direct answer:** A shallow copy duplicates pointer values (both objects point to the same memory). A deep copy allocates new memory and copies the pointed-to data. Without deep copy, destroying one object invalidates the other (double-delete or dangling pointer).

**Detailed explanation:**

```cpp
class DynArray
{
    int* m_data{};
    int m_size{};
public:
    // Shallow copy (default): both share m_data  double-delete!
    // Deep copy (correct):
    DynArray(const DynArray& src)
        : m_size{src.m_size}
        , m_data{new int[src.m_size]}
    {
        std::copy(src.m_data, src.m_data + m_size, m_data);
    }
    ~DynArray() { delete[] m_data; }
};
```

Rule of Three: if you define a custom destructor, you almost certainly need a custom copy constructor and copy assignment operator too.

</details>

4. Why is `^` a bad choice for an exponentiation operator in C++?

<details>
<summary>Show answer</summary>

**Direct answer:** `^` is the built-in XOR operator with low precedence (lower than comparison operators). Overloading it for exponentiation would give `2 + 3 ^ 4` a surprising evaluation order (`2 + (3 ^ 4)` instead of `(2 + 3^4)` mathematically). You can't change an operator's precedence or associativity. Use a named function like `pow()` instead.

**Detailed explanation:**
Operator overloading rules:

- You cannot create new operators
- You cannot change the number of operands, precedence, or associativity
- At least one operand must be a user-defined type
- The operator should behave intuitively (don't make `+` subtract)

If the meaning isn't obvious for your type, prefer a named function.

</details>

5. What is the transactional approach for `operator>>` and why is it important?

<details>
<summary>Show answer</summary>

**Direct answer:** Extract into temporary variables first, then only update the object if all extractions succeed. This ensures the object remains in a valid state if input fails partway through. Call `in.setstate(std::ios_base::failbit)` on invalid input.

**Detailed explanation:**

```cpp
friend std::istream& operator>>(std::istream& in, Point& p)
{
    int x{}, y{};      // temporaries
    in >> x >> y;       // extract to temps first

    if (in)             // all extractions succeeded?
    {
        p.m_x = x;     // commit
        p.m_y = y;
    }
    return in;
}
```

Without the transactional approach, a partial read could leave the object half-updated (e.g., `m_x` changed but `m_y` unchanged), which is a subtle bug.

</details>

6. When do you need both const and non-const versions of `operator[]`?

<details>
<summary>Show answer</summary>

**Direct answer:** The const version is called on const objects (returns `const T&` for read-only access). The non-const version is called on non-const objects (returns `T&` for read-write access). Without both, you can't index into a const instance of your class.

**Detailed explanation:**

```cpp
class IntArray
{
    int m_data[10]{};
public:
    int& operator[](int idx)              { return m_data[idx]; }       // non-const
    const int& operator[](int idx) const  { return m_data[idx]; }       // const

    // The compiler picks based on the constness of the object:
};

void print(const IntArray& arr)
{
    std::cout << arr[0];     // calls const version
}

IntArray arr;
arr[0] = 42;                // calls non-const version
```

</details>

7. How does the copy-and-swap idiom help implement a safe `operator=`?

<details>
<summary>Show answer</summary>

**Direct answer:** The parameter is taken by value (triggering the copy constructor), then swapped with `*this`. This gives you self-assignment safety and exception safety in one step if the copy throws, `*this` is untouched.

**Detailed explanation:**

```cpp
class MyString
{
    char* m_data{};
    int m_size{};

    friend void swap(MyString& a, MyString& b) noexcept
    {
        std::swap(a.m_data, b.m_data);
        std::swap(a.m_size, b.m_size);
    }
public:
    MyString& operator=(MyString copy)   // pass by value = copy
    {
        swap(*this, copy);               // swap resources
        return *this;
    }   // old resources freed when 'copy' is destroyed
};
```

Benefits: no explicit self-assignment check needed, strong exception guarantee, and the copy constructor does the allocation work.

</details>

8. What happens if you apply `operator[]` to a pointer instead of an object?

<details>
<summary>Show answer</summary>

**Direct answer:** The built-in `[]` for pointers does pointer arithmetic, not your overloaded operator. `ptr[2]` is `*(ptr + 2)` it accesses memory at an offset from the pointer, which is likely garbage or a crash if `ptr` points to a single object. Always dereference first: `(*ptr)[2]`.

**Detailed explanation:**

```cpp
IntArray* ptr{ new IntArray{} };

ptr[2];        // pointer arithmetic  accesses memory 2 IntArrays past ptr (UB!)
(*ptr)[2];     // correct  dereferences ptr, then calls operator[]

// Or use -> syntax if operator[] returns a reference:
// ptr->operator[](2);

delete ptr;
```

This is a common source of bugs when dynamically allocating container-like objects.

</details>

9. Why should binary arithmetic operators like `+` be implemented in terms of `+=`?

<details>
<summary>Show answer</summary>

**Direct answer:** `operator+=` modifies the left operand in place (member function). `operator+` can then delegate to `+=`, avoiding code duplication. `+` returns by value (new temporary), while `+=` returns `*this` by reference.

**Detailed explanation:**

```cpp
class Cents
{
    int m_cents{};
public:
    Cents(int c) : m_cents{c} {}

    Cents& operator+=(const Cents& rhs)
    {
        m_cents += rhs.m_cents;
        return *this;
    }

    friend Cents operator+(Cents lhs, const Cents& rhs)  // lhs by value
    {
        lhs += rhs;   // delegate to +=
        return lhs;
    }
};
```

</details>

10. What is the difference between prefix and postfix `operator++`?

<details>
<summary>Show answer</summary>

**Direct answer:** Prefix `++x` takes no dummy parameter, increments in place, and returns `*this` by reference (efficient). Postfix `x++` takes a dummy `int` parameter, saves a copy, increments, then returns the saved copy by value (extra copy). Prefer prefix for user-defined types when the return value is unused.

**Detailed explanation:**

```cpp
class Counter
{
    int m_val{};
public:
    Counter& operator++()         // prefix
    {
        ++m_val;
        return *this;             // return by reference
    }

    Counter operator++(int)       // postfix (dummy int)
    {
        Counter old{*this};       // save copy
        ++m_val;
        return old;               // return copy by value
    }
};
```

</details>
