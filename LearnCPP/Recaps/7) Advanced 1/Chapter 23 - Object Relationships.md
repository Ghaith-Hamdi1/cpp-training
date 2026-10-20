# Chapter 23 Recap - Object Relationships

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- **Favor composition** - it's the simplest, safest, and self-cleaning relationship.
- Implement the **simplest relationship** that meets your needs.
- Avoid bidirectional associations when unidirectional suffices.
- Each class should have a **single responsibility**.
- Use `std::reference_wrapper` to store references in standard containers.
- `{ }` prefers list constructors; use `( )` for non-list constructors.
- Adding a list constructor can **silently change** existing behavior for `{ }` initializations.
- Always provide a list assignment operator alongside a list constructor.

### 3 Tiny Examples

1.

```cpp
// Composition: Body "part-of" Person (member variable)
// Aggregation: Department "has-a" Teacher (pointer to external)
// Association: Doctor "uses-a" Patient (bidirectional link)
// Dependency: print() "depends-on" std::ostream (parameter)
```

2.

```cpp
class Creature {
    std::string m_name;     // composition: name is part-of Creature
    Point2D m_location;     // composition: location is part-of Creature
public:
    Creature(std::string_view name, const Point2D& loc)
        : m_name{name}, m_location{loc} {}
};
```

3.

