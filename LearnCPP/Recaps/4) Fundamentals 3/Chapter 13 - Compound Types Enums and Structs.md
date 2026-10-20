# Chapter 13 Recap - Compound Types: Enums and Structs

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Prefer **scoped enums** (`enum class`) over unscoped enums for type safety and no naming collisions.
- Give every struct member a **default member initializer** to prevent uninitialized data.
- Pass structs by `const&`; return by value (compiler elides copies).
- Use **designated initializers** (C++20) for readable, self-documenting struct initialization.
- Put program-defined types in header files when shared across translation units.
- Use `->` for pointer member access; it's cleaner than `(*ptr).member`.
- Order struct members largest-to-smallest to minimize padding waste.
- Use class templates for generic structs; put definitions in headers.

### 3 Tiny Examples

1.

```cpp
struct Fraction { int num{}; int den{ 1 }; };  // user-defined type
```

2.

```cpp
enum Color { red, green, blue };
Color c{ green };  // enumerator 'green' is in the enclosing scope
```

3.

```cpp
enum Color { red, green, blue };       // red=0, green=1, blue=2
int i{ green };                         // implicit: i == 1
Color c{ static_cast<Color>(2) };       // explicit: c == blue
```

### 3 Common Mistakes

- Naming collisions with unscoped enums
- Assuming integers implicitly convert to enums
- Forgetting enum values start at 0

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Program-defined type** - a custom type (enum or class/struct) defined by the programmer; must be defined before use.
- **Enumeration (enum)** - a type restricted to a fixed set of named symbolic constants called **enumerators**.
- **Unscoped enumeration** (`enum`) - enumerators are placed into the enclosing scope; implicitly convert to integers.
- **Scoped enumeration** (`enum class`) - enumerators are scoped to the enum; **no** implicit integer conversion.
- **Struct** - a program-defined type bundling multiple **data members** (member variables) into one object.
- **Aggregate** - a struct/class with no user-declared constructors, no private/protected members, and no virtual functions.
- **Aggregate initialization** - initializing struct members via braced initializer list in declaration order.
- **Designated initializers** (C++20) - explicitly naming which members to initialize: `{ .x = 5, .y = 10 }`.
- **Default member initializer** - a default value specified in the struct definition itself.
- **Member selection operator (`.`)** - accesses a member from an object or reference.
- **Arrow operator (`->`)** - accesses a member from a pointer to an object (dereference + member select).
- **Class template** - a template for struct/class types with generic type parameters.
- **CTAD** (C++17) - Class Template Argument Deduction lets the compiler deduce template types from initializers.
- **Deduction guide** - explicit rule telling the compiler how to deduce template arguments from constructor args.

### Section-by-Section Detail

### 13.1 - Introduction to program-defined (user-defined) types

- C++ lets you define **program-defined types** (enums, structs, classes) to model domain concepts that built-in types can't express
- A **type definition** tells the compiler what the type looks like; a **type alias** (`using`, `typedef`) gives an existing type a new name
- Naming convention: program-defined types use **PascalCase** (`Color`, `Fraction`) to distinguish them from variables and functions
- Definitions follow the **one-definition rule** (ODR) - they should live in **header files** so every translation unit sees the same definition

```cpp
struct Fraction { int num{}; int den{ 1 }; };  // user-defined type
```

→ _See [01_UnscopedEnumerations](../solutions/Chapter_13_Enums_And_Structs/01_UnscopedEnumerations/) for basic type definitions._

### 13.2 - Unscoped enumerations

- An **unscoped enumeration** (`enum Color { red, green, blue }`) defines a named type whose values are a fixed set of **named integral constants** (enumerators)
- Enumerators are placed in the **same scope** as the enum itself, so naming collisions with other identifiers are possible
- Each enumerator maps to a consecutive integer starting from `0` by default; you can **manually set** underlying values
- Unscoped enums **implicitly convert** to `int` (useful for array indexing) but `int` does **not** implicitly convert back

```cpp
enum Color { red, green, blue };
Color c{ green };  // enumerator 'green' is in the enclosing scope
```

→ _See [01_UnscopedEnumerations](../solutions/Chapter_13_Enums_And_Structs/01_UnscopedEnumerations/) for naming collision demos._

### 13.3 - Unscoped enumerator integral conversions

