# Chapter 22 Recap - Move Semantics and Smart Pointers

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- **Use smart pointers, not raw `new`/`delete`** - they prevent leaks and dangling pointers automatically.
- `std::unique_ptr` for default single ownership; `std::shared_ptr` only when you need shared ownership.
- Always use `std::make_unique` / `std::make_shared` - safer and more performant.
- Mark move constructors/assignment `noexcept` - required for STL container optimizations.
- Leave moved-from objects in a valid state; never read their value.
- Use `std::weak_ptr` to break circular `shared_ptr` references.
- Never allocate smart pointers on the heap - use them as stack/member variables.
- Pass `get()` (the raw pointer) to functions that don't need ownership.

### 3 Tiny Examples

1.

```cpp
void riskyFunction() {
    int* ptr{new int{42}};
    if (errorCondition) return; // leak! ptr never deleted
    delete ptr;
}
// Smart pointer version - no leak possible
void safeFunction() {
    auto ptr{ std::make_unique<int>(42) };
    if (errorCondition) return; // destructor deletes automatically
}
```

2.

```cpp
int&& rref{5};          // r-value reference to temporary
void fn(int& x)  {}     // called for l-values
void fn(int&& x) {}     // called for r-values
fn(rref);               // calls fn(int&) - rref is a named l-value!
fn(std::move(rref));    // calls fn(int&&)
```

3.

