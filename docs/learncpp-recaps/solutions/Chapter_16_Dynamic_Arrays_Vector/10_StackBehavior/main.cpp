// Chapter 16 - Project 10: Stack Behavior (push_back, pop_back, emplace_back)
// ============================================================================
// std::vector supports LIFO (Last-In, First-Out) stack operations:
//   - push_back(val)  - adds an element to the end (push)
//   - emplace_back()  - constructs an element in-place at the end
//   - pop_back()      - removes the last element (pop)
//   - back()          - returns a reference to the last element (peek)
//
// Key rules:
//   - Use reserve() (not resize()) to pre-allocate for stack usage
//   - Prefer emplace_back() when constructing objects in-place
//   - Prefer push_back() when storing an existing value
//
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <vector>
#include <string>

// A simple struct to demonstrate emplace_back vs push_back
struct Student
{
    std::string name;
    int grade;

    Student(std::string n, int g) : name{std::move(n)}, grade{g}
    {
        std::cout << "  [Constructed Student: " << name << "]\n";
    }
};

int main()
{
    // --- 1. push_back() - add elements to the end ---
    std::cout << "=== push_back() ===\n";
    std::vector<int> stack;
    stack.reserve(5); // reserve, NOT resize!

    stack.push_back(10);
    stack.push_back(20);
    stack.push_back(30);

    std::cout << "After 3 push_backs: ";
    for (const auto &v : stack)
        std::cout << v << ' ';
    std::cout << "(size=" << stack.size() << ")\n";

    // --- 2. back() - peek at the top element ---
    std::cout << "\n=== back() - peek ===\n";
    std::cout << "Top element: " << stack.back() << '\n';

    // --- 3. pop_back() - remove the last element ---
    std::cout << "\n=== pop_back() ===\n";
    stack.pop_back(); // removes 30
    std::cout << "After pop_back: ";
    for (const auto &v : stack)
        std::cout << v << ' ';
    std::cout << "(size=" << stack.size() << ")\n";
    std::cout << "New top: " << stack.back() << '\n';

    stack.pop_back(); // removes 20
    stack.pop_back(); // removes 10
    std::cout << "After popping all: size=" << stack.size() << '\n';
    // Calling pop_back() on an empty vector is UNDEFINED BEHAVIOR!

    // --- 4. emplace_back() vs push_back() for objects ---
    std::cout << "\n=== emplace_back() vs push_back() ===\n";
    std::vector<Student> roster;
    roster.reserve(3);

    // emplace_back: constructs the Student IN-PLACE (no temporary object)
    std::cout << "emplace_back(\"Alice\", 95):\n";
    roster.emplace_back("Alice", 95); // forwards args to Student constructor

    // push_back: creates a temporary Student, then moves it into the vector
    std::cout << "push_back(Student{\"Bob\", 88}):\n";
    roster.push_back(Student{"Bob", 88}); // temporary created, then moved

    // emplace_back is more efficient when constructing objects with arguments.
    std::cout << "emplace_back(\"Charlie\", 72):\n";
    roster.emplace_back("Charlie", 72);

    std::cout << "\nRoster:\n";
    for (const auto &s : roster)
        std::cout << "  " << s.name << ": " << s.grade << '\n';

    // --- 5. Stack simulation: bracket matching ---
    std::cout << "\n=== Practical example: bracket matching ===\n";
    std::string expr{"((a+b) * (c-d))"};
    std::vector<char> charStack;

    bool balanced{true};
    for (char ch : expr)
    {
        if (ch == '(')
            charStack.push_back(ch);
        else if (ch == ')')
        {
            if (charStack.empty())
            {
                balanced = false;
                break;
            }
            charStack.pop_back();
        }
    }
    balanced = balanced && charStack.empty();

    std::cout << "Expression: " << expr << '\n';
    std::cout << "Brackets balanced: " << (balanced ? "yes" : "no") << '\n';

    return 0;
}
