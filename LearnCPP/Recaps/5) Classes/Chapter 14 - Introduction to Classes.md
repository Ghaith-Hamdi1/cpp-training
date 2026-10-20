# Chapter 14 Recap - Introduction to Classes

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Use `class` when you need private data and invariants; use `struct` for plain data aggregates.
- Members default to `private` in a `class`, `public` in a `struct`.
- Make every member function that doesn't modify state `const`.
- Use the **member initializer list** for all member initialization - don't assign in the body.
- Members initialize in **declaration order**, regardless of initializer list order.
- Mark single-argument constructors `explicit` unless implicit conversion is intentionally useful.
- Use `= default` for trivial constructors; use `= delete` to prevent unwanted operations.
- Delegating constructors reduce duplication but cannot also initialize members directly.

### 3 Tiny Examples

1.

```cpp
// Procedural: data and logic separate
struct Point { int x; int y; };
void print(Point p) { std::cout << p.x << ',' << p.y; }

// OOP: data and logic bundled
class Point { int m_x, m_y; public: void print() const { std::cout << m_x << ',' << m_y; } };
```

2.

```cpp
struct S { int val; };       // members public by default
class  C { int val; };       // members private by default
S s; s.val = 5;              // OK - public
// C c; c.val = 5;           // ❌ error - val is private
```

3.

```cpp
class Foo {
    int m_val{};
public:
    void set(int v) { m_val = v; }     // implicit object provides m_val
    int  get() const { return m_val; }
};
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Object-Oriented Programming (OOP)** - a paradigm bundling data (properties) and behavior (functions) into class types.
- **Class** - a program-defined type with data members and member functions; members default to **private**.
- **Struct** - identical to a class except members default to **public**; used for simple aggregates.
- **Class invariant** - a condition that must remain true throughout an object's lifetime for it to be valid.
- **Member function** - a function declared inside a class; called on an object via `obj.func()`.
- **Implicit object** - the object a member function is called on; its members are accessed without a prefix.
- **Const member function** - `void func() const` - guarantees no modification; required to call on const objects.
- **Access specifiers** - `public:`, `private:`, `protected:` - control who can access members.
- **Encapsulation / data hiding** - private data + public interface separates what from how.
- **Getter / setter** - trivial public functions to read/write private data.
- **Constructor** - special function (same name as class, no return type) called on object creation.
- **Member initializer list** - `: m_x{val}, m_y{val}` before the constructor body; the correct way to init members.
- **Default constructor** - takes no arguments (or all have defaults); generated implicitly if none declared.
- **Delegating constructor** - one constructor forwards initialization to another via the initializer list.
- **Copy constructor** - initializes a new object from an existing one; parameter must be `const&`.
- **Copy elision** - compiler optimization eliminating unnecessary copies; **mandatory** in some cases since C++17.
- **Temporary object** - an unnamed object that lives only for the duration of a single expression.
- **Converting constructor** - any non-`explicit` constructor usable for implicit conversions.
- **`explicit` keyword** - prevents a constructor from being used for implicit conversions.
- **Constexpr class** - a class with `constexpr` constructors and member functions usable at compile time.

### Section-by-Section Detail

### 14.1 - Introduction to Object-Oriented Programming

- **OOP** bundles data (properties) and behavior (functions) into class types - **procedural** programming keeps them separate
- OOP provides **modularity**, **reusability**, and **encapsulation** - but is not universally superior to procedural code
- Use the right paradigm for the job - not everything benefits from OOP
- In procedural style, `struct Point` and `void print(Point)` are separate → in OOP, `class Point` owns its own `print()`

```cpp
// Procedural: data and logic separate
struct Point { int x; int y; };
void print(Point p) { std::cout << p.x << ',' << p.y; }

