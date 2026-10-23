# Chapter 26 Recap - Templates and Classes

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- **Keep template class code in headers.** The compiler needs the full template definition wherever it's instantiated. Putting member function definitions in `.cpp` files causes linker errors.
- **Prefer non-template function overloads over function template specializations.** They're simpler, don't require matching the primary template's signature exactly, and resolve with higher priority.
- **Functions cannot be partially specialized** - only classes can. If you need partial specialization for a member function, you must partially specialize the entire class (or use a base-class pattern to reduce code duplication).
- **Full specializations are not implicitly inline.** Mark them `inline` when defined in a header to avoid ODR violations.
- **Non-type template parameters must be constexpr.** They enable compile-time-sized arrays and other constant constructs.
- **Use `static_assert` with type traits** (e.g., `std::is_pointer_v`) to prevent undesirable template instantiations rather than relying on partial specialization alone.
- **Template classes are only instantiated when used.** If you never use `Array<float>`, the compiler never generates it.
- **When defining members outside a template class**, each member needs its own `template` declaration, and the class name includes the template arguments (e.g., `Array<T>::operator[]`).

### 3 Tiny Examples

1.

```cpp
template <typename T>
class Array {
    T* m_data{};
    int m_size{};
public:
    T& operator[](int i) { return m_data[i]; }
};
```

2.

```cpp
template <typename T, int size>
class StaticArray {
    T m_data[size]{};
public:
    T& operator[](int i) { return m_data[i]; }
};
StaticArray<int, 5> arr; // size must be constexpr
```

3.

