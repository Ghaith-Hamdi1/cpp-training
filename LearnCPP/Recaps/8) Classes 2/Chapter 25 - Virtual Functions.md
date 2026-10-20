# Chapter 25 Recap - Virtual Functions

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Use `virtual` on functions in the base class and `override` (without `virtual`) on all overrides in derived classes
- Always give base classes intended for inheritance a `virtual` destructor
- The signature of an override must **exactly** match the base function - including `const`. A mismatch silently creates a new function instead of an override
- Virtual function resolution only works through **pointers or references**, never on plain objects
- Never call virtual functions from constructors or destructors - the derived portion doesn't exist yet (or has already been destroyed)
- Virtual functions have a cost: one extra pointer per object (`__vptr`) and slightly slower dispatch
- Use pure virtual functions to define abstract interfaces and force derived classes to implement required behavior
- Pass polymorphic objects by reference or pointer, **never by value**, to avoid slicing

### 3 Tiny Examples

1.

```cpp
Dog dog; Cat cat;
Base* arr[]{ &dog, &cat };
for (auto* b : arr)
    b->speak(); // Without virtual: always calls Base::speak()
```

2.

```cpp
class Base { public: virtual void speak() { std::cout << "Base\n"; } };
class Dog : public Base { public: void speak() override { std::cout << "Woof\n"; } };
Base* b{new Dog()};
b->speak(); // "Woof" - virtual dispatch!
```

3.

```cpp
class Base { public: virtual void speak() const {} };
class Dog : public Base {
    public: void speak() const override {} // override catches mismatches
};
class Final final : public Base {}; // no class can inherit from Final
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Virtual function**: A member function declared with `virtual` that resolves to the most-derived override at runtime when called through a base pointer/reference.
- **Override**: A derived class function that matches the signature, const-ness, and return type of a base class virtual function.
- **Polymorphism**: The ability of an entity to take multiple forms - _compile-time_ (overloading, templates) vs. _runtime_ (virtual functions).
- **`override` specifier**: Tells the compiler to enforce that a function is a valid override; produces a compile error if it isn't.
- **`final` specifier**: Prevents a virtual function from being overridden further, or prevents a class from being inherited from.
- **Pure virtual function**: A virtual function assigned `= 0`; makes the class **abstract** (cannot be instantiated).
- **Abstract base class**: A class with at least one pure virtual function.
- **Interface class**: A class with no member variables and only pure virtual functions.
- **Virtual table (vtable)**: A compiler-generated lookup table of function pointers used to resolve virtual calls at runtime.
- **Early binding (static dispatch)**: Function call resolved at compile time (direct calls).
- **Late binding (dynamic dispatch)**: Function call resolved at runtime via a function pointer or vtable.
- **Object slicing**: Assigning a derived object to a base object by value, losing the derived portion.
- **`dynamic_cast`**: A runtime cast for safely downcasting a base pointer/reference to a derived type.
- **Covariant return types**: An override may return a pointer/reference to a _more-derived_ type than the base function returns.
- **Virtual base class**: Uses `virtual` inheritance to ensure a shared base is only included once in a diamond hierarchy.

### Section-by-Section Detail

### 25.1 - Pointers and references to the base class of derived objects

- A **base pointer/reference** can point to a derived object, but only sees **base class members** - derived-specific members are invisible
- Without `virtual`, calling a function through a base pointer always invokes the **base version** - even if the derived class overrides it
- This motivates **virtual functions** - an array of base pointers all calling the base version instead of their own overrides is useless
- Storing different derived types through a common base pointer is the **foundation of runtime polymorphism** in C++

```cpp
Dog dog; Cat cat;
Base* arr[]{ &dog, &cat };
for (auto* b : arr)
    b->speak(); // Without virtual: always calls Base::speak()