```cpp
MyArray::MyArray(MyArray&& src) noexcept
    : m_data{src.m_data}, m_size{src.m_size} {
    src.m_data = nullptr;  // null out source
    src.m_size = 0;
}
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Smart pointer** - a class wrapping a raw pointer that automatically `delete`s the resource when it goes out of scope (RAII).
- **R-value reference (`&&`)** - binds only to r-values (temporaries); enables move semantics.
- **`std::move`** - casts an l-value to an r-value reference so move semantics can be invoked.
- **Move constructor / move assignment** - transfer resources from the source (shallow copy + null source); should be `noexcept`.
- **`std::unique_ptr<T>`** - sole-ownership smart pointer; non-copyable, movable. Use `std::make_unique<T>(args)`.
- **`std::shared_ptr<T>`** - shared ownership via reference counting; freed when last owner is destroyed. Use `std::make_shared<T>(args)`.
- **`std::weak_ptr<T>`** - non-owning observer of a `shared_ptr`-managed resource; breaks circular references.
- **Circular reference** - `shared_ptr`s in a cycle prevent deallocation; use `weak_ptr` for back-references.
- **Rule of Five** - if you define/delete any of: copy ctor, copy assign, move ctor, move assign, destructor → define/delete all five.

### Section-by-Section Detail

### 22.1 - Introduction to smart pointers and move semantics

- Raw pointers easily **leak memory** if a function exits early (via return, exception, or error branch) before `delete` is reached
- A **smart pointer** wraps a raw pointer and automatically deletes it in its destructor - applying **RAII** to heap memory
- Naive copy-based smart pointers cause **double-delete** → motivating **move semantics** (transferring ownership instead of copying)
- `std::auto_ptr` (C++98) used copy semantics to fake moves → surprising behavior; **deprecated** in C++11, removed in C++17
- Modern C++ provides `std::unique_ptr` and `std::shared_ptr` as safe, well-designed replacements

```cpp
void riskyFunction() {
    int* ptr{new int{42}};
    if (errorCondition) return; // leak! ptr never deleted
    delete ptr;
}
// Smart pointer version - no leak possible
void safeFunction() {
    auto ptr{ std::make_unique<int>(42) };
    if (errorCondition) return; // destructor deletes automatically
}
```

→ _See [01_SmartPointerMotivation](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/01_SmartPointerMotivation/) for the RAII motivation._

### 22.2 - R-value references

- `int&& rref = 5;` binds to an **r-value** - a temporary or expression with no persistent address
- R-value references **extend the lifetime** of temporaries to match the reference's scope
- A **named** r-value reference variable is itself an **l-value** expression - passing it requires `std::move` to re-cast as an r-value
- R-value reference parameters enable function overloads that distinguish **l-value from r-value** arguments → foundation of move semantics
- L-value references (`&`) bind to l-values; r-value references (`&&`) bind to r-values - this overload resolution decides whether to **copy or move**

```cpp
int&& rref{5};          // r-value reference to temporary
void fn(int& x)  {}     // called for l-values
void fn(int&& x) {}     // called for r-values
fn(rref);               // calls fn(int&) - rref is a named l-value!
fn(std::move(rref));    // calls fn(int&&)
```

→ _See [02_RvalueReferences](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/02_RvalueReferences/) for binding rules._

**Reference Binding Rules:**

| Expression Type      | `T&` (lvalue ref)       | `const T&` | `T&&` (rvalue ref) |
| -------------------- | ----------------------- | ---------- | ------------------ |
| Named variable (`x`) | Binds                   | Binds      | No                 |
| `const` variable     | No                      | Binds      | No                 |
| Temporary (`T{5}`)   | No                      | Binds      | Binds              |
| `std::move(x)`       | No                      | Binds      | Binds              |
| Named `T&& rr`       | Binds (it's an lvalue!) | Binds      | No                 |

### 22.3 - Move constructors and move assignment

- **Move constructors** (`Foo(Foo&& src) noexcept`) and **move assignment operators** transfer resources via shallow copy + null out source
- Called when the argument is an **r-value** - temporaries or `std::move`-cast objects
- The compiler generates **implicit move operations** only if no copy ctor, copy assign, move ops, or destructor are user-declared
- Always leave the **moved-from object** in a valid state - mark move operations `noexcept` or STL containers may fall back to copying

```cpp
MyArray::MyArray(MyArray&& src) noexcept
    : m_data{src.m_data}, m_size{src.m_size} {
    src.m_data = nullptr;  // null out source
    src.m_size = 0;
}
```

→ _See [03_MoveConstructor](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/03_MoveConstructor/) and [04_MoveAssignment](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/04_MoveAssignment/)._

**Rule of Zero / Three / Five:**

| Rule              | When                                     | You Define                                      | Example                                     |
| ----------------- | ---------------------------------------- | ----------------------------------------------- | ------------------------------------------- |
| **Rule of Zero**  | Class has only RAII/value members        | None of the 5                                   | Class with `string`, `vector`, `unique_ptr` |
| **Rule of Three** | Class manages a raw resource (pre-C++11) | Destructor + copy ctor + copy assign            | Class with `new[]` in ctor                  |
| **Rule of Five**  | Class manages a raw resource (C++11+)    | All 5: dtor + copy/move ctor + copy/move assign | Class with `new[]` + move optimization      |

### 22.4 - std::move

- `std::move(x)` (from `<utility>`) is a **cast** that converts `x` to an r-value reference - it does not move anything by itself
- The actual resource transfer happens when the r-value reference is passed to a **move constructor** or **move assignment operator**
- Useful for **swaps**, filling containers with `push_back`, and explicitly transferring ownership of `std::unique_ptr`
- After `std::move`, the moved-from object is in a **valid but indeterminate** state - don't read its value without first reassigning
- You can safely call **no-precondition** member functions (`empty()`, `size()`, destructor) on moved-from objects

```cpp
std::string a{"hello"};
std::string b{std::move(a)};  // a is moved-from (valid but empty)
std::cout << b;               // "hello"
// a.empty() is safe to call; a's value is indeterminate
```

→ _See [05_StdMove](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/05_StdMove/) for explicit move examples._

### 22.5 - std::unique_ptr

- `std::unique_ptr` is the go-to smart pointer for **single-owner** resources - copy is disabled, move is supported
- Create with `std::make_unique<T>(args)` (C++14) - safer and avoids separate `new` calls
- Access the raw pointer with `get()` - pass it to functions that **don't need ownership**
- Return `std::unique_ptr` **by value** from factory functions - never construct two `unique_ptr`s from the same raw pointer

```cpp
auto ptr{ std::make_unique<int>(42) };
std::cout << *ptr;                       // 42
auto ptr2{ std::move(ptr) };             // ownership transferred
// ptr is now nullptr
```

→ _See [07_UniquePtr](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/07_UniquePtr/) for sole-ownership patterns._

### 22.6 - std::shared_ptr

- Multiple `shared_ptr`s co-own a resource via **reference counting** - freed when the count reaches zero
- Create with `std::make_shared<T>(args)` - performs a **single allocation** for both object and control block (more efficient)
- Always create additional `shared_ptr`s by **copying** an existing one - constructing independently from the same raw pointer → double-delete
- A `unique_ptr` can convert to a `shared_ptr` - but the reverse is **not allowed** since shared ownership can't be narrowed
- Prefer `unique_ptr` by default - use `shared_ptr` only when ownership **genuinely needs to be shared**

```cpp
auto sp1{ std::make_shared<int>(99) };
auto sp2{ sp1 };  // ref count: 2
sp1.reset();      // ref count: 1 - resource still alive
sp2.reset();      // ref count: 0 - resource freed
```

→ _See [08_SharedPtr](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/08_SharedPtr/) for shared ownership._

### 22.7 - Circular dependency issues with std::shared_ptr, and std::weak_ptr

- When `shared_ptr`s form a **cycle** (A→ B, B→ A) - neither is ever freed (memory leak)
- `std::weak_ptr` breaks cycles by **observing** without contributing to the reference count
- Access the resource via `lock()` - returns a `shared_ptr` if the target is alive, or empty if destroyed
- Check with `expired()` - unlike raw pointers, `weak_ptr` can **safely detect** when its target is destroyed

```cpp
auto sp{ std::make_shared<int>(42) };
std::weak_ptr<int> wp{ sp };  // observes, ref count stays 1
if (auto locked = wp.lock())  // get shared_ptr if alive
    std::cout << *locked;     // 42
