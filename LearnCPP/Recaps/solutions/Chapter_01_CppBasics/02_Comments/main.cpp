// Chapter 1 - Project 02: Comments
// ==================================
//
// KEY CONCEPTS:
//   - Comments are notes for humans; the compiler ignores them entirely.
//   - Single-line comment: //  (everything after // on that line is a comment)
//   - Multi-line comment:  /* ... */  (everything between the delimiters)
//   - Use comments to explain WHAT (function/program level), HOW (inside
//     functions), and WHY (at the statement level).
//   - You can "comment out" code to temporarily disable it.
//
// PITFALL:
//   - Multi-line comments CANNOT be nested.
//     /* outer /* inner */ this is NOT a comment anymore */ <-- compile error

#include <iostream>

// This function demonstrates different types of comments.
int main()
{
    // --- Single-line comments ---
    // This is a single-line comment. It starts with // and lasts until end-of-line.
    std::cout << "Single-line comments use //\n"; // Can also go at end of a statement

    // --- Multi-line comments ---
    /* This is a multi-line comment.
       It spans multiple lines.
       Everything between the delimiters is ignored. */
    std::cout << "Multi-line comments use /* ... */\n";

    // --- Commenting out code ---
    // If you want to temporarily disable code, comment it out:
    // std::cout << "This line is disabled and will not execute.\n";

    // You can also use multi-line comments to disable a block:
    /*
    std::cout << "This is disabled.\n";
    std::cout << "So is this.\n";
    */

    // --- WHY comments matter ---
    int age{25};
    // We subtract 1 because the system counts from age 0, but the UI shows from age 1.
    int displayAge{age - 1}; // WHY comment: explains the reasoning behind the logic
    std::cout << "Display age: " << displayAge << '\n';

    // --- PITFALL: Nested multi-line comments ---
    // The following would NOT compile if uncommented, because /* ... */ cannot nest:
    //
    //   /* outer comment
    //      /* inner comment */    <-- this */ ends the outer comment!
    //      this line is now code, not a comment
    //   */                        <-- this */ is a stray token - compile error
    //
    // If you need to disable a block that already contains /* */ comments,
    // use single-line comments (//) for each line instead.

    std::cout << "Comments help you (and others) understand your code!\n";

    return 0;
}