// OOP: data and logic bundled
class Point { int m_x, m_y; public: void print() const { std::cout << m_x << ',' << m_y; } };
```

→ _See [01_ClassVsStruct](../solutions/Chapter_14_Intro_To_Classes/01_ClassVsStruct/) for the class/struct distinction._

### 14.2 - Introduction to Classes

- A **`class`** is syntactically identical to a `struct` except members are **private by default** instead of public
- The motivation is the **class invariant** problem - structs let any code set members to invalid combinations (e.g., `Fraction` with denominator `0`)
- Classes solve this via **private data** + **constructors** (establish valid state) + **member functions** (maintain invariants on every modification)
- This separation of internal state from external access is the foundation of **encapsulation** in OOP

```cpp
struct S { int val; };       // members public by default
class  C { int val; };       // members private by default
S s; s.val = 5;              // OK - public
// C c; c.val = 5;           // ❌ error - val is private
```

→ _See [01_ClassVsStruct](../solutions/Chapter_14_Intro_To_Classes/01_ClassVsStruct/) for default access demos._

### 14.3 - Member Functions

- Member functions operate on the **implicit object** - they access data members directly without a prefix
- Members can be defined in any order inside the class - forward references within the class body are allowed
- Member functions can be **overloaded** like free functions
- `struct` types can also have member functions but should remain simple data aggregates

```cpp
class Foo {
    int m_val{};
public:
    void set(int v) { m_val = v; }     // implicit object provides m_val
    int  get() const { return m_val; }
};
```

→ _See [02_MemberFunctions](../solutions/Chapter_14_Intro_To_Classes/02_MemberFunctions/) for defining and calling member functions._

### 14.4 - Const Class Objects and Const Member Functions

- A **const object** cannot have its members modified - the compiler enforces this
- **Non-const member functions** cannot be called on const objects → the compiler rejects the call
- Append `const` after the parameter list to make a member function safe for const objects: `int get() const`
- **Best practice:** make every member function that doesn't modify state `const`

```cpp
class Foo {
    int m_val{};
public:
    int getValue() const { return m_val; }  // callable on const objects
};
const Foo f{};
std::cout << f.getValue();  // ✅ OK - getValue() is const
```

→ _See [03_ConstObjectsAndMemberFunctions](../solutions/Chapter_14_Intro_To_Classes/03_ConstObjectsAndMemberFunctions/) for const correctness demos._

### 14.5 - Public and Private Members and Access Specifiers

- **`struct`** defaults to `public` access; **`class`** defaults to `private`
- **Private** members are only accessible by other members of the same class
- Access is **per-class**, not per-object - one `Foo` can access another `Foo`'s private members inside a member function
- Use `struct` for plain data aggregates with no invariants; use `class` for types needing encapsulation

```cpp
class Foo {
    int m_secret{42};             // private by default
public:
    int getSecret() const { return m_secret; }
    bool sameSecret(const Foo& o) const { return m_secret == o.m_secret; } // per-class access
};
```

→ _See [04_AccessSpecifiers](../solutions/Chapter_14_Intro_To_Classes/04_AccessSpecifiers/) for access level demos._

**`class` vs `struct` Comparison:**

| Feature                 | `struct`                             | `class`                              |
| ----------------------- | ------------------------------------ | ------------------------------------ |
| **Default access**      | `public`                             | `private`                            |
| **Convention**          | Plain data aggregates, no invariants | Types with invariants, encapsulation |
| **Member functions?**   | Yes (but keep simple)                | Yes                                  |
| **Inheritance default** | `public`                             | `private`                            |

> **Rule of thumb:** Use `struct` for passive data bundles with no invariants. Use `class` when you need encapsulation and controlled access.

### 14.6 - Access Functions

- **Getters** return private data and should be marked `const`; **setters** assign values and can validate input
- Prefer **meaningful behaviors** (`kill()`, `takeDamage()`) over generic setters (`setAlive(false)`)
- Only provide access functions when genuinely needed - a minimal interface is easier to maintain
- Getters typically return by value for fundamental types and by `const&` for expensive-to-copy types

```cpp
class Player {
    int m_hp{100};
public:
    int  getHP() const { return m_hp; }   // getter (const)
    void takeDamage(int d) { m_hp -= d; } // meaningful behavior > setHP()
};
```

→ _See [05_EncapsulationAndDataHiding](../solutions/Chapter_14_Intro_To_Classes/05_EncapsulationAndDataHiding/) for getter/setter patterns._

### 14.7 - Member Functions Returning References to Data Members

- Returning a data member by **`const&`** avoids a copy and is safe when the implicit object outlives the call
- **Danger:** calling a member function on a **temporary** (rvalue) and saving the reference → **dangling reference** after the temporary is destroyed
- Never return a **non-const reference** to a private member - it defeats encapsulation
- Use return by value for cheap types; `const&` for expensive types when the caller doesn't need ownership

```cpp
class Str {
    std::string m_name{"hello"};
public:
    const std::string& getName() const { return m_name; } // safe const&
};
Str s{};
const auto& ref = s.getName();  // ✅ s outlives ref
```

→ _See [06_ReturningReferencesToMembers](../solutions/Chapter_14_Intro_To_Classes/06_ReturningReferencesToMembers/) for safe and dangerous return-by-ref patterns._

### 14.8 - The Benefits of Data Hiding (Encapsulation)

- **Encapsulation** hides implementation details behind a public interface - users interact with _what_ a class does, not _how_
- **Class invariants** are enforced because only member functions can modify private data - **error detection** can be added to setters without changing the interface
- Internal implementation can be **changed** (e.g., array → hash map) without breaking user code - **bugs are localized** to the class's own members
- Prefer **non-member functions** over unnecessary member functions - a smaller public interface is easier to maintain and test
- A well-encapsulated class exposes the **minimum interface** needed and no more

```cpp
class Account {
    double m_balance{0.0};
public:
    void deposit(double amt) { if (amt > 0) m_balance += amt; } // validates
    double balance() const { return m_balance; }
};
// Implementation of m_balance can change without affecting callers
```

### 14.9 - Introduction to Constructors

- **Constructors** initialize non-aggregate class objects - same name as the class, no return type, not `const`
- If no matching constructor exists for the initialization syntax → **compilation fails**
- Constructors don't create objects - they initialize **already-allocated memory**
- The compiler implicitly generates a default constructor if you declare none

```cpp
class Foo {
    int m_x{};
public:
    Foo(int x) : m_x{x} {}   // constructor - same name, no return type
};
Foo f{5};  // calls Foo(int)
```

→ _See [07_ConstructorsBasics](../solutions/Chapter_14_Intro_To_Classes/07_ConstructorsBasics/) for constructor fundamentals._

### 14.10 - Constructor Member Initializer Lists

- The **member initializer list** (: m_x{x}, m_y{y}`) initializes members **before** the constructor body runs - using direct initialization
- Members always initialize in **declaration order**, regardless of initializer list order - mismatches cause subtle bugs
- Prefer over body assignment - assignment first default-constructs then reassigns, which is less efficient and impossible for `const`/reference members
- **Default member initializers** (C++11) provide fallback values for members not listed in the initializer list

