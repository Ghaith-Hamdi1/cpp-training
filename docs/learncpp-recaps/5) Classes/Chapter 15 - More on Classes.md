# Chapter 15 Recap - More on Classes

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- `this` is a pointer, not a reference - use `this->member` or `(*this)`, not `this.member`.
- Return `*this` by reference for method chaining - returning by value creates a copy.
- Put class definitions in headers; non-trivial implementations in `.cpp` files.
- Functions defined inside the class are implicitly `inline` - no ODR violation risk.
- Use destructors for automatic cleanup - don't rely on users calling a manual cleanup function.
- Prefer `static inline` (C++17) or `static constexpr` for static members - initialize inside the class.
- Static functions have no `this` and cannot access non-static members.
- Use `friend` sparingly; prefer the public interface. Friendship is granted, not requested.

### 3 Tiny Examples

1.

```cpp
class Calc {
    int m_val{0};
public:
    Calc& add(int v) { m_val += v; return *this; }
    Calc& sub(int v) { m_val -= v; return *this; }
};
Calc c{};
c.add(5).sub(3);  // method chaining via *this
```

2.

```cpp
// foo.h
class Foo {
    int m_val{};
public:
    int get() const { return m_val; }  // implicitly inline (in class body)
    void doWork();                      // declared here, defined in foo.cpp
};
```

3.

