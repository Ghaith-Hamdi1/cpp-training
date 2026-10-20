// Chapter 15 - Project 03: Nested Types (Member Types)
// =====================================================
//
// Types defined inside a class are called "nested types" or "member types".
// They can be enums, typedefs, type aliases, or even other classes.
//
// Rules:
//   - They follow access specifiers (public/private/protected).
//   - They are accessed externally via the class scope: ClassName::NestedType.
//   - Nested types should be defined at the TOP of the class.
//   - A common pattern: nest an unscoped enum inside a class so the class
//     itself acts as a scope (avoids polluting the enclosing namespace).
//   - Nested classes can access the private members of the enclosing class,
//     but do NOT have access to its `this` pointer.

#include <iostream>
#include <string>
#include <vector>

// -------------------------------------------------------
// Example 1: Nested unscoped enum used as class-scoped constants
// -------------------------------------------------------
class Fruit
{
public:
    // Nested enum - accessed externally as Fruit::apple, Fruit::banana, etc.
    enum Type
    {
        apple,
        banana,
        cherry,
    };

private:
    Type m_type{};
    int m_percentageEaten{0};

public:
    Fruit(Type type) : m_type{type} {}

    Type getType() const { return m_type; }

    bool isCherry() const { return m_type == cherry; }

    void print() const
    {
        constexpr const char *names[]{"Apple", "Banana", "Cherry"};
        std::cout << names[m_type] << '\n';
    }
};

// -------------------------------------------------------
// Example 2: Nested type alias
// -------------------------------------------------------
class IntList
{
public:
    // Public type alias - users can write IntList::container_type
    using container_type = std::vector<int>;

private:
    container_type m_data{};

public:
    void add(int value) { m_data.push_back(value); }

    // Expose the aliased type in the interface
    const container_type &data() const { return m_data; }
};

// -------------------------------------------------------
// Example 3: Nested class
// -------------------------------------------------------
class University
{
public:
    // Nested class - logically belongs inside University
    class Student
    {
    private:
        std::string m_name{};
        int m_id{};

    public:
        Student(const std::string &name, int id)
            : m_name{name}, m_id{id}
        {
        }

        void print() const
        {
            std::cout << "Student{ " << m_name << ", id=" << m_id << " }\n";
        }
    };

private:
    std::string m_universityName{};
    std::vector<Student> m_students{};

public:
    University(const std::string &name) : m_universityName{name} {}

    void enroll(const Student &s) { m_students.push_back(s); }

    void printRoster() const
    {
        std::cout << m_universityName << " roster:\n";
        for (const auto &s : m_students)
        {
            std::cout << "  ";
            s.print();
        }
    }
};

int main()
{
    // --- Nested enum ---
    Fruit f{Fruit::cherry}; // Access enum via class scope
    f.print();              // "Cherry"
    std::cout << "Is cherry? " << std::boolalpha << f.isCherry() << '\n';

    // --- Nested type alias ---
    IntList list{};
    list.add(10);
    list.add(20);
    list.add(30);

    // Users can use IntList::container_type directly
    const IntList::container_type &vec = list.data();
    std::cout << "IntList contents:";
    for (int v : vec)
        std::cout << ' ' << v;
    std::cout << '\n';

    // --- Nested class ---
    University uni{"MIT"};

    // Student is accessed via University::Student
    University::Student alice{"Alice", 1001};
    University::Student bob{"Bob", 1002};

    uni.enroll(alice);
    uni.enroll(bob);
    uni.printRoster();

    return 0;
}