```cpp
class Foo {
    int m_a;
    int m_b;
public:
    Foo(int a, int b) : m_a{a}, m_b{b} {}  // initializer list - preferred
};
```

→ _See [08_MemberInitializerList](../solutions/Chapter_14_Intro_To_Classes/08_MemberInitializerList/) for initialization order and best practices._

> **Member Initializer List Key Rules:**
>
> - Members are initialized **before the constructor body** runs (direct initialization)
> - Initialization happens in **declaration order**, regardless of initializer list order - mismatches cause subtle bugs
> - Prefer over body assignment: assignment first default-constructs then reassigns (less efficient, impossible for `const`/reference members)
> - Default member initializers (C++11) provide fallback values for members not listed in the initializer list

### 14.11 - Default Constructors and Default Arguments

- The **default constructor** takes no arguments (or all parameters have defaults)
- If you declare no constructors, the compiler **implicitly generates** one - declaring _any_ constructor suppresses it
- Use **`= default`** to explicitly bring back the compiler-generated default constructor
- Constructors support **default arguments** and **overloading** like regular functions

```cpp
class Foo {
    int m_val{};
public:
    Foo() = default;            // bring back the default constructor
    Foo(int v) : m_val{v} {}
};
Foo a{};   // calls Foo()
Foo b{42}; // calls Foo(int)
```

→ _See [09_DefaultConstructors](../solutions/Chapter_14_Intro_To_Classes/09_DefaultConstructors/) for `= default` and implicit generation._

### 14.12 - Delegating Constructors