```

→ _See [01_PointersReferencesToBase](../solutions/Chapter_25_Virtual_Functions/01_PointersReferencesToBase/) for a demonstration of the problem._

### 25.2 - Virtual functions and polymorphism

- Marking a base function `virtual` enables the compiler to resolve calls to the **most-derived override** at runtime
- Virtual function resolution only works through **pointers or references** - not on objects directly
- All matching overrides in derived classes are **implicitly virtual** - the keyword is inherited automatically
- **Avoid** calling virtual functions from constructors or destructors - the derived part isn't yet (or is already) destroyed
- Once a function is `virtual` in a base class, it remains virtual in **all derived classes** even without the keyword

```cpp
class Base { public: virtual void speak() { std::cout << "Base\n"; } };
class Dog : public Base { public: void speak() override { std::cout << "Woof\n"; } };
Base* b{new Dog()};
b->speak(); // "Woof" - virtual dispatch!
```

→ _See [02_VirtualFunctionsPolymorphism](../solutions/Chapter_25_Virtual_Functions/02_VirtualFunctionsPolymorphism/) for virtual dispatch through base pointers._

> **Virtual vs Non-Virtual Calls Through a Base Pointer**
>
> | Aspect         | Non-virtual function              | Virtual function                    |
> | -------------- | --------------------------------- | ----------------------------------- |
> | Resolved at    | Compile time (early binding)      | Runtime (late binding)              |
> | Called version | Always the **base** class version | The **most-derived** override       |
> | Mechanism      | Direct function address           | vtable pointer lookup               |
> | Performance    | Slightly faster (no indirection)  | One extra pointer dereference       |
> | Use case       | Functions that should never vary  | Functions that vary by derived type |

### 25.3 - The override and final specifiers, and covariant return types

- `override` catches **signature mismatches** at compile time - wrong parameter type, missing `const`, or typos that silently create new functions
- `final` prevents further **overriding** of a specific function or prevents a class from being **inherited** from entirely
- **Covariant return types** allow an override to return a pointer/reference to a more-derived class - useful in clone patterns
- Always use `override` on derived virtual functions - it costs nothing and catches **subtle bugs** that are otherwise very hard to diagnose

```cpp
class Base { public: virtual void speak() const {} };
class Dog : public Base {
    public: void speak() const override {} // override catches mismatches
};
class Final final : public Base {}; // no class can inherit from Final
```

→ _See [03_OverrideAndFinal](../solutions/Chapter_25_Virtual_Functions/03_OverrideAndFinal/) for the `override`/`final` specifiers · [04_CovariantReturnTypes](../solutions/Chapter_25_Virtual_Functions/04_CovariantReturnTypes/) for covariant return types._

> **Which Specifier to Use?**
>
> - **Base class declaration** → `virtual` (enables dynamic dispatch)
> - **Derived class override** → `override` only (do NOT repeat `virtual` - it's redundant)
> - **Last override in chain** → `final` (prevents further overriding)
> - **Class not meant for inheritance** → `class C final : public B {}` (prevents subclassing)
> - **Covariant return** → return `Derived*`/`Derived&` where base returns `Base*`/`Base&` - compiler allows it automatically

### 25.4 - Virtual destructors, virtual assignment, and overriding virtualization

- Deleting a derived object through a base pointer **without a virtual destructor** → **undefined behavior** (derived destructor skipped, resources leaked)
- Always make destructors `virtual` in base classes designed for **polymorphic use** through pointers or references
- Use **scope resolution** (`base.Base::getName()`) to bypass virtual dispatch and force the base version to be called
- Avoid virtualizing `operator=` - it breaks the **symmetry** expected by assignment and causes subtle bugs

```cpp
class Base { public: virtual ~Base() = default; };
class Derived : public Base { int* m_data{new int{5}};
    public: ~Derived() { delete m_data; }
};
Base* b{new Derived()};
delete b; // virtual ~Base ensures ~Derived() runs
```

→ _See [05_VirtualDestructors](../solutions/Chapter_25_Virtual_Functions/05_VirtualDestructors/) for virtual destructor demos and undefined behavior without them._

### 25.5 - Early binding and late binding

- **Early binding** resolves direct function calls at **compile time** - the compiler knows the exact address, making it extremely fast
- **Late binding** resolves indirect calls (e.g., function pointers) at **runtime** - slightly slower but allows the target to vary
- Virtual functions use late binding via the **vtable** - the compiler generates code that looks up the correct function pointer at runtime
- The performance overhead (one extra pointer dereference) is usually **negligible** compared to the flexibility polymorphism provides

```cpp
someFunc(42);       // early binding - resolved at compile time
int (*fp)(int) = &someFunc;
fp(42);             // late binding - resolved at runtime
```

→ _See [06_EarlyAndLateBinding](../solutions/Chapter_25_Virtual_Functions/06_EarlyAndLateBinding/) for compile-time vs. runtime resolution._

> **Early Binding vs Late Binding**
>
> |                   | Early binding                     | Late binding                                      |
> | ----------------- | --------------------------------- | ------------------------------------------------- |
> | **When resolved** | Compile/link time                 | Runtime                                           |
> | **Mechanism**     | Direct jump to known address      | Pointer dereference (vtable)                      |
> | **Performance**   | Fastest - no indirection          | Slight overhead (1 pointer dereference)           |
> | **Flexibility**   | Target fixed at build time        | Target can vary per object                        |
> | **C++ examples**  | Non-virtual calls, free functions | Virtual calls, function pointers, `std::function` |

### 25.6 - The virtual table

- Each class with virtual functions gets a compiler-generated **vtable** - a static array of function pointers, one per virtual function
- Each object gets a hidden `__vptr` member (typically the first member) pointing to its class's vtable - adds **one pointer of overhead** per object
- Virtual call resolution: dereference `__vptr` → find vtable → call through the function pointer at the correct **index**
- A derived class's vtable starts as a **copy** of the base's, with entries replaced for any overridden functions - populated at compile time

```cpp
// Conceptual vtable layout:
// Base vtable:    { &Base::speak,    &Base::getName    }
// Derived vtable: { &Derived::speak, &Base::getName    }  // speak overridden
```

→ _See [07_VirtualTable](../solutions/Chapter_25_Virtual_Functions/07_VirtualTable/) for vtable and `__vptr` internals._

### 25.7 - Pure virtual functions, abstract base classes, and interface classes

- A **pure virtual function** (`= 0`) makes a class **abstract** - it cannot be instantiated and forces derived classes to provide an implementation
- **Interface classes** have no member variables and consist entirely of pure virtual functions - define a contract like Java/C# interfaces
- Pure virtual functions _can_ have a body for **default implementations** callable via `Base::func()` - the class remains abstract regardless
- Always give interface classes a **virtual destructor** so derived objects can be safely deleted through base pointers
- Abstract classes are ideal for defining **common APIs** across unrelated types in a polymorphic hierarchy

```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() = 0; // pure virtual - Shape is abstract
};
class Circle : public Shape {
    double m_r;
public:
    Circle(double r) : m_r{r} {}
    double area() override { return 3.14159 * m_r * m_r; }
};
```

→ _See [08_PureVirtualAbstractClasses](../solutions/Chapter_25_Virtual_Functions/08_PureVirtualAbstractClasses/) for pure virtual functions · [09_InterfaceClasses](../solutions/Chapter_25_Virtual_Functions/09_InterfaceClasses/) for interface class patterns._

> **Concrete vs Abstract vs Interface Classes**
>
> | Property                    | Concrete class               | Abstract class                    | Interface class                |
> | --------------------------- | ---------------------------- | --------------------------------- | ------------------------------ |
> | Has pure virtual functions? | No                           | At least one                      | All functions are pure virtual |
> | Has member variables?       | Typically yes                | May have                          | No                             |
> | Can be instantiated?        | Yes                          | No                                | No                             |
> | Purpose                     | Full implementation          | Partial implementation + contract | Pure contract (API only)       |
> | Virtual destructor needed?  | Only if used polymorphically | Yes                               | Yes                            |

### 25.8 - Virtual base classes

- In **diamond inheritance**, `virtual` on the inheritance list ensures the shared base class is included **only once**
- The **most-derived class** is responsible for constructing the virtual base class - directly calling its constructor
- Virtual base classes add a **vtable pointer** even to classes that otherwise wouldn't have one - increases complexity
- This is C++'s solution to the **diamond problem** introduced in Chapter 24 - prefer simpler designs when possible

```cpp
class PoweredDevice {};
class Scanner  : virtual public PoweredDevice {};
class Printer  : virtual public PoweredDevice {};
class Copier   : public Scanner, public Printer {};
// Only one PoweredDevice subobject in Copier
```

→ _See [10_VirtualBaseClasses](../solutions/Chapter_25_Virtual_Functions/10_VirtualBaseClasses/) for diamond inheritance and virtual base classes._

### 25.9 - Object slicing

- Assigning a derived object to a base object **by value** slices off the derived portion - derived members are **lost**
- Common slicing traps: pass-by-value parameters, `std::vector<Base>` - use **references**, **pointers**, or `std::reference_wrapper` instead
- A **Frankenobject** results from assigning one derived object to another through a base reference - base part changes but derived part retains old values
- Always pass polymorphic objects by **reference or pointer**, never by value, to preserve the full derived object

```cpp
Derived d;
Base b{d};     // ❌ Slicing - derived data lost
Base& ref{d};  // ✅ Reference preserves polymorphism
```

→ _See [11_ObjectSlicing](../solutions/Chapter_25_Virtual_Functions/11_ObjectSlicing/) for slicing demos, Frankenobjects, and prevention._

> **Common Slicing Scenarios and Fixes**
>
> | Scenario                  | Problem                                    | Fix                                         |
> | ------------------------- | ------------------------------------------ | ------------------------------------------- |
> | `Base b = derived;`       | Derived data lost on copy                  | Use `Base& b = derived;`                    |
> | `void f(Base b)`          | Parameter copied - sliced                  | `void f(const Base& b)`                     |
> | `std::vector<Base>`       | Elements stored by value - sliced          | `std::vector<std::unique_ptr<Base>>`        |
> | `base_ref = derived2;`    | Only base part overwritten → Frankenobject | Avoid cross-assignment through base refs    |
> | Returning `Base` by value | Derived portion stripped                   | Return `std::unique_ptr<Base>` or reference |

### 25.10 - Dynamic casting

- `dynamic_cast` safely converts a base pointer/reference to a derived type at **runtime** - returns `nullptr` on failure (pointers) or throws `std::bad_cast` (references)
- Requires at least one **virtual function** in the hierarchy and has a **runtime performance cost**
- Prefer **virtual functions** over downcasting - frequent use of `dynamic_cast` suggests the hierarchy needs a virtual function instead
- Always **check the result** before using it - unchecked `nullptr` dereference is undefined behavior

```cpp
Base* b{getShape()};
if (auto* d = dynamic_cast<Derived*>(b)) {
    d->derivedOnlyFunc(); // safe - cast succeeded
}
```

→ _See [12_DynamicCast](../solutions/Chapter_25_Virtual_Functions/12_DynamicCast/) for safe downcasting with `dynamic_cast`._

> **Should You Use `dynamic_cast`?**
>
> | Situation                                         | Recommendation                                                  |
> | ------------------------------------------------- | --------------------------------------------------------------- |
> | Need to call a derived-only function occasionally | `dynamic_cast` is acceptable - check for `nullptr`              |
> | Frequently downcasting in the same spot           | Add a virtual function to the base class instead                |
> | Type is known at compile time                     | Use `static_cast` (no runtime cost, no safety check)            |
> | Working with references                           | Wrap in try/catch for `std::bad_cast`, or cast to pointer first |
> | Hierarchy has no virtual functions                | `dynamic_cast` won't work - needs vtable info                   |

### 25.11 - Printing inherited classes using operator<<

- `operator<<` cannot be `virtual` because it's typically a **friend** (non-member) function - only member functions can be virtual
- Solution: have `operator<<` delegate to a **virtual member function** (e.g., `print(std::ostream&)`), which derived classes override
- This pattern only needs setup **once in the base class** - all derived classes automatically get correct output via virtual dispatch
- Each derived override can call `Base::print(out)` first to output **common fields** before appending its own data

```cpp
class Base {
    friend std::ostream& operator<<(std::ostream& os, const Base& b) {
        return b.print(os); // delegates to virtual
    }
protected:
    virtual std::ostream& print(std::ostream& os) const { return os << "Base"; }
};
```

### Edge Cases and Caveats

❌ Forgetting `virtual` on the base class function:

```cpp
class Base { public: void speak() { /*...*/ } }; // ❌ not virtual
Base* bp = new Derived;
bp->speak(); // always calls Base::speak()
```

✅ Make it virtual:

```cpp
virtual void speak() { /*...*/ } // ✅ enables polymorphism
```

---

❌ Signature mismatch in overrides:

```cpp
class Base { public: virtual void foo(int) const; };
class Derived : public Base {
    void foo(int); // ❌ missing const - silently hides, doesn't override
};
```

✅ Always use `override`:

```cpp
void foo(int) const override; // ✅ compiler catches mismatches
```

---

❌ Non-virtual destructor in a base class:

```cpp
class Base { public: ~Base() {} }; // ❌ non-virtual
Base* bp = new Derived;
delete bp; // ❌ UB - derived portion not destroyed
```

✅ Make base destructor virtual:

```cpp
virtual ~Base() = default; // ✅
```

---

❌ Object slicing via pass-by-value:

```cpp
void print(Base b) { b.speak(); } // ❌ derived part is sliced off
Derived d;
print(d); // calls Base::speak()
```

✅ Pass by const reference:

```cpp
void print(const Base& b) { b.speak(); } // ✅ polymorphism preserved
```

---

❌ Storing derived objects in `std::vector<Base>`:

```cpp
std::vector<Base> v;
v.push_back(Derived{}); // ❌ sliced to Base
```

✅ Use pointers or `std::reference_wrapper`:

```cpp
std::vector<std::unique_ptr<Base>> v; // ✅ no slicing
```

---

❌ Calling virtual functions in constructors/destructors:

```cpp
Base::Base() { speak(); } // ❌ calls Base::speak(), not Derived::speak()
```

✅ Virtual dispatch doesn't work during construction/destruction - avoid calling virtual functions there.

---

❌ Using `dynamic_cast` without checking for `nullptr`:

```cpp
Derived* dp = dynamic_cast<Derived*>(bp);
dp->foo(); // ❌ dp could be nullptr if cast failed
```

✅ Check first:

```cpp
if (auto* dp = dynamic_cast<Derived*>(bp)) dp->foo(); // ✅
```

---

❌ Writing both `virtual` and `override`:

```cpp
virtual void speak() override; // ❌ redundant - override implies virtual
```

✅ Just use `override`:

```cpp
void speak() override; // ✅
```

---

### Hands-On Code Projects

| #   | Project                                                                                                       | Concept                                                                        |
| --- | ------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------ |
| 01  | [01_PointersReferencesToBase](../solutions/Chapter_25_Virtual_Functions/01_PointersReferencesToBase/)         | Base pointers/references to derived objects - motivation for virtual functions |
| 02  | [02_VirtualFunctionsPolymorphism](../solutions/Chapter_25_Virtual_Functions/02_VirtualFunctionsPolymorphism/) | `virtual` keyword, runtime dispatch through pointers/references                |
| 03  | [03_OverrideAndFinal](../solutions/Chapter_25_Virtual_Functions/03_OverrideAndFinal/)                         | `override` specifier, `final` specifier, catching signature mismatches         |
| 04  | [04_CovariantReturnTypes](../solutions/Chapter_25_Virtual_Functions/04_CovariantReturnTypes/)                 | Returning a more-derived pointer/reference from an override                    |
| 05  | [05_VirtualDestructors](../solutions/Chapter_25_Virtual_Functions/05_VirtualDestructors/)                     | Why base classes need virtual destructors, undefined behavior without them     |
| 06  | [06_EarlyAndLateBinding](../solutions/Chapter_25_Virtual_Functions/06_EarlyAndLateBinding/)                   | Compile-time vs. runtime function resolution, function pointers                |
| 07  | [07_VirtualTable](../solutions/Chapter_25_Virtual_Functions/07_VirtualTable/)                                 | How the vtable and `__vptr` enable dynamic dispatch                            |
| 08  | [08_PureVirtualAbstractClasses](../solutions/Chapter_25_Virtual_Functions/08_PureVirtualAbstractClasses/)     | Pure virtual functions (`= 0`), abstract base classes                          |
| 09  | [09_InterfaceClasses](../solutions/Chapter_25_Virtual_Functions/09_InterfaceClasses/)                         | Classes with only pure virtual functions - defining contracts                  |
| 10  | [10_VirtualBaseClasses](../solutions/Chapter_25_Virtual_Functions/10_VirtualBaseClasses/)                     | Diamond inheritance, `virtual` inheritance, shared base                        |
| 11  | [11_ObjectSlicing](../solutions/Chapter_25_Virtual_Functions/11_ObjectSlicing/)                               | Slicing by value, Frankenobjects, prevention techniques                        |
| 12  | [12_DynamicCast](../solutions/Chapter_25_Virtual_Functions/12_DynamicCast/)                                   | `dynamic_cast` for safe downcasting, `nullptr` checks, `std::bad_cast`         |

> **Path:** `solutions/Chapter_25_Virtual_Functions/01_PointersReferencesToBase/main.cpp` … `12_DynamicCast/main.cpp`

### Quick Reference

| Feature             | Syntax / Usage                      | Notes                              |
| ------------------- | ----------------------------------- | ---------------------------------- |
| Virtual function    | `virtual void func();`              | In base class declaration          |
| Override            | `void func() override;`             | Derived class - catches mismatches |
| Final function      | `void func() final;`                | Prevents further overriding        |
| Final class         | `class C final : public B {};`      | Prevents inheritance               |
| Pure virtual        | `virtual void func() = 0;`          | Makes class abstract               |
| Virtual destructor  | `virtual ~Base() = default;`        | Always for polymorphic bases       |
| Dynamic cast (ptr)  | `auto* d = dynamic_cast<D*>(bPtr);` | Returns `nullptr` on failure       |
| Dynamic cast (ref)  | `auto& d = dynamic_cast<D&>(bRef);` | Throws `std::bad_cast` on failure  |
| Bypass virtual      | `obj.Base::func();`                 | Calls base version directly        |
| Virtual inheritance | `class D : virtual public B {};`    | Diamond problem fix                |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the purpose of the `virtual` keyword?

<details>
<summary>Show answer</summary>

**Direct answer:** `virtual` enables dynamic dispatch when a function is called through a base pointer or reference, the most-derived override is called at runtime instead of the base version. Without `virtual`, the base version is always called regardless of the actual object type.

**Detailed explanation:**

```cpp
class Animal
{
public:
    virtual std::string speak() const { return "???"; }
    virtual ~Animal() = default;
};

