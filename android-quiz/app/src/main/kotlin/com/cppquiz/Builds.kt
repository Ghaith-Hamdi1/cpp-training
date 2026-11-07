package com.cppquiz

/** Tap-to-build exercise: assemble [answer] from tiles ([answer] plus [extra] decoys). */
data class BuildExercise(
    val topic: String,
    val prompt: String,
    val answer: List<String>,
    val extra: List<String>,
    val explanation: String,
)


val virtualBuilds: List<BuildExercise> = listOf(
    BuildExercise(
        "Make it virtual",
        "Complete the declaration so `speak` is a **virtual** function in `Animal`.",
        listOf("virtual", "void", "speak()", "{ }"),
        listOf("static", "override"),
        "`virtual` goes in front of the return type. `override` belongs in the derived class, and `static` functions can never be virtual.",
    ),
    BuildExercise(
        "Override it",
        "Write the member in `Dog` that **overrides** `speak` and lets the compiler verify it.",
        listOf("void", "speak()", "override", "{ }"),
        listOf("virtual", "const"),
        "`override` goes after the parameter list. Adding `const` would change the signature and break the override, which is exactly what `override` helps catch.",
    ),
    BuildExercise(
        "Match the signature",
        "`Base` declares `virtual void f() const;`. Write the matching override in `Derived`.",
        listOf("void", "f()", "const", "override", ";"),
        listOf("virtual", "= 0"),
        "The override must repeat `const`, since it is part of the signature, and then `override` follows it.",
    ),
    BuildExercise(
        "Virtual destructor",
        "Declare a **virtual destructor** for `Base`, using the compiler's default body.",
        listOf("virtual", "~Base()", "= default", ";"),
        listOf("override", "{ }", "static"),
        "A polymorphic base needs `virtual ~Base()`. `= default` keeps the normal destruction behavior without writing a body.",
    ),
    BuildExercise(
        "Pure virtual",
        "Declare a **pure virtual** function `area` that returns `double` and does not modify the object.",
        listOf("virtual", "double", "area()", "const", "= 0", ";"),
        listOf("override", "void"),
        "`= 0` after `const` makes the function pure virtual, so the class becomes abstract.",
    ),
)