- You can `static_cast<int>(color)` to get the integer value; to convert **int** → **enum**, use `static_cast<Color>(i)`; no range check is performed
- `std::cin >>` does not work directly with enums - read an `int`, validate the range, then `static_cast` to the enum type
- `std::cout <<` prints the integer value by default; overload `operator<<` to print the **name** of the enumerator as a string

```cpp
enum Color { red, green, blue };       // red=0, green=1, blue=2
int i{ green };                         // implicit: i == 1
Color c{ static_cast<Color>(2) };       // explicit: c == blue
```

→ _See [02_EnumeratorIntegralConversions](../solutions/Chapter_13_Enums_And_Structs/02_EnumeratorIntegralConversions/) for conversion behavior._

### 13.4 - Converting an enumeration to and from a string

- A **scoped enumeration** (`enum class Color { red, green, blue }`) places enumerators inside the enum's own scope - access via `Color::red`
- Scoped enums **do not** implicitly convert to integers, preventing accidental misuse and type confusion
- Use `static_cast` or (C++23) `std::to_underlying()` for explicit integer conversion
- Scoped enums can be `using enum`'d (C++20) inside a limited scope when repeated qualification is verbose
- **Prefer scoped enums** over unscoped enums for new code

```cpp
constexpr std::string_view toStr(Color c) {
    switch (c) {
    case red:   return "red";
    case green: return "green";
    case blue:  return "blue";
    default:    return "?";
    }
}
```

→ _See [03_EnumToFromString](../solutions/Chapter_13_Enums_And_Structs/03_EnumToFromString/) for string conversion patterns._

### 13.5 - Introduction to overloading the I/O operators

- A **struct** (`struct Fraction { int num{}; int den{}; };`) groups related variables of potentially different types into a single **aggregate**
- Each variable inside the struct is called a **data member** (or field); access members with the **member-selection operator** (`.`)
- Members are **not initialized** by default - always use **default member initializers** (DMIs) (`int num{ 0 };`) or brace initialization
- Structs are commonly defined in **header files** and shared across translation units (ODR-safe because they are type definitions)

```cpp
std::ostream& operator<<(std::ostream& out, Color c) {
    out << toStr(c);
    return out;
}
std::cout << green;  // prints "green"
```

→ _See [04_OverloadingIOOperators](../solutions/Chapter_13_Enums_And_Structs/04_OverloadingIOOperators/) for operator overloading with enums._

### 13.6 - Scoped enumerations (enum classes)

- **Aggregate initialization** uses a brace-enclosed list: `Fraction f{ 1, 2 };` - values are assigned to members **in declaration order**
- Missing initializers are **value-initialized** (zero for fundamental types) if DMIs aren't present, or use the DMI
- **Designated initializers** (C++20) name the members explicitly: `Fraction f{ .num = 1, .den = 2 };` - order must match declaration order
- **Assignment** after construction also uses a brace list: `f = { 3, 4 };`

```cpp
enum class Color { red, green, blue };
Color c{ Color::red };              // must qualify
int i{ static_cast<int>(c) };       // explicit conversion required
```

→ _See [05_ScopedEnumerations](../solutions/Chapter_13_Enums_And_Structs/05_ScopedEnumerations/) for scoped enum patterns._

**Unscoped vs Scoped Enum Comparison:**

| Feature                  | Unscoped (`enum`) | Scoped (`enum class`)     |
| ------------------------ | ----------------- | ------------------------- |
| **Enumerator scope**     | Enclosing scope   | Contained in enum         |
| **Access syntax**        | `red`             | `Color::red`              |
| **Implicit - int**       | Yes               | No (`static_cast` needed) |
| **Naming collisions**    | Possible          | Prevented                 |
| **`using enum` (C++20)** | N/A               | Brings into local scope   |
| **Type safety**          | Weak              | Strong                    |

> **Best practice:** Prefer `enum class` for type safety. Use `using enum` in `switch` blocks to avoid verbose `Color::` prefixes.

### 13.7 - Introduction to structs, members, and member selection

- Structs with all public data and no user-provided constructors should be passed to functions by `const&` for read-only access
- Return structs **by value** - the compiler applies **copy elision** (RVO/NRVO) to avoid the copy
- Functions returning multiple values should return a **struct** (or `std::tuple`) rather than using multiple out parameters
- Use **structured bindings** (C++17, `auto [a, b] = func();`) to unpack returned structs concisely