```cpp
template <typename T>
void print(T val) { std::cout << val; }
template <>
void print<double>(double val) { std::cout << std::scientific << val; }
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Template class**: A class definition parameterized by one or more types (or values), allowing the compiler to generate type-specific versions on demand.
- **Non-type template parameter**: A template parameter that takes a constexpr value (e.g., `int size`) rather than a type, commonly used to define fixed-size arrays at compile time.
- **Full (explicit) template specialization**: Providing a completely custom implementation of a template for one specific set of template arguments (e.g., `Storage<bool>`).
- **Partial template specialization**: Specializing a class template for a subset of its parameters while leaving others generic (e.g., specializing `T` to `char` but keeping `size` templated). Only classes support this - functions do not.
- **Template instantiation**: The compiler generates ("stencils out") a concrete class or function from a template only when it is actually used with specific types.
- **Primary template**: The original, non-specialized template definition that serves as the default implementation.

### Section-by-Section Detail

### 26.1 - Template Classes

- **Template classes** replace type-specific duplicates (`IntArray`, `DoubleArray`) with a single `template <typename T> class Array<T>` that works for any type.
- Member functions defined outside the class each need their own `template <typename T>` declaration and use `Array<T>::` as the scope.
- Template class code should live entirely in **header files** - the compiler needs the full definition at the point of use.
- Splitting template definitions into `.cpp` files → **linker errors** because other translation units can't see the definition.

```cpp
template <typename T>
class Array {
    T* m_data{};
    int m_size{};
public:
    T& operator[](int i) { return m_data[i]; }
};
```

→ _See [01_BasicClassTemplate](../solutions/Chapter_26_Templates_And_Classes/01_BasicClassTemplate) for a basic template class · [02_MemberFunctionsOutsideClass](../solutions/Chapter_26_Templates_And_Classes/02_MemberFunctionsOutsideClass) for out-of-class member definitions._

### 26.2 - Template Non-Type Parameters

- **Non-type template parameters** accept **constexpr values** (integers, pointers, enumerators) instead of types - e.g. `StaticArray<T, int size>`.
- The non-type argument must be `constexpr` - passing a runtime variable is a **compile error**.
- Each unique non-type value generates a **separate class instantiation** - `StaticArray<int, 5>` and `StaticArray<int, 10>` are distinct types.
- `std::array` uses exactly this pattern internally - a type parameter for the element type and an integer non-type parameter for the size.

```cpp
template <typename T, int size>
class StaticArray {
    T m_data[size]{};
public:
    T& operator[](int i) { return m_data[i]; }
};
StaticArray<int, 5> arr; // size must be constexpr
```

→ _See [03_NonTypeTemplateParameters](../solutions/Chapter_26_Templates_And_Classes/03_NonTypeTemplateParameters) for constexpr non-type template parameters._

> **Non-type parameter constraints at a glance:**
>
> - Must be `constexpr` - runtime variables are a compile error
> - Allowed types: integral, enum, pointer, reference, `std::nullptr_t`, and (C++20) floating-point and literal class types
> - Each unique value creates a **distinct type** (`Array<int,5>` ≠ `Array<int,10>`)
> - Cannot be `std::string`, class types (pre-C++20), or floating-point (pre-C++20)
> - `std::array<T,N>` is the standard library's use of this pattern

### 26.3 - Function Template Specialization

- A template function needing different behavior for a specific type can use a **non-template overload** (preferred) or a **full specialization** via `template<>`.
- Non-template overloads take **higher priority** in overload resolution than specializations.
- Full specializations are **not** implicitly `inline` - mark them `inline` when defined in a header to avoid ODR violations.
- **Partial specialization of functions is not allowed** - only classes support it.
- To specialize a single member function of a class template, specialize the member directly (e.g. `template<> void Storage<double>::print()`) without rewriting the entire class.

```cpp
template <typename T>
void print(T val) { std::cout << val; }
template <>
void print<double>(double val) { std::cout << std::scientific << val; }
```

→ _See [04_FunctionTemplateSpecialization](../solutions/Chapter_26_Templates_And_Classes/04_FunctionTemplateSpecialization) for full function specialization · [05_MemberFunctionSpecialization](../solutions/Chapter_26_Templates_And_Classes/05_MemberFunctionSpecialization) for member-only specialization._

> **When to Use Which Specialization Technique?**
>
> | Goal                                                       | Technique                         | Notes                                                         |
> | ---------------------------------------------------------- | --------------------------------- | ------------------------------------------------------------- |
> | Different behavior for one specific type (function)        | Non-template overload (preferred) | Highest priority in overload resolution; simplest             |
> | Different behavior for one specific type (function)        | Full function specialization      | Must match primary signature exactly; not implicitly `inline` |
> | Different behavior for one member only                     | Member function specialization    | Rest of the class stays generic                               |
> | Different behavior for a set of types (e.g., all pointers) | Partial class specialization      | Functions cannot be partially specialized                     |
> | Completely different class for one type                    | Full class specialization         | Independent class - can change everything                     |

### 26.4 - Class Template Specialization

- Entire classes can be **fully specialized** for a specific type by providing a complete class definition preceded by `template<>`.
- The specialized class is **completely independent** - you can change data members, implementation, and interface entirely.
- Example: `Storage8<bool>` packs 8 bools into a single `uint8_t` using **bit manipulation** instead of a wasteful 8-element array.
- Specializations should be defined in the **same header** as the primary template so the compiler always sees them before attempting generic instantiation.

```cpp
template<> class Storage8<bool> {
    uint8_t m_byte{};
public:
    void set(int bit, bool val) {
        if (val) m_byte |= (1 << bit);
        else     m_byte &= ~(1 << bit);
    }
};
```

→ _See [06_ClassTemplateSpecialization](../solutions/Chapter_26_Templates_And_Classes/06_ClassTemplateSpecialization) for the `Storage8<bool>` bit-packing example._

### 26.5 - Partial Template Specialization

- **Partial specialization** fixes some template parameters while keeping others generic - e.g. `StaticArray<char, N>` for any `N`.
- Only **classes** can be partially specialized - functions cannot.
- To partially specialize a member function, you must partially specialize the **entire class**.
- A common pattern uses a **base class template** holding shared logic - both the primary and partially specialized classes inherit from it to avoid code duplication.

```cpp
template <typename T, int N>
class StaticArray { /* generic implementation */ };