class Dog : public Animal
{
public:
    std::string speak() const override { return "Woof"; }
};

Animal* ptr = new Dog{};
std::cout << ptr->speak();  // "Woof" (virtual dispatch to Dog::speak)
delete ptr;                 // virtual destructor ensures Dog::~Dog runs
```

Virtual resolution only works through pointers/references calling on a value-type object uses the compile-time type.

</details>

2. Why should you always use `override` on derived class functions?

<details>
<summary>Show answer</summary>

**Direct answer:** `override` tells the compiler to verify that the function actually overrides a virtual base function. Without it, a typo or wrong parameter type silently creates a new function instead of overriding a bug that's very hard to spot.

**Detailed explanation:**

```cpp
class Base
{
public:
    virtual void doWork(int x) const {}
};

class Derived : public Base
{
public:
    void doWork(int x) override {}          // ERROR: missing const  caught!
    void doWork(int x) const override {}    // OK: correct override
    // void dowork(int x) const override {} // ERROR: typo caught!
};
```

Also use `final` to prevent further overriding: `void doWork(int x) const final {}`.

</details>

3. What happens if a base class destructor is not virtual?

<details>
<summary>Show answer</summary>

**Direct answer:** Deleting a derived object through a base pointer with a non-virtual destructor is undefined behavior. In practice, only the base destructor runs the derived destructor is skipped, leaking any resources the derived class manages (dynamic memory, file handles, etc.).

**Detailed explanation:**

```cpp
class Base
{
public:
    ~Base() { std::cout << "~Base\n"; }  // non-virtual!
};

