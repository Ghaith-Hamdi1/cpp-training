# Chapter 24 Recap - Inheritance

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Use **public inheritance** unless you have a specific reason not to - it's the standard and most intuitive kind
- Derived constructors must delegate initialization of inherited members to the base class constructor via the initializer list (e.g., `: Base{id}`)
- Construction goes **most-base → most-derived**; destruction goes **most-derived → most-base**
- **Favor private members** over protected; use protected only when derived classes genuinely need direct access and the cost of an interface is too high
- When overriding a function, use `Base::func()` (scope resolution) to call the base version - omitting the qualifier causes infinite recursion
- Overload resolution only considers the **most-derived class** that has at least one function with the matching name; use `using Base::func;` to pull base overloads into scope
- A `using` declaration changes access for **all** overloads of a name - you cannot selectively change one overload
- **Avoid multiple inheritance** unless the alternatives produce more complexity; prefer single inheritance or interfaces

### 3 Tiny Examples

1.

```cpp
class Fruit { public: std::string m_name; };
class Apple : public Fruit { // Apple "is-a" Fruit
    public: std::string m_variety;
};
```

2.

```cpp
class Person { public: std::string m_name; };
class Employee : public Person { public: int m_id; };
class Supervisor : public Employee { public: int m_teamSize; };
```

3.