```cpp
class Department {
    std::vector<std::reference_wrapper<const Teacher>> m_teachers;
public:
    void addTeacher(const Teacher& t) { m_teachers.push_back(t); }
};
// Teacher exists independently; Department doesn't manage its lifetime
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Composition ("part-of")** - the whole owns its parts; parts belong to one object at a time; lifetime is managed by the whole.
- **Aggregation ("has-a")** - a whole/part relationship where parts can belong to multiple objects and their lifetime is managed externally.
- **Association ("uses-a")** - a relationship between unrelated objects; can be unidirectional or bidirectional; no whole/part hierarchy.
- **Dependency ("depends-on")** - the weakest relationship; one object temporarily uses another (e.g., as a function parameter).
- **Reflexive association** - an object that relates to another object of the **same** type.
- **Container class** - a class designed to hold/organize multiple instances of another type.
- **Value container** - stores copies (composition); **Reference container** - stores pointers/references (aggregation).
- **`std::initializer_list<T>`** - enables `{ }` initialization syntax for custom classes; lightweight, passed by value.
- **`std::reference_wrapper<T>`** - allows storing references in containers that normally can't hold them.

### Section-by-Section Detail

### 23.1 - Object relationships

- Real-world relationship patterns - **part-of**, **has-a**, **uses-a**, **depends-on**, **is-a** - map directly to C++ constructs
- These patterns determine the right **ownership** and **lifetime semantics** when designing classes
- This section introduces the vocabulary - **composition**, **aggregation**, **association**, **dependency**, **inheritance**
- Modeling relationships correctly → code that is easier to reason about, maintain, and extend

```cpp
// Composition: Body "part-of" Person (member variable)
// Aggregation: Department "has-a" Teacher (pointer to external)
// Association: Doctor "uses-a" Patient (bidirectional link)
// Dependency: print() "depends-on" std::ostream (parameter)
```

### 23.2 - Composition

- **Composition** is the strongest part-of relationship - the part belongs to exactly one whole, and the whole manages its entire **lifetime**
- The part doesn't know about the whole → the relationship is **unidirectional**
- Implemented with **normal member variables** - constructed with the containing object, destroyed with it
- Composition should be your **default** relationship choice - strongest encapsulation and simplest lifetime management
- If you can model a relationship as composition → **prefer it** over aggregation or association

```cpp
class Creature {
    std::string m_name;     // composition: name is part-of Creature
    Point2D m_location;     // composition: location is part-of Creature
public:
    Creature(std::string_view name, const Point2D& loc)
        : m_name{name}, m_location{loc} {}
};
```

→ _See [01_Composition](../solutions/Chapter_23_Object_Relationships/01_Composition/) for composition demos._

### 23.3 - Aggregation

- **Aggregation** is a weaker has-a relationship - parts can belong to **multiple wholes** and their lifetime is managed externally
- Implemented with **pointers or references** to objects that exist independently of the aggregate
- If the aggregate is destroyed, the parts **continue to exist**
- `std::reference_wrapper` (from `<functional>`) allows storing reference-like semantics in containers like `std::vector`
- Use aggregation when the whole needs access to a part but should **not control** its creation or destruction

```cpp
class Department {
    std::vector<std::reference_wrapper<const Teacher>> m_teachers;
public:
    void addTeacher(const Teacher& t) { m_teachers.push_back(t); }
};
// Teacher exists independently; Department doesn't manage its lifetime
```

→ _See [02_Aggregation](../solutions/Chapter_23_Object_Relationships/02_Aggregation/) and [03_ReferenceWrapper](../solutions/Chapter_23_Object_Relationships/03_ReferenceWrapper/)._

### 23.4 - Association

- An **association** is a uses-a relationship between otherwise **unrelated objects** - neither owns the other
- Can be **unidirectional** (Doctor knows Patients) or **bidirectional** (Doctor and Patient know each other)
- **Reflexive associations** link objects of the **same type** (e.g., a Course has a prerequisite Course)
- Can be **indirect** - referencing via ID rather than pointer

```cpp
class Doctor {
    std::vector<std::reference_wrapper<const Patient>> m_patients;
public:
    void addPatient(Patient& p);
};
// Bidirectional: Patient also has a list of Doctors
```

→ _See [04_UnidirectionalAssociation](../solutions/Chapter_23_Object_Relationships/04_UnidirectionalAssociation/) and [05_BidirectionalAssociation](../solutions/Chapter_23_Object_Relationships/05_BidirectionalAssociation/)._

### 23.5 - Dependencies

- A **dependency** is the weakest relationship - one object **temporarily uses** another for a specific task
- The depended-on object is typically a **parameter** or **local variable** - not a stored member
- Example: `operator<<` depends on `std::ostream` - used only during the function call
- Dependencies are always **unidirectional**

```cpp
void printPoint(std::ostream& out, const Point& p) {
    out << '(' << p.x << ", " << p.y << ')'; // depends on ostream
}
```

→ _See [07_Dependency](../solutions/Chapter_23_Object_Relationships/07_Dependency/) for dependency examples._

**Object Relationships Comparison:**

| Property                             | Composition      | Aggregation         | Association           | Dependency         |
| ------------------------------------ | ---------------- | ------------------- | --------------------- | ------------------ |
| **Relationship**                     | "part-of"        | "has-a"             | "uses-a"              | "depends-on"       |
| **Part belongs to multiple wholes?** | No               | Yes                 | N/A                   | N/A                |
| **Whole manages part lifetime?**     | Yes              | No                  | No                    | No                 |
| **Direction**                        | Unidirectional   | Unidirectional      | Uni- or bidirectional | Unidirectional     |
| **Implemented with**                 | Member variables | Pointers/references | Pointers, IDs         | Parameters, locals |
| **Strength**                         | Strongest        | Medium              | Weak                  | Weakest            |

### 23.6 - Container classes

- **Value containers** store copies of elements (composition - container owns data); **reference containers** store pointers/references (aggregation)
- Building a full `IntArray` class demonstrates memory management - dynamic allocation, resize, insert, remove, copy constructor, and copy assignment
- Each operation must correctly handle the underlying dynamic array - allocating, copying, and freeing memory → avoid leaks and double-deletes
- This exercise illustrates why `std::vector` is preferred in practice - it handles all this complexity, tested and optimized

```cpp
class IntArray {
    int* m_data{};
    int m_size{};
public:
    IntArray(int size) : m_data{new int[size]{}}, m_size{size} {}
    ~IntArray() { delete[] m_data; }
    int& operator[](int i) { return m_data[i]; }
};
```

→ _See [08_ContainerClass](../solutions/Chapter_23_Object_Relationships/08_ContainerClass/) for a hand-rolled container._

**Value Container vs Reference Container:**

| Property              | Value Container         | Reference Container             |
| --------------------- | ----------------------- | ------------------------------- |
| **Stores**            | Copies of elements      | Pointers/references to elements |
| **Relationship**      | Composition (owns data) | Aggregation (borrows data)      |
| **Element lifetime**  | Managed by container    | Managed externally              |
| **Copy semantics**    | Deep copy needed        | Shallow copy (pointer copy)     |
| **Invalidation risk** | None (self-contained)   | Dangling if source destroyed    |
| **Example**           | `std::vector<int>`      | `std::vector<int*>`             |

### 23.7 - std::initializer_list

- `std::initializer_list<T>` lets custom classes accept **brace-enclosed** `{ }` initialization syntax
- **Critical:** list initialization **prefers** list constructors - `MyArray{5}` calls the list ctor (one element), while `MyArray(5)` calls the `int` ctor (size 5)
- If you provide a list constructor → also provide a **list assignment operator** for consistency
- Adding a list constructor can **silently change** existing behavior for `{ }` initializations in previously working code

```cpp
class IntArray {
public:
    IntArray(std::initializer_list<int> list)
        : m_size{static_cast<int>(list.size())}, m_data{new int[m_size]{}} {
        int i{0};
        for (auto elem : list)
            m_data[i++] = elem;
    }
};
IntArray arr{1, 2, 3, 4, 5}; // uses initializer_list ctor
```

→ _See [09_InitializerList](../solutions/Chapter_23_Object_Relationships/09_InitializerList/) for `initializer_list` usage._

### Edge Cases and Caveats

❌ Confusing aggregation with composition:

```cpp
class Department {
    Teacher* m_teacher; // ❌ Is this composition or aggregation?
};
// If Department doesn't own Teacher's lifetime → aggregation, not composition
```

✅ Composition = part is destroyed with the whole. Aggregation = part exists independently.

---

❌ Memory leaks with aggregation:

```cpp
class Dept {
    Teacher* m_teacher; // Dept doesn't own → won't delete
};
// ❌ If nobody else deletes the Teacher → memory leak
```

✅ Ensure clear ownership - whoever creates, deletes. Or use smart pointers.

---

❌ `{ }` vs `( )` with list constructors:

```cpp
MyArray arr{5};  // ❌ list init → one element with value 5
MyArray arr(5);  // non-list init → size 5
```

✅ Be explicit about intent; know when `{}` triggers `initializer_list`.

---

❌ Shallow copying containers:

```cpp
MyArray a;
MyArray b = a; // ❌ default copy → both point to same dynamic memory → double-delete
```

✅ Implement deep copy constructor and `operator=`.

---

❌ Storing raw references in `std::vector`:

```cpp
std::vector<int&> v; // ❌ illegal - references are not assignable
```

✅ Use `std::reference_wrapper`:

```cpp
std::vector<std::reference_wrapper<int>> v; // ✅
```

---

❌ Forgetting self-assignment check in `operator=`:

```cpp
MyArray& operator=(const MyArray& rhs) {
    delete[] m_data; // ❌ if this == &rhs, just deleted our own data
    m_data = new int[rhs.m_size];
}
```

✅ Guard against self-assignment:

```cpp
if (this == &rhs) return *this; // ✅
```

---

❌ Bidirectional associations with circular dependencies:

```cpp
// A.h includes B.h, B.h includes A.h ❌ circular include
```

✅ Use forward declarations and careful header design.

---

### Hands-On Code Projects

Practice every concept with the hands-on projects in:

```
solutions/Chapter_23_Object_Relationships/
```

| Project                                                                                                                        | Concept                                                         |
| ------------------------------------------------------------------------------------------------------------------------------ | --------------------------------------------------------------- |
| [01_Composition](../solutions/Chapter_23_Object_Relationships/01_Composition/)                                                 | Composition ("part-of") - whole owns and manages part lifetime  |
| [02_Aggregation](../solutions/Chapter_23_Object_Relationships/02_Aggregation/)                                                 | Aggregation ("has-a") - parts with external lifetime management |
| [03_ReferenceWrapper](../solutions/Chapter_23_Object_Relationships/03_ReferenceWrapper/)                                       | `std::reference_wrapper` for storing references in containers   |
| [04_UnidirectionalAssociation](../solutions/Chapter_23_Object_Relationships/04_UnidirectionalAssociation/)                     | Unidirectional association ("uses-a") between unrelated objects |
| [05_BidirectionalAssociation](../solutions/Chapter_23_Object_Relationships/05_BidirectionalAssociation/)                       | Bidirectional association - Doctor ↔ Patient example            |
| [06_ReflexiveAssociation](../solutions/Chapter_23_Object_Relationships/06_ReflexiveAssociation/)                               | Object relates to another of the same type                      |
| [07_Dependency](../solutions/Chapter_23_Object_Relationships/07_Dependency/)                                                   | Dependency - weakest relationship, temporary usage              |
| [08_ContainerClass](../solutions/Chapter_23_Object_Relationships/08_ContainerClass/)                                           | Building an IntArray container with dynamic memory              |
| [09_InitializerList](../solutions/Chapter_23_Object_Relationships/09_InitializerList/)                                         | `std::initializer_list` for brace-enclosed init                 |
| [10_Pitfalls_ShallowCopy_BracesVsParens](../solutions/Chapter_23_Object_Relationships/10_Pitfalls_ShallowCopy_BracesVsParens/) | Shallow copy, `{}` vs `()`, self-assignment pitfalls            |

### Quick Reference

| Relationship | Keyword      | Ownership        | Implemented with    |
| ------------ | ------------ | ---------------- | ------------------- |
| Composition  | "part-of"    | Whole owns part  | Member variables    |
| Aggregation  | "has-a"      | External         | Pointers/references |
| Association  | "uses-a"     | None             | Pointers, IDs       |
| Dependency   | "depends-on" | None (temporary) | Parameters, locals  |

| Feature          | Syntax                                 | Notes                       |
| ---------------- | -------------------------------------- | --------------------------- |
| initializer_list | `Foo(std::initializer_list<int> list)` | `{ }` init for custom types |
| ref wrapper      | `std::reference_wrapper<T>`            | Refs in containers          |
| `std::ref()`     | `auto r = std::ref(obj);`              | Create ref wrapper          |
| Value container  | Stores copies                          | Composition pattern         |
| Ref container    | Stores pointers                        | Aggregation pattern         |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between composition and aggregation?

<details>
<summary>Show answer</summary>

**Direct answer:** In composition, the whole creates and destroys the part the part belongs to exactly one whole and can't exist independently (implemented as member variables). In aggregation, the part exists independently and can belong to multiple wholes the whole holds a pointer/reference but doesn't manage the part's lifetime.

**Detailed explanation:**

```cpp
// Composition: Heart can't exist without Body
class Body
{
    Heart m_heart;   // member variable  created/destroyed with Body
};