```cpp
class Fruit {
public:
    enum Type { apple, banana, cherry };  // nested enum
private:
    Type m_type{};
public:
    Fruit(Type t) : m_type{t} {}
};
Fruit f{Fruit::apple};  // access nested type via ClassName::
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **The `this` pointer** - a hidden `const` pointer to the implicit object, available in every non-static member function.
- **Method chaining** - returning `*this` by reference so chained calls modify the same object.
- **Header/source split** - class definition in `.h`; non-trivial member implementations in `.cpp`.
- **Implicitly inline** - functions defined inside the class body are implicitly `inline` (ODR-exempt).
- **Nested types** - enums, aliases, or classes defined inside a class; follow access specifiers.
- **Destructor (`~ClassName()`)** - called automatically on object destruction; used for cleanup.
- **Class templates + member functions** - template params from the class apply inside; external definitions resupply them.
- **Injected class name** - inside `Pair<T>`, unqualified `Pair` is shorthand for `Pair<T>`.
- **Static member variables** - shared across all instances; exist even with no objects; use `static inline` (C++17) or `static constexpr`.
- **Static member functions** - no `this` pointer; can only access static members; called via `ClassName::func()`.
- **Friend functions/classes** - granted full access to private/protected members via `friend`; non-reciprocal, non-transitive.
- **Ref qualifiers (`&` / `&&`)** - overload a member function based on whether the implicit object is lvalue or rvalue.

### Section-by-Section Detail

### 15.1 - The hidden "this" pointer and member function chaining

- Every non-static member function receives a hidden **`this`** parameter - a `const` pointer to the object the function was called on
- The compiler rewrites `m_id` to `this->m_id` behind the scenes - explicit use of `this` is rarely needed
- Returning **`*this`** by reference enables **method chaining**: `calc.add(5).sub(3).mult(4)`
- You can reset an object via `*this = {};` - replacing the current state with a default-constructed value

```cpp
class Calc {
    int m_val{0};
public:
    Calc& add(int v) { m_val += v; return *this; }
    Calc& sub(int v) { m_val -= v; return *this; }
};
Calc c{};
c.add(5).sub(3);  // method chaining via *this
```

→ _See [01_ThisPointer](../solutions/Chapter_15_More_On_Classes/01_ThisPointer) and [02_MethodChaining](../solutions/Chapter_15_More_On_Classes/02_MethodChaining) for explicit `this` usage and chaining demos._

**Where to Define Member Functions:**

| Function Location                    | Implicitly `inline`? | Where to Define       | Example                             |
| ------------------------------------ | -------------------- | --------------------- | ----------------------------------- |
| **Inside class body** (trivial)      | Yes                  | `.h` file             | `int get() const { return m_val; }` |
| **Outside class body** (non-trivial) | No                   | `.cpp` file           | `void Foo::doWork() { ... }`        |
| **Outside class body but in header** | No - add `inline`    | `.h` file             | `inline void Foo::doWork() { ... }` |
| **Default arguments**                | n/a                  | Class definition only | `void func(int x = 0);` in class    |

### 15.2 - Classes and header files

- Put the **class definition** in a `.h` file; **non-trivial member functions** in a matching `.cpp`
- **Trivial one-liners** (getters, empty constructors) can stay inside the class body
- Functions defined inside the class are **implicitly `inline`**; functions defined outside are not - add `inline` explicitly if keeping them in the header
- **Default arguments** go in the class definition (declaration), not in the out-of-class definition

```cpp
// foo.h
class Foo {
    int m_val{};
public:
    int get() const { return m_val; }  // implicitly inline (in class body)
    void doWork();                      // declared here, defined in foo.cpp
};
```

### 15.3 - Nested types (member types)

- **Nested types** defined inside a class follow access specifiers and are accessed externally as `ClassName::TypeName`
- Place nested types at the **top** of the class for visibility
- A common pattern: nest an **unscoped enum** inside a class so the class acts as the namespace
- **Nested classes** can access private members of the enclosing class but don't have its `this` pointer

```cpp
class Fruit {
public:
    enum Type { apple, banana, cherry };  // nested enum
private:
    Type m_type{};
public:
    Fruit(Type t) : m_type{t} {}
};
Fruit f{Fruit::apple};  // access nested type via ClassName::
```

→ _See [03_NestedTypes](../solutions/Chapter_15_More_On_Classes/03_NestedTypes) for nested enum, alias, and class examples._

### 15.4 - Introduction to destructors

- The **destructor** `~ClassName()` is called automatically when an object is destroyed - goes out of scope, is `delete`d, etc.
- Use it for **resource cleanup** - closing files, freeing memory, releasing locks
- A class can have **only one** destructor - it takes no parameters and has no return type
- **`std::exit()`** does **not** call destructors for local objects - beware of resource leaks

```cpp
class Resource {
public:
    Resource()  { std::cout << "acquired\n"; }
    ~Resource() { std::cout << "released\n"; }  // auto-called on destruction
};
{ Resource r{}; }  // prints: acquired, then released
```

→ _See [04_Destructors](../solutions/Chapter_15_More_On_Classes/04_Destructors) for destructor demos and the `std::exit()` pitfall._

### 15.5 - Class templates with member functions

- **Class template** parameters apply inside member definitions - no need to re-specify them within the class body
- External definitions require their own `template <typename T>` and must qualify the name as `Pair<T>::func()`
- The **injected class name** lets you write `Pair` instead of `Pair<T>` inside the class scope
- Put external member definitions in the **same header**, below the class definition

```cpp
template <typename T>
class Pair {
    T m_a, m_b;
public:
    Pair(T a, T b) : m_a{a}, m_b{b} {}
    T sum() const;
};
template <typename T>
T Pair<T>::sum() const { return m_a + m_b; }  // external definition
```

→ _See [05_ClassTemplatesWithMembers](../solutions/Chapter_15_More_On_Classes/05_ClassTemplatesWithMembers) for external definition and injected name demos._

### 15.6 - Static member variables

- **Static members** are shared across all instances and exist even with zero objects
- Traditional approach: declare with `static` inside the class, define outside with `int ClassName::s_count{};` in the `.cpp`
- Modern approach: **`static inline`** (C++17) or **`static constexpr`** for constants - both allow initialization inside the class
- Access via **`ClassName::s_count`** - no object required

```cpp
class Foo {
    static inline int s_count{0};  // C++17: init inside class
public:
    Foo()  { ++s_count; }
    static int getCount() { return s_count; }
};
```

→ _See [06_StaticMemberVariables](../solutions/Chapter_15_More_On_Classes/06_StaticMemberVariables) for all three initialization patterns._

**Static Member Initialization Styles:**

| Style                  | Syntax                                                  | In-Class Init? | C++ Standard | Use Case               |
| ---------------------- | ------------------------------------------------------- | -------------- | ------------ | ---------------------- |
| **Traditional**        | `static int s_count;` + `int Foo::s_count{};` in `.cpp` | No             | C++03        | Pre-C++17 codebases    |
| **`static inline`**    | `static inline int s_count{0};`                         | Yes            | C++17        | Modern mutable statics |
| **`static constexpr`** | `static constexpr int s_max{100};`                      | Yes            | C++11        | Compile-time constants |

### 15.7 - Static member functions

- **Static member functions** have no `this` pointer → can only access **static members**
- Call via **`ClassName::func()`** - no object needed
- A class with only static members (`pure static class`) is essentially a namespace with access control
- C++ has **no static constructors** - use a helper function or inline initialization for complex static setup

```cpp
class IDGen {
    static inline int s_next{1};
public:
    static int next() { return s_next++; }  // no this pointer
};
int id = IDGen::next();  // called via ClassName::func()
```

→ _See [07_StaticMemberFunctions](../solutions/Chapter_15_More_On_Classes/07_StaticMemberFunctions) for static function examples._

### 15.8 - Friend non-member functions

- **`friend`** inside a class grants a non-member function access to **private/protected** members
- The class **grants** friendship - it cannot be requested or claimed from outside
- Friend functions defined **inside the class body** remain non-members - they are not member functions
- Prefer using the **public interface** inside friend functions when possible

```cpp
class Foo {
    int m_val{42};
    friend void print(const Foo& f);  // grant access
};
void print(const Foo& f) { std::cout << f.m_val; }  // non-member, accesses private
```

→ _See [08_FriendFunctions](../solutions/Chapter_15_More_On_Classes/08_FriendFunctions) for friend function access patterns._

### 15.9 - Friend classes and friend member functions

- **`friend class Display;`** grants **all** of `Display`'s member functions access to the class's private and protected members
- You can also friend a **single member function**: `friend void Display::show(const Secret&);` - but this requires careful ordering of class definitions
- Friendship is **not reciprocal** (A friends B - B can't access A), **not transitive** (A→ B→ C doesn't give C access to A), and **not inherited**
- Use friend classes **sparingly** - only when tight coupling between two classes simplifies the design significantly

```cpp
class Secret {
    int m_val{42};
    friend class Printer;  // Printer can access Secret's privates
};
class Printer {
public:
    void show(const Secret& s) { std::cout << s.m_val; }  // OK
};
```

→ _See [09_FriendClasses](../solutions/Chapter_15_More_On_Classes/09_FriendClasses) for friend class demos._

> **Friendship Properties:**
>
> - **Full-class friendship:** `friend class Display;` gives all of `Display`'s members access
> - **Single-function friendship:** `friend void Display::show(const Secret&);` - requires the friend's declaration to be visible
> - **Not reciprocal:** if `A` friends `B`, `B` does _not_ automatically access `A`'s privates
> - **Not transitive:** if `A` friends `B` and `B` friends `C`, `C` cannot access `A`
> - **Not inherited:** a derived class of a friend does not inherit the friendship
> - Use sparingly - only when tight coupling simplifies the design significantly

### 15.10 - Ref qualifiers (optional)

- Append **`&`** or **`&&`** after the parameter list to overload a member function based on whether `*this` is an **lvalue** or **rvalue**
- The `&`-qualified overload returns `const&` (efficient, no copy) for lvalue objects - the `&&` overload returns **by value** (safe) for rvalue temporaries
- If you provide any ref-qualified overload, you must ref-qualify **all** overloads of that function - mixing qualified and unqualified is not allowed
- This prevents **dangling references** from member function calls on temporaries - rarely needed but is the correct solution when it applies

```cpp
class Foo {
    std::string m_name{"hello"};
public:
    const std::string& name() const &  { return m_name; }  // lvalue: return ref
    std::string        name() const && { return m_name; }   // rvalue: return copy
};
```

→ _See [10_RefQualifiers](../solutions/Chapter_15_More_On_Classes/10_RefQualifiers) for lvalue/rvalue member function overloading._

**Ref Qualifiers Comparison:**

| Qualifier     | Syntax Suffix          | Object Type           | Return Strategy          | Rationale                           |
| ------------- | ---------------------- | --------------------- | ------------------------ | ----------------------------------- |
| `&` (lvalue)  | `const &` after params | Named object (lvalue) | `const&` (efficient)     | Object outlives the call            |
| `&&` (rvalue) | `&&` after params      | Temporary (rvalue)    | By value (safe copy)     | Prevents dangling reference         |
| _(none)_      | _(no qualifier)_       | Either                | Must choose one strategy | Cannot mix with qualified overloads |

### Edge Cases and Caveats

❌ `this.member` instead of `this->member`:

```cpp
void Foo::print() { std::cout << this.m_val; } // ❌ this is a pointer
```

✅ Use arrow operator:

```cpp
void Foo::print() { std::cout << this->m_val; } // ✅ or just m_val
```

---

❌ Returning `*this` by value in chainable functions:

```cpp
Foo add(int v) { m_val += v; return *this; } // ❌ returns a copy
```

✅ Return by reference:

```cpp
Foo& add(int v) { m_val += v; return *this; } // ✅ chains on original
```

---

❌ Non-trivial member functions in a header without `inline`:

```cpp
// foo.h
void Foo::doWork() { /* ... */ } // ❌ ODR violation in multi-TU builds
```

✅ Mark as `inline` or define in the class body:

```cpp
inline void Foo::doWork() { /* ... */ } // ✅ inline in header
```

---

❌ `std::exit()` skipping local destructors:

```cpp
void cleanup() { std::exit(0); } // ❌ RAII resources not cleaned up
```

✅ Let objects go out of scope naturally, or throw an exception.

---

❌ Accessing non-static members from a static function:

```cpp
static int getVal() { return m_val; } // ❌ no this pointer - compile error
```

✅ Static functions can only access static members:

```cpp
static int getCount() { return s_count; } // ✅ s_count is static
```

---

❌ Assuming friendship is reciprocal:

```cpp
class A { friend class B; }; // B can access A's privates
// ❌ A cannot access B's privates - friendship is one-way
```

✅ Both classes must friend each other for mutual access.

---

❌ Forgetting `template <typename T>` on external member definitions:

```cpp
void MyClass<T>::doWork() {} // ❌ T is unknown - compile error
```

✅ Include the template header:

```cpp
template <typename T>
void MyClass<T>::doWork() {} // ✅
```

---

❌ Initializing non-inline/constexpr static members inside the class:

```cpp
class Foo { static int s_count = 0; }; // ❌ only inline/constexpr allowed
```

✅ Use `inline` or define outside:

```cpp
class Foo { inline static int s_count = 0; }; // ✅ C++17
```

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_15_More_On_Classes/
```

