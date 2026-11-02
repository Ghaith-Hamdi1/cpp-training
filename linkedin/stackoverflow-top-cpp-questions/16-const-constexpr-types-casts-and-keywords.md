# const, constexpr, types, casts and keywords

[Back to all topics](README.md)

485 questions, 2 with a carousel already.

Source: the 5,000 most voted questions tagged `c++` (the first 100 pages of 50 at <https://stackoverflow.com/questions/tagged/c%2b%2b?tab=votes&pagesize=50>), fetched on 2026-11-02 through the Stack Exchange API, sorted by votes. The lowest score included is 54 votes. Ties within the same score can be in a slightly different order than the website.

| Rank | Votes | Question | |
|---:|---:|---|---|
| 6 | 3,483 | [What's the problem with "using namespace std;"?](https://stackoverflow.com/questions/1452721/whats-the-problem-with-using-namespace-std) |  |
| 19 | 2,196 | [How can I convert int to string in C++?](https://stackoverflow.com/questions/5590381/how-can-i-convert-int-to-string-in-c) |  |
| 23 | 2,070 | [Regular cast vs. static_cast vs. dynamic_cast](https://stackoverflow.com/questions/28002/regular-cast-vs-static-cast-vs-dynamic-cast) |  |
| 27 | 1,874 | [What is the difference between const int*, const int * const, and int * const?](https://stackoverflow.com/questions/1143262/what-is-the-difference-between-const-int-const-int-const-and-int-const) | ✅ #8 |
| 38 | 1,328 | [What is the difference between 'typedef' and 'using'?](https://stackoverflow.com/questions/10747810/what-is-the-difference-between-typedef-and-using) |  |
| 41 | 1,283 | [How do I use extern to share variables between source files?](https://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files) |  |
| 43 | 1,237 | [What are POD types in C++?](https://stackoverflow.com/questions/146452/what-are-pod-types-in-c) |  |
| 62 | 984 | [Difference between 'struct' and 'typedef struct' in C++?](https://stackoverflow.com/questions/612328/difference-between-struct-and-typedef-struct-in-c) |  |
| 68 | 920 | [What's the difference between constexpr and const?](https://stackoverflow.com/questions/14116003/whats-the-difference-between-constexpr-and-const) | ✅ #6 |
| 75 | 884 | [Why isn't sizeof for a struct equal to the sum of sizeof of each member?](https://stackoverflow.com/questions/119123/why-isnt-sizeof-for-a-struct-equal-to-the-sum-of-sizeof-of-each-member) |  |
| 79 | 850 | [Why use static_cast<T>(x) instead of (T)x or T(x)?](https://stackoverflow.com/questions/103512/why-use-static-casttx-instead-of-tx-or-tx) |  |
| 86 | 798 | [What is meant with "const" at end of function declaration?](https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration) |  |
| 93 | 776 | [Why is enum class considered safer to use than plain enum?](https://stackoverflow.com/questions/18335861/why-is-enum-class-considered-safer-to-use-than-plain-enum) |  |
| 95 | 765 | [What does the C++ standard say about the size of int, long?](https://stackoverflow.com/questions/589575/what-does-the-c-standard-say-about-the-size-of-int-long) |  |
| 97 | 760 | [How do I detect unsigned integer overflow?](https://stackoverflow.com/questions/199333/how-do-i-detect-unsigned-integer-overflow) |  |
| 106 | 718 | [Why should you prefer unnamed namespaces over static functions?](https://stackoverflow.com/questions/154469/why-should-you-prefer-unnamed-namespaces-over-static-functions) |  |
| 118 | 680 | [How do you compare float and double while accounting for precision loss?](https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss) |  |
| 119 | 676 | [Is it possible to print (the name of) a variable's type in standard C++?](https://stackoverflow.com/questions/81870/is-it-possible-to-print-the-name-of-a-variables-type-in-standard-c) |  |
| 125 | 661 | [Does the 'mutable' keyword have any purpose other than allowing a data member to be modified by a const member function?](https://stackoverflow.com/questions/105014/does-the-mutable-keyword-have-any-purpose-other-than-allowing-a-data-member-to) |  |
| 128 | 651 | [How to initialize private static data members in a header file](https://stackoverflow.com/questions/185844/how-to-initialize-private-static-data-members-in-a-header-file) |  |
| 133 | 638 | [When should I use reinterpret_cast?](https://stackoverflow.com/questions/573294/when-should-i-use-reinterpret-cast) |  |
| 145 | 603 | [unsigned int vs. size_t](https://stackoverflow.com/questions/131803/unsigned-int-vs-size-t) |  |
| 149 | 582 | [When to use extern in C++](https://stackoverflow.com/questions/10422034/when-to-use-extern-in-c) |  |
| 166 | 547 | [Why do we use the volatile keyword?](https://stackoverflow.com/questions/4437527/why-do-we-use-the-volatile-keyword) |  |
| 190 | 501 | [const vs constexpr on variables](https://stackoverflow.com/questions/13346879/const-vs-constexpr-on-variables) |  |
| 192 | 493 | [Iteration over std::vector: unsigned vs signed index variable](https://stackoverflow.com/questions/409348/iteration-over-stdvector-unsigned-vs-signed-index-variable) |  |
| 216 | 456 | [How to convert int to QString?](https://stackoverflow.com/questions/3211771/how-to-convert-int-to-qstring) |  |
| 224 | 450 | [How can I iterate over an enum?](https://stackoverflow.com/questions/261963/how-can-i-iterate-over-an-enum) |  |
| 226 | 448 | [What are inline namespaces for?](https://stackoverflow.com/questions/11016220/what-are-inline-namespaces-for) |  |
| 238 | 428 | [What is the lifetime of a static variable in a C++ function?](https://stackoverflow.com/questions/246564/what-is-the-lifetime-of-a-static-variable-in-a-c-function) |  |
| 263 | 399 | [Should I declare a constant instead of writing a constexpr function?](https://stackoverflow.com/questions/4748083/should-i-declare-a-constant-instead-of-writing-a-constexpr-function) |  |
| 269 | 396 | [C++ Structure Initialization](https://stackoverflow.com/questions/11516657/c-structure-initialization) |  |
| 278 | 386 | [Why are unnamed namespaces used and what are their benefits?](https://stackoverflow.com/questions/357404/why-are-unnamed-namespaces-used-and-what-are-their-benefits) |  |
| 285 | 378 | [What is the uintptr_t data type?](https://stackoverflow.com/questions/1845482/what-is-the-uintptr-t-data-type) |  |
| 287 | 377 | [Namespace + functions versus static methods on a class](https://stackoverflow.com/questions/1434937/namespace-functions-versus-static-methods-on-a-class) |  |
| 311 | 356 | [Initialization of all elements of an array to one default value in C++?](https://stackoverflow.com/questions/1065774/initialization-of-all-elements-of-an-array-to-one-default-value-in-c) |  |
| 318 | 352 | [Why is the size of a character sizeof('a') different in C and C++?](https://stackoverflow.com/questions/2172943/why-is-the-size-of-a-character-sizeofa-different-in-c-and-c) |  |
| 325 | 349 | [The static keyword and its various uses in C++](https://stackoverflow.com/questions/15235526/the-static-keyword-and-its-various-uses-in-c) |  |
| 335 | 346 | [Purpose of Unions in C and C++](https://stackoverflow.com/questions/2310483/purpose-of-unions-in-c-and-c) |  |
| 354 | 334 | [Is it possible to declare two variables of different types in a for loop?](https://stackoverflow.com/questions/2687392/is-it-possible-to-declare-two-variables-of-different-types-in-a-for-loop) |  |
| 360 | 330 | [What is the difference between "long", "long long", "long int", and "long long int" in C++?](https://stackoverflow.com/questions/18971732/what-is-the-difference-between-long-long-long-long-int-and-long-long-i) |  |
| 367 | 323 | [Forward declaring an enum in C++](https://stackoverflow.com/questions/71416/forward-declaring-an-enum-in-c) |  |
| 377 | 317 | [How to cast int to enum in C++?](https://stackoverflow.com/questions/11452920/how-to-cast-int-to-enum-in-c) |  |
| 378 | 317 | [What does "default" mean after a class' function declaration?](https://stackoverflow.com/questions/6502828/what-does-default-mean-after-a-class-function-declaration) |  |
| 384 | 314 | [What are the pros and cons in use of global variables?](https://stackoverflow.com/questions/484635/what-are-the-pros-and-cons-in-use-of-global-variables) |  |
| 387 | 313 | [Is there a difference between copy-initialization and direct-initialization?](https://stackoverflow.com/questions/1051379/is-there-a-difference-between-copy-initialization-and-direct-initialization) |  |
| 394 | 309 | [Does static constexpr variable inside a function make sense?](https://stackoverflow.com/questions/13865842/does-static-constexpr-variable-inside-a-function-make-sense) |  |
| 397 | 308 | [What is the difference between static_cast<> and C style casting?](https://stackoverflow.com/questions/1609163/what-is-the-difference-between-static-cast-and-c-style-casting) |  |
| 418 | 296 | [Forward declaration of a typedef in C++](https://stackoverflow.com/questions/804894/forward-declaration-of-a-typedef-in-c) |  |
| 419 | 295 | [Why does volatile exist?](https://stackoverflow.com/questions/72552/why-does-volatile-exist) |  |
| 432 | 292 | [Should I use static_cast or reinterpret_cast when casting a void* to whatever](https://stackoverflow.com/questions/310451/should-i-use-static-cast-or-reinterpret-cast-when-casting-a-void-to-whatever) |  |
| 456 | 281 | [How do I get the type of a variable?](https://stackoverflow.com/questions/11310898/how-do-i-get-the-type-of-a-variable) |  |
| 457 | 280 | [When to use std::size_t?](https://stackoverflow.com/questions/1951519/when-to-use-stdsize-t) |  |
| 467 | 276 | [How can I declare and define multiple variables in one line using C++?](https://stackoverflow.com/questions/6838408/how-can-i-declare-and-define-multiple-variables-in-one-line-using-c) |  |
| 470 | 275 | ['static const' vs. '#define'](https://stackoverflow.com/questions/1637332/static-const-vs-define) |  |
| 485 | 270 | [Can a C++ enum class have methods?](https://stackoverflow.com/questions/21295935/can-a-c-enum-class-have-methods) |  |
| 489 | 267 | [How much is too much with C++11 auto keyword?](https://stackoverflow.com/questions/6434971/how-much-is-too-much-with-c11-auto-keyword) |  |
| 491 | 265 | [How to use enums as flags in C++?](https://stackoverflow.com/questions/1448396/how-to-use-enums-as-flags-in-c) |  |
| 492 | 265 | [What does the restrict keyword mean in C++?](https://stackoverflow.com/questions/776283/what-does-the-restrict-keyword-mean-in-c) |  |
| 497 | 262 | [What does {0} mean when initializing an object?](https://stackoverflow.com/questions/88957/what-does-0-mean-when-initializing-an-object) |  |
| 501 | 261 | [How to use enums in C++](https://stackoverflow.com/questions/12183008/how-to-use-enums-in-c) |  |
| 503 | 261 | [What is the meaning of a variable with type auto&&?](https://stackoverflow.com/questions/13230480/what-is-the-meaning-of-a-variable-with-type-auto) |  |
| 507 | 259 | [How do you properly use namespaces in C++?](https://stackoverflow.com/questions/41590/how-do-you-properly-use-namespaces-in-c) |  |
| 519 | 254 | [What is the point of noreturn?](https://stackoverflow.com/questions/10538291/what-is-the-point-of-noreturn) |  |
| 523 | 253 | [(-2147483648> 0) returns true in C++?](https://stackoverflow.com/questions/14695118/2147483648-0-returns-true-in-c) |  |
| 528 | 252 | [What's the difference between size_t and int in C++?](https://stackoverflow.com/questions/502856/whats-the-difference-between-size-t-and-int-in-c) |  |
| 539 | 247 | [How do I typedef a function pointer with the C++11 using syntax?](https://stackoverflow.com/questions/16498969/how-do-i-typedef-a-function-pointer-with-the-c11-using-syntax) |  |
| 547 | 245 | [Arrow operator (->) in function heading](https://stackoverflow.com/questions/22514855/arrow-operator-in-function-heading) |  |
| 550 | 245 | [How do inline variables work?](https://stackoverflow.com/questions/38043442/how-do-inline-variables-work) |  |
| 551 | 245 | [What is the logic behind the "using" keyword in C++?](https://stackoverflow.com/questions/20790932/what-is-the-logic-behind-the-using-keyword-in-c) |  |
| 553 | 244 | [Undefined reference to static constexpr char\[\]](https://stackoverflow.com/questions/8016780/undefined-reference-to-static-constexpr-char) |  |
| 565 | 241 | [Are members of a C++ struct initialized to 0 by default?](https://stackoverflow.com/questions/1069621/are-members-of-a-c-struct-initialized-to-0-by-default) |  |
| 580 | 236 | [maximum value of int](https://stackoverflow.com/questions/1855459/maximum-value-of-int) |  |
| 585 | 235 | [Integer to hex string in C++](https://stackoverflow.com/questions/5100718/integer-to-hex-string-in-c) |  |
| 595 | 233 | [What are some uses of decltype(auto)?](https://stackoverflow.com/questions/24109737/what-are-some-uses-of-decltypeauto) |  |
| 598 | 232 | [What is the meaning of the auto keyword?](https://stackoverflow.com/questions/7576953/what-is-the-meaning-of-the-auto-keyword) |  |
| 614 | 227 | [Static variables in member functions](https://stackoverflow.com/questions/6223355/static-variables-in-member-functions) |  |
| 625 | 226 | [Compare double to zero using epsilon](https://stackoverflow.com/questions/13698927/compare-double-to-zero-using-epsilon) |  |
| 630 | 225 | [Why do you use typedef when declaring an enum in C++?](https://stackoverflow.com/questions/385023/why-do-you-use-typedef-when-declaring-an-enum-in-c) |  |
| 635 | 223 | [Implicit type conversion rules in C++ operators](https://stackoverflow.com/questions/5563000/implicit-type-conversion-rules-in-c-operators) |  |
| 669 | 216 | [How to cast/convert pointer to reference in C++](https://stackoverflow.com/questions/10172735/how-to-cast-convert-pointer-to-reference-in-c) |  |
| 671 | 216 | [What do the following phrases mean in C++: zero-, default- and value-initialization?](https://stackoverflow.com/questions/1613341/what-do-the-following-phrases-mean-in-c-zero-default-and-value-initializat) |  |
| 685 | 212 | [How to sort with a lambda?](https://stackoverflow.com/questions/5122804/how-to-sort-with-a-lambda) |  |
| 706 | 208 | [Internal typedefs in C++ - good style or bad style?](https://stackoverflow.com/questions/759512/internal-typedefs-in-c-good-style-or-bad-style) |  |
| 715 | 207 | [What is a namespace alias?](https://stackoverflow.com/questions/1211399/what-is-a-namespace-alias) |  |
| 761 | 199 | [Why are both "const T" and "T const" valid, and which one should you use?](https://stackoverflow.com/questions/5503352/why-are-both-const-t-and-t-const-valid-and-which-one-should-you-use) |  |
| 792 | 194 | [Finding the type of an object in C++](https://stackoverflow.com/questions/351845/finding-the-type-of-an-object-in-c) |  |
| 832 | 189 | [Is there still a reason to use `int` in C++ code?](https://stackoverflow.com/questions/48729384/is-there-still-a-reason-to-use-int-in-c-code) |  |
| 866 | 184 | [C++ semantics of `static const` vs `const`](https://stackoverflow.com/questions/3709207/c-semantics-of-static-const-vs-const) |  |
| 869 | 183 | [bool to int conversion](https://stackoverflow.com/questions/5369770/bool-to-int-conversion) |  |
| 878 | 182 | [dynamic_cast and static_cast in C++](https://stackoverflow.com/questions/2253168/dynamic-cast-and-static-cast-in-c) |  |
| 881 | 182 | [Declaring an enum within a class](https://stackoverflow.com/questions/2503807/declaring-an-enum-within-a-class) |  |
| 900 | 180 | [Purpose of returning by const value?](https://stackoverflow.com/questions/8716330/purpose-of-returning-by-const-value) |  |
| 911 | 178 | ["X does not name a type" error in C++](https://stackoverflow.com/questions/2133250/x-does-not-name-a-type-error-in-c) |  |
| 913 | 178 | [Convenient C++ struct initialisation](https://stackoverflow.com/questions/6181715/convenient-c-struct-initialisation) |  |
| 944 | 173 | [Why can't I forward-declare a class in a namespace using double colons?](https://stackoverflow.com/questions/2059665/why-cant-i-forward-declare-a-class-in-a-namespace-using-double-colons) |  |
| 965 | 171 | [Elegant solution to duplicate, const and non-const, getters?](https://stackoverflow.com/questions/856542/elegant-solution-to-duplicate-const-and-non-const-getters) |  |
| 967 | 170 | [Sell me const-correctness](https://stackoverflow.com/questions/136880/sell-me-const-correctness) |  |
| 973 | 170 | [How are unnamed namespaces superior to the static keyword?](https://stackoverflow.com/questions/4422507/how-are-unnamed-namespaces-superior-to-the-static-keyword) |  |
| 977 | 169 | [Why can't variable names start with numbers?](https://stackoverflow.com/questions/342152/why-cant-variable-names-start-with-numbers) |  |
| 978 | 169 | [C++ convert hex string to signed integer](https://stackoverflow.com/questions/1070497/c-convert-hex-string-to-signed-integer) |  |
| 985 | 169 | [What does static_assert do, and what would you use it for?](https://stackoverflow.com/questions/1647895/what-does-static-assert-do-and-what-would-you-use-it-for) |  |
| 993 | 168 | [Does constexpr imply inline?](https://stackoverflow.com/questions/14391272/does-constexpr-imply-inline) |  |
| 994 | 168 | [If I copy a float to another variable, will they be equal?](https://stackoverflow.com/questions/59710531/if-i-copy-a-float-to-another-variable-will-they-be-equal) |  |
| 1001 | 167 | [Why in C++ do we use DWORD rather than unsigned int?](https://stackoverflow.com/questions/2995251/why-in-c-do-we-use-dword-rather-than-unsigned-int) |  |
| 1002 | 167 | [Why is bool 8 bits long in C++?](https://stackoverflow.com/questions/2064550/why-is-bool-8-bits-long-in-c) |  |
| 1048 | 162 | [How do I write a short literal in C++?](https://stackoverflow.com/questions/208433/how-do-i-write-a-short-literal-in-c) |  |
| 1049 | 162 | [What is uint_fast32_t and why should it be used instead of the regular int and uint32_t?](https://stackoverflow.com/questions/8500677/what-is-uint-fast32-t-and-why-should-it-be-used-instead-of-the-regular-int-and-u) |  |
| 1051 | 162 | [Which header should I include for size_t?](https://stackoverflow.com/questions/36594569/which-header-should-i-include-for-size-t) |  |
| 1061 | 161 | [How to avoid overflow in expr. A * B - C * D](https://stackoverflow.com/questions/13237046/how-to-avoid-overflow-in-expr-a-b-c-d) |  |
| 1086 | 158 | [Is "long long" = "long long int" = "long int long" = "int long long"?](https://stackoverflow.com/questions/30726423/is-long-long-long-long-int-long-int-long-int-long-long) |  |
| 1088 | 158 | [Cast to int vs floor](https://stackoverflow.com/questions/3300290/cast-to-int-vs-floor) |  |
| 1097 | 157 | [Why does long long n = 2000*2000*2000*2000; overflow?](https://stackoverflow.com/questions/66354756/why-does-long-long-n-2000200020002000-overflow) |  |
| 1100 | 157 | [Why can't I initialize non-const static member or static array in class?](https://stackoverflow.com/questions/9656941/why-cant-i-initialize-non-const-static-member-or-static-array-in-class) |  |
| 1111 | 156 | [Why does C++11 not support designated initializer lists as C99?](https://stackoverflow.com/questions/18731707/why-does-c11-not-support-designated-initializer-lists-as-c99) |  |
| 1119 | 155 | [How do I initialize a const data member?](https://stackoverflow.com/questions/14495536/how-do-i-initialize-a-const-data-member) |  |
| 1120 | 155 | [Is there a downside to declaring variables with auto in C++?](https://stackoverflow.com/questions/34758042/is-there-a-downside-to-declaring-variables-with-auto-in-c) |  |
| 1130 | 155 | [How many and which are the uses of "const" in C++?](https://stackoverflow.com/questions/455518/how-many-and-which-are-the-uses-of-const-in-c) |  |
| 1140 | 154 | [C++ auto& vs auto](https://stackoverflow.com/questions/29859796/c-auto-vs-auto) |  |
| 1146 | 153 | [What new capabilities do user-defined literals add to C++?](https://stackoverflow.com/questions/237804/what-new-capabilities-do-user-defined-literals-add-to-c) |  |
| 1152 | 153 | [Where do I find the definition of size_t, and what is it used for?](https://stackoverflow.com/questions/1119370/where-do-i-find-the-definition-of-size-t-and-what-is-it-used-for) |  |
| 1157 | 152 | [Why are types always a certain size no matter its value?](https://stackoverflow.com/questions/50819413/why-are-types-always-a-certain-size-no-matter-its-value) |  |
| 1175 | 150 | [How can I output the value of an enum class in C++11](https://stackoverflow.com/questions/11421432/how-can-i-output-the-value-of-an-enum-class-in-c11) |  |
| 1176 | 150 | [Why can I use auto on a private type?](https://stackoverflow.com/questions/13532784/why-can-i-use-auto-on-a-private-type) |  |
| 1183 | 149 | [What is the point of double negation?](https://stackoverflow.com/questions/248693/what-is-the-point-of-double-negation) |  |
| 1199 | 148 | ["using namespace" in c++ headers](https://stackoverflow.com/questions/5849457/using-namespace-in-c-headers) |  |
| 1210 | 147 | [Where should a static const data member be defined?](https://stackoverflow.com/questions/2605520/where-should-a-static-const-data-member-be-defined) |  |
| 1220 | 146 | [When should I prefer constexpr variables over macros?](https://stackoverflow.com/questions/42388077/when-should-i-prefer-constexpr-variables-over-macros) |  |
| 1234 | 145 | [How to easily map c++ enums to strings](https://stackoverflow.com/questions/207976/how-to-easily-map-c-enums-to-strings) |  |
| 1271 | 142 | [Why does dividing two int not yield the right value when assigned to double?](https://stackoverflow.com/questions/7571326/why-does-dividing-two-int-not-yield-the-right-value-when-assigned-to-double) |  |
| 1274 | 142 | [Is sizeof(bool) defined in the C++ language standard?](https://stackoverflow.com/questions/4897844/is-sizeofbool-defined-in-the-c-language-standard) |  |
| 1277 | 142 | [Can I assume (bool)true == (int)1 for any C++ compiler?](https://stackoverflow.com/questions/2725044/can-i-assume-booltrue-int1-for-any-c-compiler) |  |
| 1279 | 142 | [C++ zero initialization - Why is `b` in this program uninitialized, but `a` is initialized?](https://stackoverflow.com/questions/54350114/c-zero-initialization-why-is-b-in-this-program-uninitialized-but-a-is-i) |  |
| 1280 | 141 | ['const int' vs. 'int const' as function parameters in C++ and C](https://stackoverflow.com/questions/162480/const-int-vs-int-const-as-function-parameters-in-c-and-c) |  |
| 1329 | 138 | [Inline functions vs Preprocessor macros](https://stackoverflow.com/questions/1137575/inline-functions-vs-preprocessor-macros) |  |
| 1333 | 138 | [How to convert a number to string and vice versa in C++](https://stackoverflow.com/questions/5290089/how-to-convert-a-number-to-string-and-vice-versa-in-c) |  |
| 1344 | 137 | [Is there a better way to express nested namespaces in C++ within the header](https://stackoverflow.com/questions/11358425/is-there-a-better-way-to-express-nested-namespaces-in-c-within-the-header) |  |
| 1363 | 136 | [What is the difference between an int and a long in C++?](https://stackoverflow.com/questions/271076/what-is-the-difference-between-an-int-and-a-long-in-c) |  |
| 1366 | 136 | [Is it possible to determine the number of elements of a c++ enum class?](https://stackoverflow.com/questions/14989274/is-it-possible-to-determine-the-number-of-elements-of-a-c-enum-class) |  |
| 1367 | 136 | [What exactly do "IB" and "UB" mean?](https://stackoverflow.com/questions/2766731/what-exactly-do-ib-and-ub-mean) |  |
| 1368 | 136 | [C++: Print out enum value as text](https://stackoverflow.com/questions/3342726/c-print-out-enum-value-as-text) |  |
| 1385 | 134 | [How to initialize a private static const map in C++?](https://stackoverflow.com/questions/2636303/how-to-initialize-a-private-static-const-map-in-c) |  |
| 1387 | 134 | [how do I initialize a float to its max/min value?](https://stackoverflow.com/questions/2684603/how-do-i-initialize-a-float-to-its-max-min-value) |  |
| 1405 | 133 | [C++ map access discards qualifiers (const)](https://stackoverflow.com/questions/262853/c-map-access-discards-qualifiers-const) |  |
| 1407 | 133 | [Should I use #define, enum or const?](https://stackoverflow.com/questions/112433/should-i-use-define-enum-or-const) |  |
| 1412 | 133 | [Correct way to define C++ namespace methods in .cpp file](https://stackoverflow.com/questions/8681714/correct-way-to-define-c-namespace-methods-in-cpp-file) |  |
| 1427 | 131 | [Initialize static variables in C++ class?](https://stackoverflow.com/questions/5019856/initialize-static-variables-in-c-class) |  |
| 1436 | 131 | [The new keyword "auto"; When should it be used to declare a variable type?](https://stackoverflow.com/questions/6900459/the-new-keyword-auto-when-should-it-be-used-to-declare-a-variable-type) |  |
| 1453 | 130 | [Defining static const integer members in class definition](https://stackoverflow.com/questions/3025997/defining-static-const-integer-members-in-class-definition) |  |
| 1497 | 127 | [Using std Namespace](https://stackoverflow.com/questions/1265039/using-std-namespace) |  |
| 1505 | 127 | [Why are C character literals ints instead of chars?](https://stackoverflow.com/questions/433895/why-are-c-character-literals-ints-instead-of-chars) |  |
| 1506 | 127 | [Is it allowed to use unions for type punning, and if not, why?](https://stackoverflow.com/questions/25664848/is-it-allowed-to-use-unions-for-type-punning-and-if-not-why) |  |
| 1525 | 125 | [Undefined reference to static variable c++](https://stackoverflow.com/questions/16284629/undefined-reference-to-static-variable-c) |  |
| 1540 | 125 | [How to initialize an array member in a member initializer list](https://stackoverflow.com/questions/4057948/how-to-initialize-an-array-member-in-a-member-initializer-list) |  |
| 1547 | 124 | [Converting a pointer into an integer](https://stackoverflow.com/questions/153065/converting-a-pointer-into-an-integer) |  |
| 1560 | 123 | ['uint32_t' does not name a type](https://stackoverflow.com/questions/11069108/uint32-t-does-not-name-a-type) |  |
| 1567 | 123 | [What does extern inline do?](https://stackoverflow.com/questions/216510/what-does-extern-inline-do) |  |
| 1599 | 121 | [Are C++ enums signed or unsigned?](https://stackoverflow.com/questions/159034/are-c-enums-signed-or-unsigned) |  |
| 1607 | 121 | [How do you correctly define entities within a namespace that have been declared in a header?](https://stackoverflow.com/questions/10816600/how-do-you-correctly-define-entities-within-a-namespace-that-have-been-declared) |  |
| 1622 | 120 | [Why are the fast integer types faster than the other integer types?](https://stackoverflow.com/questions/59593541/why-are-the-fast-integer-types-faster-than-the-other-integer-types) |  |
| 1627 | 120 | [What is decltype and how is it used?](https://stackoverflow.com/questions/18815221/what-is-decltype-and-how-is-it-used) |  |
| 1645 | 119 | [(How) can I count the items in an enum?](https://stackoverflow.com/questions/2102582/how-can-i-count-the-items-in-an-enum) |  |
| 1647 | 119 | [Is 'auto const' and 'const auto' the same?](https://stackoverflow.com/questions/10709897/is-auto-const-and-const-auto-the-same) |  |
| 1651 | 119 | [When to use the brace-enclosed initializer?](https://stackoverflow.com/questions/9976927/when-to-use-the-brace-enclosed-initializer) |  |
| 1658 | 118 | [What's the scope of the "using" declaration in C++?](https://stackoverflow.com/questions/223021/whats-the-scope-of-the-using-declaration-in-c) |  |
| 1671 | 118 | [Why is "using namespace X;" not allowed at class/struct level?](https://stackoverflow.com/questions/6326805/why-is-using-namespace-x-not-allowed-at-class-struct-level) |  |
| 1672 | 117 | [Swapping two variable value without using third variable](https://stackoverflow.com/questions/1826159/swapping-two-variable-value-without-using-third-variable) |  |
| 1680 | 117 | [Accessing Environment Variables In C++](https://stackoverflow.com/questions/631664/accessing-environment-variables-in-c) |  |
| 1686 | 117 | [namespaces for enum types - best practices](https://stackoverflow.com/questions/482745/namespaces-for-enum-types-best-practices) |  |
| 1687 | 117 | [Why an unnamed namespace is a "superior" alternative to static?](https://stackoverflow.com/questions/4977252/why-an-unnamed-namespace-is-a-superior-alternative-to-static) |  |
| 1692 | 116 | [Register keyword in C++](https://stackoverflow.com/questions/3207018/register-keyword-in-c) |  |
| 1693 | 116 | [When do function-level static variables get allocated/initialized?](https://stackoverflow.com/questions/55510/when-do-function-level-static-variables-get-allocated-initialized) |  |
| 1712 | 115 | [Can I implement an autonomous `self` member type in C++?](https://stackoverflow.com/questions/21143835/can-i-implement-an-autonomous-self-member-type-in-c) |  |
| 1719 | 115 | [Proper way to initialize C++ structs](https://stackoverflow.com/questions/5914422/proper-way-to-initialize-c-structs) |  |
| 1720 | 115 | [Efficient unsigned-to-signed cast avoiding implementation-defined behavior](https://stackoverflow.com/questions/13150449/efficient-unsigned-to-signed-cast-avoiding-implementation-defined-behavior) |  |
| 1724 | 115 | [What is `constinit` in C++20?](https://stackoverflow.com/questions/57845131/what-is-constinit-in-c20) |  |
| 1725 | 115 | [Difference between std::result_of and decltype](https://stackoverflow.com/questions/2689709/difference-between-stdresult-of-and-decltype) |  |
| 1756 | 113 | [Define constant variables in C++ header](https://stackoverflow.com/questions/12042549/define-constant-variables-in-c-header) |  |
| 1765 | 113 | [How to initialize a "static const" data member in C++?](https://stackoverflow.com/questions/3531060/how-to-initialize-a-static-const-data-member-in-c) |  |
| 1769 | 113 | [Definition of int64_t](https://stackoverflow.com/questions/13604137/definition-of-int64-t) |  |
| 1772 | 113 | [Should one never use static inline function?](https://stackoverflow.com/questions/10876930/should-one-never-use-static-inline-function) |  |
| 1788 | 112 | [Why can't a static member function have a const qualifier?](https://stackoverflow.com/questions/7035356/why-cant-a-static-member-function-have-a-const-qualifier) |  |
| 1808 | 111 | [What does "const" mean in return types, in function parameters, and after member functions?](https://stackoverflow.com/questions/5598703/what-does-const-mean-in-return-types-in-function-parameters-and-after-member) |  |
| 1817 | 111 | [Detecting signed overflow in C/C++](https://stackoverflow.com/questions/3944505/detecting-signed-overflow-in-c-c) |  |
| 1843 | 110 | [Considerations for defining a member function inside or outside the class](https://stackoverflow.com/questions/9075931/considerations-for-defining-a-member-function-inside-or-outside-the-class) |  |
| 1852 | 109 | [Why isn't the \[\] operator const for STL maps?](https://stackoverflow.com/questions/1474894/why-isnt-the-operator-const-for-stl-maps) |  |
| 1858 | 109 | [Deprecation of the static keyword... no more?](https://stackoverflow.com/questions/4726570/deprecation-of-the-static-keyword-no-more) |  |
| 1875 | 108 | [Base enum class inheritance](https://stackoverflow.com/questions/644629/base-enum-class-inheritance) |  |
| 1878 | 108 | [memset() or value initialization to zero out a struct?](https://stackoverflow.com/questions/1998752/memset-or-value-initialization-to-zero-out-a-struct) |  |
| 1883 | 108 | [Why is argc not a constant?](https://stackoverflow.com/questions/20558418/why-is-argc-not-a-constant) |  |
| 1904 | 107 | [Should I use double or float?](https://stackoverflow.com/questions/1074474/should-i-use-double-or-float) |  |
| 1907 | 107 | [Unsigned keyword in C++](https://stackoverflow.com/questions/2099830/unsigned-keyword-in-c) |  |
| 1912 | 107 | [Why does MSVC not issue a warning for signed/unsigned == comparison?](https://stackoverflow.com/questions/5416414/why-does-msvc-not-issue-a-warning-for-signed-unsigned-comparison) |  |
| 1919 | 107 | [Why sizeof int is wrong, while sizeof(int) is right?](https://stackoverflow.com/questions/13120473/why-sizeof-int-is-wrong-while-sizeofint-is-right) |  |
| 1942 | 106 | [What distinguishes the declaration, the definition and the initialization of a variable?](https://stackoverflow.com/questions/23345554/what-distinguishes-the-declaration-the-definition-and-the-initialization-of-a-v) |  |
| 1948 | 106 | ["Field has incomplete type" error](https://stackoverflow.com/questions/12466055/field-has-incomplete-type-error) |  |
| 1963 | 105 | [Which is faster : if (bool) or if(int)?](https://stackoverflow.com/questions/5764956/which-is-faster-if-bool-or-ifint) |  |
| 1977 | 105 | [Why does everybody typedef over standard C types?](https://stackoverflow.com/questions/38552314/why-does-everybody-typedef-over-standard-c-types) |  |
| 2014 | 104 | [constexpr vs. static const: Which one to prefer?](https://stackoverflow.com/questions/41125651/constexpr-vs-static-const-which-one-to-prefer) |  |
| 2015 | 104 | [Is it possible to declare constexpr class in a header and define it in a separate .cpp file?](https://stackoverflow.com/questions/27345284/is-it-possible-to-declare-constexpr-class-in-a-header-and-define-it-in-a-separat) |  |
| 2017 | 104 | [Creating a C++ namespace in header and source (cpp)](https://stackoverflow.com/questions/8210935/creating-a-c-namespace-in-header-and-source-cpp) |  |
| 2027 | 103 | [Is C++14 adding new keywords to C++?](https://stackoverflow.com/questions/25380599/is-c14-adding-new-keywords-to-c) |  |
| 2031 | 103 | [How to declare a global variable in C++](https://stackoverflow.com/questions/9702053/how-to-declare-a-global-variable-in-c) |  |
| 2088 | 101 | [does `const auto` have any meaning?](https://stackoverflow.com/questions/5070521/does-const-auto-have-any-meaning) |  |
| 2092 | 101 | [What happens if I assign a negative value to an unsigned variable?](https://stackoverflow.com/questions/2711522/what-happens-if-i-assign-a-negative-value-to-an-unsigned-variable) |  |
| 2095 | 101 | [How many bytes is unsigned long long?](https://stackoverflow.com/questions/5836329/how-many-bytes-is-unsigned-long-long) |  |
| 2100 | 100 | [Member function with static linkage](https://stackoverflow.com/questions/31305717/member-function-with-static-linkage) |  |
| 2104 | 100 | [Defining a global constant in C++](https://stackoverflow.com/questions/2268749/defining-a-global-constant-in-c) |  |
| 2111 | 100 | [Why does const imply internal linkage in C++, when it doesn't in C?](https://stackoverflow.com/questions/998425/why-does-const-imply-internal-linkage-in-c-when-it-doesnt-in-c) |  |
| 2124 | 100 | [How to declare constexpr extern?](https://stackoverflow.com/questions/30208685/how-to-declare-constexpr-extern) |  |
| 2133 | 99 | [What range of values can integer types store in C++?](https://stackoverflow.com/questions/1819189/what-range-of-values-can-integer-types-store-in-c) |  |
| 2134 | 99 | [Can't use enum class as unordered_map key](https://stackoverflow.com/questions/18837857/cant-use-enum-class-as-unordered-map-key) |  |
| 2142 | 99 | [How do I avoid implicit conversions on non-constructing functions?](https://stackoverflow.com/questions/12877546/how-do-i-avoid-implicit-conversions-on-non-constructing-functions) |  |
| 2146 | 99 | [How can I "unuse" a namespace?](https://stackoverflow.com/questions/167862/how-can-i-unuse-a-namespace) |  |
| 2148 | 99 | [ULL suffix on a numeric literal](https://stackoverflow.com/questions/8809292/ull-suffix-on-a-numeric-literal) |  |
| 2149 | 99 | [What's the C++ suffix for long double literals?](https://stackoverflow.com/questions/21557816/whats-the-c-suffix-for-long-double-literals) |  |
| 2150 | 99 | [const& , & and && specifiers for member functions in C++](https://stackoverflow.com/questions/28066777/const-and-specifiers-for-member-functions-in-c) |  |
| 2162 | 98 | [Why is the size of an empty class in C++ not zero?](https://stackoverflow.com/questions/2362097/why-is-the-size-of-an-empty-class-in-c-not-zero) |  |
| 2170 | 98 | [Is const_cast safe?](https://stackoverflow.com/questions/357600/is-const-cast-safe) |  |
| 2171 | 98 | [How to forward declare a class which is in a namespace](https://stackoverflow.com/questions/19001700/how-to-forward-declare-a-class-which-is-in-a-namespace) |  |
| 2191 | 97 | [Why design a language with unique anonymous types?](https://stackoverflow.com/questions/63172736/why-design-a-language-with-unique-anonymous-types) |  |
| 2207 | 97 | [Pedantic gcc warning: type qualifiers on function return type](https://stackoverflow.com/questions/1134237/pedantic-gcc-warning-type-qualifiers-on-function-return-type) |  |
| 2228 | 96 | [Declaring an object before initializing it in c++](https://stackoverflow.com/questions/800368/declaring-an-object-before-initializing-it-in-c) |  |
| 2232 | 96 | [In this specific case, is there a difference between using a member initializer list and assigning values in a constructor?](https://stackoverflow.com/questions/4589237/in-this-specific-case-is-there-a-difference-between-using-a-member-initializer) |  |
| 2242 | 96 | [What does it mean to "poison a function" in C++?](https://stackoverflow.com/questions/33964621/what-does-it-mean-to-poison-a-function-in-c) |  |
| 2244 | 96 | [Has the new C++11 member initialization feature at declaration made initialization lists obsolete?](https://stackoverflow.com/questions/24149924/has-the-new-c11-member-initialization-feature-at-declaration-made-initializati) |  |
| 2246 | 96 | [Can a declaration affect the std namespace?](https://stackoverflow.com/questions/50898508/can-a-declaration-affect-the-std-namespace) |  |
| 2247 | 96 | [Narrowing conversions in C++0x. Is it just me, or does this sound like a breaking change?](https://stackoverflow.com/questions/4434140/narrowing-conversions-in-c0x-is-it-just-me-or-does-this-sound-like-a-breakin) |  |
| 2248 | 96 | [Does there exist a static_warning?](https://stackoverflow.com/questions/8936063/does-there-exist-a-static-warning) |  |
| 2250 | 96 | [Default, value and zero initialization mess](https://stackoverflow.com/questions/29765961/default-value-and-zero-initialization-mess) |  |
| 2253 | 95 | [The usage of anonymous enums](https://stackoverflow.com/questions/7147008/the-usage-of-anonymous-enums) |  |
| 2275 | 95 | [Max and min values in a C++ enum](https://stackoverflow.com/questions/159006/max-and-min-values-in-a-c-enum) |  |
| 2276 | 95 | [What is the difference between a static and const variable?](https://stackoverflow.com/questions/2216239/what-is-the-difference-between-a-static-and-const-variable) |  |
| 2285 | 95 | [Initializing container of unique_ptrs from initializer list fails with GCC 4.7](https://stackoverflow.com/questions/9618268/initializing-container-of-unique-ptrs-from-initializer-list-fails-with-gcc-4-7) |  |
| 2292 | 94 | [Variable declarations in header files - static or not?](https://stackoverflow.com/questions/92546/variable-declarations-in-header-files-static-or-not) |  |
| 2294 | 94 | [performance of unsigned vs signed integers](https://stackoverflow.com/questions/4712315/performance-of-unsigned-vs-signed-integers) |  |
| 2314 | 94 | [How do I deal with "signed/unsigned mismatch" warnings (C4018)?](https://stackoverflow.com/questions/7443222/how-do-i-deal-with-signed-unsigned-mismatch-warnings-c4018) |  |
| 2325 | 93 | [volatile vs. mutable in C++](https://stackoverflow.com/questions/2444695/volatile-vs-mutable-in-c) |  |
| 2336 | 93 | [Is it possible to differentiate between 0 and -0?](https://stackoverflow.com/questions/29962627/is-it-possible-to-differentiate-between-0-and-0) |  |
| 2371 | 92 | [Enum vs Strongly typed enum](https://stackoverflow.com/questions/12581064/enum-vs-strongly-typed-enum) |  |
| 2373 | 92 | [Is it good practice to make getters and setters inline?](https://stackoverflow.com/questions/3017264/is-it-good-practice-to-make-getters-and-setters-inline) |  |
| 2374 | 92 | [Is there still a use for inline?](https://stackoverflow.com/questions/29796264/is-there-still-a-use-for-inline) |  |
| 2392 | 92 | [What is consteval?](https://stackoverflow.com/questions/53347298/what-is-consteval) |  |
| 2398 | 91 | [const int = int const?](https://stackoverflow.com/questions/3247285/const-int-int-const) |  |
| 2408 | 91 | [Refreshing the auto complete (IntelliSense) database in Visual Studio](https://stackoverflow.com/questions/18289936/refreshing-the-auto-complete-intellisense-database-in-visual-studio) |  |
| 2419 | 91 | [Why can a const member function modify a static data member?](https://stackoverflow.com/questions/43936404/why-can-a-const-member-function-modify-a-static-data-member) |  |
| 2421 | 91 | [Is sizeof in C++ evaluated at compilation time or run time?](https://stackoverflow.com/questions/2615203/is-sizeof-in-c-evaluated-at-compilation-time-or-run-time) |  |
| 2427 | 91 | [Extending enums in C++?](https://stackoverflow.com/questions/1804840/extending-enums-in-c) |  |
| 2436 | 90 | [Convert float to std::string in C++](https://stackoverflow.com/questions/2125880/convert-float-to-stdstring-in-c) |  |
| 2443 | 90 | [Long Vs. Int C/C++ - What's The Point?](https://stackoverflow.com/questions/7456902/long-vs-int-c-c-whats-the-point) |  |
| 2452 | 90 | [Allow for Range-Based For with enum classes?](https://stackoverflow.com/questions/8498300/allow-for-range-based-for-with-enum-classes) |  |
| 2478 | 90 | [How can I portably call a C++ function that takes a char** on some platforms and a const char** on others?](https://stackoverflow.com/questions/11421439/how-can-i-portably-call-a-c-function-that-takes-a-char-on-some-platforms-and) |  |
| 2479 | 90 | [Can a cast operator be explicit?](https://stackoverflow.com/questions/8239356/can-a-cast-operator-be-explicit) |  |
| 2490 | 89 | [How to make a for loop variable const with the exception of the increment statement?](https://stackoverflow.com/questions/63399816/how-to-make-a-for-loop-variable-const-with-the-exception-of-the-increment-statem) |  |
| 2501 | 89 | [What should be the sizeof(int) on a 64-bit machine?](https://stackoverflow.com/questions/10197242/what-should-be-the-sizeofint-on-a-64-bit-machine) |  |
| 2503 | 89 | [long long in C/C++](https://stackoverflow.com/questions/1458923/long-long-in-c-c) |  |
| 2514 | 89 | [What is the meaning of a const at end of a member function?](https://stackoverflow.com/questions/4059932/what-is-the-meaning-of-a-const-at-end-of-a-member-function) |  |
| 2523 | 89 | [Equivalent ternary operator for constexpr if?](https://stackoverflow.com/questions/41011900/equivalent-ternary-operator-for-constexpr-if) |  |
| 2550 | 88 | [Why do C and C++ allow the expression (int) + 4*5?](https://stackoverflow.com/questions/55783615/why-do-c-and-c-allow-the-expression-int-45) |  |
| 2555 | 88 | [Why are global and static variables initialized to their default values?](https://stackoverflow.com/questions/2091499/why-are-global-and-static-variables-initialized-to-their-default-values) |  |
| 2577 | 87 | [Why would you use 'extern "C++"'?](https://stackoverflow.com/questions/610934/why-would-you-use-extern-c) |  |
| 2581 | 87 | [Why would uint32_t be preferred rather than uint_fast32_t?](https://stackoverflow.com/questions/46959685/why-would-uint32-t-be-preferred-rather-than-uint-fast32-t) |  |
| 2587 | 87 | [non-trivial designated initializers not supported](https://stackoverflow.com/questions/31215971/non-trivial-designated-initializers-not-supported) |  |
| 2612 | 87 | [Why was std::bit_cast added, if reinterpret_cast could do the same?](https://stackoverflow.com/questions/53401654/why-was-stdbit-cast-added-if-reinterpret-cast-could-do-the-same) |  |
| 2619 | 86 | [Is there any reason to use the 'auto' keyword in C++03?](https://stackoverflow.com/questions/1046477/is-there-any-reason-to-use-the-auto-keyword-in-c03) |  |
| 2620 | 86 | [Does the size of an int depend on the compiler and/or processor?](https://stackoverflow.com/questions/2331751/does-the-size-of-an-int-depend-on-the-compiler-and-or-processor) |  |
| 2621 | 86 | [C++ style cast from unsigned char * to const char *](https://stackoverflow.com/questions/658913/c-style-cast-from-unsigned-char-to-const-char) |  |
| 2622 | 86 | [Is 'float a = 3.0;' a correct statement?](https://stackoverflow.com/questions/25229832/is-float-a-3-0-a-correct-statement) |  |
| 2629 | 86 | [const to Non-const Conversion in C++](https://stackoverflow.com/questions/7311041/const-to-non-const-conversion-in-c) |  |
| 2633 | 86 | [How to define different types for the same class in C++](https://stackoverflow.com/questions/14232293/how-to-define-different-types-for-the-same-class-in-c) |  |
| 2643 | 86 | [Why are references not "const" in C++?](https://stackoverflow.com/questions/38044834/why-are-references-not-const-in-c) |  |
| 2644 | 86 | [inline vs __inline vs __inline__ vs __forceinline?](https://stackoverflow.com/questions/2765164/inline-vs-inline-vs-inline-vs-forceinline) |  |
| 2656 | 86 | [long double vs double](https://stackoverflow.com/questions/3454576/long-double-vs-double) |  |
| 2666 | 85 | [const char* and char const* - are they the same?](https://stackoverflow.com/questions/8091770/const-char-and-char-const-are-they-the-same) |  |
| 2675 | 85 | [How is "int* ptr = int()" value initialization not illegal?](https://stackoverflow.com/questions/8067897/how-is-int-ptr-int-value-initialization-not-illegal) |  |
| 2677 | 85 | [How do I specify an integer literal of type unsigned char in C++?](https://stackoverflow.com/questions/2304732/how-do-i-specify-an-integer-literal-of-type-unsigned-char-in-c) |  |
| 2679 | 85 | [Why doesn't this reinterpret_cast compile?](https://stackoverflow.com/questions/2205353/why-doesnt-this-reinterpret-cast-compile) |  |
| 2680 | 85 | [Is using an unsigned rather than signed int more likely to cause bugs? Why?](https://stackoverflow.com/questions/51677855/is-using-an-unsigned-rather-than-signed-int-more-likely-to-cause-bugs-why) |  |
| 2692 | 85 | [C++ static initialization order](https://stackoverflow.com/questions/1005685/c-static-initialization-order) |  |
| 2693 | 85 | [Is it allowed for a compiler to optimize away a local volatile variable?](https://stackoverflow.com/questions/51472394/is-it-allowed-for-a-compiler-to-optimize-away-a-local-volatile-variable) |  |
| 2713 | 84 | [initialize a const array in a class initializer in C++](https://stackoverflow.com/questions/161790/initialize-a-const-array-in-a-class-initializer-in-c) |  |
| 2731 | 84 | [C++11 "auto" semantics](https://stackoverflow.com/questions/8542873/c11-auto-semantics) |  |
| 2740 | 84 | [When can I use explicit operator bool without a cast?](https://stackoverflow.com/questions/39995573/when-can-i-use-explicit-operator-bool-without-a-cast) |  |
| 2746 | 84 | [What's the difference between static constexpr and static inline variables in C++17?](https://stackoverflow.com/questions/45183324/whats-the-difference-between-static-constexpr-and-static-inline-variables-in-c) |  |
| 2749 | 84 | [Generic way to cast int to enum in C++](https://stackoverflow.com/questions/4165439/generic-way-to-cast-int-to-enum-in-c) |  |
| 2763 | 83 | [Using 'auto' type deduction - how to find out what type the compiler deduced?](https://stackoverflow.com/questions/38820579/using-auto-type-deduction-how-to-find-out-what-type-the-compiler-deduced) |  |
| 2774 | 83 | [Weird enum in destructor](https://stackoverflow.com/questions/33800783/weird-enum-in-destructor) |  |
| 2776 | 83 | [What does casting to `void` really do?](https://stackoverflow.com/questions/34288844/what-does-casting-to-void-really-do) |  |
| 2781 | 83 | [How can this structure have sizeof == 0?](https://stackoverflow.com/questions/47352663/how-can-this-structure-have-sizeof-0) |  |
| 2797 | 82 | [what is the size of an enum type data in C++?](https://stackoverflow.com/questions/8115550/what-is-the-size-of-an-enum-type-data-in-c) |  |
| 2810 | 82 | [When should I use typedef in C++?](https://stackoverflow.com/questions/516237/when-should-i-use-typedef-in-c) |  |
| 2817 | 82 | [How to cast the size_t to double or int C++](https://stackoverflow.com/questions/22184403/how-to-cast-the-size-t-to-double-or-int-c) |  |
| 2825 | 82 | [When should I make a function inline?](https://stackoverflow.com/questions/5971736/when-should-i-make-a-function-inline) |  |
| 2837 | 82 | [What is the difference between decltype and auto as a placeholder type for variables?](https://stackoverflow.com/questions/12084040/what-is-the-difference-between-decltype-and-auto-as-a-placeholder-type-for-varia) |  |
| 2838 | 82 | [Are default-initialized variables automatically zero?](https://stackoverflow.com/questions/6032638/are-default-initialized-variables-automatically-zero) |  |
| 2846 | 82 | [Mixing extern and const](https://stackoverflow.com/questions/2190919/mixing-extern-and-const) |  |
| 2855 | 82 | [enum vs constexpr for actual static constants inside classes](https://stackoverflow.com/questions/22867654/enum-vs-constexpr-for-actual-static-constants-inside-classes) |  |
| 2856 | 81 | [Why do I need to explicitly write the 'auto' keyword?](https://stackoverflow.com/questions/50483204/why-do-i-need-to-explicitly-write-the-auto-keyword) |  |
| 2874 | 81 | [Portably safe to pass NULL/zero to dynamic_cast?](https://stackoverflow.com/questions/5155820/portably-safe-to-pass-null-zero-to-dynamic-cast) |  |
| 2875 | 81 | [Declaring a variable with two types: "int char"](https://stackoverflow.com/questions/51239649/declaring-a-variable-with-two-types-int-char) |  |
| 2877 | 81 | [Get list of static libraries used in an executable](https://stackoverflow.com/questions/1124571/get-list-of-static-libraries-used-in-an-executable) |  |
| 2884 | 81 | [When are static C++ class members initialized?](https://stackoverflow.com/questions/1421671/when-are-static-c-class-members-initialized) |  |
| 2892 | 81 | [Where to declare/define class scope constants in C++?](https://stackoverflow.com/questions/2043493/where-to-declare-define-class-scope-constants-in-c) |  |
| 2910 | 80 | [C++ namespaces advice](https://stackoverflow.com/questions/713698/c-namespaces-advice) |  |
| 2915 | 80 | [error C2065: 'cout' : undeclared identifier](https://stackoverflow.com/questions/1868603/error-c2065-cout-undeclared-identifier) |  |
| 2959 | 79 | [In header files, what is the difference between a static global variable and a static data member?](https://stackoverflow.com/questions/3698043/in-header-files-what-is-the-difference-between-a-static-global-variable-and-a-s) |  |
| 2963 | 79 | [error: cast from 'void*' to 'int' loses precision](https://stackoverflow.com/questions/1640423/error-cast-from-void-to-int-loses-precision) |  |
| 2976 | 79 | [C/C++ global vs static global](https://stackoverflow.com/questions/7837190/c-c-global-vs-static-global) |  |
| 3009 | 78 | [What's the difference between sizeof and alignof?](https://stackoverflow.com/questions/11386946/whats-the-difference-between-sizeof-and-alignof) |  |
| 3019 | 78 | [Is there some ninja trick to make a variable constant after its declaration?](https://stackoverflow.com/questions/3669315/is-there-some-ninja-trick-to-make-a-variable-constant-after-its-declaration) |  |
| 3027 | 78 | [What are the differences between C-like, constructor, and uniform initialization?](https://stackoverflow.com/questions/24953658/what-are-the-differences-between-c-like-constructor-and-uniform-initialization) |  |
| 3030 | 78 | [What does "Symbol not found / Expected in: flat namespace" actually mean?](https://stackoverflow.com/questions/35006614/what-does-symbol-not-found-expected-in-flat-namespace-actually-mean) |  |
| 3031 | 78 | [Are there practical uses for dynamic-casting to void pointer?](https://stackoverflow.com/questions/8123776/are-there-practical-uses-for-dynamic-casting-to-void-pointer) |  |
| 3045 | 77 | [Why use !! when converting int to bool?](https://stackoverflow.com/questions/1310344/why-use-when-converting-int-to-bool) |  |
| 3050 | 77 | [What does this typedef statement mean?](https://stackoverflow.com/questions/22061750/what-does-this-typedef-statement-mean) |  |
| 3052 | 77 | [What is the difference between #define and const?](https://stackoverflow.com/questions/6442328/what-is-the-difference-between-define-and-const) |  |
| 3067 | 77 | [Global scope vs global namespace](https://stackoverflow.com/questions/10269012/global-scope-vs-global-namespace) |  |
| 3070 | 77 | [Why does constexpr seemingly not imply const for char*?](https://stackoverflow.com/questions/28845058/why-does-constexpr-seemingly-not-imply-const-for-char) |  |
| 3073 | 77 | [How does a failed static_assert work in an if constexpr (false) block?](https://stackoverflow.com/questions/38304847/how-does-a-failed-static-assert-work-in-an-if-constexpr-false-block) |  |
| 3088 | 77 | [Enum variable default value?](https://stackoverflow.com/questions/6842799/enum-variable-default-value) |  |
| 3097 | 76 | [int vs const int&](https://stackoverflow.com/questions/4705593/int-vs-const-int) |  |
| 3108 | 76 | [Getting a bunch of crosses initialization error](https://stackoverflow.com/questions/11578936/getting-a-bunch-of-crosses-initialization-error) |  |
| 3110 | 76 | [casting non const to const in c++](https://stackoverflow.com/questions/5853833/casting-non-const-to-const-in-c) |  |
| 3139 | 76 | [Why do some people prefer "T const&" over "const T&"?](https://stackoverflow.com/questions/2640446/why-do-some-people-prefer-t-const-over-const-t) |  |
| 3140 | 76 | [Unsigned double in C++?](https://stackoverflow.com/questions/2523025/unsigned-double-in-c) |  |
| 3146 | 76 | [Enum to String C++](https://stackoverflow.com/questions/6281461/enum-to-string-c) |  |
| 3157 | 76 | [Integrate type name in static_assert output?](https://stackoverflow.com/questions/6415186/integrate-type-name-in-static-assert-output) |  |
| 3158 | 75 | [Binary literals](https://stackoverflow.com/questions/537303/binary-literals) |  |
| 3182 | 75 | [Returning a const reference to an object instead of a copy](https://stackoverflow.com/questions/134731/returning-a-const-reference-to-an-object-instead-of-a-copy) |  |
| 3183 | 75 | [When does a constexpr function get evaluated at compile time?](https://stackoverflow.com/questions/14248235/when-does-a-constexpr-function-get-evaluated-at-compile-time) |  |
| 3216 | 75 | [What is the difference in const-correctness between C and C++?](https://stackoverflow.com/questions/8908071/what-is-the-difference-in-const-correctness-between-c-and-c) |  |
| 3224 | 74 | [What does the compiler do here: int a = b * (c * d * + e)?](https://stackoverflow.com/questions/30361112/what-does-the-compiler-do-here-int-a-b-c-d-e) |  |
| 3237 | 74 | [what is the new feature in c++20 \[\[no_unique_address\]\]?](https://stackoverflow.com/questions/62784750/what-is-the-new-feature-in-c20-no-unique-address) |  |
| 3240 | 74 | [C++ singleton vs. global static object](https://stackoverflow.com/questions/1463707/c-singleton-vs-global-static-object) |  |
| 3246 | 74 | [Doesn't constraining the "auto" in C++ defeat the purpose of it?](https://stackoverflow.com/questions/69801126/doesnt-constraining-the-auto-in-c-defeat-the-purpose-of-it) |  |
| 3256 | 74 | [Why must const members be initialized in the constructor initializer rather than in its body?](https://stackoverflow.com/questions/355258/why-must-const-members-be-initialized-in-the-constructor-initializer-rather-than) |  |
| 3262 | 74 | [fixed length data types in C/C++](https://stackoverflow.com/questions/20237451/fixed-length-data-types-in-c-c) |  |
| 3263 | 74 | [Proper way of casting pointer types](https://stackoverflow.com/questions/15578935/proper-way-of-casting-pointer-types) |  |
| 3300 | 73 | [C++ cannot convert from base A to derived type B via virtual base A](https://stackoverflow.com/questions/3747066/c-cannot-convert-from-base-a-to-derived-type-b-via-virtual-base-a) |  |
| 3302 | 73 | [What is the difference between static_cast and reinterpret_cast?](https://stackoverflow.com/questions/6855686/what-is-the-difference-between-static-cast-and-reinterpret-cast) |  |
| 3307 | 73 | [Does true equal to 1 and false equal to 0?](https://stackoverflow.com/questions/5189072/does-true-equal-to-1-and-false-equal-to-0) |  |
| 3324 | 73 | [Do C++ enums Start at 0?](https://stackoverflow.com/questions/34811486/do-c-enums-start-at-0) |  |
| 3327 | 73 | [Uses of unnamed namespace in C++](https://stackoverflow.com/questions/5312213/uses-of-unnamed-namespace-in-c) |  |
| 3347 | 72 | [C++ "multiple types in one declaration" error](https://stackoverflow.com/questions/1753189/c-multiple-types-in-one-declaration-error) |  |
| 3353 | 72 | [Why is sizeof(unsigned double) equal to 4?](https://stackoverflow.com/questions/14977454/why-is-sizeofunsigned-double-equal-to-4) |  |
| 3354 | 72 | [C++ floating point to integer type conversions](https://stackoverflow.com/questions/2544394/c-floating-point-to-integer-type-conversions) |  |
| 3365 | 72 | [How to use const_cast?](https://stackoverflow.com/questions/19554841/how-to-use-const-cast) |  |
| 3366 | 72 | [What is an 'undeclared identifier' error and how do I fix it?](https://stackoverflow.com/questions/22197030/what-is-an-undeclared-identifier-error-and-how-do-i-fix-it) |  |
| 3368 | 72 | [Finding C++ static initialization order problems](https://stackoverflow.com/questions/335369/finding-c-static-initialization-order-problems) |  |
| 3370 | 72 | [Why does bool and not bool both return true in this case?](https://stackoverflow.com/questions/23268357/why-does-bool-and-not-bool-both-return-true-in-this-case) |  |
| 3380 | 72 | [Explanation of \[\[nodiscard\]\] in C++17](https://stackoverflow.com/questions/76489630/explanation-of-nodiscard-in-c17) |  |
| 3396 | 72 | [What is the maximum length in chars needed to represent any double value?](https://stackoverflow.com/questions/1701055/what-is-the-maximum-length-in-chars-needed-to-represent-any-double-value) |  |
| 3397 | 72 | [Why is size_t unsigned?](https://stackoverflow.com/questions/10168079/why-is-size-t-unsigned) |  |
| 3411 | 71 | [Why would you use the keyword const if you already know variable should be constant?](https://stackoverflow.com/questions/18157523/why-would-you-use-the-keyword-const-if-you-already-know-variable-should-be-const) |  |
| 3424 | 71 | [How to declare a static const char* in your header file?](https://stackoverflow.com/questions/1639154/how-to-declare-a-static-const-char-in-your-header-file) |  |
| 3427 | 71 | [double or float, which is faster?](https://stackoverflow.com/questions/4584637/double-or-float-which-is-faster) |  |
| 3441 | 71 | [Is there any way to make Visual Studio stop indenting namespaces?](https://stackoverflow.com/questions/3727862/is-there-any-way-to-make-visual-studio-stop-indenting-namespaces) |  |
| 3443 | 71 | [Why is C++ allowing me to assign a const char to a const char *?​!](https://stackoverflow.com/questions/12024706/why-is-c-allowing-me-to-assign-a-const-char-to-a-const-char) |  |
| 3462 | 71 | [Why would someone use #define to define constants?](https://stackoverflow.com/questions/6274008/why-would-someone-use-define-to-define-constants) |  |
| 3466 | 71 | [Namespace without a name in C++](https://stackoverflow.com/questions/5238932/namespace-without-a-name-in-c) |  |
| 3472 | 71 | [Why does the compiler match "char" to "int" but not "short"?](https://stackoverflow.com/questions/37166131/why-does-the-compiler-match-char-to-int-but-not-short) |  |
| 3475 | 71 | [Why is my log in the std namespace?](https://stackoverflow.com/questions/11892976/why-is-my-log-in-the-std-namespace) |  |
| 3480 | 71 | [When would I use std::integral_constant over constexpr?](https://stackoverflow.com/questions/20368187/when-would-i-use-stdintegral-constant-over-constexpr) |  |
| 3488 | 70 | [Why main() in C++ cannot be inlined?](https://stackoverflow.com/questions/6981104/why-main-in-c-cannot-be-inlined) |  |
| 3491 | 70 | [Initialize integer literal to std::size_t](https://stackoverflow.com/questions/22346369/initialize-integer-literal-to-stdsize-t) |  |
| 3500 | 70 | [Difference in behavior while using dynamic_cast with reference and pointers](https://stackoverflow.com/questions/1276847/difference-in-behavior-while-using-dynamic-cast-with-reference-and-pointers) |  |
| 3514 | 70 | [Why does C++ promote an int to a float when a float cannot represent all int values?](https://stackoverflow.com/questions/28010565/why-does-c-promote-an-int-to-a-float-when-a-float-cannot-represent-all-int-val) |  |
| 3519 | 70 | [Do negative numbers return false in C/C++?](https://stackoverflow.com/questions/18840422/do-negative-numbers-return-false-in-c-c) |  |
| 3520 | 70 | [How do I get a const_iterator using auto?](https://stackoverflow.com/questions/15233188/how-do-i-get-a-const-iterator-using-auto) |  |
| 3537 | 70 | [How to check if enum value is valid?](https://stackoverflow.com/questions/4969233/how-to-check-if-enum-value-is-valid) |  |
| 3544 | 70 | [Why can't non-static data members be constexpr?](https://stackoverflow.com/questions/27408819/why-cant-non-static-data-members-be-constexpr) |  |
| 3545 | 70 | [Remove reference in decltype (return T instead of T& where T& is the decltype)](https://stackoverflow.com/questions/13202289/remove-reference-in-decltype-return-t-instead-of-t-where-t-is-the-decltype) |  |
| 3550 | 70 | [Are there any uses for unnamed namespaces in header files?](https://stackoverflow.com/questions/357564/are-there-any-uses-for-unnamed-namespaces-in-header-files) |  |
| 3572 | 69 | [C++ Global variable declaration](https://stackoverflow.com/questions/19929681/c-global-variable-declaration) |  |
| 3641 | 68 | [Using enum inside types - Compiler warning C4482 C++](https://stackoverflow.com/questions/514194/using-enum-inside-types-compiler-warning-c4482-c) |  |
| 3651 | 68 | [static vs non-static variables in namespace](https://stackoverflow.com/questions/11623451/static-vs-non-static-variables-in-namespace) |  |
| 3658 | 68 | [What are top-level const qualifiers?](https://stackoverflow.com/questions/7914444/what-are-top-level-const-qualifiers) |  |
| 3662 | 68 | [When is uint8_t ≠ unsigned char?](https://stackoverflow.com/questions/16138237/when-is-uint8-t-%e2%89%a0-unsigned-char) |  |
| 3668 | 68 | [const vector implies const elements?](https://stackoverflow.com/questions/27065617/const-vector-implies-const-elements) |  |
| 3677 | 68 | [Reinterpret_cast vs. C-style cast](https://stackoverflow.com/questions/7831696/reinterpret-cast-vs-c-style-cast) |  |
| 3694 | 68 | [When and why would you use static with constexpr?](https://stackoverflow.com/questions/26152096/when-and-why-would-you-use-static-with-constexpr) |  |
| 3709 | 67 | [How can I intentionally discard a \[\[nodiscard\]\] return value?](https://stackoverflow.com/questions/53581744/how-can-i-intentionally-discard-a-nodiscard-return-value) |  |
| 3725 | 67 | [static const vs. const static](https://stackoverflow.com/questions/12005959/static-const-vs-const-static) |  |
| 3732 | 67 | [Use of constexpr in header file](https://stackoverflow.com/questions/50488831/use-of-constexpr-in-header-file) |  |
| 3735 | 67 | [How to Get enum item name from its value](https://stackoverflow.com/questions/11714325/how-to-get-enum-item-name-from-its-value) |  |
| 3739 | 67 | [Can a near-zero floating value cause a divide-by-zero error?](https://stackoverflow.com/questions/12114498/can-a-near-zero-floating-value-cause-a-divide-by-zero-error) |  |
| 3742 | 67 | [What is the actual use of "signed" keyword?](https://stackoverflow.com/questions/28012943/what-is-the-actual-use-of-signed-keyword) |  |
| 3753 | 67 | [C++11 - declaring non-static data members as 'auto'](https://stackoverflow.com/questions/11302981/c11-declaring-non-static-data-members-as-auto) |  |
| 3758 | 67 | [scope of using declaration within a namespace](https://stackoverflow.com/questions/6175705/scope-of-using-declaration-within-a-namespace) |  |
| 3765 | 67 | [What's the point of const void?](https://stackoverflow.com/questions/5057987/whats-the-point-of-const-void) |  |
| 3766 | 67 | [Why can't I static_cast between char * and unsigned char *?](https://stackoverflow.com/questions/10151834/why-cant-i-static-cast-between-char-and-unsigned-char) |  |
| 3771 | 67 | [Why isn't `std::initializer_list` defined as a literal type?](https://stackoverflow.com/questions/27496004/why-isnt-stdinitializer-list-defined-as-a-literal-type) |  |
| 3791 | 66 | [Iterating over different types](https://stackoverflow.com/questions/34314193/iterating-over-different-types) |  |
| 3798 | 66 | [What is the underlying type of a c++ enum?](https://stackoverflow.com/questions/1122096/what-is-the-underlying-type-of-a-c-enum) |  |
| 3800 | 66 | [Why is argc an 'int' (rather than an 'unsigned int')?](https://stackoverflow.com/questions/1773897/why-is-argc-an-int-rather-than-an-unsigned-int) |  |
| 3837 | 66 | [Using an enum as an array index](https://stackoverflow.com/questions/404231/using-an-enum-as-an-array-index) |  |
| 3868 | 66 | [Why does auto x{3} deduce an initializer_list?](https://stackoverflow.com/questions/25612262/why-does-auto-x3-deduce-an-initializer-list) |  |
| 3870 | 66 | [What is the return type of sizeof operator?](https://stackoverflow.com/questions/19870192/what-is-the-return-type-of-sizeof-operator) |  |
| 3878 | 65 | [Namespaces in C](https://stackoverflow.com/questions/389827/namespaces-in-c) |  |
| 3897 | 65 | [Why are unsigned integers error prone?](https://stackoverflow.com/questions/30395205/why-are-unsigned-integers-error-prone) |  |
| 3909 | 65 | [Is this self initialization valid?](https://stackoverflow.com/questions/3309042/is-this-self-initialization-valid) |  |
| 3921 | 65 | [Can you use keyword explicit to prevent automatic conversion of method parameters?](https://stackoverflow.com/questions/175689/can-you-use-keyword-explicit-to-prevent-automatic-conversion-of-method-parameter) |  |
| 3926 | 65 | [Why do the C++ language designers keep re-using keywords?](https://stackoverflow.com/questions/32757571/why-do-the-c-language-designers-keep-re-using-keywords) |  |
| 3955 | 65 | [Whyever **not** declare a function to be `constexpr`?](https://stackoverflow.com/questions/5112305/whyever-not-declare-a-function-to-be-constexpr) |  |
| 3962 | 64 | [Do we really need "enum class" in C++11?](https://stackoverflow.com/questions/6936030/do-we-really-need-enum-class-in-c11) |  |
| 3968 | 64 | [C++11 auto declaration with and without pointer declarator](https://stackoverflow.com/questions/34560365/c11-auto-declaration-with-and-without-pointer-declarator) |  |
| 3981 | 64 | [Difference between static in C and static in C++??](https://stackoverflow.com/questions/943280/difference-between-static-in-c-and-static-in-c) |  |
| 3994 | 64 | [How do sizeof(arr) / sizeof(arr\[0\]) work?](https://stackoverflow.com/questions/33523585/how-do-sizeofarr-sizeofarr0-work) |  |
| 4027 | 64 | [What's the difference between const array and static const array in C/C++](https://stackoverflow.com/questions/56057662/whats-the-difference-between-const-array-and-static-const-array-in-c-c) |  |
| 4031 | 64 | [C++11 member initializer list vs in-class initializer?](https://stackoverflow.com/questions/27352021/c11-member-initializer-list-vs-in-class-initializer) |  |
| 4040 | 64 | [Strongly typed using and typedef](https://stackoverflow.com/questions/34287842/strongly-typed-using-and-typedef) |  |
| 4056 | 63 | [Adding smallest possible float to a float](https://stackoverflow.com/questions/41317661/adding-smallest-possible-float-to-a-float) |  |
| 4058 | 63 | [My enum is not a class or namespace](https://stackoverflow.com/questions/5188554/my-enum-is-not-a-class-or-namespace) |  |
| 4059 | 63 | [What is the use of "using namespace std"?](https://stackoverflow.com/questions/18914106/what-is-the-use-of-using-namespace-std) |  |
| 4063 | 63 | [Destruction order of static objects in C++](https://stackoverflow.com/questions/469597/destruction-order-of-static-objects-in-c) |  |
| 4064 | 63 | [int to unsigned int conversion](https://stackoverflow.com/questions/4975340/int-to-unsigned-int-conversion) |  |
| 4075 | 63 | [What's the difference between long long and long](https://stackoverflow.com/questions/6462439/whats-the-difference-between-long-long-and-long) |  |
| 4092 | 63 | [Why does `int ;` compile fine in C, but not in C++?](https://stackoverflow.com/questions/33273550/why-does-int-compile-fine-in-c-but-not-in-c) |  |
| 4103 | 63 | [C++ extern keyword on functions. Why no just include the header file?](https://stackoverflow.com/questions/2604202/c-extern-keyword-on-functions-why-no-just-include-the-header-file) |  |
| 4105 | 63 | [C++11 - static_assert within constexpr function?](https://stackoverflow.com/questions/8626055/c11-static-assert-within-constexpr-function) |  |
| 4123 | 63 | [Are function static variables thread-safe in GCC?](https://stackoverflow.com/questions/1270927/are-function-static-variables-thread-safe-in-gcc) |  |
| 4135 | 62 | [M_PI flagged as undeclared identifier](https://stackoverflow.com/questions/26065359/m-pi-flagged-as-undeclared-identifier) |  |
| 4137 | 62 | [warning C4003 and errors C2589 and C2059 on: x = std::numeric_limits<int>::max();](https://stackoverflow.com/questions/1904635/warning-c4003-and-errors-c2589-and-c2059-on-x-stdnumeric-limitsintmax) |  |
| 4163 | 62 | [#define statements within a namespace](https://stackoverflow.com/questions/1088290/define-statements-within-a-namespace) |  |
| 4196 | 62 | [Are there types bigger than long long int in C++?](https://stackoverflow.com/questions/5381882/are-there-types-bigger-than-long-long-int-in-c) |  |
| 4203 | 62 | [Class static variable initialization order](https://stackoverflow.com/questions/51279270/class-static-variable-initialization-order) |  |
| 4208 | 62 | [Why is `const T&` not sure to be const?](https://stackoverflow.com/questions/54480599/why-is-const-t-not-sure-to-be-const) |  |
| 4216 | 62 | [Why is most uses of volatile deprecated in C++20?](https://stackoverflow.com/questions/59223814/why-is-most-uses-of-volatile-deprecated-in-c20) |  |
| 4217 | 62 | [Does a declaration using "auto" match an extern declaration that uses a concrete type specifier?](https://stackoverflow.com/questions/26386010/does-a-declaration-using-auto-match-an-extern-declaration-that-uses-a-concrete) |  |
| 4281 | 61 | [Why not mark everything inline?](https://stackoverflow.com/questions/3999806/why-not-mark-everything-inline) |  |
| 4284 | 61 | [constexpr overloading](https://stackoverflow.com/questions/8936549/constexpr-overloading) |  |
| 4287 | 61 | [How to write an unsigned short int literal?](https://stackoverflow.com/questions/1329163/how-to-write-an-unsigned-short-int-literal) |  |
| 4312 | 60 | [Why use abs() or fabs() instead of conditional negation?](https://stackoverflow.com/questions/48608993/why-use-abs-or-fabs-instead-of-conditional-negation) |  |
| 4313 | 60 | [Why is my HelloWorld function not declared in this scope?](https://stackoverflow.com/questions/8234484/why-is-my-helloworld-function-not-declared-in-this-scope) |  |
| 4323 | 60 | [Check double variable if it contains an integer](https://stackoverflow.com/questions/1521607/check-double-variable-if-it-contains-an-integer) |  |
| 4354 | 60 | [Is bool guaranteed to be 0 or 1 when converted to int?](https://stackoverflow.com/questions/4276207/is-bool-guaranteed-to-be-0-or-1-when-converted-to-int) |  |
| 4362 | 60 | [Is there const in C?](https://stackoverflow.com/questions/5248571/is-there-const-in-c) |  |
| 4374 | 60 | [Can sizeof return 0 (zero)](https://stackoverflow.com/questions/2632021/can-sizeof-return-0-zero) |  |
| 4379 | 60 | [C++ Linker Error With Class static constexpr](https://stackoverflow.com/questions/8452952/c-linker-error-with-class-static-constexpr) |  |
| 4390 | 60 | [c++ how to have same enum members name in different enum names without getting err:redefinition; previous definition was 'enumerator'](https://stackoverflow.com/questions/23288934/c-how-to-have-same-enum-members-name-in-different-enum-names-without-getting-e) |  |
| 4392 | 60 | [Elaborated-type-specifier for a scoped enum must not use the ‘class’ keyword](https://stackoverflow.com/questions/20459120/elaborated-type-specifier-for-a-scoped-enum-must-not-use-the-class-keyword) |  |
| 4413 | 60 | [What is the modern, correct way to do type punning in C++?](https://stackoverflow.com/questions/67636231/what-is-the-modern-correct-way-to-do-type-punning-in-c) |  |
| 4421 | 59 | [How can I make a variable always equal to the result of some calculations?](https://stackoverflow.com/questions/55402807/how-can-i-make-a-variable-always-equal-to-the-result-of-some-calculations) |  |
| 4432 | 59 | [Using decltype to get an expression's type, without the const](https://stackoverflow.com/questions/19235496/using-decltype-to-get-an-expressions-type-without-the-const) |  |
| 4441 | 59 | [In C++11 is sqrt defined as constexpr?](https://stackoverflow.com/questions/8622256/in-c11-is-sqrt-defined-as-constexpr) |  |
| 4449 | 59 | [When to use `short` over `int`?](https://stackoverflow.com/questions/24371077/when-to-use-short-over-int) |  |
| 4462 | 59 | [Is std::is_unsigned<bool>::value well defined?](https://stackoverflow.com/questions/34612344/is-stdis-unsignedboolvalue-well-defined) |  |
| 4463 | 59 | [Type safe physics operations in C++](https://stackoverflow.com/questions/19910888/type-safe-physics-operations-in-c) |  |
| 4487 | 59 | [What makes a static variable initialize only once?](https://stackoverflow.com/questions/5567529/what-makes-a-static-variable-initialize-only-once) |  |
| 4495 | 59 | [invalid use of non-static data member](https://stackoverflow.com/questions/9590265/invalid-use-of-non-static-data-member) |  |
| 4498 | 59 | [static constexpr variable vs function](https://stackoverflow.com/questions/16287776/static-constexpr-variable-vs-function) |  |
| 4514 | 59 | [How should I write my C++ to be prepared for C++ modules?](https://stackoverflow.com/questions/34652029/how-should-i-write-my-c-to-be-prepared-for-c-modules) |  |
| 4560 | 58 | [Casting int to bool in C/C++](https://stackoverflow.com/questions/31551888/casting-int-to-bool-in-c-c) |  |
| 4591 | 58 | [What is the rationale behind decltype behavior?](https://stackoverflow.com/questions/40282118/what-is-the-rationale-behind-decltype-behavior) |  |
| 4595 | 58 | [C++ inlining class methods causes undefined reference](https://stackoverflow.com/questions/4769479/c-inlining-class-methods-causes-undefined-reference) |  |
| 4598 | 58 | [In C/C++, is there a directive similar to #ifndef for typedefs?](https://stackoverflow.com/questions/6772802/in-c-c-is-there-a-directive-similar-to-ifndef-for-typedefs) |  |
| 4613 | 58 | [Is it possible to manually define a conversion for an enum class?](https://stackoverflow.com/questions/12753543/is-it-possible-to-manually-define-a-conversion-for-an-enum-class) |  |
| 4618 | 58 | [Why is the restrict keyword not part of C++?](https://stackoverflow.com/questions/22724980/why-is-the-restrict-keyword-not-part-of-c) |  |
| 4670 | 57 | [Correct usage(s) of const_cast<>](https://stackoverflow.com/questions/2673508/correct-usages-of-const-cast) |  |
| 4678 | 57 | [How much memory do Enums take?](https://stackoverflow.com/questions/143285/how-much-memory-do-enums-take) |  |
| 4689 | 57 | [Are there any downsides to marking all variables you don't modify const?](https://stackoverflow.com/questions/38925121/are-there-any-downsides-to-marking-all-variables-you-dont-modify-const) |  |
| 4695 | 57 | [What does "typedef void (*Something)()" mean](https://stackoverflow.com/questions/3982470/what-does-typedef-void-something-mean) |  |
| 4702 | 57 | [What does the 'void()' in 'auto f(params) -> decltype(..., void())' do?](https://stackoverflow.com/questions/14003366/what-does-the-void-in-auto-fparams-decltype-void-do) |  |
| 4713 | 57 | [How are templates handled in C++ module system?](https://stackoverflow.com/questions/43861385/how-are-templates-handled-in-c-module-system) |  |
| 4714 | 57 | [Does specifying constexpr on a constructor automatically make all objects created from it to be constexpr?](https://stackoverflow.com/questions/31375381/does-specifying-constexpr-on-a-constructor-automatically-make-all-objects-create) |  |
| 4731 | 56 | [Static global variables in C++](https://stackoverflow.com/questions/14349877/static-global-variables-in-c) |  |
| 4760 | 56 | [Why do C programmers use typedefs to rename basic types?](https://stackoverflow.com/questions/3340843/why-do-c-programmers-use-typedefs-to-rename-basic-types) |  |
| 4763 | 56 | [C++ static local function vs global function](https://stackoverflow.com/questions/14742664/c-static-local-function-vs-global-function) |  |
| 4789 | 56 | [Easy way find uninitialized member variables](https://stackoverflow.com/questions/2099692/easy-way-find-uninitialized-member-variables) |  |
| 4799 | 56 | [Equivalent of "using namespace X" for scoped enumerations?](https://stackoverflow.com/questions/9450338/equivalent-of-using-namespace-x-for-scoped-enumerations) |  |
| 4801 | 56 | [Why do we need to mark functions as constexpr?](https://stackoverflow.com/questions/14472359/why-do-we-need-to-mark-functions-as-constexpr) |  |
| 4812 | 56 | [A confusing typedef involves class scope](https://stackoverflow.com/questions/33764533/a-confusing-typedef-involves-class-scope) |  |
| 4815 | 56 | [When does lvalue-to-rvalue conversion happen, how does it work, and can it fail?](https://stackoverflow.com/questions/20850536/when-does-lvalue-to-rvalue-conversion-happen-how-does-it-work-and-can-it-fail) |  |
| 4840 | 55 | [Is !! a safe way to convert to bool in C++?](https://stackoverflow.com/questions/206106/is-a-safe-way-to-convert-to-bool-in-c) |  |
| 4851 | 55 | [Difference between classes and namespaces?](https://stackoverflow.com/questions/3188156/difference-between-classes-and-namespaces) |  |
| 4854 | 55 | [sizeof a union in C/C++](https://stackoverflow.com/questions/740577/sizeof-a-union-in-c-c) |  |
| 4857 | 55 | [Is it better to remove "const" in front of "primitive" types used as function parameters in the header?](https://stackoverflow.com/questions/46292490/is-it-better-to-remove-const-in-front-of-primitive-types-used-as-function-pa) |  |
| 4858 | 55 | [Can I mimic a C header that redefines bool in C++?](https://stackoverflow.com/questions/21966230/can-i-mimic-a-c-header-that-redefines-bool-in-c) |  |
| 4860 | 55 | [Difference between Enum and Define Statements](https://stackoverflow.com/questions/136946/difference-between-enum-and-define-statements) |  |
| 4889 | 55 | [C++ - value of uninitialized vector<int>](https://stackoverflow.com/questions/5222404/c-value-of-uninitialized-vectorint) |  |
| 4891 | 55 | [In what order are non-static data members initialized?](https://stackoverflow.com/questions/2669888/in-what-order-are-non-static-data-members-initialized) |  |
| 4936 | 55 | [Why is C++11 constexpr so restrictive?](https://stackoverflow.com/questions/8308812/why-is-c11-constexpr-so-restrictive) |  |
| 4959 | 55 | [Enumerating monitors on a computer](https://stackoverflow.com/questions/18022612/enumerating-monitors-on-a-computer) |  |
| 4972 | 54 | [How to convert enum to QString?](https://stackoverflow.com/questions/34281682/how-to-convert-enum-to-qstring) |  |
| 4992 | 54 | [Why do C++ classes without member variables occupy space?](https://stackoverflow.com/questions/25786853/why-do-c-classes-without-member-variables-occupy-space) |  |