// Aggregation: Teacher exists independently of Department
class Department
{
    std::vector<Teacher*> m_teachers;  // pointers to externally-owned objects
    // Department doesn't delete teachers in destructor
};
```

Prefer composition when possible it gives the strongest encapsulation and simplest lifetime management.

</details>

2. What is an association and how does it differ from aggregation?

<details>
<summary>Show answer</summary>

**Direct answer:** An association is a "uses-a" relationship between otherwise unrelated objects neither owns the other, and there's no whole-part hierarchy. In aggregation, there's a clear whole-part relationship (Department has Teachers). Associations can be bidirectional (Doctor knows Patient and Patient knows Doctor) or reflexive (a Course has a prerequisite Course).

**Detailed explanation:**

```cpp
// Association: Doctor and Patient use each other, no ownership
class Patient;
class Doctor
{
    std::vector<Patient*> m_patients;   // knows patients, doesn't own them
};

class Patient
{
    std::vector<Doctor*> m_doctors;     // knows doctors, doesn't own them
};

// Indirect association (via ID instead of pointer):
class Order
{
    int m_customerId;   // refers to a Customer without holding a pointer
};
```

</details>

3. What is a dependency relationship?

<details>
<summary>Show answer</summary>

**Direct answer:** A dependency is the weakest relationship one object temporarily uses another to perform a task. The depended-on object is typically a function parameter or local variable, not a stored member. Example: `operator<<` depends on `std::ostream`. Dependencies are always unidirectional.

**Detailed explanation:**

```cpp
class Point
{
    int m_x{}, m_y{};
public:
    // Point depends on std::ostream  uses it temporarily
    friend std::ostream& operator<<(std::ostream& out, const Point& p)
    {
        out << '(' << p.m_x << ", " << p.m_y << ')';
        return out;
    }
};
// Point doesn't store std::ostream as a member  it's only used during the call
```

Relationship strength (strongest to weakest): composition > aggregation > association > dependency.

</details>

4. Why can't you store references directly in a `std::vector`?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::vector` requires elements to be assignable and default-constructible, but references can't be reseated or default-constructed. Use `std::reference_wrapper<T>` (from `<functional>`) instead it wraps a reference in a copyable, assignable object.