| Project                                                                                               | Concept                                                         |
| ----------------------------------------------------------------------------------------------------- | --------------------------------------------------------------- |
| [01_ThisPointer](../solutions/Chapter_15_More_On_Classes/01_ThisPointer)                             | The hidden `this` pointer - implicit parameter and explicit use |
| [02_MethodChaining](../solutions/Chapter_15_More_On_Classes/02_MethodChaining)                       | Returning `*this` by reference for fluent-style chaining        |
| [03_NestedTypes](../solutions/Chapter_15_More_On_Classes/03_NestedTypes)                             | Nested enums, aliases, and classes inside a class               |
| [04_Destructors](../solutions/Chapter_15_More_On_Classes/04_Destructors)                             | Destructor basics, automatic cleanup, `std::exit()` pitfall     |
| [05_ClassTemplatesWithMembers](../solutions/Chapter_15_More_On_Classes/05_ClassTemplatesWithMembers) | Class templates with member functions, injected class name      |
| [06_StaticMemberVariables](../solutions/Chapter_15_More_On_Classes/06_StaticMemberVariables)         | `static`, `static inline`, `static constexpr` members           |
| [07_StaticMemberFunctions](../solutions/Chapter_15_More_On_Classes/07_StaticMemberFunctions)         | Static functions, no `this`, pure static classes                |
| [08_FriendFunctions](../solutions/Chapter_15_More_On_Classes/08_FriendFunctions)                     | `friend` non-member functions with private access               |
| [09_FriendClasses](../solutions/Chapter_15_More_On_Classes/09_FriendClasses)                         | Friend classes, non-reciprocal and non-transitive               |
| [10_RefQualifiers](../solutions/Chapter_15_More_On_Classes/10_RefQualifiers)                         | Overloading for lvalue (`&`) vs rvalue (`&&`) objects           |
| [11_Composition](../solutions/Chapter_15_More_On_Classes/11_Composition)                             | Classes containing classes - "has-a" relationships              |
| [12_CommonPitfalls](../solutions/Chapter_15_More_On_Classes/12_CommonPitfalls)                       | Comprehensive demo of frequent class mistakes                   |