class Derived : public Base
{
    int* m_data{new int[100]};
public:
    ~Derived() { delete[] m_data; std::cout << "~Derived\n"; }
};

Base* ptr = new Derived{};
delete ptr;   // only ~Base runs  m_data leaks! UB!

// Fix: make ~Base() virtual
```

Rule: any class with virtual functions should have a virtual destructor.

</details>

4. What is object slicing and how do you prevent it?

<details>
<summary>Show answer</summary>

**Direct answer:** When you assign or copy a derived object to a base object by value, the derived-specific members are "sliced off" only the base portion is kept. Virtual function calls on the sliced object call the base version. Prevent it by using references or pointers.

**Detailed explanation:**

```cpp
class Base    { public: virtual std::string name() { return "Base"; } };
class Derived : public Base { public: std::string name() override { return "Derived"; } };

Derived d;
Base b = d;         // SLICING: derived part lost
std::cout << b.name();  // "Base"  not "Derived"!

// Prevent slicing:
Base& ref = d;      // reference  no slicing
std::cout << ref.name();  // "Derived"  correct

// Also dangerous: std::vector<Base>  stores by value  slicing!
// Use std::vector<std::unique_ptr<Base>> for polymorphic containers
```

Also beware "Frankenobjects" from assigning derived objects through base references the base part changes but derived part doesn't, creating an inconsistent state.

</details>

5. Why can't you call virtual functions polymorphically in constructors?

<details>
<summary>Show answer</summary>

**Direct answer:** During base class construction, the derived portion hasn't been constructed yet calling a virtual function resolves to the base version, not the derived override. Similarly, during destruction, the derived part is already destroyed. This prevents accessing uninitialized derived data.

**Detailed explanation:**

```cpp
class Base
{
public:
    Base() { print(); }            // always calls Base::print
    virtual void print() const     { std::cout << "Base\n"; }
    virtual ~Base() = default;
};

