# String

(Slides 53–58)

- `std::string` is a class introduced in C++ to make string management easier (list of characters)
- It is a container named `basic_string` with `char` as elements type (many analogies with containers management like iterators and APIs)
- Can be created using list of characters, copied or moved from another string
- The most similar container to string is vector, almost all member functions are the same

# Construction

- Below are different ways to create a string (see example for full listing)

# Length and capacity

- `.length()` returns the number of characters inside the string
- `.empty()` returns a boolean to check if the string is empty
- `.capacity()` returns the number of characters that can be put without reallocation
- `.reserve()` allocates memory for string without initialization

# Accessing string

- `operator[]` and `.at()` can be used to access characters at a given position
- `.c_str()` returns a pointer to a constant buffer of string (`const char*`)
- `.data()` returns a pointer to buffer of string (`char*`)

# Assignment

- `.assign()`: overrides the contents of the string (returns `*this` to chain calls)
- `operator=`: equivalent to assign
- `.append()`: concatenates strings (returns `*this` to chain calls)
- `operator+=`: equivalent to append

# Insertion, clear and substring

- `.insert()` used to insert data into string (returns `*this` for chaining, or an iterator to first inserted character)
- `.clear()` to erase the string
- `.substr()` to get a substring from another

```cpp
// Trimmed excerpt — full runnable example: Examples/03_CPP_Standard_Library/09_string/51_strings.cpp
#include <iostream>
#include <string>

int main()
{
    std::string str; // empty string
    std::string char_str { "This is a string" };
    str = char_str; // copy assignment
    std::string copy_str { str }; // copy constructor
    std::string move_string { std::move(str)};
    std::cout << "Moved string " << move_string << " and old one *" << str << "*" << std::endl;
    std::string sub_string (copy_str, 4);
    std::cout << "New string from 4 first character:" << sub_string << std::endl;
    std::string from_numeric { std::to_string(2.0) };
    std::cout << "From numeric " << from_numeric << std::endl;

    ///// length and capacity
    std::cout << "String: *" << char_str << "* length=" << char_str.length() << " capacity=" << char_str.capacity() << std::endl;
    char_str.reserve(20);
    std::cout << "After reserve String: *" << char_str << "* length=" << char_str.length() << " capacity=" << char_str.capacity() << std::endl;

    // access string
    std::cout << "Character at index 2 *" << char_str[2] << std::endl;
    try
    {
        std::cout << "Character at index 2 with at*" << char_str.at(2) << std::endl;
        // exception is thrown even char_str is reserved with 32 chars
        std::cout << "Throwing exception with invalid index " << char_str.at(17);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Handle exception " << e.what() << std::endl;
    }

    std::string assign_str;
    assign_str.assign("CHAR");
    assign_str.assign(char_str, 0, 4);
    std::cout << assign_str << "*" << assign_str.assign(4, 'x').append("XXXX").append(char_str, 0, 4) << std::endl;

    std::cout << assign_str.insert(0, 3, '/').insert(0, "HELLO") << std::endl;
    assign_str.insert(assign_str.begin(), 2, '-');
    std::cout << "Final value " << assign_str << std::endl;

    std::string substr = assign_str.substr(0, 7);
    std::cout << "Substring " << substr << std::endl;

    return 0;
}
```

---