```cpp
class Base    { public: Base()    { std::cout << "Base\n"; } };
class Derived : public Base {
    public: Derived() { std::cout << "Derived\n"; }
};
Derived d; // Output: Base, then Derived
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Inheritance** - creating new classes by acquiring attributes and behaviors from existing classes ("is-a" relationship), as opposed to composition ("has-a")
- **Base class / Parent class / Superclass** - the class being inherited from
- **Derived class / Child class / Subclass** - the class doing the inheriting
- **Public inheritance** - the most common form; inherited public members stay public, protected stay protected
- **Protected access specifier** - accessible by the class itself, friends, and derived classes, but not the public
- **Private and protected inheritance** - rarely used forms that restrict inherited member access
- **Function overriding (redefining)** - providing a new definition of a base class function in the derived class
- **Inheritance chains** - classes derived from classes that are themselves derived (A → B → C)
- **Multiple inheritance** - a class inheriting from more than one base class
- **Diamond problem** - ambiguity that arises when two base classes share a common ancestor
- **Mixins** - small classes designed to be inherited from to add specific functionality

### Section-by-Section Detail

### 24.1 - Introduction to inheritance

- **Inheritance** models is-a relationships - an `Apple` is-a `Fruit`, inheriting all its properties and behaviors
- Hierarchies flow from **general** (top) to **specific** (bottom), with each level adding more detail
- Derived classes automatically acquire all **base class members** - no need to redefine shared functionality
- **Composition** (has-a) is the alternative - use inheritance only when the derived type truly is a kind of the base type
- Inheritance enables **code reuse** across related types without duplicating logic

```cpp
class Fruit { public: std::string m_name; };
class Apple : public Fruit { // Apple "is-a" Fruit
    public: std::string m_variety;
};
```

### 24.2 - Basic inheritance in C++

- Syntax for public inheritance: `class Derived : public Base` - the derived class gets all base members plus its own
- **Inheritance chains** allow multi-level derivation (e.g., `Supervisor` → `Employee` → `Person`), each level inheriting everything above
- Each derived class only defines what **distinguishes it** from its parent - shared functionality lives in the base
- Avoids **code duplication** across the hierarchy by centralizing common logic in the most-base class

```cpp
class Person { public: std::string m_name; };
class Employee : public Person { public: int m_id; };
class Supervisor : public Employee { public: int m_teamSize; };
```

→ _See [01_BasicInheritance](../solutions/Chapter_24_Inheritance/01_BasicInheritance) for basic inheritance syntax · [02_InheritanceChains](../solutions/Chapter_24_Inheritance/02_InheritanceChains) for multi-level derivation._

### 24.3 - Order of construction of derived classes

- Construction runs **most-base first** → down to **most-derived** - ensures base members are initialized before derived code runs
- Destruction runs in **reverse order** - most-derived first, then back up to most-base
- Memory for the entire object (base + derived parts) is allocated in **one step**, but constructors execute sequentially
- The base class is **fully constructed** before the derived constructor body begins executing

```cpp
class Base    { public: Base()    { std::cout << "Base\n"; } };
class Derived : public Base {
    public: Derived() { std::cout << "Derived\n"; }
};
Derived d; // Output: Base, then Derived
```

→ _See [03_OrderOfConstruction](../solutions/Chapter_24_Inheritance/03_OrderOfConstruction) for a demonstration with print statements showing the construction/destruction sequence._

> **Construction / Destruction Order at a Glance**
>
> For `class C : public B` and `class B : public A`:
>
> - Construction: `A()` → `B()` → `C()` (most-base first)
> - Destruction: `~C()` → `~B()` → `~A()` (most-derived first)
> - Memory: allocated all at once; constructors run in sequence

### 24.4 - Constructors and initialization of derived classes

- Derived constructors call a base constructor via the **member initializer list**: `Derived(int x, int y) : Base{x}, m_y{y} {}`
- Inherited members **cannot** be initialized directly in the derived initializer list - they must be delegated to the base constructor
- If no base constructor is explicitly called → the **default base constructor** is used automatically
- Destructors run in **reverse** construction order - if a base class has virtual functions, its destructor should be `virtual`

```cpp
class Base {
public:
    Base(int x) : m_x{x} {}
protected:
    int m_x;
};
class Derived : public Base {
public:
    Derived(int x, int y) : Base{x}, m_y{y} {} // delegate to Base
private:
    int m_y;
};
```

→ _See [04_ConstructorsAndInitialization](../solutions/Chapter_24_Inheritance/04_ConstructorsAndInitialization) for delegating to the base constructor._

### 24.5 - Inheritance and access specifiers

- The `protected` access specifier - accessible by the class, **friends**, and **derived classes**, but not the public
- **Public inheritance** preserves access levels; **private inheritance** makes all inherited members private; **protected inheritance** makes public members protected
- The inheritance type acts as an **access ceiling** - members can only stay the same or become more restrictive
- **Private** base members are always inaccessible to derived classes regardless of inheritance type
- Favor `private` members with public/protected accessors - use `protected` only when derived classes genuinely need direct access

```cpp
class Base { protected: int m_x; private: int m_priv; };
class Derived : public Base {
    void foo() { m_x = 5; } // OK - protected
    // m_priv is inaccessible
};
```

→ _See [05_ProtectedAccessSpecifier](../solutions/Chapter_24_Inheritance/05_ProtectedAccessSpecifier) for `protected` demos · [06_InheritanceAccessTypes](../solutions/Chapter_24_Inheritance/06_InheritanceAccessTypes) for public vs protected vs private inheritance._

> **Access Specifier × Inheritance Type**
>
> | Base member access | `public` inheritance | `protected` inheritance | `private` inheritance |
> | ------------------ | -------------------- | ----------------------- | --------------------- |
> | `public`           | `public`             | `protected`             | `private`             |
> | `protected`        | `protected`          | `protected`             | `private`             |
> | `private`          | inaccessible         | inaccessible            | inaccessible          |
>
> Rule: the inheritance type acts as a **ceiling** - members can only stay the same or become more restrictive. `private` base members are always inaccessible regardless.

### 24.6 - Adding new functionality to a derived class

- Derived classes can define **new member functions** not present in the base class, extending its interface
- Useful when the base class is part of a **library** and cannot be modified directly
- Base class objects **cannot call** derived-only functions - accessible only through derived objects or via virtual dispatch
- Only add functionality that **logically belongs** to the more-specific type - general functions belong in the base

```cpp
class Base { public: int getValue() { return m_val; } protected: int m_val; };
class Derived : public Base {
    public: void setNewThing(int x) { m_extra = x; } // new functionality
    private: int m_extra;
};
```

→ _See [07_AddingNewFunctionality](../solutions/Chapter_24_Inheritance/07_AddingNewFunctionality) for examples of extending base class interfaces._

### 24.7 - Calling inherited functions and overriding behavior

- A derived function with the **same name** as a base function **hides** the base version for derived objects
- Use the **scope resolution operator** (`Base::functionName()`) inside the derived version to call the base version - omitting it → **infinite recursion**
- A `using` declaration (`using Base::print;`) brings base class **overloads** back into the derived class's overload set
- Overload resolution only considers the **most-derived class** that has at least one function with the matching name

```cpp
class Derived : public Base {
public:
    void identify() {
        Base::identify(); // call base version first
        std::cout << "I am Derived\n";
    }
};
```

→ _See [08_OverridingBehavior](../solutions/Chapter_24_Inheritance/08_OverridingBehavior) for overriding · [10_UsingDeclarationOverloads](../solutions/Chapter_24_Inheritance/10_UsingDeclarationOverloads) for `using` declarations._

> **Overriding vs Hiding vs `using` Declaration**
>
> | Mechanism               | What happens                                        | Base overloads visible?        |
> | ----------------------- | --------------------------------------------------- | ------------------------------ |
> | **Override**            | Derived redefines same-name, same-params function   | No - all base overloads hidden |
> | **Hide (access)**       | Move inherited member to different access specifier | All overloads moved together   |
> | **Delete**              | Prevent calling an inherited function               | Only deleted overload blocked  |
> | **`using` declaration** | Pull base overloads into derived scope              | Yes - all overloads restored   |
>
> Key rule: `using` is all-or-nothing - you cannot selectively bring one overload while excluding another.

### 24.8 - Hiding inherited functionality

- A `using` declaration under a different access specifier **changes** an inherited member's visibility in the derived class
- Functions can be **deleted** in the derived class (`= delete`) to prevent their use entirely
- Hidden or private members can still be accessed by **casting** to a base reference - hiding is not airtight
- A `using` declaration changes access for **all overloads** of a name - you cannot selectively change one overload

```cpp
class Derived : public Base {
private:
    using Base::publicFunc;        // hide from Derived's users
public:
    void anotherFunc() = delete;   // prevent calling
};
```

→ _See [09_HidingInheritedFunctionality](../solutions/Chapter_24_Inheritance/09_HidingInheritedFunctionality) for hiding and deleting inherited members._

### 24.9 - Multiple inheritance

- A class can inherit from **multiple bases**: `class T : public A, public B` - introduces risk of ambiguous function calls
- The **diamond problem** arises when two bases share a common ancestor → the shared base gets included twice
- Ambiguities must be resolved with **explicit scope resolution**: `obj.Base::func()`
- The diamond problem is solved with **virtual base classes** (covered in Chapter 25) - many languages disallow multiple inheritance entirely
- Prefer **composition** or **interfaces** over multiple inheritance to reduce coupling and complexity

```cpp
class A { public: void foo() {} };
class B { public: void foo() {} };
class C : public A, public B {};
C c;
c.A::foo(); // must disambiguate
```

→ _See [11_MultipleInheritance](../solutions/Chapter_24_Inheritance/11_MultipleInheritance) for multiple base classes · [12_DiamondProblem](../solutions/Chapter_24_Inheritance/12_DiamondProblem) for the diamond problem._

> **When Is Multiple Inheritance Acceptable?**
>
> - Inheriting from **pure interface classes** (no data, only pure virtuals) - safe and common
> - Inheriting from **mixin classes** that add orthogonal behavior (e.g., `Serializable`, `Printable`)
> - Two bases with **no shared ancestor** and **no overlapping function names** - proceed with caution
> - Two bases that **share a common ancestor** - diamond problem; use virtual inheritance or redesign
> - When **composition** can achieve the same result with less coupling - prefer composition

### 24.x - Chapter 24 summary and quiz

- Consolidates all topics with a **summary table** of access specifiers and inheritance types and practice quiz problems
- Tests understanding of **construction/destruction order**, access rules, and class design under different inheritance types
- **Public inheritance** is by far the most useful and most common form - private and protected inheritance are niche tools
- Key takeaway - favor `private` members, delegate to base constructors, and use `using` declarations to manage overload visibility

```cpp
class Base { public: int pub; protected: int prot; private: int priv; };
class Derived : public Base {
    void test() { pub = 1; prot = 2; } // priv is inaccessible
};
```

### Edge Cases and Caveats

❌ Trying to initialize inherited members in the derived initializer list:

```cpp
Derived(int x) : m_base_val{x} {} // ❌ C++ forbids this
```

✅ Delegate to the base constructor:

```cpp
Derived(int x) : Base{x} {} // ✅ base handles its own members
```

---

❌ Assigning inherited members in the derived constructor body:

```cpp
Derived(int x) { m_base_val = x; } // ❌ fails for const/ref members, less efficient
```

✅ Use the base constructor in the member initializer list.

---

❌ Calling a same-named function without scope resolution:

```cpp
void Derived::print() {
    print(); // ❌ infinite recursion - calls itself, not Base::print()
}
```

✅ Use scope resolution:

```cpp
void Derived::print() {
    Base::print(); // ✅ calls the base version
}
```

---

❌ Forgetting that private base members are inaccessible:

```cpp
class Derived : public Base {
    void foo() { m_private = 5; } // ❌ can't access Base's private members
};
```

✅ Use `protected` in the base, or provide public/protected accessors.

---

❌ Assuming overload resolution checks the base class:

```cpp
class Base { public: void foo(int); void foo(double); };
class Derived : public Base { public: void foo(int); };
Derived d;
d.foo(3.14); // ❌ calls Derived::foo(int), not Base::foo(double) - base overloads hidden
```

✅ Use a `using` declaration:

```cpp
class Derived : public Base {
public:
    using Base::foo; // ✅ brings all base overloads into scope
    void foo(int);
};
```

---

❌ Using multiple inheritance carelessly:

```cpp
class D : public A, public B {};
D d;
d.func(); // ❌ ambiguous if both A and B have func()
```

✅ Resolve with explicit scope:

```cpp
d.A::func(); // ✅ explicit
```

---

❌ Hiding base functionality unintentionally:

```cpp
class Derived : public Base {
public:
    void print(int x); // ❌ hides ALL Base::print() overloads
};
```

✅ Use `using Base::print;` to keep base overloads visible.

---

### Hands-On Code Projects

| #   | Project                                                                                                   | Concept                                                                            |
| --- | --------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------------- |
| 01  | [01_BasicInheritance](../solutions/Chapter_24_Inheritance/01_BasicInheritance)                           | Basic public inheritance syntax and "is-a" relationships                           |
| 02  | [02_InheritanceChains](../solutions/Chapter_24_Inheritance/02_InheritanceChains)                         | Multi-level inheritance (A → B → C)                                                |
| 03  | [03_OrderOfConstruction](../solutions/Chapter_24_Inheritance/03_OrderOfConstruction)                     | Construction (most-base first) and destruction (most-derived first) order          |
| 04  | [04_ConstructorsAndInitialization](../solutions/Chapter_24_Inheritance/04_ConstructorsAndInitialization) | Delegating initialization of inherited members to the base constructor             |
| 05  | [05_ProtectedAccessSpecifier](../solutions/Chapter_24_Inheritance/05_ProtectedAccessSpecifier)           | The `protected` keyword and its interaction with derived classes                   |
| 06  | [06_InheritanceAccessTypes](../solutions/Chapter_24_Inheritance/06_InheritanceAccessTypes)               | Public vs protected vs private inheritance                                         |
| 07  | [07_AddingNewFunctionality](../solutions/Chapter_24_Inheritance/07_AddingNewFunctionality)               | Adding new member functions in derived classes                                     |
| 08  | [08_OverridingBehavior](../solutions/Chapter_24_Inheritance/08_OverridingBehavior)                       | Overriding base class functions and calling the base version with scope resolution |
| 09  | [09_HidingInheritedFunctionality](../solutions/Chapter_24_Inheritance/09_HidingInheritedFunctionality)   | Hiding/deleting inherited functions and changing access levels                     |
| 10  | [10_UsingDeclarationOverloads](../solutions/Chapter_24_Inheritance/10_UsingDeclarationOverloads)         | Using declarations to bring base overloads into scope                              |
| 11  | [11_MultipleInheritance](../solutions/Chapter_24_Inheritance/11_MultipleInheritance)                     | Inheriting from multiple base classes and resolving ambiguities                    |
| 12  | [12_DiamondProblem](../solutions/Chapter_24_Inheritance/12_DiamondProblem)                               | The diamond problem and common pitfalls with multiple inheritance                  |

> **Path:** `solutions/Chapter_24_Inheritance/01_BasicInheritance/main.cpp` … `12_DiamondProblem/main.cpp`

### Quick Reference

| Feature               | Syntax / Usage                    | Notes                            |
| --------------------- | --------------------------------- | -------------------------------- |
| Public inheritance    | `class D : public B {}`           | Preserves access levels          |
| Protected inheritance | `class D : protected B {}`        | Public → protected               |
| Private inheritance   | `class D : private B {}`          | Everything → private             |
| Call base constructor | `D(int x) : B{x} {}`              | In member initializer list       |
| Call base function    | `Base::func()`                    | Scope resolution inside override |
| Bring base overloads  | `using Base::func;`               | In derived class body            |
| Delete inherited func | `void func() = delete;`           | Prevents calling in derived      |
| Multiple inheritance  | `class T : public A, public B {}` | Beware ambiguity                 |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. Why can't a derived class initialize base class members in its own initializer list?

<details>
<summary>Show answer</summary>

**Direct answer:** C++ constructs objects in phases the base class is constructed first, using its own constructor. By the time the derived initializer list runs, the base members are already initialized. The derived class must delegate to a base constructor instead: `Derived(int x, int y) : Base{x}, m_y{y} {}`.

**Detailed explanation:**

```cpp
class Base
{
    int m_x{};
public:
    Base(int x) : m_x{x} {}
};