```cpp
struct Employee { int id{}; std::string name{}; };
Employee e{ 1, "Alice" };
std::cout << e.name;  // "Alice"
```

→ _See [06_StructBasics](../solutions/Chapter_13_Enums_And_Structs/06_StructBasics/) for struct definition and member access._

### 13.8 - Struct aggregate initialization

- **Nested structs** place one struct definition inside another; the inner type is accessed as `Outer::Inner`
- **Size of a struct** - `sizeof(S)` - equals at least the sum of member sizes, but **padding** may be added for alignment
- Members are typically aligned to their size (e.g., `int` aligned to 4 bytes); the struct's total size is padded to a multiple of the **largest member's alignment**
- Sort members **from largest to smallest** to minimize padding waste

```cpp
struct Point { int x{}; int y{}; };
Point p1{ 3, 7 };                // memberwise
Point p2{ .x = 3, .y = 7 };     // designated (C++20)
```

→ _See [07_AggregateInitialization](../solutions/Chapter_13_Enums_And_Structs/07_AggregateInitialization/) and [08_DesignatedInitializers](../solutions/Chapter_13_Enums_And_Structs/08_DesignatedInitializers/)._

### 13.9 - Default member initialization

- Use `const&` when passing structs and classes to functions for read-only access (`void print(const Employee& e)`)
- Returning structs by value is fine - the compiler applies **RVO/NRVO** to elide the copy
- The **member-selection-from-pointer** operator (`->`) dereferences a pointer and selects a member in one step: `ptr->name` instead of `(*ptr).name`

```cpp
struct Config { int width{ 800 }; int height{ 600 }; bool fullscreen{ false }; };
Config c{};          // uses all defaults: 800, 600, false
Config c2{ 1920 };   // width=1920, rest default
```

→ _See [09_DefaultMemberInitializers](../solutions/Chapter_13_Enums_And_Structs/09_DefaultMemberInitializers/) for default value patterns._

**Struct Initialization Methods:**

| Method                  | Syntax                   | Order matters?          | Self-documenting? | Since |
| ----------------------- | ------------------------ | ----------------------- | ----------------- | ----- |
| **Aggregate init**      | `Point p{ 3, 7 }`        | Yes (declaration order) | No                | C++11 |
| **Designated init**     | `Point p{ .x=3, .y=7 }`  | Yes (declaration order) | Yes               | C++20 |
| **Default member init** | `struct P { int x{0}; }` | N/A (in definition)     | Yes               | C++11 |
| **Value init**          | `Point p{}`              | N/A (all defaults)      | N/A               | C++11 |

> **Priority:** Explicit initializer values override default member initializers. Missing values use the default member initializer, or value-initialize (zero) if none exists.

### 13.10 - Passing and returning structs

- **Class templates** (`template <typename T> struct Pair { T first; T second; };`) let you write a single struct definition that works with **any type**
- The compiler generates a **concrete specialization** (e.g., `Pair<int>`, `Pair<std::string>`) for each distinct type used
- Templates must be defined in **header files** because the compiler needs the full definition at every point of instantiation
- Use multiple template parameters (`template <typename T, typename U>`) when members need **different types**

```cpp
void print(const Point& p) { std::cout << p.x << ',' << p.y; }
Point midpoint(const Point& a, const Point& b) {
    return { (a.x + b.x) / 2, (a.y + b.y) / 2 };
}
```

→ _See [10_PassingReturningStructs](../solutions/Chapter_13_Enums_And_Structs/10_PassingReturningStructs/) for parameter and return patterns._

**Struct Passing and Returning Conventions:**

| Direction          | Method        | Syntax                   | Notes                                |
| ------------------ | ------------- | ------------------------ | ------------------------------------ |
| **In (read-only)** | `const&`      | `void f(const Point& p)` | No copy - preferred                  |
| **In (modify)**    | Non-const `&` | `void f(Point& p)`       | Modifies original                    |
| **Out (return)**   | By value      | `Point f()`              | Copy elision (C++17 guaranteed NRVO) |
| **Temporary arg**  | Brace init    | `f({ 3, 7 })`            | Anonymous struct at call site        |

### 13.11 - Struct miscellany

