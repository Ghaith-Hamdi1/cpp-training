# Introduction to C++

- C++ is an Object Oriented Programming Language
- Extension of C Language
- Compiled Language
- Low Level language (no memory management)
- Trust the programmer
- Used for high performance systems and embedded systems
- Benefit from OOP concept

## Software development using C++

[Diagram — extracted labels, laid out as a development-process diagram]
- UML
- Compilation / Cross Compilation
- Unit testing
- Integration Testing
- IDE (Integrated Development Environment)
- Software debugger
- Hardware Debugger
- Tracing (Logs)

## C++ program

- Unique entry point "main"
- With parameters (console applications):

```cpp
int main(int argc, char * argv[]) {
    return 0;
}
```

- Without parameters:

```cpp
int main() {
    return 0;
}
```

## C++ program — files

- Header files
  - STL header files without extension
  - Header files ".h" or ".hpp"
- Source files
  - Files ".cpp" or ".cc"
- Static libraries
- Dynamic Libraries

## First program

```cpp
#include <iostream>
int main() {
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
```

Corresponds to `examples/01-cpp-basics/01-introduction-to-cpp/01_first_program.cpp` (the deck's build/run example below uses argument handling, matching that file):

```cpp
#include <iostream>

int main(int argc, char* argv[])
{
     for (int i = 0; i < argc; i++) {
          std::cout << "Arg " << i << "= " << argv[i] <<  std::endl;
     }
     return 0;
}
```

- Build code (Linux):

```
~$ g++ 01_firstProgram.cpp -o firstProgram
```

- Run Binary file:

```
~$ ./firstProgram -d opt1 -p opt2
```

## Code hierarchy

[Diagram — extracted project tree structure]

```
project_name
├── inc
│   ├── folder1
│   │   ├── file1.h
│   │   └── file2.h
│   └── folder2
│       ├── file3.h
│       └── file4.h
└── src
    ├── folder1
    │   ├── file1.cpp
    │   └── file2.cpp
    └── folder2
        ├── file3.cpp
        └── file4.cpp
```

## Build large projects

- Use of command line not convenient
- Use of Make files / CMake files
- CMake is simpler than a Makefile
- How to build: create a build directory in the workspace
  - `~/build$ cmake ..`
  - `~/build$ make`

Example `CMakeLists.txt`:

```cmake
# Almost all CMake files should start with this
cmake_minimum_required(VERSION 2.8)
# This is your project statement. You should always list languages;
project(ModernCMakeExample
        VERSION 1.0
        LANGUAGES CXX)

# Library sample
add_library(MyLibExample simple_lib.cpp simple_lib.hpp)

# Adding something we can run - Output name matches target name
add_executable(MyExample simple_example.cpp)

# Make sure you link your targets with this command
target_link_libraries(MyExample PRIVATE MyLibExample)
```

## Comments in C++

- Source code should be well commented
- Comments should always be in English
- Single line comment, C++ style:

```cpp
// this is a single line comment
```

- Multi-line comment, C style:

```cpp
/* This is a multi
 * line comment */
```

- Must describe ambiguous actions

---