sp.reset();                   // resource freed
std::cout << wp.expired();    // true
```

→ _See [09_WeakPtr](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/09_WeakPtr/) and [10_CircularReferenceProblem](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/10_CircularReferenceProblem/) for cycle-breaking._

**Smart Pointer Comparison:**

| Property      | `unique_ptr`                | `shared_ptr`                | `weak_ptr`                  |
| ------------- | --------------------------- | --------------------------- | --------------------------- |
| **Ownership** | Exclusive (sole)            | Shared (ref-counted)        | None (observer)             |
| **Copyable?** | No                          | Yes (increments count)      | Yes                         |
| **Movable?**  | Yes                         | Yes                         | Yes                         |
| **Overhead**  | Zero (no control block)     | Control block + ref count   | Uses existing control block |
| **Creation**  | `std::make_unique<T>(args)` | `std::make_shared<T>(args)` | From `shared_ptr`           |
| **Use case**  | Default choice              | Multiple owners needed      | Break circular refs         |

### Edge Cases and Caveats

❌ Two `shared_ptr`s from the same raw pointer:

```cpp
int* raw = new int{5};
std::shared_ptr<int> a{raw};
std::shared_ptr<int> b{raw}; // ❌ independent ref counts → double-delete
```

✅ Create one `shared_ptr` and copy it:

```cpp
auto a = std::make_shared<int>(5);
auto b = a; // ✅ shared ownership, single ref count
```

---

❌ Forgetting to null the source in move operations:

```cpp
Foo(Foo&& other) : m_ptr{other.m_ptr} {} // ❌ other.m_ptr still points to resource
// other's destructor will delete it → dangling
```

✅ Null the source:

```cpp
Foo(Foo&& other) : m_ptr{other.m_ptr} { other.m_ptr = nullptr; } // ✅
```

---

❌ Reading a moved-from object's value:

```cpp
std::string a{"hello"};
std::string b{std::move(a)};
std::cout << a; // ❌ valid but indeterminate - unreliable
```

✅ Don't rely on moved-from state; reset or discard the object.

---

❌ Circular `shared_ptr` references:

```cpp
struct Node { std::shared_ptr<Node> next; };
auto a = std::make_shared<Node>();
auto b = std::make_shared<Node>();
a->next = b; b->next = a; // ❌ circular → memory leak
```

✅ Use `std::weak_ptr` for back-references.

---

❌ Passing `unique_ptr` by value without `std::move`:

```cpp
void take(std::unique_ptr<int> p) {}
auto up = std::make_unique<int>(5);
take(up); // ❌ doesn't compile - copy is deleted
```

✅ Move it:

```cpp
take(std::move(up)); // ✅
```

---

❌ Manually deleting a smart-pointer-managed resource:

```cpp
auto sp = std::make_shared<int>(5);
delete sp.get(); // ❌ double-delete when sp goes out of scope
```

✅ Never manually delete a smart-pointer-managed resource.

---

❌ Using `std::swap` in move ctor/assign:

```cpp
Foo(Foo&& other) { std::swap(m_ptr, other.m_ptr); } // ❌ swap calls move → infinite recursion
```

✅ Use direct member-wise moves or a manual swap.

---

❌ Deleting only the move ctor while keeping copy:

```cpp
Foo(Foo&&) = delete; // ❌ blocks return-by-value even though copy exists
```

✅ Deleted move still participates in overload resolution. Don't delete just the move ctor.

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_22_Move_Semantics_Smart_Pointers/
```

