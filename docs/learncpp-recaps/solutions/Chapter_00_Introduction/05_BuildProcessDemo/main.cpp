// ============================================================================
// Chapter 0, Project 05 - Build Process Demo
// Concept: Understanding the compile → link → execute pipeline.
// ============================================================================
//
// KEY IDEAS (Sections 0.4, 0.5):
//   The build process has multiple stages:
//
//   1. PREPROCESSING
//      - The preprocessor handles lines starting with # (like #include).
//      - #include <iostream> literally copies the contents of the iostream
//        header file into your source file before compilation.
//      - The output is called a "translation unit."
//
//   2. COMPILATION
//      - The compiler translates each .cpp file into an object file (.o / .obj).
//      - Each .cpp is compiled independently - the compiler doesn't know about
//        other .cpp files at this stage.
//      - Syntax errors are caught here.
//
//   3. LINKING
//      - The linker combines all object files + libraries into one executable.
//      - It resolves references between files (e.g., function calls).
//      - Linker errors occur when the linker can't find a function definition.
//      - The C++ Standard Library is linked in at this stage.
//
//   4. EXECUTION
//      - The OS loads the executable into memory and starts running at main().
//
//   This single-file demo simulates the concept. In real projects, you'd have
//   multiple .cpp files compiled separately and linked together.
//
// BUILD:  g++ -std=c++20 -Wall -Wextra -Werror -o BuildProcessDemo main.cpp
// ============================================================================

#include <iostream> // Step 1 (Preprocessing): This header gets copy-pasted here

// A function declaration (the linker will look for its definition)
void demonstrateLinking();

int main()
{
    std::cout << "=== The C++ Build Process ===" << std::endl;
    std::cout << std::endl;

    // Step 1: Preprocessing
    std::cout << "STEP 1 - Preprocessing:" << std::endl;
    std::cout << "  - #include directives are resolved." << std::endl;
    std::cout << "  - Macros are expanded." << std::endl;
    std::cout << "  - The result is a 'translation unit'." << std::endl;
    std::cout << std::endl;

    // Step 2: Compilation
    std::cout << "STEP 2 - Compilation:" << std::endl;
    std::cout << "  - Each .cpp file is compiled into an object file (.o/.obj)." << std::endl;
    std::cout << "  - Syntax errors are caught here." << std::endl;
    std::cout << "  - Each file is compiled independently." << std::endl;
    std::cout << std::endl;

    // Step 3: Linking
    std::cout << "STEP 3 - Linking:" << std::endl;
    std::cout << "  - Object files are combined into an executable." << std::endl;
    std::cout << "  - External references are resolved." << std::endl;
    std::cout << "  - The Standard Library is linked here." << std::endl;
    std::cout << std::endl;

    // Step 4: Execution
    std::cout << "STEP 4 - Execution:" << std::endl;
    std::cout << "  - The OS loads the executable into memory." << std::endl;
    std::cout << "  - Execution begins at main()." << std::endl;
    std::cout << "  - This message proves all 4 steps succeeded!" << std::endl;
    std::cout << std::endl;

    // Demonstrate that the linker resolved the call to this function:
    demonstrateLinking();

    // Build terminology:
    std::cout << "--- Build Terminology ---" << std::endl;
    std::cout << "Build   = compile all modified files + link." << std::endl;
    std::cout << "Clean   = delete all compiled objects and executables." << std::endl;
    std::cout << "Rebuild = clean + build from scratch." << std::endl;
    std::cout << "Run     = execute the final program." << std::endl;

    return 0;
}

// Function definition - the linker connects the call in main() to this code.
// If this were in a separate .cpp file, the linker would still find it
// (as long as both object files are linked together).
void demonstrateLinking()
{
    std::cout << ">> demonstrateLinking() was called successfully!" << std::endl;
    std::cout << "   The linker resolved the function reference from main()." << std::endl;
    std::cout << std::endl;
}