### Quick Reference

| Feature            | Syntax                                  | Notes                                         |
| ------------------ | --------------------------------------- | --------------------------------------------- |
| `this` pointer     | `this->m_x`                             | Hidden const ptr; compiler adds automatically |
| Method chaining    | `return *this;`                         | Return by non-const ref                       |
| Destructor         | `~Foo() { }`                            | Only one; auto-called on destroy              |
| Nested type        | `class Foo { public: enum Type { }; };` | Access: `Foo::Type`                           |
| Static member var  | `static inline int s_count{};`          | Shared; exists without objects                |
| Static constexpr   | `static constexpr int s_max{100};`      | Compile-time constant                         |
| Static member func | `static int getCount();`                | No `this`; call via `Foo::getCount()`         |
| Friend function    | `friend void print(const Foo&);`        | Full private access                           |
| Friend class       | `friend class Display;`                 | All Display members get access                |
| Ref qualifier      | `int& getValue() & { }`                 | Only callable on lvalues                      |
| Rvalue ref qual    | `int getValue() && { }`                 | Only callable on rvalues                      |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. Why is `this` a pointer and not a reference?

<details>
<summary>Show answer</summary>

**Direct answer:** `this` is a pointer for historical reasons - it was introduced in early C++ before references existed. It's a `const` pointer to the current object (`ClassName* const`), meaning you can't change what `this` points to, but you can modify the object through it (unless the member function is `const`, in which case `this` is `const ClassName* const`).

