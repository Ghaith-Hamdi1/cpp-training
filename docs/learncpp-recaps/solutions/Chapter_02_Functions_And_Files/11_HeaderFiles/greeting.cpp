// greeting.cpp - Definitions for greeting functions
// Include paired header first.

#include "greeting.h"

#include <iostream>

void sayHello(const std::string &name)
{
    std::cout << "Hello, " << name << "!\n";
}

void sayGoodbye(const std::string &name)
{
    std::cout << "Goodbye, " << name << "! See you next time.\n";
}
