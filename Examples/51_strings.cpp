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
    std::string sub_string2 (copy_str, 5, 2);
    std::cout << "New string from 5 index 2 characters:" << sub_string2 << "*" << std::endl;
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
    std::cout << "Assign *" << assign_str << "*-*";
    assign_str.assign(char_str, 0, 4);
    std::cout << assign_str << "*" << assign_str.assign(4, 'x').append("XXXX").append(char_str, 0, 4);
    std::cout << std::endl;

    std::cout << assign_str.insert(0, 3, '/').insert(0, "HELLO") << std::endl;
    auto it = assign_str.insert(assign_str.begin(), 2, '-');
    std::cout << "Final value " << assign_str << std::endl;

    std::string substr = assign_str.substr(0, 7);
    std::cout << "Substring " << substr << std::endl;

    return 0;
}