- **Class Template Argument Deduction (CTAD)** (C++17) lets the compiler deduce template arguments from the initializer: `Pair p{ 1, 2 };` instead of `Pair<int> p{ 1, 2 };`
- CTAD only works when **all** template parameters can be deduced; partial deduction requires explicit specification
- **Deduction guides** teach the compiler how to map constructor arguments to template parameters - needed for types where deduction is ambiguous
- Non-type template parameters (`template <int N>`) use **constant values** instead of types - useful for fixed-size arrays and compile-time configuration

```cpp
struct Address { std::string city{}; int zip{}; };
struct Employee { std::string name{}; Address addr{}; };
Employee e{ "Bob", { "NYC", 10001 } };  // nested braces
```

→ _See [11_StructMiscellany](../solutions/Chapter_13_Enums_And_Structs/11_StructMiscellany/) for nested structs and padding demo._

### 13.12 - Member selection with pointers and references

- **Type aliases** with `using` create readable names for complex types: `using Pair_ii = Pair<int, int>;`
- **Alias templates** extend this to templates themselves: `template <typename T> using Coord = Pair<T, T>;` - allows `Coord<double>` instead of `Pair<double, double>`
- Aliases improve readability, reduce repetition, and centralize type changes
- `using` is preferred over `typedef` in modern C++

```cpp
Employee e{ 1, "Alice" };
Employee* ptr{ &e };
std::cout << ptr->name;  // cleaner than (*ptr).name
```

→ _See [12_MemberSelectionWithPointers](../solutions/Chapter_13_Enums_And_Structs/12_MemberSelectionWithPointers/) for `.` vs `->` examples._

### 13.13 - Class templates

- A `struct` can have **member functions** (methods) defined inside the struct body - they can access all data members directly
- The **implicit object** is the instance the method is called on (`p.print()` - `p` is the implicit object)
- Member functions declared inside the struct are **implicitly inline**, so defining them in a header is ODR-safe
- This section bridges structs toward **classes** - the only difference is the **default access level** (`public` for structs, `private` for classes)

```cpp
template <typename T>
struct Pair { T first{}; T second{}; };
Pair<int> p{ 1, 2 };
Pair<double> d{ 3.14, 2.72 };
```

→ _See [13_ClassTemplates](../solutions/Chapter_13_Enums_And_Structs/13_ClassTemplates/) for template struct usage._

### 13.14 - Class template argument deduction (CTAD) and deduction guides

- `static` **member variables** are shared by all instances of a structure - they have `static` storage duration and exist for the lifetime of the program
- Declare `static` members inside the struct body; define and initialize them **outside** in a `.cpp` file (or use `inline static` in C++17)
- `static` **member functions** can access only `static` members - they have **no implicit object**
- Call via the class name: `MyStruct::getCount()`; useful for **factory functions**, counters, and singleton patterns

```cpp
Pair p{ 1, 2 };          // CTAD deduces Pair<int>
std::pair sp{ 1, 3.14 }; // std::pair<int, double>
```

→ _See [14_CTADAndDeductionGuides](../solutions/Chapter_13_Enums_And_Structs/14_CTADAndDeductionGuides/) for CTAD and custom deduction guide examples._

### Edge Cases and Caveats

- **Naming collisions with unscoped enums** - enumerators share the enclosing scope.

  ❌ **Bad:** `enum Color { red }; enum Light { red };` - redefinition.
  ✅ **Good:** Use `enum class Color { red };` (scoped enum).

- **Assuming integers implicitly convert to enums** - they don't.

  ❌ **Bad:** `Color c{ 2 };` - error.
  ✅ **Good:** `Color c{ static_cast<Color>(2) };`

- **Forgetting enum values start at 0** -

  ❌ **Bad:** Assuming the first enumerator is 1.
  ✅ **Good:** First value is 0 unless explicitly set.

- **Missing default member initializers** - leaves members uninitialized.

  ❌ **Bad:** `struct S { int x; }; S s;` - `x` is garbage.
  ✅ **Good:** `struct S { int x{}; };` or `S s{};`

- **Passing structs by value** - expensive copy.

  ❌ **Bad:** `void print(Employee e);`
  ✅ **Good:** `void print(const Employee& e);`

- **`std::string_view` as a data member** - doesn't own the data.

  ❌ **Bad:** `struct S { std::string_view name; };` - may dangle.
  ✅ **Good:** `struct S { std::string name; };` for owned strings.