template <int N> // partial: char fixed, size generic
class StaticArray<char, N> {
    void print() { for (int i{0}; i < N; ++i) std::cout << m_data[i]; }
};
```

→ _See [07_PartialTemplateSpecialization](../solutions/Chapter_26_Templates_And_Classes/07_PartialTemplateSpecialization) for partial class specialization · [10_BaseClassPatternPartialSpec](../solutions/Chapter_26_Templates_And_Classes/10_BaseClassPatternPartialSpec) for the base-class pattern._

### 26.6 - Partial Template Specialization for Pointers

- Instantiating `Storage<T>` with a pointer type stores the **address**, not a copy - leading to **dangling-pointer bugs** if the pointed-to data changes or is destroyed.
- Solution 1: use `static_assert` with `std::is_pointer_v` to **block** pointer instantiation entirely.
- Solution 2: **partially specialize** the class for `T*` so it dereferences and deep-copies the value (e.g. using `std::unique_ptr`).
- Mixing **copy semantics** (primary template) with **reference semantics** (pointer specialization) is a common source of bugs - be consistent and explicit.

```cpp
template <typename T>
class Storage<T*> { // partial spec for pointer types
    std::unique_ptr<T> m_value;
public:
    Storage(T* ptr) : m_value{std::make_unique<T>(*ptr)} {} // deep copy
};
```

→ _See [08_PartialSpecForPointers](../solutions/Chapter_26_Templates_And_Classes/08_PartialSpecForPointers) for pointer partial specialization · [09_StaticAssertTypeTraits](../solutions/Chapter_26_Templates_And_Classes/09_StaticAssertTypeTraits) for `static_assert` + type traits to block pointer instantiation._

> **Handling Pointer Instantiation - Decision Guide**
>
> | Strategy                                       | When to use                                         | Pros                                       | Cons                                    |
> | ---------------------------------------------- | --------------------------------------------------- | ------------------------------------------ | --------------------------------------- |
> | `static_assert(!std::is_pointer_v<T>)`         | Pointers should never be used with this class       | Simple, clear compile error                | Blocks all pointer use - no flexibility |
> | Partial specialization for `T*` with deep copy | Class should work with pointers via value semantics | Transparent to caller; consistent behavior | Extra code; must manage ownership       |
> | Document reference semantics                   | Pointer use is intentional (e.g., observer pattern) | No extra code                              | Callers must understand ownership model |

### Edge Cases and Caveats

❌ Putting template member function definitions in a `.cpp` file:

```cpp
// myclass.cpp
template <typename T>
void MyClass<T>::doWork() {} // ❌ linker error - other TUs can't see this
```

✅ Keep everything in the header:

```cpp
// myclass.h
template <typename T>
void MyClass<T>::doWork() {} // ✅ visible to all TUs
```

---

❌ Forgetting `template <typename T>` on out-of-class definitions:

```cpp
void Array<T>::resize(int n) {} // ❌ T is unknown
```

✅ Include the template header:

```cpp
template <typename T>
void Array<T>::resize(int n) {} // ✅
```

---

❌ Using `Array` instead of `Array<T>` outside the class body:

```cpp
template <typename T>
Array Array<T>::copy() { ... } // ❌ return type should be Array<T>
```

✅ Use the full name outside the class:

```cpp
template <typename T>
Array<T> Array<T>::copy() { ... } // ✅
```

---

❌ Trying to partially specialize a function:

```cpp
template <typename T>
void print(T) {}
template <typename T>
void print<T*>(T*) {} // ❌ partial specialization of functions not allowed
```

✅ Use a non-template overload or partially specialize the enclosing class.

---

❌ Passing a non-constexpr value as a non-type template argument:

```cpp
int n = 5;
std::array<int, n> a; // ❌ n must be constexpr
```

✅ Use a compile-time constant:

```cpp
constexpr int n = 5;
std::array<int, n> a; // ✅
```

---

❌ Instantiating a template with a pointer without considering ownership:

```cpp
Storage<int*> s{&localVar}; // ❌ dangling if localVar dies
```

✅ Be aware that `Storage<int*>` stores the pointer, not a copy of the value.

---

❌ Forgetting to make full specializations `inline` in headers:

```cpp
// header.h
template <>
void print<double>(double d) { ... } // ❌ multiple definition errors
```

✅ Mark as `inline`:

```cpp
template <>
inline void print<double>(double d) { ... } // ✅
```

---

❌ Defining a specialization in a separate header without including it:

```cpp
// If specialization header isn't included, compiler silently uses the generic template ❌
```

✅ Ensure specialization headers are always included where needed.

---

### Hands-On Code Projects

| #   | Project                                                                                                               | Concept                                                                                    |
| --- | --------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| 01  | [01_BasicClassTemplate](../solutions/Chapter_26_Templates_And_Classes/01_BasicClassTemplate)                         | Defining a template class (`Array<T>`) with member functions inside the class body         |
| 02  | [02_MemberFunctionsOutsideClass](../solutions/Chapter_26_Templates_And_Classes/02_MemberFunctionsOutsideClass)       | Correctly defining template member functions outside the class (common pitfalls)           |
| 03  | [03_NonTypeTemplateParameters](../solutions/Chapter_26_Templates_And_Classes/03_NonTypeTemplateParameters)           | Using constexpr non-type template parameters (`StaticArray<T, int size>`)                  |
| 04  | [04_FunctionTemplateSpecialization](../solutions/Chapter_26_Templates_And_Classes/04_FunctionTemplateSpecialization) | Full function template specialization vs. non-template overloads                           |
| 05  | [05_MemberFunctionSpecialization](../solutions/Chapter_26_Templates_And_Classes/05_MemberFunctionSpecialization)     | Specializing a single member function without rewriting the entire class                   |
| 06  | [06_ClassTemplateSpecialization](../solutions/Chapter_26_Templates_And_Classes/06_ClassTemplateSpecialization)       | Full class template specialization (`Storage8<bool>` bit-packing example)                  |
| 07  | [07_PartialTemplateSpecialization](../solutions/Chapter_26_Templates_And_Classes/07_PartialTemplateSpecialization)   | Partial template specialization for classes (fixing one parameter, keeping others generic) |
| 08  | [08_PartialSpecForPointers](../solutions/Chapter_26_Templates_And_Classes/08_PartialSpecForPointers)                 | Partial specialization for pointer types - avoiding dangling-pointer bugs                  |
| 09  | [09_StaticAssertTypeTraits](../solutions/Chapter_26_Templates_And_Classes/09_StaticAssertTypeTraits)                 | Using `static_assert` + `std::is_pointer_v` to prevent unwanted instantiations             |
| 10  | [10_BaseClassPatternPartialSpec](../solutions/Chapter_26_Templates_And_Classes/10_BaseClassPatternPartialSpec)       | Base-class pattern to avoid code duplication when partially specializing                   |

> **Path:** `solutions/Chapter_26_Templates_And_Classes/01_BasicClassTemplate/main.cpp` … `10_BaseClassPatternPartialSpec/main.cpp`

### Quick Reference

| Feature                   | Syntax / Usage                          | Notes                           |
| ------------------------- | --------------------------------------- | ------------------------------- |
| Template class            | `template <typename T> class Arr {};`   | Keep in header files            |
| Non-type param            | `template <typename T, int N>`          | Must be constexpr               |
| Out-of-class member       | `template <typename T> T Arr<T>::get()` | Each member needs `template`    |
| Full func specialization  | `template<> void func<int>(int)`        | Not implicitly inline           |
| Full class specialization | `template<> class C<bool> {};`          | Completely independent class    |
| Partial class spec        | `template<int N> class C<char, N> {};`  | Fix some params, keep others    |
| Pointer partial spec      | `template<typename T> class C<T*> {};`  | Handle pointer types separately |
| Prevent instantiation     | `static_assert(!std::is_pointer_v<T>)`  | Inside class body               |
| Member func spec          | `template<> void C<double>::print()`    | Without rewriting whole class   |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. Why must template definitions be in headers, not `.cpp` files?

<details>
<summary>Show answer</summary>

**Direct answer:** The compiler needs the full template definition at the point of instantiation to generate code for the specific type. If the definition is in a `.cpp` file, other translation units can't see it resulting in linker errors ("undefined reference"). Put both the declaration and definition in the header.

**Detailed explanation:**

```cpp
// Array.h  everything in the header
template <typename T>
class Array
{
    T* m_data{};
    int m_size{};
public:
    Array(int size) : m_size{size}, m_data{new T[size]{}} {}
    T& operator[](int idx) { return m_data[idx]; }
    int size() const { return m_size; }
    ~Array() { delete[] m_data; }
};