class Derived : public Base
{
    int m_y{};
public:
    // Derived(int x, int y) : m_x{x}, m_y{y} {}  // ERROR: can't init m_x here
    Derived(int x, int y) : Base{x}, m_y{y} {}     // OK: delegate to Base ctor
};
```

If no base constructor is specified, the default base constructor is called. If the base has no default constructor, you must explicitly call one.

</details>

2. What access specifier allows derived classes to access a base member but not outside code?

<details>
<summary>Show answer</summary>

**Direct answer:** `protected` accessible by the class itself, its friends, and all derived classes, but not by outside code. Use it for members that derived classes genuinely need to access directly; otherwise prefer `private` with public/protected getters.

**Detailed explanation:**

```cpp
class Base
{
public:    int m_pub{};      // anyone can access
protected: int m_prot{};     // derived classes + friends only
private:   int m_priv{};     // only Base + friends
};

class Derived : public Base
{
    void foo()
    {
        m_pub = 1;     // OK
        m_prot = 2;    // OK (protected)
        // m_priv = 3; // ERROR: private to Base
    }
};
```

The type of inheritance (public/protected/private) further restricts access public inheritance preserves access levels, private makes everything private.

</details>

3. How does hiding differ from overriding?

<details>
<summary>Show answer</summary>

**Direct answer:** Hiding occurs when a derived class defines a function with the same name as a base function the base version becomes hidden (regardless of parameters). Overriding specifically refers to virtual functions where the derived class provides a new implementation that is called via dynamic dispatch. Hiding is resolved at compile time; overriding is resolved at runtime through the vtable.

**Detailed explanation:**

```cpp
class Base
{
public:
    void print(int x)    { std::cout << "Base: " << x; }
    virtual void greet() { std::cout << "Hello from Base"; }
};

