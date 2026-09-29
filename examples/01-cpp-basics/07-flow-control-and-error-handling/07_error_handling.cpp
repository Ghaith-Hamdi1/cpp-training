#include <iostream>
#include <cassert>
#include <exception>

void manageWithinFunction()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        // Check whether the user entered meaningful input
        switch (operation) {
        case '+':
        case '-':
        case '*':
        case '/':
            std::cout << "Bravo, this is a good input" << std::endl;
            return; // return it to the caller
        default: // otherwise tell the user what went wrong
            std::cerr << "Oops, that input is invalid.  Please try again." << std::endl;
        }
    } // and try again
}

int returnToCaller(int input)
{
    // test if input is valid
    if (input < 0)
    {
        // we may log the error as well
        std::cerr << "We cannot accept negative value" << std::endl;
        return 1;
    }

    std::cout << "Processing is done with positive value" << std::endl;

    return 0; // return success
}

int main() {
    // manage within function
    manageWithinFunction();

    int ret{0};
    int input{-3};
    ret = returnToCaller(input);
    if (ret == 1) {
        // action to be performed by caller
    }
    else if (ret == 0) { // success
        // action on success
    }

    return 0;
}