- A **delegating constructor** calls another constructor via the initializer list: `Foo(int x) : Foo{x, 0} {}` - reducing code duplication
- A delegating constructor **cannot** also directly initialize members in its own initializer list - delegation is exclusive
- Watch for **infinite delegation chains** - `Foo()` → `Foo(int)` → `Foo()` is undefined behavior
- Use delegation to centralize shared setup logic in one primary constructor

```cpp
class Foo {
    int m_x, m_y;
public:
    Foo(int x, int y) : m_x{x}, m_y{y} {}
    Foo(int x) : Foo{x, 0} {}   // delegates to Foo(int, int)
    Foo()      : Foo{0} {}       // delegates to Foo(int)
};
```

→ _See [10_DelegatingConstructors](../solutions/Chapter_14_Intro_To_Classes/10_DelegatingConstructors/) for delegation patterns._

### 14.13 - Introduction to Copy Constructors

- The **copy constructor** has the signature `Foo(const Foo& other)` - called when initializing from an existing object of the same type
- The compiler **generates one** if you don't declare it - it performs memberwise copy
- Use **`= delete`** to prevent copying entirely: `Foo(const Foo&) = delete;`
- Members are initialized in **declaration order**, not the order listed in the initializer list

```cpp
class Foo {
    int m_val{};
public:
    Foo(int v) : m_val{v} {}
    Foo(const Foo& other) : m_val{other.m_val} {}  // copy constructor
};
Foo a{5};
Foo b{a};  // calls copy constructor
```

→ _See [11_CopyConstructors](../solutions/Chapter_14_Intro_To_Classes/11_CopyConstructors/) for copy constructor demos._

### 14.14 - Copy Elision

- **Copy elision** lets the compiler skip copy/move constructor calls - constructing the object directly in its final destination, even if those constructors have side effects
- Since C++17, elision is **mandatory** when initializing from a **prvalue**: `Foo f = Foo{1, 2}` - the copy constructor doesn't even need to exist
- **NRVO** (Named Return Value Optimization) elides the copy when returning a named local variable - but NRVO is **optional**, not guaranteed
- Because of mandatory elision, expressive syntax like `Foo f = Foo{args}` has **zero overhead** in modern C++

```cpp
class Foo { public: Foo(int) {} Foo(const Foo&) { std::cout << "copy"; } };
Foo f = Foo{5};  // mandatory elision (C++17) - no copy printed
```

→ _See [12_CopyElision](../solutions/Chapter_14_Intro_To_Classes/12_CopyElision/) for elision behavior demos._

### 14.15 - Introduction to Temporary Objects

- `Foo{1, 2}` creates an **unnamed temporary** (anonymous object) - it exists only until the end of the **full expression**
- Passing a temporary directly to a function (`printFoo(Foo{1, 2})`) is common - constructed, used, and destroyed in one statement
- Prefer anonymous temporaries over named objects when the value is used only once and doesn't need a descriptive name
- Binding a **`const&`** to a temporary extends the temporary's lifetime to match the reference's scope

```cpp
void print(const Foo& f);
print(Foo{1, 2});  // anonymous temporary - created, used, destroyed
```

→ _See [13_TemporaryObjects](../solutions/Chapter_14_Intro_To_Classes/13_TemporaryObjects/) for temporary object patterns._

### 14.16 - Converting Constructors and the explicit Keyword

- By default, any single-argument constructor enables **implicit conversions**: `Foo f = 5;` silently calls `Foo(int)`
- This is usually undesirable - mark single-argument constructors **`explicit`** to require direct initialization: `Foo f{5};`
- `explicit` blocks both **copy-initialization** (`Foo f = 5;`) and **implicit argument conversion** in function calls
- **Best practice:** make all constructors `explicit` unless implicit conversion is intentionally useful

```cpp
class Foo {
    int m_val;
public:
    explicit Foo(int v) : m_val{v} {}
};
Foo a{5};     // ✅ direct init
// Foo b = 5; // ❌ error - implicit conversion blocked by explicit
```

→ _See [14_ConvertingConstructorsAndExplicit](../solutions/Chapter_14_Intro_To_Classes/14_ConvertingConstructorsAndExplicit/) for implicit conversion traps._

**Constructor Types Comparison:**