| Project                                                                                                                 | Concept                                                     |
| ----------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------- |
| [01_SmartPointerMotivation](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/01_SmartPointerMotivation/)           | Why raw pointers leak and how RAII smart pointers fix it    |
| [02_RvalueReferences](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/02_RvalueReferences/)                       | R-value references (`&&`), binding rules, and overloading   |
| [03_MoveConstructor](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/03_MoveConstructor/)                         | Writing a move constructor that transfers ownership         |
| [04_MoveAssignment](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/04_MoveAssignment/)                           | Writing a move assignment operator                          |
| [05_StdMove](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/05_StdMove/)                                         | Using `std::move` to invoke move semantics on l-values      |
| [06_RuleOfFive](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/06_RuleOfFive/)                                   | Defining all five special member functions correctly        |
| [07_UniquePtr](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/07_UniquePtr/)                                     | `std::unique_ptr` - sole ownership smart pointer            |
| [08_SharedPtr](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/08_SharedPtr/)                                     | `std::shared_ptr` - shared ownership via reference counting |
| [09_WeakPtr](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/09_WeakPtr/)                                         | `std::weak_ptr` - non-owning observer, breaking cycles      |
| [10_CircularReferenceProblem](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/10_CircularReferenceProblem/)       | Demonstrating and solving circular `shared_ptr` references  |
| [11_MoveSemanticsWithContainers](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/11_MoveSemanticsWithContainers/) | Move semantics with STL containers and `noexcept`           |
| [12_CommonPitfalls](../solutions/Chapter_22_Move_Semantics_Smart_Pointers/12_CommonPitfalls/)                           | Double-delete, moved-from access, and other pitfalls        |

### Quick Reference

| Feature      | Syntax                                | Notes                        |
| ------------ | ------------------------------------- | ---------------------------- |
| R-value ref  | `int&& rr = 5;`                       | Binds to r-values only       |
| `std::move`  | `auto y = std::move(x);`              | Casts l-value → r-value ref  |
| Move ctor    | `Foo(Foo&& src) noexcept;`            | Transfer resources           |
| Move assign  | `Foo& operator=(Foo&& src) noexcept;` | Transfer + cleanup           |
| `unique_ptr` | `auto p = std::make_unique<T>(args);` | Sole ownership               |
| `shared_ptr` | `auto p = std::make_shared<T>(args);` | Ref-counted shared ownership |
| `weak_ptr`   | `std::weak_ptr<T> wp = sp;`           | Non-owning observer          |
| `lock()`     | `auto sp2 = wp.lock();`               | Get shared_ptr from weak     |
| `expired()`  | `wp.expired()`                        | Check if target is alive     |
| `get()`      | `p.get()`                             | Raw pointer (no ownership)   |
| `reset()`    | `p.reset();`                          | Release ownership            |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between `std::unique_ptr` and `std::shared_ptr`?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::unique_ptr` has exclusive ownership only one `unique_ptr` can own a resource at a time (non-copyable, only movable). `std::shared_ptr` allows multiple pointers to co-own a resource via reference counting the resource is freed when the last `shared_ptr` is destroyed.

**Detailed explanation:**

```cpp
// unique_ptr: single owner
auto up = std::make_unique<int>(42);
// auto up2 = up;                   // ERROR: can't copy
auto up2 = std::move(up);           // OK: transfers ownership