- **Padding bloating struct size** - poor member ordering wastes bytes.

  ❌ **Bad:** `struct { char a; int b; char c; };` - 12 bytes.
  ✅ **Good:** `struct { int b; char a; char c; };` - 8 bytes.

- **CTAD type mismatch** - template deduction fails.

  ❌ **Bad:** `Pair p{ 1, 2.0 };` with `template<typename T> struct Pair { T a; T b; };`
  ✅ **Good:** Use explicit `Pair<double>{ 1, 2.0 }` or add a deduction guide.

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_13_Enums_And_Structs/
```

| Project                                                                                                         | Concept                                                 |
| --------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------- |
| [01_UnscopedEnumerations](../solutions/Chapter_13_Enums_And_Structs/01_UnscopedEnumerations/)                   | Unscoped enums, enumerator values, naming collisions    |
| [02_EnumeratorIntegralConversions](../solutions/Chapter_13_Enums_And_Structs/02_EnumeratorIntegralConversions/) | Implicit int conversion, `static_cast`, explicit values |
| [03_EnumToFromString](../solutions/Chapter_13_Enums_And_Structs/03_EnumToFromString/)                           | Converting enumerators to/from strings with switch      |
| [04_OverloadingIOOperators](../solutions/Chapter_13_Enums_And_Structs/04_OverloadingIOOperators/)               | Overloading `<<` and `>>` for enums                     |
| [05_ScopedEnumerations](../solutions/Chapter_13_Enums_And_Structs/05_ScopedEnumerations/)                       | `enum class`, type safety, `using enum` (C++20)         |
| [06_StructBasics](../solutions/Chapter_13_Enums_And_Structs/06_StructBasics/)                                   | Struct definition, members, `.` operator                |
| [07_AggregateInitialization](../solutions/Chapter_13_Enums_And_Structs/07_AggregateInitialization/)             | Braced init lists, memberwise initialization            |
| [08_DesignatedInitializers](../solutions/Chapter_13_Enums_And_Structs/08_DesignatedInitializers/)               | C++20 designated initializers (`.member = value`)       |
| [09_DefaultMemberInitializers](../solutions/Chapter_13_Enums_And_Structs/09_DefaultMemberInitializers/)         | Default values in struct definitions                    |
| [10_PassingReturningStructs](../solutions/Chapter_13_Enums_And_Structs/10_PassingReturningStructs/)             | Pass by const ref, return by value, temporaries         |
| [11_StructMiscellany](../solutions/Chapter_13_Enums_And_Structs/11_StructMiscellany/)                           | Nested structs, ownership, padding/alignment            |
| [12_MemberSelectionWithPointers](../solutions/Chapter_13_Enums_And_Structs/12_MemberSelectionWithPointers/)     | `.` vs `->`, pointer member access                      |
| [13_ClassTemplates](../solutions/Chapter_13_Enums_And_Structs/13_ClassTemplates/)                               | `template <typename T> struct`, `std::pair`             |
| [14_CTADAndDeductionGuides](../solutions/Chapter_13_Enums_And_Structs/14_CTADAndDeductionGuides/)               | CTAD and deduction guides                               |

### Quick Reference

| Feature              | Syntax                                          | Notes                                              |
| -------------------- | ----------------------------------------------- | -------------------------------------------------- |
| Unscoped enum        | `enum Color { red, green, blue };`              | Values in enclosing scope; implicit int conversion |
| Scoped enum          | `enum class Color { red, green, blue };`        | Scoped; no implicit conversion                     |
| Enum value access    | `Color::red` (scoped) / `red` (unscoped)        | Scoped requires prefix                             |
| Explicit underlying  | `enum Color : uint8_t { ... };`                 | Specify storage type                               |
| `using enum`         | `using enum Color;` (C++20, inside switch)      | Removes prefix need                                |
| `std::to_underlying` | `std::to_underlying(e)` (C++23)                 | Enum → integer safely                              |
| Struct definition    | `struct Point { int x; int y; };`               | Members public by default                          |
| Aggregate init       | `Point p{ 1, 2 };`                              | Memberwise, in order                               |
| Designated init      | `Point p{ .x=1, .y=2 };` (C++20)                | Named members                                      |
| Default member init  | `struct S { int x{ 0 }; };`                     | Default if not overridden                          |
| Member select        | `obj.member` / `ptr->member`                    | `.` for objects, `->` for ptrs                     |
| Class template       | `template <typename T> struct Box { T val; };`  | In header files                                    |
| CTAD                 | `Box b{ 42 };` → `Box<int>` (C++17)             | Auto-deduces template args                         |
| `operator<<`         | `std::ostream& operator<<(std::ostream&, Type)` | Return stream for chaining                         |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between an **unscoped** and a **scoped** enum?

<details>
<summary>Show answer</summary>

**Direct answer:** An unscoped enum (`enum Color { red, green, blue }`) places its enumerators into the surrounding scope, so you access them directly as `red`. A scoped enum (`enum class Color { red, green, blue }`) contains enumerators within its own scope, requiring `Color::red`. Scoped enums also block implicit conversion to integers, providing stronger type safety.

**Detailed explanation:**
Unscoped enums can cause naming collisions when two enums in the same scope share enumerator names. Scoped enums prevent this and prevent accidental arithmetic on enum values. Use `static_cast<int>(c)` or `std::to_underlying(c)` (C++23) to get the integer from a scoped enum. C++20 `using enum Color;` can be used inside a `switch` block to avoid the `Color::` prefix locally.

```cpp
enum Color { red, green, blue };        // unscoped - red is in global scope
enum class Fruit { apple, banana };     // scoped - must use Fruit::apple