class Derived : public Base
{
public:
    void print(double x) { std::cout << "Derived: " << x; }  // HIDES Base::print(int)
    void greet() override { std::cout << "Hello from Derived"; }  // OVERRIDES
};

Derived d;
d.print(42);           // calls Derived::print(double)  Base version is hidden
// d.print((int)42);   // still calls Derived version
d.Base::print(42);     // explicit scope resolution to call hidden base version

// Use 'using Base::print;' in Derived to bring both overloads into scope
```

</details>

4. What is the diamond problem in multiple inheritance?

<details>
<summary>Show answer</summary>

**Direct answer:** When two base classes share a common ancestor, the derived class gets two copies of the common ancestor's members leading to ambiguity (which copy?). For example: `D` inherits from `B` and `C`, both of which inherit from `A`. `D` has two `A` sub-objects. The fix is virtual inheritance: `class B : virtual public A`.

**Detailed explanation:**

```cpp
class A { public: int m_val{}; };
class B : public A {};
class C : public A {};
class D : public B, public C {};  // Diamond: D has two A sub-objects

D d;
// d.m_val = 5;    // ERROR: ambiguous  B::m_val or C::m_val?
d.B::m_val = 5;    // OK but ugly

// Fix with virtual inheritance:
class B2 : virtual public A {};
class C2 : virtual public A {};
class D2 : public B2, public C2 {};  // single shared A sub-object
D2 d2;
d2.m_val = 5;      // OK: only one m_val
```

Multiple inheritance adds complexity prefer composition or interfaces where possible.

</details>

5. What does a `using` declaration do for inherited functions?

<details>
<summary>Show answer</summary>

**Direct answer:** A `using` declaration brings base class functions into the derived class's scope. This is useful for (1) un-hiding base overloads when the derived class has its own function of the same name, and (2) changing the access level of an inherited member. Note: `using` applies to all overloads of a name you can't selectively bring one.

**Detailed explanation:**

```cpp
class Base
{
public:
    void print(int x)    { std::cout << "int: " << x; }
    void print(double x) { std::cout << "double: " << x; }
protected:
    int m_value{};
};