// main.cpp
#include "Array.h"
Array<int> a{10};     // compiler generates Array<int> from the header
Array<double> b{5};   // generates Array<double>  separate class
```

</details>

2. What is the difference between full specialization and partial specialization?

<details>
<summary>Show answer</summary>

**Direct answer:** Full specialization (`template<>`) fixes all template parameters for one specific type. Partial specialization fixes some parameters while keeping others generic. Only classes can be partially specialized functions cannot.

**Detailed explanation:**

```cpp
// Primary template
template <typename T, int size>
class StaticArray { T m_arr[size]; };

// Full specialization: all params fixed
template <>
class StaticArray<bool, 8>
{
    unsigned char m_data{};  // pack 8 bools into one byte
};

// Partial specialization: T fixed to char, size still generic
template <int size>
class StaticArray<char, size>
{
    char m_arr[size]{};
public:
    void print() const { std::cout << m_arr; }  // char-specific printing
};

StaticArray<int, 5> a;     // uses primary
StaticArray<bool, 8> b;    // uses full specialization
StaticArray<char, 20> c;   // uses partial specialization
```

</details>

3. Can you partially specialize a function template? What's the workaround?

<details>
<summary>Show answer</summary>

**Direct answer:** No C++ does not allow partial specialization of function templates. The workaround is to use a non-template function overload (preferred, because overloads are prioritized over specializations) or to wrap the function in a class template that can be partially specialized.

**Detailed explanation:**

```cpp
// Primary template
template <typename T>
void print(const T& val) { std::cout << val; }