**Detailed explanation:**

```cpp
std::string a{"Alice"}, b{"Bob"}, c{"Charlie"};

// std::vector<std::string&> v;  // ERROR: can't store references

// Solution: std::reference_wrapper
std::vector<std::reference_wrapper<std::string>> v{a, b, c};

for (auto& ref : v)
    std::cout << ref.get() << ' ';  // .get() returns the underlying reference

// Modifying through the wrapper modifies the original:
v[0].get() = "Modified";
std::cout << a;  // "Modified"
```

</details>

5. What problem does the `initializer_list` constructor cause with `{}`?

<details>
<summary>Show answer</summary>

**Direct answer:** List initialization (`{}`) prefers the `initializer_list` constructor over other constructors. So `MyArray{5}` calls the list constructor (creates array with one element of value 5), not the size constructor (creates array of size 5). Use `()` to call the size constructor: `MyArray(5)`.

**Detailed explanation:**

```cpp
class IntArray
{
public:
    IntArray(int size) { /* allocate size elements */ }
    IntArray(std::initializer_list<int> list) { /* copy from list */ }
};

IntArray a(5);    // calls IntArray(int)  array of size 5
IntArray b{5};    // calls IntArray(initializer_list)  array with element {5}
IntArray c{1, 2, 3};  // calls IntArray(initializer_list)  array with {1, 2, 3}
```

