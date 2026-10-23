// internal.h - Declarations for internal.cpp's externally-visible functions
// These functions are NOT given internal linkage - they exist to let
// main.cpp observe what's happening inside internal.cpp.

#ifndef INTERNAL_H
#define INTERNAL_H

// Returns the value of internal.cpp's s_count
int getInternalCount();

// Demonstrates unnamed namespace content
void printUnnamedDemo();

#endif