class Derived : public Base
{
public:
    using Base::print;    // brings both Base::print overloads into Derived scope
    using Base::m_value;  // changes m_value from protected to public

    void print(std::string s) { std::cout << "string: " << s; }
};

Derived d;
d.print(42);        // calls Base::print(int)  no longer hidden
d.print(3.14);      // calls Base::print(double)
d.print("hello");   // calls Derived::print(string)
```

</details>

6. What is the order of construction and destruction in inheritance?

<details>
<summary>Show answer</summary>

**Direct answer:** Construction goes from most-base to most-derived: `Base` constructor runs first, then `Derived`. Destruction is the reverse: `Derived` destructor runs first, then `Base`. This ensures base members are fully initialized before derived code runs, and derived resources are cleaned up before the base is destroyed.

**Detailed explanation:**

```cpp
class A
{
public:
    A()  { std::cout << "A ctor\n"; }
    ~A() { std::cout << "A dtor\n"; }
};

class B : public A
{
public:
    B()  { std::cout << "B ctor\n"; }
    ~B() { std::cout << "B dtor\n"; }
};

class C : public B
{
public:
    C()  { std::cout << "C ctor\n"; }
    ~C() { std::cout << "C dtor\n"; }
};

C c;
// Output: A ctor, B ctor, C ctor, C dtor, B dtor, A dtor
```

</details>

7. Can a derived class access a base class's private members? How can you work around this?

<details>
<summary>Show answer</summary>

**Direct answer:** No private members are only accessible to the class that defines them and its friends. Derived classes cannot access them directly. Workarounds: use `protected` (if derived access is needed), or provide public/protected getter/setter functions in the base class.

**Detailed explanation:**

```cpp
class Base
{
private:
    int m_secret{42};
protected:
    int getSecret() const { return m_secret; }  // derived can call this
public:
    int getPublicSecret() const { return m_secret; }
};