| Constructor Type  | Signature Example           | When Called                 | Key Rule                                                  |
| ----------------- | --------------------------- | --------------------------- | --------------------------------------------------------- |
| **Default**       | `Foo()` / `Foo() = default` | `Foo f{};`                  | Suppressed once any ctor declared; use `= default`        |
| **Parameterized** | `Foo(int x, int y)`         | `Foo f{1, 2};`              | Use member initializer list                               |
| **Copy**          | `Foo(const Foo&)`           | `Foo b{a};` / pass-by-value | Compiler-generated if not declared; `= delete` to prevent |
| **Delegating**    | `Foo(int x) : Foo{x, 0} {}` | Internally redirects        | Cannot also initialize members in its own list            |
| **Converting**    | `Foo(int)` (non-explicit)   | `Foo f = 5;`                | Mark `explicit` to prevent implicit conversions           |
| **Constexpr**     | `constexpr Foo(int x)`      | `constexpr Foo f{5};`       | All expressions must be constexpr-evaluable               |

### 14.17 - Constexpr Aggregates and Classes

- A class with **`constexpr`** constructors and member functions can be instantiated and used entirely at **compile time**: `constexpr Foo f{1, 2};`
- All member initializers and expressions must be **constexpr-evaluable** - no dynamic allocation, I/O, or runtime-only operations
- Enables **`static_assert`** validations on class objects and non-type template parameters (C++20)
- **Aggregates** are implicitly constexpr-capable if their members are literal types - making a class constexpr has no downside for purely computational types

```cpp
class Foo {
    int m_val;
public:
    constexpr Foo(int v) : m_val{v} {}
    constexpr int get() const { return m_val; }
};
constexpr Foo f{10};
static_assert(f.get() == 10);  // compile-time check
```

→ _See [15_ConstexprClasses](../solutions/Chapter_14_Intro_To_Classes/15_ConstexprClasses/) for compile-time class usage._

### Edge Cases and Caveats

❌ Calling a non-const member function on a const object:

```cpp
const Foo f{5};
f.setValue(10); // ❌ compile error - setValue() is non-const
```

✅ Mark member functions `const` when they don't modify the object:

```cpp
int getValue() const { return m_value; } // ✅ callable on const objects
```

---

❌ Initializer list order vs. declaration order:

```cpp
class Foo {
    int m_a;
    int m_b;
public:
    Foo(int v) : m_b{v}, m_a{m_b} {} // ❌ m_a inits first, m_b is garbage
};
```

✅ Keep member-initializer list in declaration order:

```cpp
Foo(int v) : m_a{v}, m_b{m_a} {} // ✅ m_a inits first, then m_b
```

---

❌ Forgetting `= default` after adding a parameterized constructor:

```cpp
class Foo {
public:
    Foo(int v) : m_val{v} {}
    // ❌ Foo f{}; won't compile - implicit default constructor suppressed
};
```

✅ Explicitly default it:

```cpp
Foo() = default; // ✅ brings back the default constructor
```

---

❌ Returning a non-const reference to a private member:

```cpp
int& getValue() { return m_value; } // ❌ defeats encapsulation
```

✅ Return by value or const reference:

```cpp
int getValue() const { return m_value; }         // ✅ by value
const int& getValue() const { return m_value; }   // ✅ const ref
```

---

❌ Dangling reference from getter on a temporary:

```cpp
const auto& ref = Foo{5}.getValue(); // ❌ temporary dies, ref dangles
```

✅ Store by value or keep the object alive:

```cpp
auto val = Foo{5}.getValue(); // ✅ copy is safe
```

---

❌ Missing `explicit` on a converting constructor:

```cpp
Foo(int v) : m_val{v} {} // ❌ allows Foo f = 5; and implicit conversions
```

✅ Use `explicit`:

```cpp
explicit Foo(int v) : m_val{v} {} // ✅ prevents accidental conversions
```

---

❌ Delegating constructor also initializing members:

```cpp
Foo(int a) : Foo{} , m_a{a} {} // ❌ not allowed - pick delegation or members
```

✅ Delegate only, then assign in the body:

```cpp
Foo(int a) : Foo{} { m_a = a; } // ✅ delegation + body assignment
```

---

❌ Infinite delegation chains:

```cpp
Foo() : Foo(0) {}
Foo(int) : Foo() {} // ❌ infinite recursion
```

✅ Ensure one constructor doesn't delegate back:

