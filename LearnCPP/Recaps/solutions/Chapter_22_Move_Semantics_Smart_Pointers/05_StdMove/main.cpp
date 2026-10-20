// Chapter 22 - Project 05: std::move
// std::move (from <utility>) casts an l-value to an r-value reference,
// enabling move semantics to be invoked on named objects.
//
// IMPORTANT:
//   - std::move does NOT move anything - it's just a cast.
//   - The actual moving happens in the move constructor / move assignment.
//   - After std::move, the source object is in a valid but indeterminate state.
//   - You can safely reassign it or call functions like empty(), but
//     don't rely on its old value.

#include <iostream>
#include <string>
#include <vector>
#include <utility> // std::move, std::swap

// -----------------------------------------------------------------------
// 1. Basic std::move with std::string
// -----------------------------------------------------------------------
void basicMove()
{
    std::cout << "=== 1. Basic std::move ===\n";

    std::string src = "Hello, World!";
    std::cout << "  Before move: src = \"" << src << "\"\n";

    // std::move casts 'src' to std::string&&, so the move constructor is called
    std::string dst = std::move(src);

    std::cout << "  After move:  src = \"" << src << "\" (valid but indeterminate)\n";
    std::cout << "  After move:  dst = \"" << dst << "\"\n";

    // Safe to reassign src
    src = "Reassigned!";
    std::cout << "  After reassign: src = \"" << src << "\"\n";
}

// -----------------------------------------------------------------------
// 2. std::move to fill a container efficiently
// -----------------------------------------------------------------------
void moveIntoVector()
{
    std::cout << "\n=== 2. Moving elements into a vector ===\n";

    std::vector<std::string> names;
    std::string name1 = "Alice";
    std::string name2 = "Bob";
    std::string name3 = "Charlie";

    // Without std::move: each push_back copies the string
    names.push_back(name1); // copy
    std::cout << "  After copy push: name1 = \"" << name1 << "\"\n";

    // With std::move: push_back moves the string (much cheaper for large strings)
    names.push_back(std::move(name2)); // move
    std::cout << "  After move push: name2 = \"" << name2 << "\" (moved-from)\n";

    names.push_back(std::move(name3)); // move
    std::cout << "  After move push: name3 = \"" << name3 << "\" (moved-from)\n";

    std::cout << "  Vector contents: ";
    for (const auto &n : names)
        std::cout << '"' << n << "\" ";
    std::cout << '\n';
}

// -----------------------------------------------------------------------
// 3. Implementing swap with std::move
// -----------------------------------------------------------------------
template <typename T>
void mySwap(T &a, T &b)
{
    // std::move enables efficient 3-step swap using moves instead of copies
    T temp = std::move(a); // a -> temp  (move)
    a = std::move(b);      // b -> a     (move)
    b = std::move(temp);   // temp -> b  (move)
}

void swapDemo()
{
    std::cout << "\n=== 3. Swap using std::move ===\n";

    std::string x = "First";
    std::string y = "Second";
    std::cout << "  Before swap: x = \"" << x << "\", y = \"" << y << "\"\n";

    mySwap(x, y);
    std::cout << "  After swap:  x = \"" << x << "\", y = \"" << y << "\"\n";
}

// -----------------------------------------------------------------------
// 4. std::move with function parameters
// -----------------------------------------------------------------------
void takeOwnership(std::string s)
{
    std::cout << "  Took ownership: \"" << s << "\"\n";
}

void passByMove()
{
    std::cout << "\n=== 4. Passing by move ===\n";

    std::string data = "Important data";
    std::cout << "  Before: data = \"" << data << "\"\n";

    // Moves 'data' into the function parameter 's'
    takeOwnership(std::move(data));

    std::cout << "  After:  data = \"" << data << "\" (moved-from)\n";
}

// -----------------------------------------------------------------------
// 5. Return value - std::move is usually WRONG here
// -----------------------------------------------------------------------
std::string createMessage()
{
    std::string msg = "Automatic return";

    // DO NOT do:  return std::move(msg);
    // The compiler applies NRVO (Named Return Value Optimization) automatically.
    // Using std::move here PREVENTS the optimization!

    return msg; // Compiler will move or elide - no std::move needed
}

void returnValueDemo()
{
    std::cout << "\n=== 5. Return by value (no std::move needed) ===\n";
    std::string result = createMessage();
    std::cout << "  result = \"" << result << "\"\n";
}

// -----------------------------------------------------------------------
int main()
{
    basicMove();
    moveIntoVector();
    swapDemo();
    passByMove();
    returnValueDemo();

    std::cout << "\nDone.\n";
    return 0;
}