class Derived : public Base
{
    int m_x{42};
public:
    void print() const override    { std::cout << "Derived: " << m_x << "\n"; }
};

Derived d;  // Output: "Base"  NOT "Derived: 42"
// During Base(), m_x doesn't exist yet, so calling Derived::print would be unsafe
```

If you need post-construction polymorphic initialization, use a separate `init()` method called after construction.

</details>

6. What is a pure virtual function and what does it make the class?

<details>
<summary>Show answer</summary>

**Direct answer:** A pure virtual function is declared with `= 0` and has no required implementation in the base class. It makes the class abstract the class cannot be instantiated directly. Any derived class must override all pure virtual functions to be concrete (instantiable).

**Detailed explanation:**

```cpp
class Shape   // abstract  can't create Shape objects
{
public:
    virtual double area() const = 0;     // pure virtual
    virtual ~Shape() = default;
};

class Circle : public Shape
{
    double m_radius{};
public:
    Circle(double r) : m_radius{r} {}
    double area() const override { return 3.14159 * m_radius * m_radius; }
};

// Shape s;         // ERROR: abstract
Circle c{5.0};      // OK: all pure virtuals overridden
Shape& ref = c;     // OK: references/pointers to abstract classes work
```

Pure virtuals can have a body (default implementation): `virtual void foo() = 0 { /* default */ }` derived classes can call it via `Base::foo()`.

</details>

7. How does `dynamic_cast` work and when does it return `nullptr`?

<details>
<summary>Show answer</summary>

**Direct answer:** `dynamic_cast<Derived*>(basePtr)` performs a runtime type check. It returns the derived pointer if the object is actually of that derived type (or a class derived from it), otherwise `nullptr`. For references, it throws `std::bad_cast` on failure. Requires at least one virtual function in the hierarchy (needs vtable info).

**Detailed explanation:**

```cpp
class Base    { public: virtual ~Base() = default; };
class Derived : public Base { public: void special() {} };
class Other   : public Base {};