int i{ red };                // OK: unscoped implicitly converts to int
// int j{ Fruit::apple };   // ERROR: scoped enum won't convert
int k{ static_cast<int>(Fruit::apple) }; // OK: explicit cast
```

</details>

2. Why does C++ not allow implicit conversion from integers to enums?

<details>
<summary>Show answer</summary>

**Direct answer:** Not every integer value corresponds to a valid enumerator. Allowing implicit conversion would let nonsensical values like `42` silently become a `Color`, defeating the purpose of using named constants. You must use `static_cast<Color>(2)` to convert explicitly, documenting that you've verified the value is meaningful.

**Detailed explanation:**
Enumerators implicitly convert _to_ integers (for unscoped enums) because every enumerator maps to a specific integer, so the conversion is always valid. The reverse is not true - many integers have no corresponding enumerator. By requiring an explicit cast, C++ forces the programmer to acknowledge the potential for invalid values. Best practice: make the enumerator with value `0` represent a default or "unknown" state, since value-initialization (`Color c{};`) yields `0`.

</details>

3. What is an **aggregate** in C++? How is aggregate initialization different from value initialization?

<details>
<summary>Show answer</summary>

**Direct answer:** An aggregate is a struct (or array) without user-provided constructors, private/protected members, or virtual functions. Aggregate initialization uses a brace-enclosed list where values are assigned to members in declaration order: `Employee e{ 1, "Alice" }`. Value initialization (`Config c{}`) zero-initializes members that lack default member initializers; aggregate initialization assigns specific values to specific members.

**Detailed explanation:**
If fewer initializers are provided than members, remaining members use their default member initializers (if defined) or are value-initialized. C++20 designated initializers (`Employee e{ .id = 1, .name = "Alice" }`) name each member explicitly for clarity and must appear in declaration order.

```cpp
struct Config
{
    int width{ 800 };     // default member initializer
    int height{ 600 };
};

Config a{};              // value init: width=800, height=600 (defaults used)
Config b{ 1920 };        // aggregate init: width=1920, height=600 (default kept)
Config c{ 1920, 1080 };  // aggregate init: both specified
```

</details>

4. What are **designated initializers** (C++20), and why are they useful?

<details>
<summary>Show answer</summary>

**Direct answer:** Designated initializers let you name each member explicitly during aggregate initialization: `Point p{ .x = 3, .y = 4 }`. They are more readable, self-documenting (you see which value goes to which member), and less error-prone when structs have many members or when members are reordered.

**Detailed explanation:**
Designators must appear in the same order as the members are declared in the struct. Any undesignated members use their default member initializers or are value-initialized. Designated initializers are especially valuable for structs with many same-type members where positional initialization is ambiguous.

```cpp
struct Rect { int x{}; int y{}; int width{}; int height{}; };

