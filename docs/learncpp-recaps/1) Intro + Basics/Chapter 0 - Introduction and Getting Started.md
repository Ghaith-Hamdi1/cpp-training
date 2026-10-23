# Chapter 0 Recap - Introduction and Getting Started

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- C++ is a compiled language: you write source code, compile it, then run an executable.
- Programs are built in stages: compile each source file, then link everything together.
- You should learn with modern C++ (at least C++17), not legacy C-style habits.
- Use an IDE and compiler setup that helps you catch mistakes early.
- Turn warnings up and treat warnings as errors from day one.
- Disable compiler extensions so your code stays portable and standard-compliant.
- Use Debug while developing; use Release when benchmarking or shipping.
- Follow an explicit workflow: define -> design -> code -> compile -> link -> test -> debug.

### 3 Tiny Examples

1. Minimal first program:

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    return 0;
}
```

2. Build pipeline from terminal:

```cpp
// Compile only:
g++ -c main.cpp -o main.o

// Link object file(s):
g++ main.o -o myProgram

// Compile + link in one command:
g++ main.cpp -o myProgram
```

3. Confirm active standard:

```cpp
std::cout << "C++ standard: " << __cplusplus << '\n';
```

### 3 Common Mistakes

- Missing `#include <iostream>` when using `std::cout` or `std::cin`.
- Leaving defaults enabled (extensions on, low warnings, old language standard).
- Building/running the wrong project or wrong configuration (Debug vs Release).

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Computer program**: a sequence of instructions that tells a computer what to do.
- **Programming language**: a language for writing computer instructions.
- **Machine code**: binary instructions a CPU executes natively; architecture-specific.
- **Assembly language**: low-level human-readable code translated by an assembler.
- **High-level language**: language that abstracts hardware details (e.g., C++).
- **Compiler**: translates source code to machine code/object files before execution.
- **Interpreter**: executes source line-by-line at runtime.
- **Source code**: human-readable code you write.
- **Object file**: intermediate compiled output (`.o`/`.obj`) per translation unit.
- **Linker**: combines object files and libraries into a final executable.
- **Build**: compile + link process.
- **IDE**: integrated environment with editor/build/debug tools.
- **Build configuration**: a set of project settings, commonly Debug or Release.
- **Compiler extensions**: non-standard compiler-specific features.
- **Language standard**: version of the C++ spec (C++11/14/17/20/23).
- **Portability**: ability to compile/run on different platforms without code changes.

### Section-by-Section Detail

#### 0.1 Introduction to These Tutorials

- The tutorials assume **no prior programming experience** and build concepts incrementally.
- Lessons are intended to be followed **in order** each builds on the previous one.
- Focus is on **modern C++ (C++17+)**, not legacy C-with-classes style.
- **Type examples by hand**, experiment with changes, and complete every quiz for retention.
- Avoid skipping chapters missing one concept will cascade into confusion in later lessons.

> **Tip:** Active engagement (typing code, predicting output, debugging) beats passive reading by a wide margin.

#### 0.2 Introduction to Programs and Programming Languages

Programs run on hardware (CPU, memory) that natively understands only **machine code** raw binary instructions specific to a CPU architecture. For example, the x86 instruction `10110000 01100001` means "put value `97` into register `al`".

**Assembly language** provides a human-readable mapping to machine code using mnemonics:

```asm
mov al, 0x61    ; same as the binary instruction above  move 97 into register al
```

Assembly is still architecture-specific and requires detailed hardware knowledge. A program written for x86 won't run on ARM.

**High-level languages** (C, C++, Java, Python) abstract hardware details:

```cpp
a = 97;    // one line replaces several assembly instructions
```

**Compilation vs. Interpretation:**

| Aspect          | Compiled (C++)                              | Interpreted (Python, JS)                   |
| --------------- | ------------------------------------------- | ------------------------------------------ |
| Translation     | Entire source machine code before execution | Executes line-by-line at runtime           |
| Speed           | Fast native machine code                    | Slower overhead of runtime translation     |
| Error detection | Many errors caught at compile time          | Errors found only when reached at runtime  |
| Distribution    | Standalone executable                       | Requires interpreter installed             |
| Portability     | Recompile for each platform                 | Same source runs anywhere with interpreter |

**Key concepts:**

- **Portability:** the ability to run the same code on different platforms with minimal changes.
- **Porting:** modifying a program to work on a different platform.
- C++ is sometimes called a "mid-level" language it provides high-level abstractions while still allowing low-level hardware access when needed.

