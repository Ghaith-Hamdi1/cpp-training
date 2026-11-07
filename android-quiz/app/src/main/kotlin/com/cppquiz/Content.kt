package com.cppquiz

/** [questionIds] are indexes into [questions], or BUILD_BASE + index into [builds]. */
data class Lesson(val title: String, val intro: List<String>, val questionIds: List<Int>)

data class Chapter(val title: String, val lessons: List<Lesson>)

val chapterOne = Chapter(
    "1. OOP: virtual functions",
    listOf(
        Lesson(
            "Dynamic dispatch",
            listOf(
                "By default C++ picks the function to call **at compile time**, from the type of the pointer or reference. This is called **static binding**.",
                "Mark a member function `virtual` and the choice moves to **run time**: the real type of the object decides. This is **dynamic binding**.",
            ),
            listOf(19, 0, 1, 1000, 2, 6, 8),
        ),
        Lesson(
            "Slicing and overriding",
            listOf(
                "Virtual dispatch needs a **pointer or a reference**. Copy a `Dog` into an `Animal` by value and the Dog part is sliced off.",
                "Once a function is virtual, every override down the chain is virtual too, even without the keyword. The call reaches the **final overrider**.",
            ),
            listOf(3, 4, 1001, 5, 7, 32),
        ),
        Lesson(
            "Override pitfalls",
            listOf(
                "`override` asks the compiler to check that you really override a base virtual. A wrong signature becomes a **compile error** instead of a silent bug.",
                "Watch for a different `const`, different parameter types, hidden names, and default arguments, which are bound at **compile time**.",
            ),
            listOf(21, 9, 10, 1002, 11, 12, 13, 22, 27, 28, 30),
        ),
        Lesson(
            "Constructors and destructors",
            listOf(
                "While a constructor or destructor runs, the object is only the class being built or torn down, so virtual calls **do not reach** derived overrides.",
                "A polymorphic base class needs a **virtual destructor**. Deleting a derived object through a base pointer without one is undefined behavior.",
            ),
            listOf(14, 15, 16, 1003, 17, 23, 26, 29, 31),
        ),
        Lesson(
            "Abstract classes and internals",
            listOf(
                "`= 0` makes a function **pure virtual** and the class **abstract**: it cannot be instantiated, only used through pointers and references.",
                "Under the hood each object holds a hidden **vptr** pointing to a per-class **vtable**. The cost is about one pointer per object and one indirect call.",
            ),
            listOf(18, 25, 1004, 20, 24, 33, 34),
        ),
    ),
)

val lockedChapters = listOf(
    "2. Inheritance and access",
    "3. Templates",
    "4. Smart pointers",
    "5. Move semantics",
)