// Full specialization  works:
template <>
void print<double>(const double& val) { std::cout << std::fixed << val; }

// Partial specialization  NOT allowed:
// template <typename T>
// void print<T*>(T* val) { ... }  // ERROR

// Workaround 1: non-template overload (preferred)
void print(const char* str) { std::cout << '"' << str << '"'; }

// Workaround 2: wrap in a class
template <typename T> struct Printer            { static void print(const T& v) { std::cout << v; } };
template <typename T> struct Printer<T*>        { static void print(T* v) { std::cout << *v; } };  // partial spec OK
```

</details>

4. What is a non-type template parameter and what constraints does it have?

<details>
<summary>Show answer</summary>

**Direct answer:** A non-type template parameter is a compile-time constant value (not a type) used as a template argument most commonly an integer. The argument must be `constexpr`. Each unique value creates a separate class instantiation (`Array<int, 5>` and `Array<int, 10>` are distinct types).

**Detailed explanation:**

```cpp
template <typename T, int size>    // 'size' is a non-type parameter
class StaticArray
{
    T m_arr[size]{};               // size known at compile time
public:
    T& operator[](int idx) { return m_arr[idx]; }
    constexpr int length() const { return size; }
};

StaticArray<int, 5> a;    // size = 5
StaticArray<int, 10> b;   // size = 10, different type from a

// constexpr n{5};
// StaticArray<int, n> c; // OK if n is constexpr
// int x{5};
// StaticArray<int, x> d; // ERROR: x is not constexpr
```

`std::array<T, N>` uses exactly this pattern internally.

</details>

5. Why is `Array` allowed inside the class body but requires `Array<T>` outside?

<details>
<summary>Show answer</summary>

**Direct answer:** Inside the class template body, the compiler knows the template parameters from the surrounding declaration, so `Array` alone is sufficient (it implicitly means `Array<T>`). Outside the class, the compiler doesn't have that context, so you must write `Array<T>::` to specify which instantiation you're defining a member for.

**Detailed explanation:**

```cpp
template <typename T>
class Array
{
    // Inside the class: 'Array' implicitly means 'Array<T>'
    Array(const Array& src);            // OK
    Array& operator=(const Array& rhs); // OK
};

// Outside the class: must use Array<T>
template <typename T>
Array<T>::Array(const Array<T>& src) { /* ... */ }

template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& rhs) { /* ... */ }
```

</details>

6. What happens if a full specialization isn't marked `inline` in a header?

<details>
<summary>Show answer</summary>

**Direct answer:** Full specializations are no longer templates they're concrete functions/classes. If defined in a header included by multiple translation units, you get multiple-definition linker errors. Mark them `inline` (or define them in a `.cpp` file) to avoid this.

**Detailed explanation:**

```cpp
// Primary template (implicitly inline as a template):
template <typename T>
void print(const T& val) { std::cout << val; }

