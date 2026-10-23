// other.cpp - Uses the same inline header to verify single-instance behavior

#include <iostream>
#include "mathutils.h"

void otherFileDemo()
{
    // Using the same inline function and variable from mathutils.h
    std::cout << "   square(7) from other.cpp = " << MathUtils::square(7) << '\n';
    std::cout << "   pi from other.cpp        = " << MathUtils::pi << '\n';
    std::cout << "   Address in other.cpp:     " << &MathUtils::pi << '\n';
    // The address should match the one printed in main.cpp - proving single instance
}