**Detailed explanation:**
The compiler rewrites member access like `m_id` to `this->m_id` behind the scenes. You rarely need `this` explicitly, but it's useful for:

- Returning `*this` by reference to enable method chaining
- Disambiguating when a parameter shadows a member name

```cpp
class Calc
{
    int m_value{};
public:
    Calc& add(int v) { m_value += v; return *this; }
    Calc& sub(int v) { m_value -= v; return *this; }
};

Calc c;
c.add(5).sub(3);  // method chaining via *this
```

</details>

2. What must the return type be for method chaining to work on the original object?

<details>
<summary>Show answer</summary>

**Direct answer:** The function must return `*this` by non-const reference (`ClassName&`). Returning by value would create a copy, so subsequent calls would operate on the copy, not the original object. Returning by pointer would require arrow syntax (`->`) instead of dot syntax (`.`).

**Detailed explanation:**

```cpp
class Builder
{
    std::string m_result;
public:
    Builder& append(std::string_view s)
    {
        m_result += s;
        return *this;  // returns reference to the SAME object
    }
    std::string build() const { return m_result; }
};

Builder b;
std::string s = b.append("Hello").append(" ").append("World").build();
// All calls operate on the same Builder object 'b'
```

</details>

3. What is the One Definition Rule (ODR) and how does `inline` help?

<details>
<summary>Show answer</summary>

**Direct answer:** The ODR states that a function or variable can have only one definition across all translation units (with some exceptions). Member functions defined inside the class body are implicitly `inline`, which allows multiple identical definitions across translation units. Functions defined outside the class in a header need the `inline` keyword explicitly to avoid ODR violations.

**Detailed explanation:**

```cpp
// widget.h
class Widget
{
    int m_x{};
public:
    int getX() const { return m_x; }  // implicitly inline (defined inside class)
    void setX(int x);                 // declared only - defined elsewhere
};

// Option A: define in widget.cpp (no inline needed)
void Widget::setX(int x) { m_x = x; }

// Option B: define in header (must add inline)
inline void Widget::setX(int x) { m_x = x; }
```

Default arguments go in the class definition (declaration), not in the out-of-class definition.

</details>

4. Why does `std::exit()` not call local destructors?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::exit()` terminates the program immediately without unwinding the call stack, so destructors for local (automatic) objects are never called. Only destructors for static and global objects are called. This can leak resources (open files, allocated memory, etc.) that rely on destructor cleanup.

**Detailed explanation:**

```cpp
void process()
{
    std::ofstream file("data.txt");  // destructor flushes and closes file
    // ... work ...
    std::exit(0);  // file destructor NOT called - data may be lost!
}
```

Prefer returning from `main()` or throwing exceptions (which unwind the stack and call destructors) over `std::exit()`. Use `std::exit()` only for truly fatal situations where cleanup is impossible or irrelevant.

</details>

5. Can a static member function access non-static members? Why or why not?

<details>
<summary>Show answer</summary>

**Direct answer:** No. A static member function has no `this` pointer because it is not associated with any particular object instance. Since non-static members belong to specific object instances and can only be accessed through `this`, a static member function cannot access them. It can only access static member variables and call other static member functions.

**Detailed explanation:**

```cpp
class Counter
{
    static inline int s_count{ 0 };    // shared by all instances
    int m_id{};                         // per-instance

public:
    Counter() : m_id{ ++s_count } {}