// shared_ptr: shared ownership
auto sp1 = std::make_shared<int>(42);
auto sp2 = sp1;                      // OK: ref count = 2
// resource freed when both sp1 and sp2 are destroyed
```

Use `unique_ptr` by default (zero overhead). Use `shared_ptr` only when multiple owners genuinely need the resource.

</details>

2. What problem does `std::weak_ptr` solve?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::weak_ptr` breaks circular references between `shared_ptr`s. If A holds a `shared_ptr` to B and B holds one back to A, neither is ever freed (reference counts never reach zero). Replacing one with `weak_ptr` breaks the cycle because `weak_ptr` doesn't increment the reference count.

**Detailed explanation:**

```cpp
struct B;
struct A { std::shared_ptr<B> b_ptr; };
struct B { std::weak_ptr<A> a_ptr; };    // weak, not shared  breaks cycle

auto a = std::make_shared<A>();
auto b = std::make_shared<B>();
a->b_ptr = b;
b->a_ptr = a;     // weak_ptr doesn't increase ref count

// Access weak_ptr safely:
if (auto locked = b->a_ptr.lock())   // returns shared_ptr or nullptr
    std::cout << "A still alive";
```

Use `expired()` to check if the target has been destroyed without locking.

</details>

3. Why must you null the source pointer in a move constructor?

<details>
<summary>Show answer</summary>

**Direct answer:** After stealing the source's resource pointer, you must set the source's pointer to `nullptr`. Otherwise, when the source's destructor runs, it will `delete` the resource that the new object now owns causing a dangling pointer / double-delete.

**Detailed explanation:**

```cpp
class DynArray
{
    int* m_data{};
    int m_size{};
public:
    // Move constructor
    DynArray(DynArray&& src) noexcept
        : m_data{src.m_data}     // steal the pointer
        , m_size{src.m_size}
    {
        src.m_data = nullptr;    // CRITICAL: null the source
        src.m_size = 0;
    }

    ~DynArray() { delete[] m_data; }  // safe: delete nullptr is a no-op
};
```

Mark move operations `noexcept` STL containers like `std::vector` fall back to copying in `resize()` if the move constructor can throw.

</details>

4. What does `std::move` actually do?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::move` is just a cast it converts its argument to an rvalue reference (`T&&`). It does not move anything by itself. The actual resource transfer happens when the rvalue reference is passed to a move constructor or move assignment operator.

**Detailed explanation:**

```cpp
std::string a{"hello"};
std::string b{std::move(a)};  // std::move casts a to string&&
                                // string's move ctor does the actual move

// After move, 'a' is in a valid but indeterminate state
// Safe to call: a.empty(), a.size(), a = "new value"
// Unsafe to assume: a == ""
```

`std::move` is defined in `<utility>`. It's essentially:

```cpp
template <typename T>
constexpr std::remove_reference_t<T>&& move(T&& t) noexcept
{
    return static_cast<std::remove_reference_t<T>&&>(t);
}
```

</details>

5. Why should you use `std::make_shared` instead of `new` + `shared_ptr`?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::make_shared<T>(args)` performs a single memory allocation for both the object and the control block (reference count). Using `shared_ptr<T>(new T{args})` requires two separate allocations. `make_shared` is also exception-safe with `new`, a leak can occur if another argument's evaluation throws between the `new` and the `shared_ptr` construction.

**Detailed explanation:**

```cpp
// Two allocations (object + control block separately):
std::shared_ptr<Widget> sp1{new Widget{42}};

// One allocation (object + control block together  faster):
auto sp2 = std::make_shared<Widget>(42);

// Exception safety issue:
foo(std::shared_ptr<int>(new int{42}), throwingFunction());
// If throwingFunction() throws after new but before shared_ptr ctor,
// the int leaks. make_shared avoids this.
```

Similarly, prefer `std::make_unique<T>(args)` over `new` + `unique_ptr`.

</details>

6. What is the Rule of Five and when does it apply?

<details>
<summary>Show answer</summary>

**Direct answer:** If you define or delete any of the five special member functions (destructor, copy constructor, copy assignment, move constructor, move assignment), you should define or delete all five. This ensures consistent ownership semantics if you need a custom destructor, the default copy/move are almost certainly wrong.

**Detailed explanation:**