Rect r{ .x = 10, .width = 200, .height = 100 };
// y uses default (0), x=10, width=200, height=100
```

</details>

5. Why should structs always have **default member initializers**?

<details>
<summary>Show answer</summary>

**Direct answer:** Default member initializers prevent uninitialized members, which would contain garbage values for fundamental types. They also serve as documentation, showing the "normal" state of the struct. When value-initialized (`Config c{}`) or when an aggregate initializer omits a member, the default is used automatically.

**Detailed explanation:**
Without defaults, `Config c;` (default-initialization) leaves fundamental-type members uninitialized. With defaults, even this case is safe. Always prefer `Config c{}` (value-initialization) over `Config c;` for extra safety.

```cpp
struct Config
{
    int width{ 800 };        // always has a safe default
    int height{ 600 };
    bool fullscreen{ false };
};

Config c;    // default-init: members use default member initializers (safe)
Config d{};  // value-init: same result, more explicit (preferred)
```

</details>

6. Why is `std::string_view` dangerous as a **data member**?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::string_view` is non-owning - it points to memory owned by someone else. If the owning string is destroyed or goes out of scope while the struct still holds the view, the view becomes a dangling pointer. Struct data members should use owning types like `std::string` to ensure the data lives as long as the struct.

**Detailed explanation:**

```cpp
struct Person
{
    std::string_view name;  // DANGEROUS - who owns the string?
};

Person createPerson()
{
    std::string s{ "Alice" };
    return Person{ s };  // s destroyed at function exit - name dangles!
}
// Use std::string name; instead for safety
```

</details>

7. How does **struct padding** work, and how do you minimize it?

<details>
<summary>Show answer</summary>

**Direct answer:** The compiler inserts padding bytes between struct members to satisfy alignment requirements (e.g., a 4-byte `int` must start at a 4-byte boundary). This means `sizeof(struct)` may exceed the sum of `sizeof` of each member. Minimize padding by ordering members from largest alignment to smallest.

**Detailed explanation:**

```cpp
// BAD order - 12 bytes (with padding):
struct Bad { char a; int b; char c; };
// Layout: [a][pad][pad][pad][b b b b][c][pad][pad][pad] = 12 bytes

// GOOD order - 8 bytes (minimal padding):
struct Good { int b; char a; char c; };
// Layout: [b b b b][a][c][pad][pad] = 8 bytes
```

</details>

8. What is **CTAD**, and when do you need an explicit deduction guide?

<details>
<summary>Show answer</summary>

**Direct answer:** CTAD (Class Template Argument Deduction, C++17) lets the compiler deduce template arguments from initializer types, so you can write `Pair p{ 1, 2 }` instead of `Pair<int> p{ 1, 2 }`. An explicit deduction guide is needed when the compiler can't infer the types - e.g., when the constructor takes `std::initializer_list` or when template parameters don't appear directly in the constructor signature.

**Detailed explanation:**
For aggregates, the compiler generates implicit deduction guides from the member types. For non-aggregate classes, guides come from constructors. You can write custom guides:

```cpp
template <typename T>
struct Pair { T first; T second; };

Pair p{ 1, 2 };  // CTAD: deduces Pair<int>

// Custom deduction guide example:
template <typename T>
Pair(T, T) -> Pair<T>;
```

</details>

9. What is a **class template**, and how does it differ from a function template?

<details>
<summary>Show answer</summary>

**Direct answer:** A class template is a blueprint for a struct/class with one or more type parameters (e.g., `template <typename T> struct Pair { T first; T second; }`). Like function templates, the compiler generates a concrete class for each set of types used. Class templates must be defined in headers. The key difference: function templates can use argument deduction automatically; class templates required explicit types before CTAD (C++17).

**Detailed explanation:**
The standard library provides `std::pair<T, U>` and `std::tuple<T...>` so you rarely need custom pair/tuple types. Class templates can have multiple template parameters for heterogeneous types and can use NTTPs for compile-time constants.

</details>

10. What is the difference between `struct` and `class` in C++?

<details>
<summary>Show answer</summary>

**Direct answer:** In C++, `struct` and `class` are nearly identical. The only difference is default access: `struct` members are `public` by default, while `class` members are `private` by default. Convention: use `struct` for plain data aggregates and `class` for types with invariants, private data, and member functions.

**Detailed explanation:**
Both support constructors, destructors, member functions, inheritance, and templates. The choice between them is purely conventional - the compiler treats them the same except for the default access level.

</details>