    static int getCount() { return s_count; }   // OK: static accessing static
    // static int getId() { return m_id; }      // ERROR: no this pointer
    int getId() const { return m_id; }           // OK: non-static has this
};

int n = Counter::getCount();  // called without an object
```

</details>

6. Is friendship transitive or reciprocal in C++?

<details>
<summary>Show answer</summary>

**Direct answer:** No to both. Friendship is neither reciprocal nor transitive, nor inherited. If class `A` friends class `B`, `B` can access `A`'s private members, but `A` cannot access `B`'s privates (not reciprocal). If `B` friends `C`, `C` still cannot access `A`'s privates (not transitive). A derived class of `B` does not inherit `B`'s friendship with `A`.

**Detailed explanation:**

```cpp
class Secret
{
    int m_data{};
    friend class Display;  // Display can access Secret's privates
};

class Display
{
public:
    void show(const Secret& s) { std::cout << s.m_data; }  // OK: friend access
    // Secret cannot access Display's privates - not reciprocal
};
```

You can also `friend` individual functions or specific member functions of another class. Use friendship sparingly - only when two classes are tightly coupled and the public interface would be awkward.

</details>

7. What keyword must precede an out-of-class template member definition?

<details>
<summary>Show answer</summary>

**Direct answer:** `template <typename T>` (or equivalent) must precede the definition, and the class name must be qualified with the template parameter: `Pair<T>::functionName()`. The definition must be in the same header as the class template.

**Detailed explanation:**

```cpp
template <typename T>
class Pair
{
    T m_first{};
    T m_second{};
public:
    Pair(T a, T b);
    T getFirst() const;
};

// Out-of-class definitions - need template<> and Pair<T>::
template <typename T>
Pair<T>::Pair(T a, T b) : m_first{ a }, m_second{ b } {}

template <typename T>
T Pair<T>::getFirst() const { return m_first; }
```

Inside the class scope, you can use the injected class name `Pair` instead of `Pair<T>`.

</details>

8. How do you initialize a static member variable inside a class definition in C++17?

<details>
<summary>Show answer</summary>

**Direct answer:** Use `static inline`: `static inline int s_count{ 0 };`. The `inline` keyword allows the variable to be defined in the header without violating ODR. For compile-time constants, `static constexpr` works without `inline` (constexpr static members are implicitly inline since C++17).

**Detailed explanation:**

```cpp
class Widget
{
    // Pre-C++17: declare here, define in .cpp file
    // static int s_count;  // declaration only
    // int Widget::s_count{ 0 };  // in .cpp file

    // C++17: initialize directly in class
    static inline int s_count{ 0 };              // runtime static
    static constexpr double s_pi{ 3.14159 };     // compile-time constant (implicitly inline)
};
```

</details>

9. What is a **nested type** and how is it accessed from outside the class?

<details>
<summary>Show answer</summary>

**Direct answer:** A nested type is a type (class, struct, enum, typedef, using alias) defined inside a class body. It follows the enclosing class's access specifiers. From outside, it's accessed as `ClassName::TypeName`. Nested types are useful for implementation details or closely related types that shouldn't pollute the outer namespace.

**Detailed explanation:**

```cpp
class Fruit
{
public:
    enum Type { apple, banana, cherry };  // nested enum
private:
    Type m_type{};
public:
    explicit Fruit(Type t) : m_type{ t } {}
};

Fruit f{ Fruit::apple };  // access nested enum via Fruit::
```

Nested classes can access private members of the enclosing class but do not have the enclosing class's `this` pointer.

</details>

10. What is the difference between a **friend function** and a **friend class**?

<details>
<summary>Show answer</summary>

**Direct answer:** A friend function is a single non-member function granted access to a class's private/protected members. A friend class grants _all_ member functions of that class the same access. Friend functions are more granular; friend classes are more sweeping.

**Detailed explanation:**

```cpp
class Secret
{
    int m_data{};
    friend void printSecret(const Secret& s); // single friend function
    friend class Auditor;                      // entire class is a friend
};

void printSecret(const Secret& s) { std::cout << s.m_data; } // OK

class Auditor
{
public:
    void audit(const Secret& s) { /* can access s.m_data */ }
    void log(const Secret& s) { /* can also access s.m_data */ }
};
```

The class grants friendship - it cannot be "claimed" from outside. Friend functions defined inside the class body remain non-member functions.

</details>