If you provide an `initializer_list` constructor, also provide a matching assignment operator for consistency.

</details>

6. Why is deep copy important for classes with dynamic memory?

<details>
<summary>Show answer</summary>

**Direct answer:** The default (compiler-generated) copy constructor and assignment operator perform shallow memberwise copy pointer members are copied as addresses, so both objects point to the same memory. When one is destroyed, it frees the shared memory, leaving the other with a dangling pointer. Deep copy allocates new memory and copies the data.

**Detailed explanation:**

```cpp
class IntArray
{
    int* m_data{};
    int m_size{};
public:
    IntArray(int size) : m_size{size}, m_data{new int[size]{}} {}

    // Shallow copy (default): m_data copied as pointer  shared memory  crash
    // Deep copy (correct):
    IntArray(const IntArray& src)
        : m_size{src.m_size}
        , m_data{new int[src.m_size]}
    {
        std::copy(src.m_data, src.m_data + m_size, m_data);  // copy data
    }

    ~IntArray() { delete[] m_data; }
};
```

Follow the Rule of Three: custom destructor also need custom copy ctor + copy assignment.

</details>

7. How do you resolve circular dependencies between two classes?

<details>
<summary>Show answer</summary>

**Direct answer:** Use a forward declaration of one class and store pointers/references to it (not by value). Define the member functions that use the forward-declared class in the `.cpp` file where the full definition is available. Alternatively, introduce an interface or break the cycle with `std::weak_ptr` for shared ownership.