// Full specialization  NOT implicitly inline:
template <>
inline void print<double>(const double& val)  // 'inline' needed in header!
{
    std::cout << std::fixed << val;
}

// Without 'inline': if two .cpp files include this header,
// the linker sees two definitions of print<double>  error
```

This does not apply to class full specializations when defined in a single `.cpp` file.

</details>

7. How do class template argument deduction (CTAD) guides work?

<details>
<summary>Show answer</summary>

**Direct answer:** CTAD (C++17) lets the compiler deduce template arguments from constructor arguments. Deduction guides are custom rules that tell the compiler how to map constructor parameter types to template arguments when the automatic deduction isn't sufficient or would deduce the wrong type.

**Detailed explanation:**

```cpp
template <typename T>
class Wrapper
{
    T m_value;
public:
    Wrapper(T val) : m_value{val} {}
};

// CTAD works automatically here:
Wrapper w{42};        // deduces Wrapper<int>
Wrapper w2{3.14};     // deduces Wrapper<double>

// Custom deduction guide for string literals:
Wrapper(const char*) -> Wrapper<std::string>;

Wrapper w3{"hello"};  // without guide: Wrapper<const char*>
                       // with guide:    Wrapper<std::string> (preferred)
```

The compiler generates implicit deduction guides from constructors, but explicit guides take priority.

</details>

8. What is the danger of templating a class with a pointer type?

<details>
<summary>Show answer</summary>

**Direct answer:** If `Storage<T>` stores `T m_value`, then `Storage<char*>` stores a pointer not a copy of the data. If the original data changes or is destroyed, the stored pointer dangles. The template silently switches from value semantics to reference semantics for pointer types.

**Detailed explanation:**

```cpp
template <typename T>
class Storage
{
    T m_value;
public:
    Storage(T val) : m_value{val} {}
    T get() const { return m_value; }
};

char name[]{"Alex"};
Storage<char*> s{name};   // stores pointer to name, not a copy
name[0] = 'B';
std::cout << s.get();      // "Blex"  unexpected!

// Fix: partial specialization for pointers
template <typename T>
class Storage<T*>
{
    T* m_value;   // deep copy in constructor
public:
    Storage(T* val) : m_value{new T{*val}} {}
    ~Storage() { delete m_value; }
};
```

Or use `static_assert(!std::is_pointer_v<T>)` to prevent pointer instantiation entirely.

</details>

9. How do you specialize a single member function without rewriting the entire class?

<details>
<summary>Show answer</summary>

**Direct answer:** You can fully specialize individual member functions using `template<>` followed by the specific type. The rest of the class uses the primary template you only override the single function's behavior for that type.

**Detailed explanation:**

```cpp
template <typename T>
class Storage
{
    T m_value;
public:
    Storage(T val) : m_value{val} {}
    void print() const { std::cout << m_value << '\n'; }
};

// Specialize only print() for type double:
template <>
void Storage<double>::print() const
{
    std::cout << std::scientific << m_value << '\n';
}

Storage<int> si{42};
si.print();             // uses primary: "42"

Storage<double> sd{3.14};
sd.print();             // uses specialization: "3.140000e+00"
```

</details>

10. What is the purpose of a class full specialization?

<details>
<summary>Show answer</summary>

**Direct answer:** A class full specialization provides a completely different implementation for a specific type. The specialized class can have different members, different data layout, and different behavior it's essentially a separate class that shares the template name. Example: `Storage8<bool>` packs 8 bools into a single byte instead of using 8 `bool` variables.

**Detailed explanation:**

```cpp
// Primary template
template <typename T>
class Storage8
{
    T m_arr[8];
public:
    void set(int idx, T val) { m_arr[idx] = val; }
    T get(int idx) const { return m_arr[idx]; }
};

// Full specialization for bool  completely different implementation
template <>
class Storage8<bool>
{
    unsigned char m_data{};
public:
    void set(int idx, bool val)
    {
        if (val) m_data |= (1 << idx);
        else     m_data &= ~(1 << idx);
    }
    bool get(int idx) const { return (m_data >> idx) & 1; }
};
```

</details>