> **Best Practice:** Avoid platform-specific code to maximize portability.

#### 0.3 Introduction to C and C++

**History:**

- **C** was developed in 1972 by Dennis Ritchie at Bell Labs, originally for Unix.
- **C++** was created by Bjarne Stroustrup starting in 1979 as "C with Classes", adding object-oriented features to C. It was renamed C++ in 1982.
- C++ has evolved through ISO standards: **C++11** (major modernization), **C++14** (refinements), **C++17** (significant additions), **C++20** (major update with concepts, ranges, coroutines), **C++23** (latest finalized standard).

**C++ design philosophy "trust the programmer":**

- C++ gives the programmer maximum control and performance at the cost of requiring more discipline.
- The language will not prevent you from doing dangerous things (e.g., accessing invalid memory) it trusts you know what you're doing.
- This philosophy produces very fast programs but means you must be more careful about correctness.

**C++ strengths:** performance-critical applications, operating systems, game engines, embedded systems, finance.
**C++ challenges:** steeper learning curve, manual resource management (though modern C++ mitigates this), complex compilation.

#### 0.4 Introduction to C++ Development

The typical development workflow follows these steps:

| Step           | Action                                                | Output                        |
| -------------- | ----------------------------------------------------- | ----------------------------- |
| 1. **Define**  | Write a clear problem statement                       | Requirements                  |
| 2. **Design**  | Plan the solution structure                           | Pseudocode / architecture     |
| 3. **Write**   | Author source code in `.cpp` / `.h` files             | Source files                  |
| 4. **Compile** | Compiler checks syntax and translates to machine code | Object files (`.o` / `.obj`)  |
| 5. **Link**    | Linker combines objects + libraries                   | Executable                    |
| 6. **Test**    | Run the program and verify behavior                   | Test results                  |
| 7. **Debug**   | Find and fix problems                                 | Corrected code back to step 3 |

**Source file naming conventions:**

- C++ source files typically use `.cpp` extension (also `.cc`, `.cxx` on some systems).
- Header files use `.h`, `.hpp`, or `.hxx`.
- Convention: name the file containing `main()` as `main.cpp`.

**Key insight:** A large fraction of real-world work is **maintenance** reading, understanding, and modifying existing code. Writing readable, modular code from the start saves significant time later.

Related:

- [Chapter 3 Debugging C++ Programs](<../2) Fundamentals 1/Chapter 3 - Debugging C++ Programs.md>)
- [10_DesignBeforeCode](../solutions/Chapter_00_Introduction/10_DesignBeforeCode)

#### 0.5 Compiler, Linker, and Libraries

The build process has two main stages:

**1. Compilation** each `.cpp` file is compiled independently as a **translation unit**:

- The preprocessor handles `#include` directives, macros, and conditional compilation.
- The compiler checks syntax, enforces type rules, and translates to machine code.
- Output: one **object file** per source file (`.o` on Linux/Mac, `.obj` on Windows).

**2. Linking** the linker combines everything:

- Resolves cross-file references (e.g., a function declared in one file and defined in another).
- Links in library code (standard library, third-party libraries).
- Produces the final **executable**.

```
               main.cpp    main.o
Source files   math.cpp    math.o   Linker  myProgram(.exe)
               io.cpp      io.o
                                           Standard Library
```

**Common linker errors:**

- **"Unresolved external symbol"** / **"Undefined reference"**: a function or variable was declared but never defined, or the file containing its definition wasn't included in the build.

**Libraries:**

- **Standard Library** (`<iostream>`, `<string>`, `<vector>`, `<algorithm>`, etc.) ships with every compliant C++ compiler; linked automatically.
- **Third-party Libraries** must be downloaded, configured, and explicitly linked (e.g., Boost, SDL, SFML).

Related:

- [Chapter 2 C++ Basics: Functions and Files](Chapter%202%20-%20C++%20Basics%20Functions%20and%20Files.md)
- [05_BuildProcessDemo](../solutions/Chapter_00_Introduction/05_BuildProcessDemo)

#### 0.6 Installing an IDE

An **IDE (Integrated Development Environment)** bundles a code editor, build system, and debugger into one tool. Key features include:

- Line numbering and syntax highlighting
- Code completion and integrated help
- Build/run/debug workflow in one click
- Plugin support for customization

**Recommended IDEs:**

