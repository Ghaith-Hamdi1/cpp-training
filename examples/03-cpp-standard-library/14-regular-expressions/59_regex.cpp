#include <iostream>
#include <regex>
#include <string>

int main()
{
    std::regex pattern ("(t(e|s)t)+");
    std::string str("This is a tet string tst tst");

    bool match = std::regex_match(str, pattern);
    if (match)
    {
        std::cout << "Matched" << std::endl;
    }
    else 
    {
        std::cout << "Not matched" << std::endl;
    }

    std::smatch smatch;

    match = std::regex_search(str, smatch, pattern);
    if (match)
    {
        std::cout << "Matched " << smatch[0] << "-" << smatch[1].str() << std::endl;
    }
    else 
    {
        std::cout << "Not matched" << std::endl;
    }

    std::sregex_iterator itr(str.begin(), str.end(), pattern);

    for (std::sregex_iterator end; itr != end; itr++)
    {
        std::cout << "With iterator match " << itr->str() << std::endl; 
    }

    return 0;
}