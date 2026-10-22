// Tiny test helper shared by the practice exercises.
#pragma once
#include <iostream>

inline int& failures() { static int n = 0; return n; }

#define CHECK(cond) do { if (!(cond)) { std::cout << "  FAIL (line " << __LINE__ << "): " #cond "\n"; ++failures(); } } while (0)

inline int finish(const char* name)
{
    if (failures() == 0) { std::cout << name << ": all checks passed\n"; return 0; }
    std::cout << name << ": " << failures() << " check(s) failed\n";
    return 1;
}