```cpp
class Resource
{
    int* m_data{};
public:
    Resource(int val) : m_data{new int{val}} {}

    ~Resource()                                   { delete m_data; }
    Resource(const Resource& src)                 // deep copy
        : m_data{new int{*src.m_data}} {}
    Resource& operator=(const Resource& src)      // copy assign
    {
        if (this != &src) { delete m_data; m_data = new int{*src.m_data}; }
        return *this;
    }
    Resource(Resource&& src) noexcept             // move
        : m_data{src.m_data} { src.m_data = nullptr; }
    Resource& operator=(Resource&& src) noexcept  // move assign
    {
        if (this != &src) { delete m_data; m_data = src.m_data; src.m_data = nullptr; }
        return *this;
    }
};
```

Rule of Zero: if your class only has RAII members (smart pointers, `std::string`, `std::vector`), you don't need any of the five.

</details>

7. Why does deleting only the move constructor cause problems?

<details>
<summary>Show answer</summary>

**Direct answer:** If you `= delete` the move constructor, the compiler won't fall back to the copy constructor for rvalue arguments it will produce a hard compile error instead. Normally, if no move constructor exists (not declared at all), the compiler uses copy. But declaring it as deleted is different from not declaring it deleted still participates in overload resolution.

**Detailed explanation:**

```cpp
class Foo
{
public:
    Foo() = default;
    Foo(const Foo&) = default;       // copy OK
    Foo(Foo&&) = delete;             // move explicitly deleted
};

Foo a;
Foo b{a};              // OK: copy
Foo c{std::move(a)};   // ERROR: deleted move selected, won't fall back to copy

// Fix: either don't declare the move ctor at all, or follow Rule of Five
```

If you delete one special member, consider what happens to all five.

</details>

8. What is the state of a moved-from object?

<details>
<summary>Show answer</summary>

**Direct answer:** A moved-from object is in a "valid but indeterminate" state. You must not rely on its value, but you can safely destroy it, assign a new value to it, or call member functions with no preconditions (like `empty()` or `size()`).

**Detailed explanation:**

```cpp
std::vector<int> v{1, 2, 3};
std::vector<int> v2{std::move(v)};

// v is now valid but indeterminate:
v.size();              // safe to call (likely 0, but not guaranteed by standard)
v.push_back(42);       // safe  assigns new state
v = {4, 5, 6};         // safe  assigns new value

// NOT safe:
// Assuming v.empty() == true (implementation-defined)
// Assuming v[0] has any particular value
```

Best practice: after moving from an object, either reassign it or let it go out of scope.

</details>

9. Why was `std::auto_ptr` removed and what replaced it?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::auto_ptr` used copy semantics to fake ownership transfer copying an `auto_ptr` silently nulled the source, which was surprising and broke containers (copying an element into a vector would destroy the original). It was deprecated in C++11 and removed in C++17. `std::unique_ptr` replaces it using proper move semantics copying is a compile error, moving is explicit.

**Detailed explanation:**

```cpp
// auto_ptr (broken  removed in C++17):
std::auto_ptr<int> a(new int{42});
std::auto_ptr<int> b = a;     // "copies" but actually moves  a is now null!

// unique_ptr (correct):
auto a2 = std::make_unique<int>(42);
// auto b2 = a2;              // ERROR: can't copy
auto b2 = std::move(a2);      // explicit move  clear intent
```

</details>

10. When should you use `get()` on a smart pointer?

<details>
<summary>Show answer</summary>

**Direct answer:** Use `get()` to pass the raw pointer to functions that need a non-owning pointer (e.g., C APIs, legacy code). The function must not `delete` the pointer or store it beyond the smart pointer's lifetime. Never use `get()` to construct another smart pointer from the same raw pointer that creates independent ownership and double-delete.

**Detailed explanation:**

```cpp
auto ptr = std::make_unique<Widget>(42);

legacyCFunction(ptr.get());    // OK: passes raw pointer, no ownership transfer

// NEVER do this:
// std::unique_ptr<Widget> ptr2{ptr.get()};  // double ownership  double delete!

// For shared_ptr, never create a second shared_ptr from get():
auto sp = std::make_shared<int>(10);
// std::shared_ptr<int> sp2{sp.get()};  // independent control block  crash
auto sp2 = sp;                          // correct: shared ownership
```

</details>