class Derived : public Base
{
public:
    void show()
    {
        // std::cout << m_secret;       // ERROR: private
        std::cout << getSecret();       // OK: protected getter
        std::cout << getPublicSecret(); // OK: public getter
    }
};
```

Prefer `private` + accessors over `protected` members it preserves encapsulation.

</details>

8. What happens if you call a function with the same name as a base function without scope resolution?

<details>
<summary>Show answer</summary>

**Direct answer:** The derived version hides the base version entirely. All base overloads with that name become invisible. Inside the derived class, calling the same-named function without `Base::` prefix creates infinite recursion if you're in the derived version itself.

**Detailed explanation:**

```cpp
class Base
{
public:
    void print() { std::cout << "Base\n"; }
};

class Derived : public Base
{
public:
    void print()
    {
        // print();          // INFINITE RECURSION  calls Derived::print
        Base::print();       // correct: explicitly calls Base version
        std::cout << "Derived\n";
    }
};

Derived d;
d.print();       // calls Derived::print (Base version is hidden)
d.Base::print(); // explicitly calls Base::print
```

</details>

9. What is the difference between public, protected, and private inheritance?

<details>
<summary>Show answer</summary>

**Direct answer:** Public inheritance preserves all access levels (most common models "is-a"). Protected inheritance makes public members protected in the derived class. Private inheritance makes all inherited members private (models "implemented-in-terms-of"). Almost always use public inheritance.

**Detailed explanation:**

| Base member | Public inheritance | Protected inheritance | Private inheritance |
| ----------- | ------------------ | --------------------- | ------------------- |
| public      | public             | protected             | private             |
| protected   | protected          | protected             | private             |
| private     | inaccessible       | inaccessible          | inaccessible        |

```cpp
class Base { public: int m_x{}; protected: int m_y{}; };

class PubDerived  : public Base {};     // m_x is public, m_y is protected
class ProtDerived : protected Base {};  // m_x is protected, m_y is protected
class PrivDerived : private Base {};    // m_x is private, m_y is private
```

</details>

10. Why should a base class with virtual functions have a virtual destructor?

<details>
<summary>Show answer</summary>

**Direct answer:** If you delete a derived object through a base pointer with a non-virtual destructor, only the base destructor runs the derived destructor is skipped, leaking any resources the derived class manages. A virtual destructor ensures the correct (most-derived) destructor is called.

**Detailed explanation:**

```cpp
class Base
{
public:
    virtual ~Base() = default;   // virtual destructor  safe polymorphic deletion
};

class Derived : public Base
{
    int* m_data{new int[100]};
public:
    ~Derived() { delete[] m_data; }  // runs correctly when deleted via Base*
};

Base* ptr = new Derived{};
delete ptr;   // calls Derived::~Derived, then Base::~Base  correct!

// Without virtual: only Base::~Base runs  m_data leaks!
```

Rule of thumb: if a class has any virtual function, give it a virtual destructor.

</details>