**Detailed explanation:**

```cpp
// A.h
class B;               // forward declaration
class A
{
    B* m_b{nullptr};    // pointer  doesn't need B's full definition
public:
    void setB(B* b);
    void useB();        // defined in A.cpp where B.h is included
};

// B.h
#include "A.h"         // needs full definition of A
class B
{
    A* m_a{nullptr};
public:
    void setA(A* a) { m_a = a; }
};

// A.cpp
#include "A.h"
#include "B.h"         // now B is fully defined
void A::setB(B* b) { m_b = b; }
void A::useB() { /* can use B members here */ }
```

</details>

8. Who is responsible for cleanup in an aggregation relationship?

<details>
<summary>Show answer</summary>

**Direct answer:** The external code that created the parts is responsible for cleanup not the aggregate. The aggregate holds pointers/references to parts it doesn't own, so the aggregate's destructor should not `delete` them. If the aggregate is destroyed, the parts continue to exist.

**Detailed explanation:**

```cpp
class Department
{
    std::vector<Teacher*> m_teachers;  // doesn't own these
public:
    void addTeacher(Teacher* t) { m_teachers.push_back(t); }
    // Destructor does NOT delete teachers
};

int main()
{
    Teacher t1{"Alice"}, t2{"Bob"};    // parts created externally
    {
        Department dept;
        dept.addTeacher(&t1);
        dept.addTeacher(&t2);
    }  // dept destroyed  t1 and t2 still alive

    // t1 and t2 cleaned up when they go out of scope here
}
```

</details>

9. What are the five object relationship types from strongest to weakest?

<details>
<summary>Show answer</summary>

**Direct answer:** From strongest to weakest: **Composition** (part-of, exclusive ownership, member variables) > **Aggregation** (has-a, shared access, pointers to external objects) > **Association** (uses-a, no ownership, bidirectional possible) > **Dependency** (temporary use, parameter/local) > **Inheritance** (is-a, separate topic).

**Detailed explanation:**

| Relationship | Ownership        | Implemented with  | Example                     |
| ------------ | ---------------- | ----------------- | --------------------------- |
| Composition  | Whole owns part  | Member variable   | Body has Heart              |
| Aggregation  | No ownership     | Pointer/reference | Dept has Teachers           |
| Association  | No ownership     | Pointer/reference | Doctor Patient              |
| Dependency   | None (temporary) | Parameter/local   | `operator<<` uses `ostream` |

</details>

10. What is a container class and what are the two types?

<details>
<summary>Show answer</summary>

**Direct answer:** A container class holds and manages a collection of elements. **Value containers** store copies of their elements (composition container owns the data, e.g., `std::vector`). **Reference containers** store pointers/references to externally-owned objects (aggregation container doesn't own the data, e.g., `std::vector<T*>`).

**Detailed explanation:**

```cpp
// Value container (composition): owns copies of elements
std::vector<std::string> names{"Alice", "Bob"};
// Destroying the vector destroys the strings

// Reference container (aggregation): pointers to external objects
std::vector<Widget*> widgets;
Widget w1, w2;
widgets.push_back(&w1);
widgets.push_back(&w2);
// Destroying the vector does NOT destroy w1, w2
```

Prefer standard library containers over writing your own they handle memory management correctly.

</details>