```cpp
Foo() : Foo(0) {}
Foo(int v) : m_val{v} {} // ✅ terminates the chain
```

---

❌ Assuming copy elision always happens:

```cpp
Foo makeFoo() { Foo f{5}; return f; } // NRVO - not guaranteed
```

✅ Mandatory for prvalues (C++17), but NRVO is optional - don't rely on it for correctness.

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_14_Intro_To_Classes/
```

| Project                                                                                                                | Concept                                                |
| ---------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------ |
| [01_ClassVsStruct](../solutions/Chapter_14_Intro_To_Classes/01_ClassVsStruct/)                                         | `class` vs `struct` - default access levels            |
| [02_MemberFunctions](../solutions/Chapter_14_Intro_To_Classes/02_MemberFunctions/)                                     | Defining and calling member functions, implicit object |
| [03_ConstObjectsAndMemberFunctions](../solutions/Chapter_14_Intro_To_Classes/03_ConstObjectsAndMemberFunctions/)       | Const objects and const member functions               |
| [04_AccessSpecifiers](../solutions/Chapter_14_Intro_To_Classes/04_AccessSpecifiers/)                                   | `public`, `private`, `protected`                       |
| [05_EncapsulationAndDataHiding](../solutions/Chapter_14_Intro_To_Classes/05_EncapsulationAndDataHiding/)               | Encapsulation, getters, setters, data hiding           |
| [06_ReturningReferencesToMembers](../solutions/Chapter_14_Intro_To_Classes/06_ReturningReferencesToMembers/)           | Returning const/non-const references to data members   |
| [07_ConstructorsBasics](../solutions/Chapter_14_Intro_To_Classes/07_ConstructorsBasics/)                               | Constructors - initialization semantics                |
| [08_MemberInitializerList](../solutions/Chapter_14_Intro_To_Classes/08_MemberInitializerList/)                         | Member initializer lists and initialization order      |
| [09_DefaultConstructors](../solutions/Chapter_14_Intro_To_Classes/09_DefaultConstructors/)                             | Default constructors, `= default`, implicit generation |
| [10_DelegatingConstructors](../solutions/Chapter_14_Intro_To_Classes/10_DelegatingConstructors/)                       | Delegating constructors to reduce redundancy           |
| [11_CopyConstructors](../solutions/Chapter_14_Intro_To_Classes/11_CopyConstructors/)                                   | Copy constructors, `= delete` to prevent copies        |
| [12_CopyElision](../solutions/Chapter_14_Intro_To_Classes/12_CopyElision/)                                             | Copy elision and mandatory elision since C++17         |
| [13_TemporaryObjects](../solutions/Chapter_14_Intro_To_Classes/13_TemporaryObjects/)                                   | Temporary (unnamed) class objects                      |
| [14_ConvertingConstructorsAndExplicit](../solutions/Chapter_14_Intro_To_Classes/14_ConvertingConstructorsAndExplicit/) | Converting constructors and the `explicit` keyword     |
| [15_ConstexprClasses](../solutions/Chapter_14_Intro_To_Classes/15_ConstexprClasses/)                                   | Constexpr constructors and compile-time objects        |

### Quick Reference

| Feature           | Syntax                              | Notes                          |
| ----------------- | ----------------------------------- | ------------------------------ |
| Class definition  | `class Foo { };`                    | Members private by default     |
| Struct definition | `struct Foo { };`                   | Members public by default      |
| Member function   | `void doThing() { }`                | Inside class definition        |
| Const member func | `int getValue() const { }`          | Safe on const objects          |
| Access specifiers | `public:`, `private:`, `protected:` | Apply to all following members |
| Constructor       | `Foo(int x, int y);`                | Same name, no return type      |
| Initializer list  | `Foo(int x) : m_x{x} { }`           | Before constructor body        |
| Default ctor      | `Foo() = default;`                  | Compiler-generated             |
| Delegating ctor   | `Foo(int x) : Foo{x, 0} { }`        | Calls another ctor             |
| Copy ctor         | `Foo(const Foo& other);`            | From existing object           |
| Delete copy       | `Foo(const Foo&) = delete;`         | Prevent copying                |
| Explicit ctor     | `explicit Foo(int x);`              | No implicit conversion         |
| Constexpr class   | `constexpr Foo(int x) : m_x{x} { }` | Compile-time usable            |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between a struct and a class in C++?

<details>
<summary>Show answer</summary>

**Direct answer:** The only language-level difference is default access: `struct` members are `public` by default, `class` members are `private` by default. By convention, use `struct` for plain data aggregates (no invariants) and `class` for types that enforce invariants through private data and public member functions.

**Detailed explanation:**
The class invariant problem motivates the distinction: a struct's public members can be set to any combination of values, even invalid ones (e.g., a `Fraction` with denominator 0). Classes solve this by making data private and controlling access through constructors and member functions.

```cpp
struct Point { int x{}; int y{}; };          // plain data - struct is fine
class Fraction                                // has invariant: denom != 0
{
    int m_num{};
    int m_denom{ 1 };
public:
    Fraction(int n, int d) : m_num{ n }, m_denom{ d }
    {
        if (d == 0) throw std::invalid_argument("zero denominator");
    }
};
```

</details>

2. Why should member functions that don't modify the object be marked `const`?

<details>
<summary>Show answer</summary>

**Direct answer:** A `const` member function promises not to modify the object, so it can be called on both const and non-const objects. Without the `const` qualifier, the function cannot be called on const objects or through const references - the compiler will reject the call.

**Detailed explanation:**

```cpp
class Circle
{
    double m_radius{};
public:
    double area() const { return 3.14159 * m_radius * m_radius; }  // const - OK on const objects
    void setRadius(double r) { m_radius = r; }                     // non-const - modifies state
};