Base* ptr = new Derived{};

Derived* d = dynamic_cast<Derived*>(ptr);  // succeeds: d != nullptr
Other*   o = dynamic_cast<Other*>(ptr);    // fails: o == nullptr

if (d)
    d->special();   // safe to call

delete ptr;
```

Prefer virtual functions over `dynamic_cast` frequent downcasting is often a sign that the class hierarchy needs redesign.

</details>

8. What is the difference between early binding and late binding?

<details>
<summary>Show answer</summary>

**Direct answer:** Early binding (static binding) resolves function calls at compile time the compiler knows the exact function address. Late binding (dynamic binding) resolves calls at runtime through a function pointer lookup (vtable). Virtual functions use late binding; non-virtual calls use early binding. Late binding has a small overhead (one pointer indirection) but enables polymorphism.

**Detailed explanation:**

```cpp
class Base
{
public:
    void earlyBound()          { std::cout << "Base\n"; }   // early binding
    virtual void lateBound()   { std::cout << "Base\n"; }   // late binding
};

class Derived : public Base
{
public:
    void earlyBound()          { std::cout << "Derived\n"; }
    void lateBound() override  { std::cout << "Derived\n"; }
};

Base* ptr = new Derived{};
ptr->earlyBound();  // "Base"     resolved at compile time (early binding)
ptr->lateBound();   // "Derived"  resolved at runtime via vtable (late binding)
delete ptr;
```

</details>

9. What is an interface class and why is it useful?

<details>
<summary>Show answer</summary>

**Direct answer:** An interface class has no member variables and consists entirely of pure virtual functions (plus a virtual destructor). It defines a contract that derived classes must implement similar to interfaces in Java/C#. This lets unrelated classes be used polymorphically through a common API.

**Detailed explanation:**

```cpp
class ISerializable    // interface class (convention: prefix with I)
{
public:
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& data) = 0;
    virtual ~ISerializable() = default;
};

class Player : public ISerializable
{
    std::string m_name;
    int m_score{};
public:
    std::string serialize() const override { return m_name + ":" + std::to_string(m_score); }
    void deserialize(const std::string& data) override { /* parse data */ }
};
```

A class can inherit from multiple interfaces (since they have no data), avoiding the diamond problem.

</details>

10. What is the covariant return type and when is it useful?

<details>
<summary>Show answer</summary>

**Direct answer:** If a base virtual function returns `Base*` or `Base&`, a derived override can return `Derived*` or `Derived&` instead this is a covariant return type. It's useful for clone/factory patterns where the derived version should return the more specific type.

**Detailed explanation:**

```cpp
class Base
{
public:
    virtual Base* clone() const { return new Base{*this}; }
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    Derived* clone() const override { return new Derived{*this}; }
    // Returns Derived* instead of Base*  covariant return
};

Derived d;
Derived* d2 = d.clone();       // returns Derived*  no cast needed
Base* b = d.clone();            // also works  Derived* converts to Base*
delete d2;
delete b;
```

Only works with pointers and references, not value types.

</details>