| IDE                          | Platform      | Compiler           | Notes                                                                   |
| ---------------------------- | ------------- | ------------------ | ----------------------------------------------------------------------- |
| Visual Studio Community 2022 | Windows       | MSVC               | Best Windows experience; select "Desktop development with C++" workload |
| Code::Blocks                 | Windows/Linux | GCC (MinGW)        | Free, open-source; update MinGW for C++20 support                       |
| VS Code + C++ extension      | All platforms | Any (manual setup) | Powerful but harder to configure not recommended for beginners          |

**Minimum compiler versions for C++17:** GCC/G++ 7, Clang++ 8, Visual Studio 2017 (15.7).

> **Best Practice:** Install the newest compiler version available and ensure it supports at least C++17.

**Web-based alternatives** (temporary, for simple exercises): [Wandbox](https://wandbox.org/), [Godbolt Compiler Explorer](https://godbolt.org/), [TutorialsPoint](https://www.tutorialspoint.com/compile_cpp_online.php).

#### 0.7 Compiling Your First Program

- Create a **console project**, not a GUI application.
- Keep **one program per project** to avoid multiple `main()` linker conflicts.
- **Build terminology:**
  - **Compile:** translate source object files (checks syntax).
  - **Build:** compile + link into an executable.
  - **Clean:** remove all generated files (objects, executables).
  - **Rebuild:** clean followed by build.
  - **Run/Start:** execute the built program.
- Always **save files before building** and verify the correct startup project is selected.

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
```

Related:

- [01_HelloWorld](../solutions/Chapter_00_Introduction/01_HelloWorld)
- [02_ProgramStructure](../solutions/Chapter_00_Introduction/02_ProgramStructure)

#### 0.8 Common Beginner Problems

| Problem                    | Symptom                            | Fix                                                                             |
| -------------------------- | ---------------------------------- | ------------------------------------------------------------------------------- |
| Console closes immediately | Output flashes and disappears      | Add `std::cin.get();` before `return`, or run from terminal                     |
| Missing `#include`         | `'cout' is not a member of 'std'`  | Add `#include <iostream>`                                                       |
| Missing `std::`            | `'cout' was not declared`          | Use `std::cout`, not bare `cout`                                                |
| Confusing characters       | Code looks right but won't compile | Check `l` vs `1`, `O` vs `0`, `"` vs `"` (smart quotes)                         |
| Precompiled headers (MSVC) | `fatal error C1010`                | Add `#include "pch.h"` as the first include, or disable PCH in project settings |

**Cascading errors:** A single real error (e.g., missing semicolon on line 5) can cause the compiler to report dozens of errors on subsequent lines. **Always fix the first error first**, then recompile many later errors will disappear.

> **Tip:** Read compiler error messages carefully. Start from the first error. The line number may not be exact but will be close.

Related:

- [08_CommonMistakes](../solutions/Chapter_00_Introduction/08_CommonMistakes)
- [09_ConsoleWindowFix](../solutions/Chapter_00_Introduction/09_ConsoleWindowFix)

#### 0.9 Build Configurations

| Configuration | Optimization               | Debug Symbols       | Use Case                                                 |
| ------------- | -------------------------- | ------------------- | -------------------------------------------------------- |
| **Debug**     | None (`-O0` / `/Od`)       | Full                | Development, stepping through code, inspecting variables |
| **Release**   | High (`-O2`/`-O3` / `/O2`) | Stripped or minimal | Benchmarking, shipping, performance testing              |

- **Use Debug by default** while learning and developing it preserves your code structure for the debugger.
- **Use Release** only when measuring performance or distributing your program.
- Optimization can reorder, inline, or eliminate code, making debugging unpredictable.
- Some bugs only manifest under optimization (especially undefined behavior) this does not mean Release is "buggier", it means the original code had latent issues.

#### 0.10 Compiler Extensions

Compiler extensions are **non-standard features** that specific compilers add beyond the C++ specification. Code relying on extensions may compile on your compiler but fail on others.

**Why disable them:**

- Forces you to write **portable, standards-compliant** code.
- Prevents accidental dependence on vendor-specific behavior.
- Ensures your code works across GCC, Clang, and MSVC.

**Flags to disable extensions:**

| Compiler  | Flag               | Effect                             |
| --------- | ------------------ | ---------------------------------- |
| MSVC      | `/permissive-`     | Strict conformance mode            |
| GCC/Clang | `-pedantic-errors` | Reject non-standard code as errors |

> **Best Practice:** Always disable extensions when learning. This teaches you what is real C++ vs. what is a compiler-specific shortcut.

#### 0.11 Warning and Error Levels

Default compiler warning levels are too lenient they miss many real issues. Raising warning levels catches problems like uninitialized variables, implicit conversions, and unreachable code.

**Recommended flags:**

| Compiler  | Warnings                                       | Treat as Errors |
| --------- | ---------------------------------------------- | --------------- |
| MSVC      | `/W4`                                          | `/WX`           |
| GCC/Clang | `-Wall -Wextra -Wconversion -Wsign-conversion` | `-Werror`       |

**What the GCC/Clang flags mean:**

- `-Wall`: enables most common warnings (despite the name, not literally "all").
- `-Wextra`: additional useful warnings not covered by `-Wall`.
- `-Wconversion`: warns on implicit type conversions that may lose data.
- `-Wsign-conversion`: warns on sign changes (signed unsigned).
- `-Werror`: treats all warnings as errors build fails until you fix them.

**IDE configuration:**

- **Visual Studio:** Project Properties C/C++ General Warning Level.
- **Code::Blocks:** Settings Compiler Compiler Settings Warnings tab.

> **Best Practice:** Fix warnings immediately. Warning-free code is not guaranteed bug-free, but code with many warnings is high-risk.

Related:

- [07_WarningsDemo](../solutions/Chapter_00_Introduction/07_WarningsDemo)

#### 0.12 Choosing a Language Standard

C++ standards are named by publication year. Each adds new features and improvements:

| Standard | Year | Key Additions                                                            |
| -------- | ---- | ------------------------------------------------------------------------ |
| C++11    | 2011 | `auto`, range-for, lambdas, `nullptr`, move semantics, smart pointers    |
| C++14    | 2014 | Generic lambdas, `std::make_unique`, relaxed `constexpr`                 |
| C++17    | 2017 | Structured bindings, `if constexpr`, `std::optional`, `std::string_view` |
| C++20    | 2020 | Concepts, ranges, coroutines, modules, `<=>` (spaceship operator)        |
| C++23    | 2023 | `std::print`, more `constexpr`, `std::expected`, `std::mdspan`           |

**Set the standard explicitly** do not rely on compiler defaults:

| Compiler  | Flag Examples                                |
| --------- | -------------------------------------------- |
| MSVC      | `/std:c++17`, `/std:c++20`, `/std:c++latest` |
| GCC/Clang | `-std=c++17`, `-std=c++20`, `-std=c++23`     |

**IDE-specific configuration:**

- **Visual Studio 2022:** Project Properties C/C++ Language "C++ Language Standard". Must be set for **each new project**.
- **Code::Blocks:** Settings Compiler Global Settings find `-std=c++XX` checkbox. Applies **globally** to all new projects.
- **VS Code:** Add flag in `tasks.json` `"args"` section; set IntelliSense in `settings.json`: `"C_Cpp.default.cppStandard": "c++20"`.

> **Warning:** Some compilers offer "experimental" support for non-finalized standards these features may be incomplete or buggy. When changing language standard, apply to **all build configurations** (Debug and Release).

> **Best Practice:** Use C++17 or later for new projects. This tutorial targets C++17 with some C++20/C++23 content.

Related:

- [06_LanguageStandardCheck](../solutions/Chapter_00_Introduction/06_LanguageStandardCheck)

#### 0.13 What Language Standard Is My Compiler Using?

You can detect the active standard at runtime using the `__cplusplus` predefined macro:

| Macro Value | Standard  |
| ----------- | --------- |
| `199711L`   | Pre-C++11 |
| `201103L`   | C++11     |
| `201402L`   | C++14     |
| `201703L`   | C++17     |
| `202002L`   | C++20     |
| `202302L`   | C++23     |

**Detection program:**

```cpp
#include <iostream>

const int numStandards = 7;
const long stdCode[numStandards] = { 199711L, 201103L, 201402L, 201703L, 202002L, 202302L, 202612L };
const char* stdName[numStandards] = { "Pre-C++11", "C++11", "C++14", "C++17", "C++20", "C++23", "C++26" };

long getCPPStandard()
{
#if defined (_MSVC_LANG)
    return _MSVC_LANG;
#elif defined (_MSC_VER)
    return -1;
#else
    return __cplusplus;
#endif
}

int main()
{
    long standard = getCPPStandard();
    if (standard == -1)
    {
        std::cout << "Error: Unable to determine your language standard.\n";
        return 0;
    }

    for (int i = 0; i < numStandards; ++i)
    {
        if (standard == stdCode[i])
        {
            std::cout << "Your compiler is using " << stdName[i]
                << " (language standard code " << standard << "L)\n";
            break;
        }
        if (standard < stdCode[i])
        {
            std::cout << "Your compiler is using a preview/pre-release of " << stdName[i]
                << " (language standard code " << standard << "L)\n";
            break;
        }
    }
    return 0;
}
```

**MSVC quirk:** `__cplusplus` historically always reported `199711L` regardless of the actual standard. Use `_MSVC_LANG` as a fallback, or enable `/Zc:__cplusplus` in project settings. If the output is unexpected, verify the language standard is set correctly in **both** Debug and Release configurations.

### Edge Cases and Caveats

- C++ supports dangerous operations by design; discipline matters.
- Optimization can expose undefined behavior differently across builds.
- Warning-free code is not guaranteed bug-free, but warning-heavy code is high risk.
- Non-standard extensions can silently lock your code to one toolchain.
- Misconfigured project templates (GUI vs console, PCH on by default) cause misleading errors.

### Hands-On Code Projects

| #   | Project                                                                                    | Concept                                                                    |
| --- | ------------------------------------------------------------------------------------------ | -------------------------------------------------------------------------- |
| 01  | [01_HelloWorld](../solutions/Chapter_00_Introduction/01_HelloWorld)                       | "Hello, world!" with `std::cout`; confirms build pipeline works            |
| 02  | [02_ProgramStructure](../solutions/Chapter_00_Introduction/02_ProgramStructure)           | Anatomy of a C++ program: `main()`, return statements, statement structure |
| 03  | [03_CommentStyles](../solutions/Chapter_00_Introduction/03_CommentStyles)                 | Single-line (`//`) and multi-line (`/* */`) comment syntax                 |
| 04  | [04_IOStreamBasics](../solutions/Chapter_00_Introduction/04_IOStreamBasics)               | `std::cout`, `std::cin`, `<<`, `>>`, `'\n'` vs `std::endl`                 |
| 05  | [05_BuildProcessDemo](../solutions/Chapter_00_Introduction/05_BuildProcessDemo)           | Compile -> link -> execute pipeline with multiple source files             |
| 06  | [06_LanguageStandardCheck](../solutions/Chapter_00_Introduction/06_LanguageStandardCheck) | Prints active C++ standard via `__cplusplus` / `_MSVC_LANG`                |
| 07  | [07_WarningsDemo](../solutions/Chapter_00_Introduction/07_WarningsDemo)                   | Code that compiles but triggers warnings                                   |
| 08  | [08_CommonMistakes](../solutions/Chapter_00_Introduction/08_CommonMistakes)               | Missing includes, missing `std::`, confusing characters                    |
| 09  | [09_ConsoleWindowFix](../solutions/Chapter_00_Introduction/09_ConsoleWindowFix)           | Keeping console window open with `std::cin.get()`                          |
| 10  | [10_DesignBeforeCode](../solutions/Chapter_00_Introduction/10_DesignBeforeCode)           | Development cycle: problem -> design -> implement -> test                  |

### Quick Reference

| Topic                        | Details                                                                   |
| ---------------------------- | ------------------------------------------------------------------------- |
| Minimal program              | `int main() { return 0; }`                                                |
| Hello World                  | `#include <iostream>` then `std::cout << "Hello, world!\n";`              |
| Input                        | `std::cin >> variable;`                                                   |
| Include for I/O              | `#include <iostream>` is required for `std::cout` / `std::cin`            |
| Newline                      | Prefer `'\n'` over `std::endl` for normal output                          |
| MSVC disable extensions      | `/permissive-`                                                            |
| GCC/Clang disable extensions | `-pedantic-errors`                                                        |
| MSVC warnings                | `/W4` and `/WX`                                                           |
| GCC/Clang warnings           | `-Wall -Wextra -Wconversion -Wsign-conversion -Werror`                    |
| MSVC standard                | `/std:c++17` or `/std:c++20`                                              |
| GCC/Clang standard           | `-std=c++17` or `-std=c++20`                                              |
| Check active standard        | inspect `__cplusplus` (and `_MSVC_LANG` on MSVC when needed)              |
| Debug build                  | low optimization, full symbols                                            |
| Release build                | optimized binary, less debug visibility                                   |
| File naming                  | primary source file convention: `main.cpp`                                |
| Build terms                  | Build = compile + link, Clean = remove artifacts, Rebuild = clean + build |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between a compiler and an interpreter? Which one does C++ use?

<details>
<summary>Show answer</summary>

**Direct answer:** A compiler translates the entire source code into machine code (an executable) before the program runs, catching errors at compile time. An interpreter executes source code line-by-line at runtime, without producing a standalone executable. C++ uses a compiler.

**Detailed explanation:**
A compiler reads all of your source files, translates them into machine code object files, and then a linker combines those objects into a single executable binary. Because compilation happens before execution, many errors (syntax errors, type mismatches) are caught before the program ever runs, and the resulting executable runs at native speed. An interpreter, by contrast, reads and executes code one statement at a time - this is more flexible (no separate build step) but generally slower and catches errors only when the faulty line is reached. C++ is a compiled language, which is why you must compile and link before you can run your program.

</details>

2. What does each stage produce: compile, link, run?

<details>
<summary>Show answer</summary>

**Direct answer:** Compiling produces an object file (`.o`/`.obj`) for each source file. Linking combines all object files and libraries into a single executable. Running executes that executable on the CPU.

**Detailed explanation:**
Each `.cpp` source file is an independent **translation unit**. The compiler translates each one into an object file containing machine code and symbolic references to external identifiers. The linker then resolves those cross-file references, connects calls to the standard library (e.g., `<iostream>`), and produces a final executable binary. If the linker cannot find a definition for a declared identifier, you get an "unresolved external symbol" or "undefined reference" error. Running the executable loads it into memory and the CPU begins executing from `main()`.

</details>

3. Why should Debug be your default while learning and building new features?

<details>
<summary>Show answer</summary>

**Direct answer:** Debug builds use low optimization and include full debug symbols, which makes it much easier to step through code, inspect variables, and diagnose bugs. Release builds optimize aggressively, which can reorder or eliminate code and make debugging extremely difficult.

**Detailed explanation:**
A Debug build (`-O0`/`/Od`) keeps your code structure close to what you wrote, includes symbol information for the debugger, and leaves runtime checks in place. This makes stepping through code, setting breakpoints, and inspecting variable values straightforward. A Release build (`-O2`/`-O3`/`/O2`) optimizes for speed - the compiler may inline functions, eliminate unused variables, or reorder statements, which means the executing code no longer maps neatly to your source. Optimization can also mask or expose undefined behavior differently, making bugs appear and disappear unpredictably. Use Debug for development and testing; use Release only for performance benchmarking or shipping.

</details>

4. Why disable compiler extensions? Which flags do that in MSVC and GCC/Clang?

<details>
<summary>Show answer</summary>

**Direct answer:** Compiler extensions allow non-standard C++ code that may compile on one compiler but fail on another, reducing portability. You disable them with `/permissive-` on MSVC and `-pedantic-errors` on GCC/Clang.

**Detailed explanation:**
Each compiler vendor adds their own language extensions (extra syntax, relaxed rules) on top of the C++ standard. If you rely on these extensions, your code becomes tied to that specific compiler and may not compile elsewhere. Disabling extensions forces you to write standards-compliant code from the start, which is portable across compilers and platforms. The flags are:

- **MSVC:** `/permissive-` (strict conformance mode)
- **GCC/Clang:** `-pedantic-errors` (reject non-standard code as errors)

You should also set an explicit language standard (e.g., `/std:c++17` or `-std=c++17`) rather than relying on the compiler's default.

</details>

5. Which warning flags are recommended, and why should warnings be treated as errors?

<details>
<summary>Show answer</summary>

**Direct answer:** For MSVC, use `/W4` (high warning level) and `/WX` (treat warnings as errors). For GCC/Clang, use `-Wall -Wextra -Wconversion -Wsign-conversion -Werror`. Treating warnings as errors forces you to fix potential issues immediately, preventing "warning debt" from accumulating into real bugs.

**Detailed explanation:**
Default compiler warning levels are often too lenient and miss many common mistakes. Higher warning levels catch issues like uninitialized variables, implicit narrowing conversions, sign-conversion problems, and unreachable code. Treating warnings as errors (`/WX` or `-Werror`) prevents you from ignoring these warnings - you must fix them before the build succeeds. This discipline is valuable because many warnings point to genuine bugs or code that will behave unexpectedly. Warning-free code is not guaranteed bug-free, but code with many warnings is high-risk.

</details>

6. What does `__cplusplus` tell you, and why might `_MSVC_LANG` matter on MSVC?

<details>
<summary>Show answer</summary>

**Direct answer:** `__cplusplus` is a predefined macro that reports the active C++ standard as a `long` value (e.g., `201703L` for C++17, `202002L` for C++20). On MSVC, `__cplusplus` historically always reported `199711L` regardless of the actual standard unless `/Zc:__cplusplus` was set, so `_MSVC_LANG` is a more reliable fallback to check the actual standard in use.

**Detailed explanation:**
You can print `__cplusplus` at runtime to verify which language standard your compiler is actually using:

```cpp
std::cout << __cplusplus << '\n';
```

Common values: `201402L` (C++14), `201703L` (C++17), `202002L` (C++20), `202302L` (C++23). On MSVC, due to a long-standing conformance issue, `__cplusplus` would report `199711L` (the C++98 value) even when compiling with `/std:c++17`. The macro `_MSVC_LANG` was introduced as a workaround and correctly reflects the configured standard. Modern MSVC versions fix this if `/Zc:__cplusplus` is enabled. If your output is unexpected, also verify you're checking the correct build configuration (Debug vs Release may have different settings).

</details>

7. Why should each separate program have its own project?

<details>
<summary>Show answer</summary>

**Direct answer:** Each C++ program needs exactly one `main()` function. If you put multiple programs (each with their own `main()`) in the same project, the linker will report a "multiple definition of main" error because it cannot determine which entry point to use.

**Detailed explanation:**
The linker expects a single `main()` function as the program's entry point. When two or more source files in the same project each define `main()`, the linker sees duplicate definitions and produces an error. Keeping each program in its own project (or build target) avoids this conflict and also keeps your build clean - you compile and run only the code you intend to. This also prevents accidentally linking unrelated object files together.

</details>

8. If you see 20 compiler errors at once, which one should you fix first, and why?

<details>
<summary>Show answer</summary>

**Direct answer:** Always fix the very first error reported by the compiler (the one on the lowest line number). A single real error - such as a missing semicolon, missing `#include`, or missing `std::` prefix - often causes the compiler to misparse everything after it, generating many cascading errors that disappear once the first one is fixed.

**Detailed explanation:**
Compilers process code top-to-bottom. When they encounter an error, they try to recover and continue parsing, but their assumptions after the error are often wrong. For example, a missing semicolon on line 5 can confuse the parser so badly that it reports errors on lines 6, 7, 10, 15, and beyond - none of which are real problems. The fix is simple: address the first error, recompile, and see how many errors remain. Often, fixing one or two real errors eliminates dozens of cascading ones. This is why you should always start from the top of the error list.

</details>

9. What is machine code, and why can't you write programs directly in it?

<details>
<summary>Show answer</summary>

**Direct answer:** Machine code is the binary instruction set that a CPU executes natively. Each CPU architecture (x86, ARM, etc.) has its own machine code format. You _can_ write programs in it, but it is extremely tedious, error-prone, and not portable - hence the need for higher-level languages like C++ that abstract away hardware details.

**Detailed explanation:**
Machine code consists of raw binary values that directly control the CPU's operations. It is architecture-specific: code written for an x86 processor will not run on ARM hardware. Assembly language provides a human-readable representation of machine code, but it is still architecture-specific and low-level. C++ is a high-level compiled language that lets you write portable, readable code which the compiler then translates into the appropriate machine code for the target architecture.

</details>

10. Describe the typical C++ development workflow from start to finish.

<details>
<summary>Show answer</summary>

**Direct answer:** The workflow is: **define** the problem → **design** the solution → **write** the source code → **compile** each source file into object files → **link** the object files into an executable → **test** the program → **debug** any issues found. This cycle repeats as you add features or fix bugs.

**Detailed explanation:**
Good development starts with a clear problem statement and solution design before writing any code. Once you start coding, you should work incrementally - write a small piece, compile, and test it before moving on. The compile stage translates `.cpp` files into object files; the link stage combines them into an executable. Testing reveals bugs, which you then diagnose using debugging tools (breakpoints, stepping, variable inspection). A large fraction of real-world work is maintenance, so writing clear, readable, modular code from the start saves significant time later.

</details>
