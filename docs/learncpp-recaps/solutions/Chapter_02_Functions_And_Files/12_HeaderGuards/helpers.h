// helpers.h - Includes other headers to demonstrate transitive inclusion.
// If constants.h or utils.h lacked guards, including helpers.h alongside
// a direct include of those headers would cause duplication errors.

#pragma once

#include "constants.h"
#include "utils.h"

#include <iostream>

// Inline function that uses both constants.h and utils.h content.
inline void printAppInfo()
{
    std::cout << "App: " << appName << " (v" << appVersion << ")\n";
    std::cout << "max(3, 7) via utils.h = " << maxOf(3, 7) << '\n';
}