void print(const Circle& c)
{
    std::cout << c.area();       // OK: area() is const
    // c.setRadius(5.0);         // ERROR: setRadius() is non-const
}
```

Best practice: mark every member function that doesn't modify state as `const`.

</details>

3. What happens if the member-initializer list order doesn't match declaration order?

<details>
<summary>Show answer</summary>

**Direct answer:** Members are always initialized in declaration order within the class, regardless of the order they appear in the member initializer list. Mismatching the order has no effect on initialization order but can cause subtle bugs if one member's initialization depends on another member that hasn't been initialized yet.

**Detailed explanation:**

```cpp
class Pair
{
    int m_x;
    int m_y;
public:
    // BUG: m_y listed first, but m_x is initialized first (declaration order)
    Pair(int v) : m_y{ v }, m_x{ m_y }  // m_x reads uninitialized m_y!
    { }
};
```

Best practice: always list members in the initializer list in the same order they are declared. Compilers can warn about this with `-Wreorder`.

</details>

4. Why is the implicit default constructor suppressed when you add a parameterized constructor?

<details>
<summary>Show answer</summary>

**Direct answer:** The compiler assumes that if you wrote a constructor with parameters, you likely want to control how objects are initialized, so it stops generating the implicit default constructor. To get it back, explicitly declare it with `= default`.

**Detailed explanation:**

```cpp
class Foo
{
    int m_x{};
public:
    Foo(int x) : m_x{ x } {}     // parameterized constructor
    // Foo() is now suppressed - Foo f{}; won't compile
    Foo() = default;               // explicitly bring it back
};
```

This prevents accidental default construction of objects that are meaningless without specific arguments (e.g., a `DatabaseConnection` without a connection string).

</details>

5. What does `explicit` on a constructor prevent?

<details>
<summary>Show answer</summary>

**Direct answer:** `explicit` prevents a constructor from being used for implicit conversions and copy-initialization. Without it, any constructor callable with a single argument can be invoked silently: `Foo f = 5;` would call `Foo(int)`. With `explicit`, only direct initialization works: `Foo f{ 5 };`.

**Detailed explanation:**

```cpp
class Temperature
{
    double m_celsius{};
public:
    explicit Temperature(double c) : m_celsius{ c } {}
};

