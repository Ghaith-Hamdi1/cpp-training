// Chapter 8 - Project 03: If-Else Chains
// Demonstrates flattening nested ifs into clean else-if chains.
// Compile: g++ -std=c++20 -o main main.cpp

#include <iostream>
#include <string_view>

// Helper: returns a letter grade for a numeric score
std::string_view getGrade(int score)
{
    // else-if chain - cleaner than deeply nested ifs
    if (score >= 90)
        return "A";
    else if (score >= 80)
        return "B";
    else if (score >= 70)
        return "C";
    else if (score >= 60)
        return "D";
    else
        return "F";
}

int main()
{
    // -------------------------------------------------------
    // 1. Grading with an else-if chain
    // -------------------------------------------------------
    int scores[]{95, 82, 74, 65, 40};

    for (int s : scores)
    {
        std::cout << "Score " << s << " => Grade " << getGrade(s) << '\n';
    }
    std::cout << '\n';

    // -------------------------------------------------------
    // 2. Classifying a number
    // -------------------------------------------------------
    int num{-7};

    if (num > 0)
        std::cout << num << " is positive.\n";
    else if (num < 0)
        std::cout << num << " is negative.\n";
    else
        std::cout << num << " is zero.\n";

    // -------------------------------------------------------
    // 3. BMI classification (else-if chain)
    // -------------------------------------------------------
    double bmi{24.5};

    std::cout << "\nBMI " << bmi << ": ";
    if (bmi < 18.5)
        std::cout << "Underweight\n";
    else if (bmi < 25.0)
        std::cout << "Normal weight\n";
    else if (bmi < 30.0)
        std::cout << "Overweight\n";
    else
        std::cout << "Obese\n";

    // -------------------------------------------------------
    // 4. Deeply nested ifs (bad) vs else-if chain (good)
    // -------------------------------------------------------
    int day{3}; // 1=Mon, 2=Tue, ... 7=Sun

    // BAD - hard to read
    // if (day == 1)
    //     std::cout << "Monday\n";
    // else
    //     if (day == 2)
    //         std::cout << "Tuesday\n";
    //     else
    //         if (day == 3)
    //             std::cout << "Wednesday\n";

    // GOOD - flat else-if chain
    if (day == 1)
        std::cout << "\nDay: Monday\n";
    else if (day == 2)
        std::cout << "\nDay: Tuesday\n";
    else if (day == 3)
        std::cout << "\nDay: Wednesday\n";
    else if (day == 4)
        std::cout << "\nDay: Thursday\n";
    else if (day == 5)
        std::cout << "\nDay: Friday\n";
    else if (day == 6)
        std::cout << "\nDay: Saturday\n";
    else if (day == 7)
        std::cout << "\nDay: Sunday\n";
    else
        std::cout << "\nInvalid day number.\n";

    // Note: when testing one value against many constants,
    // a switch statement (next project) is even better!

    return 0;
}
