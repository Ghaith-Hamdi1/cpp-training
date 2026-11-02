# Move semantics, references and value categories

[Back to all topics](README.md)

159 questions, 3 with a carousel already.

Source: the 5,000 most voted questions tagged `c++` (the first 100 pages of 50 at <https://stackoverflow.com/questions/tagged/c%2b%2b?tab=votes&pagesize=50>), fetched on 2026-11-02 through the Stack Exchange API, sorted by votes. The lowest score included is 54 votes. Ties within the same score can be in a slightly different order than the website.

| Rank | Votes | Question | |
|---:|---:|---|---|
| 4 | 3,960 | [What are the differences between a pointer variable and a reference variable?](https://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable) |  |
| 11 | 2,562 | [What is The Rule of Three?](https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three) | ✅ #13 |
| 14 | 2,427 | [What is the copy-and-swap idiom?](https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom) |  |
| 22 | 2,147 | [What is move semantics?](https://stackoverflow.com/questions/3106110/what-is-move-semantics) |  |
| 42 | 1,248 | [push_back vs emplace_back](https://stackoverflow.com/questions/4303513/push-back-vs-emplace-back) |  |
| 44 | 1,236 | [What is std::move(), and when should it be used?](https://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used) | ✅ #14 |
| 49 | 1,138 | [What does T&& (double ampersand) mean in C++11?](https://stackoverflow.com/questions/5481539/what-does-t-double-ampersand-mean-in-c11) | ✅ #15, #17 |
| 143 | 605 | [What are the main purposes of std::forward and which problems does it solve?](https://stackoverflow.com/questions/3582001/what-are-the-main-purposes-of-stdforward-and-which-problems-does-it-solve) |  |
| 157 | 562 | [What are copy elision and return value optimization?](https://stackoverflow.com/questions/12953127/what-are-copy-elision-and-return-value-optimization) |  |
| 176 | 531 | [C++11 rvalues and move semantics with return statement](https://stackoverflow.com/questions/4986673/c11-rvalues-and-move-semantics-with-return-statement) |  |
| 177 | 531 | [Why can you return a std::unique_ptr without std::move?](https://stackoverflow.com/questions/4316727/why-can-you-return-a-stdunique-ptr-without-stdmove) |  |
| 209 | 467 | [When should I use pointers instead of references in API-design?](https://stackoverflow.com/questions/7058339/when-should-i-use-pointers-instead-of-references-in-api-design) |  |
| 243 | 419 | [Is the practice of returning a C++ reference variable evil?](https://stackoverflow.com/questions/752658/is-the-practice-of-returning-a-c-reference-variable-evil) |  |
| 321 | 351 | [Rule-of-Three becomes Rule-of-Five with C++11?](https://stackoverflow.com/questions/4782757/rule-of-three-becomes-rule-of-five-with-c11) |  |
| 391 | 311 | [Range based loop: get item by value or reference to const?](https://stackoverflow.com/questions/15176104/range-based-loop-get-item-by-value-or-reference-to-const) |  |
| 412 | 300 | [Are there benefits of passing by pointer over passing by reference in C++?](https://stackoverflow.com/questions/334856/are-there-benefits-of-passing-by-pointer-over-passing-by-reference-in-c) |  |
| 466 | 277 | [Should I use a pointer or a reference to remotely assign a variable?](https://stackoverflow.com/questions/114180/should-i-use-a-pointer-or-a-reference-to-remotely-assign-a-variable) |  |
| 472 | 275 | [How should I pass objects to functions?](https://stackoverflow.com/questions/2139224/how-should-i-pass-objects-to-functions) |  |
| 476 | 273 | [What is the "rvalue reference for *this" proposal?](https://stackoverflow.com/questions/8610571/what-is-the-rvalue-reference-for-this-proposal) |  |
| 493 | 265 | [How come a non-const reference cannot bind to a temporary object?](https://stackoverflow.com/questions/1565600/how-come-a-non-const-reference-cannot-bind-to-a-temporary-object) |  |
| 495 | 263 | [Advantages of pass-by-value and std::move over pass-by-reference](https://stackoverflow.com/questions/51705967/advantages-of-pass-by-value-and-stdmove-over-pass-by-reference) |  |
| 561 | 242 | [Is it better in C++ to pass by value or pass by reference-to-const?](https://stackoverflow.com/questions/270408/is-it-better-in-c-to-pass-by-value-or-pass-by-reference-to-const) |  |
| 604 | 230 | [Return value optimization or move in C++11](https://stackoverflow.com/questions/17473753/return-value-optimization-or-move-in-c11) |  |
| 607 | 229 | [make_unique and perfect forwarding](https://stackoverflow.com/questions/7038357/make-unique-and-perfect-forwarding) |  |
| 662 | 217 | [What is the result type of '?:' (ternary/conditional operator)?](https://stackoverflow.com/questions/8535226/what-is-the-result-type-of-ternary-conditional-operator) |  |
| 668 | 216 | [Disable copy constructor](https://stackoverflow.com/questions/6077143/disable-copy-constructor) |  |
| 698 | 209 | [Why is 'this' a pointer and not a reference?](https://stackoverflow.com/questions/645994/why-is-this-a-pointer-and-not-a-reference) |  |
| 711 | 207 | [What is the difference between std::move and std::forward?](https://stackoverflow.com/questions/9671749/what-is-the-difference-between-stdmove-and-stdforward) |  |
| 734 | 203 | [Does a const reference class member prolong the life of a temporary?](https://stackoverflow.com/questions/2784262/does-a-const-reference-class-member-prolong-the-life-of-a-temporary) |  |
| 742 | 201 | [C++: const reference, before vs after type-specifier](https://stackoverflow.com/questions/3694630/c-const-reference-before-vs-after-type-specifier) |  |
| 744 | 201 | [Why can we use `std::move` on a `const` object?](https://stackoverflow.com/questions/28595117/why-can-we-use-stdmove-on-a-const-object) |  |
| 809 | 192 | [Why are arrays of references illegal?](https://stackoverflow.com/questions/1164266/why-are-arrays-of-references-illegal) |  |
| 847 | 187 | [When should std::move be used on a function return value?](https://stackoverflow.com/questions/14856344/when-should-stdmove-be-used-on-a-function-return-value) |  |
| 860 | 184 | [How does std::forward work, especially when passing lvalue/rvalue references?](https://stackoverflow.com/questions/8526598/how-does-stdforward-work-especially-when-passing-lvalue-rvalue-references) |  |
| 902 | 180 | [What is the advantage of using forwarding references in range-based for loops?](https://stackoverflow.com/questions/13130708/what-is-the-advantage-of-using-forwarding-references-in-range-based-for-loops) |  |
| 922 | 176 | [C++ error: undefined reference to 'clock_gettime' and 'clock_settime'](https://stackoverflow.com/questions/2418157/c-error-undefined-reference-to-clock-gettime-and-clock-settime) |  |
| 958 | 172 | [What can I do with a moved-from object?](https://stackoverflow.com/questions/7027523/what-can-i-do-with-a-moved-from-object) |  |
| 1014 | 166 | [Conditions for automatic generation of default/copy/move ctor and copy/move assignment operator?](https://stackoverflow.com/questions/4943958/conditions-for-automatic-generation-of-default-copy-move-ctor-and-copy-move-assi) |  |
| 1016 | 166 | [How can I make my class immune to the "auto value = copy of proxy" landmine in C++?](https://stackoverflow.com/questions/66930450/how-can-i-make-my-class-immune-to-the-auto-value-copy-of-proxy-landmine-in-c) |  |
| 1020 | 165 | [Should I prefer pointers or references as data members?](https://stackoverflow.com/questions/892133/should-i-prefer-pointers-or-references-as-data-members) |  |
| 1026 | 164 | [Is returning by rvalue reference more efficient?](https://stackoverflow.com/questions/1116641/is-returning-by-rvalue-reference-more-efficient) |  |
| 1091 | 158 | [How would one call std::forward on all arguments in a variadic function?](https://stackoverflow.com/questions/2821223/how-would-one-call-stdforward-on-all-arguments-in-a-variadic-function) |  |
| 1114 | 156 | [Is a null reference possible?](https://stackoverflow.com/questions/4364536/is-a-null-reference-possible) |  |
| 1115 | 156 | [Move assignment operator and `if (this != &rhs)`](https://stackoverflow.com/questions/9322174/move-assignment-operator-and-if-this-rhs) |  |
| 1124 | 155 | [Passing references to pointers in C++](https://stackoverflow.com/questions/823426/passing-references-to-pointers-in-c) |  |
| 1163 | 152 | [Default value to a parameter while passing by reference in C++](https://stackoverflow.com/questions/1059630/default-value-to-a-parameter-while-passing-by-reference-in-c) |  |
| 1173 | 150 | [What is the difference between a const reference and normal parameter?](https://stackoverflow.com/questions/2627166/what-is-the-difference-between-a-const-reference-and-normal-parameter) |  |
| 1185 | 149 | [Returning a reference to a local variable in C++](https://stackoverflow.com/questions/4643713/returning-a-reference-to-a-local-variable-in-c) |  |
| 1193 | 148 | [Why should the copy constructor accept its parameter by reference in C++?](https://stackoverflow.com/questions/2685854/why-should-the-copy-constructor-accept-its-parameter-by-reference-in-c) |  |
| 1248 | 144 | [Do rvalue references to const have any use?](https://stackoverflow.com/questions/4938875/do-rvalue-references-to-const-have-any-use) |  |
| 1261 | 143 | [Why is std::move named std::move?](https://stackoverflow.com/questions/21358432/why-is-stdmove-named-stdmove) |  |
| 1337 | 138 | [initializer_list and move semantics](https://stackoverflow.com/questions/8193102/initializer-list-and-move-semantics) |  |
| 1354 | 137 | [When to make a type non-movable in C++11?](https://stackoverflow.com/questions/14302834/when-to-make-a-type-non-movable-in-c11) |  |
| 1357 | 137 | [Non const lvalue references cannot be bound to an lvalue of different type](https://stackoverflow.com/questions/18565167/non-const-lvalue-references-cannot-be-bound-to-an-lvalue-of-different-type) |  |
| 1423 | 132 | [How does guaranteed copy elision work?](https://stackoverflow.com/questions/38043319/how-does-guaranteed-copy-elision-work) |  |
| 1445 | 130 | [Reason to Pass a Pointer by Reference in C++?](https://stackoverflow.com/questions/10240161/reason-to-pass-a-pointer-by-reference-in-c) |  |
| 1467 | 129 | [Is it idiomatic to store references members in a class, and are there pitfalls?](https://stackoverflow.com/questions/12387239/is-it-idiomatic-to-store-references-members-in-a-class-and-are-there-pitfalls) |  |
| 1473 | 129 | [How does std::move convert expressions to rvalues?](https://stackoverflow.com/questions/7510182/how-does-stdmove-convert-expressions-to-rvalues) |  |
| 1553 | 124 | [Pass by value vs pass by rvalue reference](https://stackoverflow.com/questions/37935393/pass-by-value-vs-pass-by-rvalue-reference) |  |
| 1602 | 121 | [What is the advantage of std::ref and std::reference_wrapper compared to regular references?](https://stackoverflow.com/questions/33240993/what-is-the-advantage-of-stdref-and-stdreference-wrapper-compared-to-regular) |  |
| 1657 | 118 | [How can I change the variable to which a C++ reference refers?](https://stackoverflow.com/questions/7713266/how-can-i-change-the-variable-to-which-a-c-reference-refers) |  |
| 1679 | 117 | [Passing object by reference to std::thread in C++11](https://stackoverflow.com/questions/34078208/passing-object-by-reference-to-stdthread-in-c11) |  |
| 1691 | 116 | [C++ - passing references to std::shared_ptr or boost::shared_ptr](https://stackoverflow.com/questions/327573/c-passing-references-to-stdshared-ptr-or-boostshared-ptr) |  |
| 1704 | 116 | [Reusing a moved container?](https://stackoverflow.com/questions/9168823/reusing-a-moved-container) |  |
| 1745 | 114 | [In C++, is it still bad practice to return a vector from a function?](https://stackoverflow.com/questions/3134831/in-c-is-it-still-bad-practice-to-return-a-vector-from-a-function) |  |
| 1763 | 113 | [Usage of std::forward vs std::move](https://stackoverflow.com/questions/28828159/usage-of-stdforward-vs-stdmove) |  |
| 1797 | 112 | [Guaranteed lifetime of temporary in C++?](https://stackoverflow.com/questions/584824/guaranteed-lifetime-of-temporary-in-c) |  |
| 1829 | 110 | [Passing std::string by Value or Reference](https://stackoverflow.com/questions/10789740/passing-stdstring-by-value-or-reference) |  |
| 1945 | 106 | [Declare a reference and initialize later?](https://stackoverflow.com/questions/14882995/declare-a-reference-and-initialize-later) |  |
| 1967 | 105 | [Meaning of *& and **& in C++](https://stackoverflow.com/questions/5789806/meaning-of-and-in-c) |  |
| 1999 | 104 | [C++ pass an array by reference](https://stackoverflow.com/questions/10007986/c-pass-an-array-by-reference) |  |
| 2008 | 104 | [Why do we copy then move?](https://stackoverflow.com/questions/16724657/why-do-we-copy-then-move) |  |
| 2082 | 101 | [Isn't "const" redundant when passing by value?](https://stackoverflow.com/questions/8714250/isnt-const-redundant-when-passing-by-value) |  |
| 2139 | 99 | [error: invalid initialization of non-const reference of type ‘int&’ from an rvalue of type ‘int’](https://stackoverflow.com/questions/8293426/error-invalid-initialization-of-non-const-reference-of-type-int-from-an-rval) |  |
| 2185 | 98 | [C++ Return value, reference, const reference](https://stackoverflow.com/questions/21778045/c-return-value-reference-const-reference) |  |
| 2202 | 97 | [When do we have to write a user-defined copy constructor?](https://stackoverflow.com/questions/3278625/when-do-we-have-to-write-a-user-defined-copy-constructor) |  |
| 2204 | 97 | [Can we reassign a reference in C++?](https://stackoverflow.com/questions/9293674/can-we-reassign-a-reference-in-c) |  |
| 2255 | 95 | [Why is ++x a lvalue and x++ a rvalue?](https://stackoverflow.com/questions/50802859/why-is-x-a-lvalue-and-x-a-rvalue) |  |
| 2315 | 94 | [Why is there no default move-assignment/move-constructor in early drafts of the C++11 standard?](https://stackoverflow.com/questions/4819936/why-is-there-no-default-move-assignment-move-constructor-in-early-drafts-of-the) |  |
| 2345 | 93 | [Is the pass-by-value-and-then-move construct a bad idiom?](https://stackoverflow.com/questions/21035417/is-the-pass-by-value-and-then-move-construct-a-bad-idiom) |  |
| 2410 | 91 | [Why are references not reseatable in C++](https://stackoverflow.com/questions/728233/why-are-references-not-reseatable-in-c) |  |
| 2522 | 89 | [Does C++ pass objects by value or reference?](https://stackoverflow.com/questions/21215409/does-c-pass-objects-by-value-or-reference) |  |
| 2528 | 89 | [Why can I assign the result of a function returning a value? Is it an lvalue?](https://stackoverflow.com/questions/6111905/why-can-i-assign-the-result-of-a-function-returning-a-value-is-it-an-lvalue) |  |
| 2536 | 88 | [Is there any way to find the address of a reference?](https://stackoverflow.com/questions/1950779/is-there-any-way-to-find-the-address-of-a-reference) |  |
| 2537 | 88 | [How to get a pointer from a reference?](https://stackoverflow.com/questions/9263658/how-to-get-a-pointer-from-a-reference) |  |
| 2542 | 88 | [how does the ampersand(&) sign work in c++?](https://stackoverflow.com/questions/8857857/how-does-the-ampersand-sign-work-in-c) |  |
| 2601 | 87 | [C++ view types: pass by const& or by value?](https://stackoverflow.com/questions/27256377/c-view-types-pass-by-const-or-by-value) |  |
| 2611 | 87 | [C++11 auto: what if it gets a constant reference?](https://stackoverflow.com/questions/7138588/c11-auto-what-if-it-gets-a-constant-reference) |  |
| 2652 | 86 | [Is there a difference between universal references and forwarding references?](https://stackoverflow.com/questions/39552272/is-there-a-difference-between-universal-references-and-forwarding-references) |  |
| 2653 | 86 | [C++: difference between ampersand "&" and asterisk "*" in function/method declaration?](https://stackoverflow.com/questions/596636/c-difference-between-ampersand-and-asterisk-in-function-method-declar) |  |
| 2703 | 84 | [How do I make this C++ object non-copyable?](https://stackoverflow.com/questions/2173746/how-do-i-make-this-c-object-non-copyable) |  |
| 2724 | 84 | [Why would the behavior of std::memcpy be undefined for objects that are not TriviallyCopyable?](https://stackoverflow.com/questions/29777492/why-would-the-behavior-of-stdmemcpy-be-undefined-for-objects-that-are-not-triv) |  |
| 2777 | 83 | [Is it safe to use the std::string::c_str() of a temporary string?](https://stackoverflow.com/questions/10006891/is-it-safe-to-use-the-stdstringc-str-of-a-temporary-string) |  |
| 2820 | 82 | [What is the lifetime of temporary function arguments?](https://stackoverflow.com/questions/2506793/what-is-the-lifetime-of-temporary-function-arguments) |  |
| 2842 | 82 | [Correct usage of rvalue references as parameters](https://stackoverflow.com/questions/15673889/correct-usage-of-rvalue-references-as-parameters) |  |
| 2850 | 82 | [Is there any case where a return of a RValue Reference (&&) is useful?](https://stackoverflow.com/questions/5770253/is-there-any-case-where-a-return-of-a-rvalue-reference-is-useful) |  |
| 2898 | 80 | [Passing as const and by reference - Worth it?](https://stackoverflow.com/questions/5060137/passing-as-const-and-by-reference-worth-it) |  |
| 2920 | 80 | [Object destruction in C++](https://stackoverflow.com/questions/6403055/object-destruction-in-c) |  |
| 2937 | 80 | [Return value optimization and copy elision in C](https://stackoverflow.com/questions/30034171/return-value-optimization-and-copy-elision-in-c) |  |
| 2954 | 79 | [What is a constant reference? (not a reference to a constant)](https://stackoverflow.com/questions/7420780/what-is-a-constant-reference-not-a-reference-to-a-constant) |  |
| 2967 | 79 | [Why do some people use swap for move assignments?](https://stackoverflow.com/questions/6687388/why-do-some-people-use-swap-for-move-assignments) |  |
| 2990 | 79 | [Initialization of a constant reference with a number](https://stackoverflow.com/questions/50359481/initialization-of-a-constant-reference-with-a-number) |  |
| 2992 | 79 | [How do I write a range pipeline that uses temporary containers?](https://stackoverflow.com/questions/36820639/how-do-i-write-a-range-pipeline-that-uses-temporary-containers) |  |
| 3039 | 78 | [Cv-qualifications of prvalues (revisited)](https://stackoverflow.com/questions/54381791/cv-qualifications-of-prvalues-revisited) |  |
| 3074 | 77 | [initial value of reference to non-const must be an lvalue](https://stackoverflow.com/questions/17771406/initial-value-of-reference-to-non-const-must-be-an-lvalue) |  |
| 3089 | 77 | [What are the reference collapsing rules, and how are they utilized by the C++ standard library?](https://stackoverflow.com/questions/13725747/what-are-the-reference-collapsing-rules-and-how-are-they-utilized-by-the-c-st) |  |
| 3114 | 76 | [Why do you use std::move when you have && in C++11?](https://stackoverflow.com/questions/14486367/why-do-you-use-stdmove-when-you-have-in-c11) |  |
| 3125 | 76 | [Passing integers as constant references versus copying](https://stackoverflow.com/questions/3009543/passing-integers-as-constant-references-versus-copying) |  |
| 3126 | 76 | [difference between a pointer and reference parameter?](https://stackoverflow.com/questions/620604/difference-between-a-pointer-and-reference-parameter) |  |
| 3188 | 75 | [Why does std::optional not have a specialization for reference types?](https://stackoverflow.com/questions/26858034/why-does-stdoptional-not-have-a-specialization-for-reference-types) |  |
| 3209 | 75 | [Perfect forwarding - what's it all about?](https://stackoverflow.com/questions/6829241/perfect-forwarding-whats-it-all-about) |  |
| 3214 | 75 | [Why does std::move prevent RVO (return value optimization)?](https://stackoverflow.com/questions/19267408/why-does-stdmove-prevent-rvo-return-value-optimization) |  |
| 3215 | 75 | [Overload resolution between value, rvalue reference, const lvalue reference](https://stackoverflow.com/questions/17961719/overload-resolution-between-value-rvalue-reference-const-lvalue-reference) |  |
| 3297 | 73 | [const reference parameters](https://stackoverflow.com/questions/1035795/const-reference-parameters) |  |
| 3336 | 73 | [Returning temporary object and binding to const reference](https://stackoverflow.com/questions/11560339/returning-temporary-object-and-binding-to-const-reference) |  |
| 3404 | 72 | [c++ "Incomplete type not allowed" error accessing class reference information (Circular dependency with forward declaration)](https://stackoverflow.com/questions/21743301/c-incomplete-type-not-allowed-error-accessing-class-reference-information-c) |  |
| 3406 | 72 | [Move-only version of std::function](https://stackoverflow.com/questions/25330716/move-only-version-of-stdfunction) |  |
| 3457 | 71 | [What makes moving objects faster than copying?](https://stackoverflow.com/questions/36827900/what-makes-moving-objects-faster-than-copying) |  |
| 3531 | 70 | [Is it a premature optimization to use std::move()?](https://stackoverflow.com/questions/25529582/is-it-a-premature-optimization-to-use-stdmove) |  |
| 3536 | 70 | [Can I typically/always use std::forward instead of std::move?](https://stackoverflow.com/questions/13219484/can-i-typically-always-use-stdforward-instead-of-stdmove) |  |
| 3543 | 70 | [Why not non-const reference to temporary objects?](https://stackoverflow.com/questions/13826897/why-not-non-const-reference-to-temporary-objects) |  |
| 3605 | 69 | [Exact moment of "return" in a C++-function](https://stackoverflow.com/questions/52931095/exact-moment-of-return-in-a-c-function) |  |
| 3616 | 69 | [Should all/most setter functions in C++11 be written as function templates accepting universal references?](https://stackoverflow.com/questions/14197526/should-all-most-setter-functions-in-c11-be-written-as-function-templates-accep) |  |
| 3710 | 67 | [C++ references - are they just syntactic sugar?](https://stackoverflow.com/questions/31262942/c-references-are-they-just-syntactic-sugar) |  |
| 3723 | 67 | [C++ Compiler Error C2280 "attempting to reference a deleted function" in Visual Studio 2013 and 2015](https://stackoverflow.com/questions/31264984/c-compiler-error-c2280-attempting-to-reference-a-deleted-function-in-visual) |  |
| 3772 | 67 | [Workarounds for no 'rvalue references to *this' feature](https://stackoverflow.com/questions/14562984/workarounds-for-no-rvalue-references-to-this-feature) |  |
| 3844 | 66 | [Reference of Reference in C++](https://stackoverflow.com/questions/5590978/reference-of-reference-in-c) |  |
| 3867 | 66 | [Function References](https://stackoverflow.com/questions/480248/function-references) |  |
| 3869 | 66 | [Move constructor on derived object](https://stackoverflow.com/questions/4086800/move-constructor-on-derived-object) |  |
| 3936 | 65 | [Using std::move() when returning a value from a function to avoid to copy](https://stackoverflow.com/questions/11817873/using-stdmove-when-returning-a-value-from-a-function-to-avoid-to-copy) |  |
| 4014 | 64 | [Why Can't I store references in a `std::map` in C++?](https://stackoverflow.com/questions/1543193/why-cant-i-store-references-in-a-stdmap-in-c) |  |
| 4015 | 64 | [Reference to non-static member function must be called](https://stackoverflow.com/questions/26331628/reference-to-non-static-member-function-must-be-called) |  |
| 4050 | 63 | [How do I print vector values of type glm::vec3 that have been passed by reference?](https://stackoverflow.com/questions/11515469/how-do-i-print-vector-values-of-type-glmvec3-that-have-been-passed-by-referenc) |  |
| 4079 | 63 | [Is returning references of member variables bad practice?](https://stackoverflow.com/questions/8005514/is-returning-references-of-member-variables-bad-practice) |  |
| 4091 | 63 | [Why does using a temporary object in the range-based for initializer result in a crash?](https://stackoverflow.com/questions/40954539/why-does-using-a-temporary-object-in-the-range-based-for-initializer-result-in-a) |  |
| 4125 | 63 | [Transferring the ownership of object from one unique_ptr to another unique_ptr in C++11?](https://stackoverflow.com/questions/26318506/transferring-the-ownership-of-object-from-one-unique-ptr-to-another-unique-ptr-i) |  |
| 4184 | 62 | [The implementation of std::forward](https://stackoverflow.com/questions/27501400/the-implementation-of-stdforward) |  |
| 4233 | 61 | [How do I use Reference Parameters in C++?](https://stackoverflow.com/questions/2564873/how-do-i-use-reference-parameters-in-c) |  |
| 4278 | 61 | [dereferencing a pointer when passing by reference](https://stackoverflow.com/questions/11347111/dereferencing-a-pointer-when-passing-by-reference) |  |
| 4296 | 61 | [Move or Named Return Value Optimization (NRVO)?](https://stackoverflow.com/questions/6233879/move-or-named-return-value-optimization-nrvo) |  |
| 4314 | 60 | [Passing optional parameter by reference in c++](https://stackoverflow.com/questions/2816293/passing-optional-parameter-by-reference-in-c) |  |
| 4407 | 60 | [std::is_same different results between compilers](https://stackoverflow.com/questions/73877384/stdis-same-different-results-between-compilers) |  |
| 4465 | 59 | [When is a const reference better than pass-by-value in C++11?](https://stackoverflow.com/questions/24543330/when-is-a-const-reference-better-than-pass-by-value-in-c11) |  |
| 4497 | 59 | [Function that accepts both lvalue and rvalue arguments](https://stackoverflow.com/questions/17644133/function-that-accepts-both-lvalue-and-rvalue-arguments) |  |
| 4502 | 59 | [Why is derived class move constructible when base class isn't?](https://stackoverflow.com/questions/39139087/why-is-derived-class-move-constructible-when-base-class-isnt) |  |
| 4530 | 58 | [How does a C++ reference look, memory-wise?](https://stackoverflow.com/questions/1179937/how-does-a-c-reference-look-memory-wise) |  |
| 4583 | 58 | [How true is "Want Speed? Pass by value"](https://stackoverflow.com/questions/21605579/how-true-is-want-speed-pass-by-value) |  |
| 4614 | 58 | [What does the standard library guarantee about self move assignment?](https://stackoverflow.com/questions/13127455/what-does-the-standard-library-guarantee-about-self-move-assignment) |  |
| 4660 | 57 | [Qt undefined reference to vtable](https://stackoverflow.com/questions/14010922/qt-undefined-reference-to-vtable) |  |
| 4680 | 57 | [What are the differences between a pointer and a reference in Rust?](https://stackoverflow.com/questions/62232753/what-are-the-differences-between-a-pointer-and-a-reference-in-rust) |  |
| 4747 | 56 | [How to return a class object by reference in C++?](https://stackoverflow.com/questions/8914509/how-to-return-a-class-object-by-reference-in-c) |  |
| 4784 | 56 | [Is there a one-liner to unpack tuple/pair into references?](https://stackoverflow.com/questions/37876288/is-there-a-one-liner-to-unpack-tuple-pair-into-references) |  |
| 4825 | 56 | [Why is it impossible to have a reference-to-void?](https://stackoverflow.com/questions/457896/why-is-it-impossible-to-have-a-reference-to-void) |  |
| 4849 | 55 | [Why can I assign a new value to a reference, and how can I make a reference refer to something else?](https://stackoverflow.com/questions/7181372/why-can-i-assign-a-new-value-to-a-reference-and-how-can-i-make-a-reference-refe) |  |
| 4913 | 55 | [Is it possible to std::move local stack variables?](https://stackoverflow.com/questions/43070571/is-it-possible-to-stdmove-local-stack-variables) |  |
| 4919 | 55 | [Difference between const. pointer and reference?](https://stackoverflow.com/questions/2336230/difference-between-const-pointer-and-reference) |  |
| 4922 | 55 | [Return reference to a vector member variable](https://stackoverflow.com/questions/8384234/return-reference-to-a-vector-member-variable) |  |
| 4949 | 55 | [Real life examples of xvalues, glvalues, and prvalues?](https://stackoverflow.com/questions/6609968/real-life-examples-of-xvalues-glvalues-and-prvalues) |  |
| 4983 | 54 | [How to determine programmatically if an expression is rvalue or lvalue in C++?](https://stackoverflow.com/questions/36296425/how-to-determine-programmatically-if-an-expression-is-rvalue-or-lvalue-in-c) |  |