Temperature t1{ 36.6 };         // OK: direct initialization
// Temperature t2 = 36.6;       // ERROR: copy-initialization blocked by explicit
// void print(Temperature t);
// print(36.6);                  // ERROR: implicit conversion blocked
```

Best practice: make all constructors `explicit` unless implicit conversion is intentionally part of the class's design (rare).

</details>

6. Can a delegating constructor also have a member-initializer list? Why or why not?

<details>
<summary>Show answer</summary>

**Direct answer:** No. When a constructor delegates to another constructor, the delegate initializes all members. If the delegating constructor also had its own member initializer list, members would be initialized twice, which is not allowed. A delegating constructor can only have a constructor body (for additional logic after delegation).

**Detailed explanation:**

```cpp
class Rect
{
    int m_w{};
    int m_h{};
public:
    Rect(int w, int h) : m_w{ w }, m_h{ h } {}
    Rect(int side) : Rect(side, side) {}   // delegates - no m_w{} allowed here
    // Rect(int side) : Rect(side, side), m_w{ side } {} // ERROR!
};
```

Watch for infinite delegation chains - `Rect()` delegates to `Rect(int)` which delegates back to `Rect()` - this is undefined behavior.

</details>

7. What is the difference between mandatory copy elision and NRVO?

<details>
<summary>Show answer</summary>

**Direct answer:** Mandatory copy elision (C++17) guarantees that when initializing from a prvalue (e.g., `Foo f = Foo{1, 2}`), the copy/move constructor is never called - the object is constructed directly in place. NRVO (Named Return Value Optimization) is an _optional_ optimization where the compiler constructs a named local return variable directly in the caller's storage, but it's not guaranteed.

**Detailed explanation:**

```cpp
Foo makeFoo()
{
    Foo f{ 1, 2 };   // named local variable
    return f;         // NRVO may elide the copy (optional)
}

Foo a = Foo{ 1, 2 };        // mandatory elision: no copy constructor needed
Foo b = makeFoo();           // NRVO: copy may be elided (compiler-dependent)
```

Because of mandatory copy elision, the copy/move constructor doesn't even need to exist for prvalue initialization. NRVO requires an accessible copy/move constructor (even if the compiler ends up eliding the call).

</details>

8. Why is returning a non-const reference to a private member dangerous?

<details>
<summary>Show answer</summary>

**Direct answer:** It defeats encapsulation by allowing callers to modify private data directly, bypassing any invariant checks the class enforces. Also, calling a member function on a temporary (rvalue) and saving the returned reference creates a dangling reference.

**Detailed explanation:**

```cpp
class Account
{
    int m_balance{ 0 };
public:
    int& balance() { return m_balance; }         // BAD: exposes private member
    const int& balance() const { return m_balance; } // OK: read-only access
};

Account a;
a.balance() = -1000;  // directly modifies private m_balance - no validation!
```

Return by `const&` to allow efficient read access, or return by value for small types. Never return a non-const reference to a private member unless there's a compelling reason.

</details>

9. What is the purpose of the `= default` and `= delete` specifiers on special member functions?

<details>
<summary>Show answer</summary>

**Direct answer:** `= default` tells the compiler to generate the default implementation of a special member function (e.g., default constructor, copy constructor). `= delete` prevents the function from being called entirely - any attempt results in a compile error. Use `= delete` to prevent copying, and `= default` to explicitly request the compiler-generated version when it would otherwise be suppressed.

**Detailed explanation:**

```cpp
class NoCopy
{
public:
    NoCopy() = default;                       // explicitly defaulted
    NoCopy(const NoCopy&) = delete;           // cannot copy
    NoCopy& operator=(const NoCopy&) = delete; // cannot copy-assign
};

NoCopy a;
// NoCopy b{ a };    // ERROR: copy constructor is deleted
```

</details>

10. What is a constexpr class and when can you use one?

<details>
<summary>Show answer</summary>

**Direct answer:** A class with `constexpr` constructors and `constexpr` member functions can be instantiated and used entirely at compile-time: `constexpr Foo f{1, 2};`. All member initializers and constructor expressions must be constexpr-evaluable. Aggregates (structs with no user-provided constructors) are implicitly constexpr-capable if their members are literal types.

**Detailed explanation:**

```cpp
class Point
{
    int m_x{};
    int m_y{};
public:
    constexpr Point(int x, int y) : m_x{ x }, m_y{ y } {}
    constexpr int sum() const { return m_x + m_y; }
};

constexpr Point p{ 3, 4 };
static_assert(p.sum() == 7);  // evaluated entirely at compile-time
```

</details>
