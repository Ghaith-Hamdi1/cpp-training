# Memory, pointers and smart pointers

[Back to all topics](README.md)

358 questions, 4 with a carousel already.

Source: the 5,000 most voted questions tagged `c++` (the first 100 pages of 50 at <https://stackoverflow.com/questions/tagged/c%2b%2b?tab=votes&pagesize=50>), fetched on 2026-11-02 through the Stack Exchange API, sorted by votes. The lowest score included is 54 votes. Ties within the same score can be in a slightly different order than the website.

| Rank | Votes | Question | |
|---:|---:|---|---|
| 8 | 3,192 | [When should static_cast, dynamic_cast, const_cast, and reinterpret_cast be used?](https://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-const-cast-and-reinterpret-cast-be-used) | ✅ #10 |
| 18 | 2,197 | [What is a smart pointer and when should I use one?](https://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one) |  |
| 26 | 1,915 | [Why should I use a pointer rather than the object itself?](https://stackoverflow.com/questions/22146094/why-should-i-use-a-pointer-rather-than-the-object-itself) | ✅ #2 |
| 47 | 1,175 | [Can a local variable's memory be accessed outside its scope?](https://stackoverflow.com/questions/6441218/can-a-local-variables-memory-be-accessed-outside-its-scope) |  |
| 50 | 1,124 | [Do the parentheses after the type name make a difference with new?](https://stackoverflow.com/questions/620137/do-the-parentheses-after-the-type-name-make-a-difference-with-new) |  |
| 60 | 1,002 | [Why should C++ programmers minimize use of 'new'?](https://stackoverflow.com/questions/6500313/why-should-c-programmers-minimize-use-of-new) |  |
| 69 | 909 | [What is a segmentation fault?](https://stackoverflow.com/questions/2346806/what-is-a-segmentation-fault) |  |
| 84 | 807 | [Why is my program slow when looping over exactly 8192 elements?](https://stackoverflow.com/questions/12264970/why-is-my-program-slow-when-looping-over-exactly-8192-elements) |  |
| 91 | 787 | [How to determine CPU and memory consumption from inside a process](https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process) |  |
| 109 | 713 | [What does 'dereferencing' a pointer mean in C/C++?](https://stackoverflow.com/questions/4955198/what-does-dereferencing-a-pointer-mean-in-c-c) | ✅ #1 |
| 114 | 698 | [What is the nullptr keyword, and why is it better than NULL?](https://stackoverflow.com/questions/1282295/what-is-the-nullptr-keyword-and-why-is-it-better-than-null) |  |
| 134 | 630 | [In what cases do I use malloc and/or new?](https://stackoverflow.com/questions/184537/in-what-cases-do-i-use-malloc-and-or-new) |  |
| 150 | 581 | [Typedef function pointer?](https://stackoverflow.com/questions/4295432/typedef-function-pointer) |  |
| 163 | 552 | [Which is faster: Stack allocation or Heap allocation](https://stackoverflow.com/questions/161053/which-is-faster-stack-allocation-or-heap-allocation) |  |
| 173 | 535 | [What is meant by Resource Acquisition is Initialization (RAII)?](https://stackoverflow.com/questions/2321511/what-is-meant-by-resource-acquisition-is-initialization-raii) |  |
| 178 | 530 | [What uses are there for "placement new"?](https://stackoverflow.com/questions/222557/what-uses-are-there-for-placement-new) |  |
| 186 | 512 | [How do I pass a unique_ptr argument to a constructor or a function?](https://stackoverflow.com/questions/8114276/how-do-i-pass-a-unique-ptr-argument-to-a-constructor-or-a-function) |  |
| 188 | 509 | [What is array-to-pointer conversion aka. decay?](https://stackoverflow.com/questions/1461432/what-is-array-to-pointer-conversion-aka-decay) |  |
| 201 | 481 | [How many levels of pointers can we have?](https://stackoverflow.com/questions/10087113/how-many-levels-of-pointers-can-we-have) |  |
| 206 | 472 | [Why use pointers?](https://stackoverflow.com/questions/162941/why-use-pointers) |  |
| 208 | 468 | [What are the barriers to understanding pointers and what can be done to overcome them?](https://stackoverflow.com/questions/5727/what-are-the-barriers-to-understanding-pointers-and-what-can-be-done-to-overcome) |  |
| 245 | 418 | [Difference in make_shared and normal shared_ptr in C++](https://stackoverflow.com/questions/20895648/difference-in-make-shared-and-normal-shared-ptr-in-c) |  |
| 259 | 402 | [Should we pass a shared_ptr by reference or by value?](https://stackoverflow.com/questions/3310737/should-we-pass-a-shared-ptr-by-reference-or-by-value) |  |
| 262 | 400 | [What is the purpose of std::launder?](https://stackoverflow.com/questions/39382501/what-is-the-purpose-of-stdlaunder) |  |
| 267 | 396 | [When is std::weak_ptr useful?](https://stackoverflow.com/questions/12030650/when-is-stdweak-ptr-useful) |  |
| 297 | 371 | [NULL vs nullptr (Why was it replaced?)](https://stackoverflow.com/questions/20509734/null-vs-nullptr-why-was-it-replaced) |  |
| 301 | 368 | [When should I use the new keyword in C++?](https://stackoverflow.com/questions/655065/when-should-i-use-the-new-keyword-in-c) |  |
| 303 | 366 | [Is it safe to delete a NULL pointer?](https://stackoverflow.com/questions/4190703/is-it-safe-to-delete-a-null-pointer) |  |
| 304 | 365 | [Differences between unique_ptr and shared_ptr](https://stackoverflow.com/questions/6876751/differences-between-unique-ptr-and-shared-ptr) |  |
| 312 | 356 | [Meaning of `= delete` after function declaration](https://stackoverflow.com/questions/5513881/meaning-of-delete-after-function-declaration) |  |
| 350 | 336 | [How do malloc() and free() work?](https://stackoverflow.com/questions/1119134/how-do-malloc-and-free-work) |  |
| 361 | 329 | [Is there any use for unique_ptr with array?](https://stackoverflow.com/questions/16711697/is-there-any-use-for-unique-ptr-with-array) |  |
| 362 | 329 | [What is a pointer to class data member "::*" and what is its use?](https://stackoverflow.com/questions/670734/what-is-a-pointer-to-class-data-member-and-what-is-its-use) |  |
| 375 | 320 | [Is std::unique_ptr<T> required to know the full definition of T?](https://stackoverflow.com/questions/6012157/is-stdunique-ptrt-required-to-know-the-full-definition-of-t) |  |
| 382 | 316 | [How does delete\[\] "know" the size of the operand array?](https://stackoverflow.com/questions/197675/how-does-delete-know-the-size-of-the-operand-array) |  |
| 396 | 308 | [What is the difference between new/delete and malloc/free?](https://stackoverflow.com/questions/240212/what-is-the-difference-between-new-delete-and-malloc-free) |  |
| 407 | 303 | [Why can I not push_back a unique_ptr into a vector?](https://stackoverflow.com/questions/3283778/why-can-i-not-push-back-a-unique-ptr-into-a-vector) |  |
| 423 | 294 | [Is "delete this" allowed in C++?](https://stackoverflow.com/questions/3150942/is-delete-this-allowed-in-c) |  |
| 451 | 285 | [C++ new int\[0\] -- will it allocate memory?](https://stackoverflow.com/questions/1087042/c-new-int0-will-it-allocate-memory) |  |
| 454 | 282 | [What is memory fragmentation?](https://stackoverflow.com/questions/3770457/what-is-memory-fragmentation) |  |
| 460 | 279 | [std::unique_ptr with an incomplete type won't compile](https://stackoverflow.com/questions/9954518/stdunique-ptr-with-an-incomplete-type-wont-compile) |  |
| 480 | 272 | [Determine the line of code that causes a segmentation fault?](https://stackoverflow.com/questions/2876357/determine-the-line-of-code-that-causes-a-segmentation-fault) |  |
| 483 | 270 | [How do I call ::std::make_shared on a class with only protected or private constructors?](https://stackoverflow.com/questions/8147027/how-do-i-call-stdmake-shared-on-a-class-with-only-protected-or-private-const) |  |
| 509 | 259 | [Is the sizeof(some pointer) always equal to four?](https://stackoverflow.com/questions/399003/is-the-sizeofsome-pointer-always-equal-to-four) |  |
| 540 | 246 | [How to find memory leak in a C++ code/project?](https://stackoverflow.com/questions/6261201/how-to-find-memory-leak-in-a-c-code-project) |  |
| 542 | 246 | [Why are two different concepts both called "heap"?](https://stackoverflow.com/questions/1699057/why-are-two-different-concepts-both-called-heap) |  |
| 549 | 245 | [Which kind of pointer do I use when?](https://stackoverflow.com/questions/8706192/which-kind-of-pointer-do-i-use-when) |  |
| 571 | 238 | [Are memory leaks ever OK?](https://stackoverflow.com/questions/273209/are-memory-leaks-ever-ok) |  |
| 574 | 238 | [When vectors are allocated, do they use memory on the heap or the stack?](https://stackoverflow.com/questions/8036474/when-vectors-are-allocated-do-they-use-memory-on-the-heap-or-the-stack) | ✅ #7 |
| 576 | 237 | [Why would I std::move an std::shared_ptr?](https://stackoverflow.com/questions/41871115/why-would-i-stdmove-an-stdshared-ptr) |  |
| 579 | 237 | [The new syntax "= default" in C++11](https://stackoverflow.com/questions/20828907/the-new-syntax-default-in-c11) |  |
| 587 | 235 | [smart pointers (boost) explained](https://stackoverflow.com/questions/569775/smart-pointers-boost-explained) |  |
| 590 | 234 | [What is the difference between delete and delete\[\]?](https://stackoverflow.com/questions/2425728/what-is-the-difference-between-delete-and-delete) |  |
| 628 | 225 | [Compelling examples of custom C++ allocators?](https://stackoverflow.com/questions/826569/compelling-examples-of-custom-c-allocators) |  |
| 640 | 222 | [std::auto_ptr to std::unique_ptr](https://stackoverflow.com/questions/3451099/stdauto-ptr-to-stdunique-ptr) |  |
| 645 | 221 | [Can you make a std::shared_ptr manage an array allocated with new T\[\]?](https://stackoverflow.com/questions/13061979/can-you-make-a-stdshared-ptr-manage-an-array-allocated-with-new-t) |  |
| 655 | 218 | [How to initialise memory with new operator in C++?](https://stackoverflow.com/questions/2204176/how-to-initialise-memory-with-new-operator-in-c) |  |
| 660 | 217 | [RAII and smart pointers in C++](https://stackoverflow.com/questions/395123/raii-and-smart-pointers-in-c) |  |
| 692 | 210 | [Can I use if (pointer) instead of if (pointer != NULL)?](https://stackoverflow.com/questions/17772103/can-i-use-if-pointer-instead-of-if-pointer-null) |  |
| 701 | 208 | [Do you use NULL or 0 (zero) for pointers in C++?](https://stackoverflow.com/questions/176989/do-you-use-null-or-0-zero-for-pointers-in-c) |  |
| 714 | 207 | [Differences between std::make_unique and std::unique_ptr with new](https://stackoverflow.com/questions/22571202/differences-between-stdmake-unique-and-stdunique-ptr-with-new) |  |
| 722 | 206 | [Advantages of using std::make_unique over new operator](https://stackoverflow.com/questions/37514509/advantages-of-using-stdmake-unique-over-new-operator) |  |
| 745 | 201 | [polymorphic_allocator: when and why should I use it?](https://stackoverflow.com/questions/38010544/polymorphic-allocator-when-and-why-should-i-use-it) |  |
| 769 | 198 | [What does "Memory allocated at compile time" really mean?](https://stackoverflow.com/questions/21350478/what-does-memory-allocated-at-compile-time-really-mean) |  |
| 779 | 196 | [How can I pass a member function where a free function is expected?](https://stackoverflow.com/questions/12662891/how-can-i-pass-a-member-function-where-a-free-function-is-expected) |  |
| 785 | 195 | [How do I use a custom deleter with a std::unique_ptr member?](https://stackoverflow.com/questions/19053351/how-do-i-use-a-custom-deleter-with-a-stdunique-ptr-member) |  |
| 800 | 193 | [Stack, Static, and Heap in C++](https://stackoverflow.com/questions/408670/stack-static-and-heap-in-c) |  |
| 822 | 190 | [How much is the overhead of smart pointers compared to normal pointers in C++?](https://stackoverflow.com/questions/22295665/how-much-is-the-overhead-of-smart-pointers-compared-to-normal-pointers-in-c) |  |
| 825 | 190 | [Is it good practice to NULL a pointer after deleting it?](https://stackoverflow.com/questions/1931126/is-it-good-practice-to-null-a-pointer-after-deleting-it) |  |
| 830 | 189 | [Using smart pointers for class members](https://stackoverflow.com/questions/15648844/using-smart-pointers-for-class-members) |  |
| 849 | 187 | [Calling constructors in c++ without new](https://stackoverflow.com/questions/2722879/calling-constructors-in-c-without-new) |  |
| 853 | 186 | [What's the difference between assignment operator and copy constructor?](https://stackoverflow.com/questions/11706040/whats-the-difference-between-assignment-operator-and-copy-constructor) |  |
| 854 | 186 | [How can I pass std::unique_ptr into a function](https://stackoverflow.com/questions/30905487/how-can-i-pass-stdunique-ptr-into-a-function) |  |
| 874 | 183 | [How to debug heap corruption errors?](https://stackoverflow.com/questions/1010106/how-to-debug-heap-corruption-errors) |  |
| 883 | 182 | [What is the meaning of the term arena in relation to memory?](https://stackoverflow.com/questions/12825148/what-is-the-meaning-of-the-term-arena-in-relation-to-memory) |  |
| 892 | 180 | [Declaring pointers; asterisk on the left or right of the space between the type and name?](https://stackoverflow.com/questions/2660633/declaring-pointers-asterisk-on-the-left-or-right-of-the-space-between-the-type) |  |
| 916 | 177 | [What is the difference between std::reference_wrapper and a simple pointer?](https://stackoverflow.com/questions/26766939/what-is-the-difference-between-stdreference-wrapper-and-a-simple-pointer) |  |
| 931 | 175 | [What are the advantages of using nullptr?](https://stackoverflow.com/questions/13816385/what-are-the-advantages-of-using-nullptr) |  |
| 956 | 172 | [Is leaked memory freed up when the program exits?](https://stackoverflow.com/questions/2975831/is-leaked-memory-freed-up-when-the-program-exits) |  |
| 971 | 170 | [Should I store entire objects, or pointers to objects in containers?](https://stackoverflow.com/questions/141337/should-i-store-entire-objects-or-pointers-to-objects-in-containers) |  |
| 986 | 169 | [Difference between `const shared_ptr<T>` and `shared_ptr<const T>`?](https://stackoverflow.com/questions/17793333/difference-between-const-shared-ptrt-and-shared-ptrconst-t) |  |
| 987 | 169 | [Does delete on a pointer to a subclass call the base class destructor?](https://stackoverflow.com/questions/677653/does-delete-on-a-pointer-to-a-subclass-call-the-base-class-destructor) |  |
| 1006 | 167 | [Does C++11 unique_ptr and shared_ptr able to convert to each other's type?](https://stackoverflow.com/questions/37884728/does-c11-unique-ptr-and-shared-ptr-able-to-convert-to-each-others-type) |  |
| 1024 | 164 | [How can I create a pointer to a member function and call it?](https://stackoverflow.com/questions/1485983/how-can-i-create-a-pointer-to-a-member-function-and-call-it) |  |
| 1043 | 162 | [Pointer expressions: *ptr++, *++ptr and ++*ptr](https://stackoverflow.com/questions/18481740/pointer-expressions-ptr-ptr-and-ptr) |  |
| 1047 | 162 | [C/C++ maximum stack size of program on mainstream OSes](https://stackoverflow.com/questions/1825964/c-c-maximum-stack-size-of-program-on-mainstream-oses) |  |
| 1050 | 162 | [Why do C++ libraries and frameworks never use smart pointers?](https://stackoverflow.com/questions/10334511/why-do-c-libraries-and-frameworks-never-use-smart-pointers) |  |
| 1069 | 160 | [What's the point of const pointers?](https://stackoverflow.com/questions/7715371/whats-the-point-of-const-pointers) |  |
| 1071 | 160 | [To what degree does std::shared_ptr ensure thread-safety?](https://stackoverflow.com/questions/9127816/to-what-degree-does-stdshared-ptr-ensure-thread-safety) |  |
| 1096 | 157 | [Why doesn't delete set the pointer to NULL?](https://stackoverflow.com/questions/704466/why-doesnt-delete-set-the-pointer-to-null) |  |
| 1098 | 157 | [When and why will a compiler initialise memory to 0xCD, 0xDD, etc. on malloc/free/new/delete?](https://stackoverflow.com/questions/370195/when-and-why-will-a-compiler-initialise-memory-to-0xcd-0xdd-etc-on-malloc-fre) |  |
| 1099 | 157 | [Difference between 'new operator' and 'operator new'?](https://stackoverflow.com/questions/1885849/difference-between-new-operator-and-operator-new) |  |
| 1112 | 156 | [Copy constructor for a class with unique_ptr](https://stackoverflow.com/questions/16030081/copy-constructor-for-a-class-with-unique-ptr) |  |
| 1125 | 155 | [std::shared_ptr of this](https://stackoverflow.com/questions/11711034/stdshared-ptr-of-this) |  |
| 1127 | 155 | [Passing shared_ptr<Derived> as shared_ptr<Base>](https://stackoverflow.com/questions/13403490/passing-shared-ptrderived-as-shared-ptrbase) |  |
| 1143 | 154 | [C++, Free-Store vs Heap](https://stackoverflow.com/questions/1350819/c-free-store-vs-heap) |  |
| 1154 | 153 | [How to declare std::unique_ptr and what is the use of it?](https://stackoverflow.com/questions/16894400/how-to-declare-stdunique-ptr-and-what-is-the-use-of-it) |  |
| 1164 | 152 | [Should I pass a shared_ptr by reference?](https://stackoverflow.com/questions/8385457/should-i-pass-a-shared-ptr-by-reference) |  |
| 1180 | 149 | [Why is x\[0\] != x\[0\]\[0\] != x\[0\]\[0\]\[0\]?](https://stackoverflow.com/questions/31231376/why-is-x0-x00-x000) |  |
| 1187 | 149 | [How does std::shared_ptr<void> call the correct object destructor?](https://stackoverflow.com/questions/5913396/how-does-stdshared-ptrvoid-call-the-correct-object-destructor) |  |
| 1191 | 148 | [Placement of the asterisk in pointer declarations](https://stackoverflow.com/questions/180401/placement-of-the-asterisk-in-pointer-declarations) |  |
| 1196 | 148 | [How does delete\[\] know it's an array?](https://stackoverflow.com/questions/703691/how-does-delete-know-its-an-array) |  |
| 1235 | 145 | [What is the meaning of the term "free function" in C++?](https://stackoverflow.com/questions/4861914/what-is-the-meaning-of-the-term-free-function-in-c) |  |
| 1245 | 144 | [Can I call memcpy() and memmove() with "number of bytes" set to zero?](https://stackoverflow.com/questions/3751797/can-i-call-memcpy-and-memmove-with-number-of-bytes-set-to-zero) |  |
| 1256 | 143 | [Fixing Segmentation faults in C++](https://stackoverflow.com/questions/3718998/fixing-segmentation-faults-in-c) |  |
| 1266 | 142 | [Does unique_ptr::release() call the destructor?](https://stackoverflow.com/questions/25609457/does-unique-ptrrelease-call-the-destructor) |  |
| 1299 | 140 | [Segmentation fault on large array sizes](https://stackoverflow.com/questions/1847789/segmentation-fault-on-large-array-sizes) |  |
| 1313 | 139 | [What can I use instead of the arrow operator, `->`?](https://stackoverflow.com/questions/221346/what-can-i-use-instead-of-the-arrow-operator) |  |
| 1321 | 139 | [Why is address zero used for the null pointer?](https://stackoverflow.com/questions/2759845/why-is-address-zero-used-for-the-null-pointer) |  |
| 1323 | 138 | [Why does the use of 'new' cause memory leaks?](https://stackoverflow.com/questions/8839943/why-does-the-use-of-new-cause-memory-leaks) |  |
| 1328 | 138 | [Why are function pointers and data pointers incompatible in C/C++?](https://stackoverflow.com/questions/12358843/why-are-function-pointers-and-data-pointers-incompatible-in-c-c) |  |
| 1334 | 138 | [Why use std::make_unique in C++17?](https://stackoverflow.com/questions/53870522/why-use-stdmake-unique-in-c17) |  |
| 1338 | 138 | [Why is stack memory size so limited?](https://stackoverflow.com/questions/10482974/why-is-stack-memory-size-so-limited) |  |
| 1388 | 134 | [Why aren't pointers initialized with NULL by default?](https://stackoverflow.com/questions/1910832/why-arent-pointers-initialized-with-null-by-default) |  |
| 1390 | 134 | [What does Visual Studio do with a deleted pointer and why?](https://stackoverflow.com/questions/33374483/what-does-visual-studio-do-with-a-deleted-pointer-and-why) |  |
| 1396 | 133 | [General guidelines to avoid memory leaks in C++](https://stackoverflow.com/questions/76796/general-guidelines-to-avoid-memory-leaks-in-c) |  |
| 1411 | 133 | [Why explicitly delete the constructor instead of making it private?](https://stackoverflow.com/questions/13654927/why-explicitly-delete-the-constructor-instead-of-making-it-private) |  |
| 1419 | 132 | [error: ‘NULL’ was not declared in this scope](https://stackoverflow.com/questions/462165/error-null-was-not-declared-in-this-scope) |  |
| 1422 | 132 | [When to use "new" and when not to, in C++?](https://stackoverflow.com/questions/679571/when-to-use-new-and-when-not-to-in-c) |  |
| 1425 | 132 | [How to return smart pointers (shared_ptr), by reference or by value?](https://stackoverflow.com/questions/10643563/how-to-return-smart-pointers-shared-ptr-by-reference-or-by-value) |  |
| 1438 | 131 | [Pointers, smart pointers or shared pointers?](https://stackoverflow.com/questions/417481/pointers-smart-pointers-or-shared-pointers) |  |
| 1443 | 131 | [Stack Memory vs Heap Memory](https://stackoverflow.com/questions/5836309/stack-memory-vs-heap-memory) |  |
| 1454 | 130 | [Memory alignment : how to use alignof / alignas?](https://stackoverflow.com/questions/17091382/memory-alignment-how-to-use-alignof-alignas) |  |
| 1480 | 129 | [Why is shared_ptr<void> legal, while unique_ptr<void> is ill-formed?](https://stackoverflow.com/questions/39288891/why-is-shared-ptrvoid-legal-while-unique-ptrvoid-is-ill-formed) |  |
| 1484 | 128 | [How do you detect/avoid Memory leaks in your (Unmanaged) code?](https://stackoverflow.com/questions/45627/how-do-you-detect-avoid-memory-leaks-in-your-unmanaged-code) |  |
| 1494 | 127 | [Why do linked lists use pointers instead of storing nodes inside of nodes](https://stackoverflow.com/questions/29543780/why-do-linked-lists-use-pointers-instead-of-storing-nodes-inside-of-nodes) |  |
| 1498 | 127 | [What C++ Smart Pointer Implementations are available?](https://stackoverflow.com/questions/5026197/what-c-smart-pointer-implementations-are-available) |  |
| 1512 | 126 | [Is there a non-atomic equivalent of std::shared_ptr? And why isn't there one in <memory>?](https://stackoverflow.com/questions/15129263/is-there-a-non-atomic-equivalent-of-stdshared-ptr-and-why-isnt-there-one-in) |  |
| 1523 | 125 | [Proper stack and heap usage in C++?](https://stackoverflow.com/questions/599308/proper-stack-and-heap-usage-in-c) |  |
| 1530 | 125 | [How to track down a "double free or corruption" error](https://stackoverflow.com/questions/2902064/how-to-track-down-a-double-free-or-corruption-error) |  |
| 1565 | 123 | [How far can memory leaks go?](https://stackoverflow.com/questions/15467298/how-far-can-memory-leaks-go) |  |
| 1579 | 122 | [What is a void pointer in C++?](https://stackoverflow.com/questions/8530080/what-is-a-void-pointer-in-c) |  |
| 1581 | 122 | [Why is #include <string> preventing a stack overflow error here?](https://stackoverflow.com/questions/43733672/why-is-include-string-preventing-a-stack-overflow-error-here) |  |
| 1594 | 122 | [Smart pointers: who owns the object?](https://stackoverflow.com/questions/94227/smart-pointers-who-owns-the-object) |  |
| 1601 | 121 | [Understanding the meaning of the term and the concept - RAII (Resource Acquisition is Initialization)](https://stackoverflow.com/questions/712639/understanding-the-meaning-of-the-term-and-the-concept-raii-resource-acquisiti) |  |
| 1616 | 120 | [Deleting a pointer in C++](https://stackoverflow.com/questions/13223399/deleting-a-pointer-in-c) |  |
| 1619 | 120 | [error::make_unique is not a member of ‘std’](https://stackoverflow.com/questions/24609271/errormake-unique-is-not-a-member-of-std) |  |
| 1644 | 119 | [How to catch segmentation fault in Linux?](https://stackoverflow.com/questions/2350489/how-to-catch-segmentation-fault-in-linux) |  |
| 1664 | 118 | [Is accessing data in the heap faster than from the stack?](https://stackoverflow.com/questions/24057331/is-accessing-data-in-the-heap-faster-than-from-the-stack) |  |
| 1666 | 118 | [What is difference between instantiating an object using new vs. without](https://stackoverflow.com/questions/3673998/what-is-difference-between-instantiating-an-object-using-new-vs-without) |  |
| 1668 | 118 | [Is it still safe to delete nullptr in c++0x?](https://stackoverflow.com/questions/6731331/is-it-still-safe-to-delete-nullptr-in-c0x) |  |
| 1709 | 115 | [Why is a segmentation fault not recoverable?](https://stackoverflow.com/questions/70258418/why-is-a-segmentation-fault-not-recoverable) |  |
| 1717 | 115 | [unique_ptr to a derived class as an argument to a function that takes a unique_ptr to a base class](https://stackoverflow.com/questions/17473900/unique-ptr-to-a-derived-class-as-an-argument-to-a-function-that-takes-a-unique-p) |  |
| 1732 | 114 | [Passing shared pointers as arguments](https://stackoverflow.com/questions/10826541/passing-shared-pointers-as-arguments) |  |
| 1754 | 113 | [Proper way to create unique_ptr that holds an allocated array](https://stackoverflow.com/questions/21377360/proper-way-to-create-unique-ptr-that-holds-an-allocated-array) |  |
| 1761 | 113 | [How to pass std::unique_ptr around?](https://stackoverflow.com/questions/11277249/how-to-pass-stdunique-ptr-around) |  |
| 1766 | 113 | [Why is auto_ptr being deprecated?](https://stackoverflow.com/questions/3697686/why-is-auto-ptr-being-deprecated) |  |
| 1804 | 112 | [Malloc vs new -- different padding](https://stackoverflow.com/questions/13286706/malloc-vs-new-different-padding) |  |
| 1821 | 111 | [Why can a T* be passed in register, but a unique_ptr<T> cannot?](https://stackoverflow.com/questions/58339165/why-can-a-t-be-passed-in-register-but-a-unique-ptrt-cannot) |  |
| 1840 | 110 | [How do you 'realloc' in C++?](https://stackoverflow.com/questions/3482941/how-do-you-realloc-in-c) |  |
| 1847 | 109 | [How do you check if two pointers point to the same object?](https://stackoverflow.com/questions/9086372/how-do-you-check-if-two-pointers-point-to-the-same-object) |  |
| 1862 | 109 | [C++11 When clearing shared_ptr, should I use reset or set to nullptr?](https://stackoverflow.com/questions/16151550/c11-when-clearing-shared-ptr-should-i-use-reset-or-set-to-nullptr) |  |
| 1872 | 108 | [What makes this usage of pointers unpredictable?](https://stackoverflow.com/questions/31816473/what-makes-this-usage-of-pointers-unpredictable) |  |
| 1884 | 108 | [Where is shared_ptr?](https://stackoverflow.com/questions/2918202/where-is-shared-ptr) |  |
| 1894 | 108 | [Forward declaration with unique_ptr](https://stackoverflow.com/questions/13414652/forward-declaration-with-unique-ptr) |  |
| 1933 | 106 | [Is it safe to delete a void pointer?](https://stackoverflow.com/questions/941832/is-it-safe-to-delete-a-void-pointer) |  |
| 1937 | 106 | [What are the pointer-to-member operators ->* and .* in C++?](https://stackoverflow.com/questions/6586205/what-are-the-pointer-to-member-operators-and-in-c) |  |
| 1940 | 106 | [Deleting a pointer to const (T const*)](https://stackoverflow.com/questions/755196/deleting-a-pointer-to-const-t-const) |  |
| 1961 | 105 | [Operator new initializes memory to zero](https://stackoverflow.com/questions/7546620/operator-new-initializes-memory-to-zero) |  |
| 1992 | 104 | [Testing pointers for validity (C/C++)](https://stackoverflow.com/questions/551069/testing-pointers-for-validity-c-c) |  |
| 1994 | 104 | [What is the point of function pointers?](https://stackoverflow.com/questions/2592137/what-is-the-point-of-function-pointers) |  |
| 2016 | 104 | [How is it possible (if it is) to implement shared_ptr without requiring polymorphic classes to have virtual destructor?](https://stackoverflow.com/questions/3899790/how-is-it-possible-if-it-is-to-implement-shared-ptr-without-requiring-polymorp) |  |
| 2019 | 104 | [Is using malloc for int undefined behavior until C++20](https://stackoverflow.com/questions/63379066/is-using-malloc-for-int-undefined-behavior-until-c20) |  |
| 2033 | 103 | [delete vs delete\[\]](https://stackoverflow.com/questions/4255598/delete-vs-delete) |  |
| 2056 | 102 | [Correct way of declaring pointer variables in C/C++](https://stackoverflow.com/questions/6990726/correct-way-of-declaring-pointer-variables-in-c-c) |  |
| 2058 | 102 | [How to get memory usage at runtime using C++?](https://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-runtime-using-c) |  |
| 2085 | 101 | [When to use shared_ptr and when to use raw pointers?](https://stackoverflow.com/questions/7657718/when-to-use-shared-ptr-and-when-to-use-raw-pointers) |  |
| 2103 | 100 | [Can a pointer to base point to an array of derived objects?](https://stackoverflow.com/questions/7196172/can-a-pointer-to-base-point-to-an-array-of-derived-objects) |  |
| 2110 | 100 | [What is a “memory stomp”?](https://stackoverflow.com/questions/13669329/what-is-a-memory-stomp) |  |
| 2130 | 99 | [what's the point of std::unique_ptr::get](https://stackoverflow.com/questions/10802046/whats-the-point-of-stdunique-ptrget) |  |
| 2135 | 99 | [What's the advantage of using std::allocator instead of new in C++?](https://stackoverflow.com/questions/31358804/whats-the-advantage-of-using-stdallocator-instead-of-new-in-c) |  |
| 2157 | 98 | [Is it a good idea to typedef pointers?](https://stackoverflow.com/questions/750178/is-it-a-good-idea-to-typedef-pointers) |  |
| 2163 | 98 | [Does an unused data member take up memory?](https://stackoverflow.com/questions/55060820/does-an-unused-data-member-take-up-memory) |  |
| 2173 | 98 | [Why don't you have to use the new keyword to create objects?](https://stackoverflow.com/questions/1764831/why-dont-you-have-to-use-the-new-keyword-to-create-objects) |  |
| 2218 | 96 | [How to get available memory C++/g++?](https://stackoverflow.com/questions/2513505/how-to-get-available-memory-c-g) |  |
| 2239 | 96 | [Does 'auto' type assignments of a pointer in c++11 require '*'?](https://stackoverflow.com/questions/12773257/does-auto-type-assignments-of-a-pointer-in-c11-require) |  |
| 2283 | 95 | [How do I create a "spacer" in a C++ class memory structure?](https://stackoverflow.com/questions/53109888/how-do-i-create-a-spacer-in-a-c-class-memory-structure) |  |
| 2289 | 95 | [Why is std::aligned_storage to be deprecated in C++23 and what to use instead?](https://stackoverflow.com/questions/71828288/why-is-stdaligned-storage-to-be-deprecated-in-c23-and-what-to-use-instead) |  |
| 2339 | 93 | [cout << with char* argument prints string, not pointer value](https://stackoverflow.com/questions/17813423/cout-with-char-argument-prints-string-not-pointer-value) |  |
| 2350 | 93 | [Should I assign or reset a unique_ptr?](https://stackoverflow.com/questions/16061407/should-i-assign-or-reset-a-unique-ptr) |  |
| 2357 | 92 | [A Base Class pointer can point to a derived class object. Why is the vice-versa not true?](https://stackoverflow.com/questions/4937180/a-base-class-pointer-can-point-to-a-derived-class-object-why-is-the-vice-versa) |  |
| 2361 | 92 | [How does one downcast a std::shared_ptr?](https://stackoverflow.com/questions/6795629/how-does-one-downcast-a-stdshared-ptr) |  |
| 2390 | 92 | [Is unique_ptr guaranteed to store nullptr after move?](https://stackoverflow.com/questions/24061767/is-unique-ptr-guaranteed-to-store-nullptr-after-move) |  |
| 2397 | 91 | [What is the size of a pointer?](https://stackoverflow.com/questions/6751749/what-is-the-size-of-a-pointer) |  |
| 2412 | 91 | [When is it best to use the stack instead of the heap and vice versa?](https://stackoverflow.com/questions/102009/when-is-it-best-to-use-the-stack-instead-of-the-heap-and-vice-versa) |  |
| 2418 | 91 | [Is it a good practice to always use smart pointers?](https://stackoverflow.com/questions/2454214/is-it-a-good-practice-to-always-use-smart-pointers) |  |
| 2426 | 91 | [Why can't a weak_ptr be constructed from a unique_ptr?](https://stackoverflow.com/questions/29059343/why-cant-a-weak-ptr-be-constructed-from-a-unique-ptr) |  |
| 2488 | 89 | [How does this program work?](https://stackoverflow.com/questions/2377733/how-does-this-program-work) |  |
| 2496 | 89 | [How does a weak_ptr prevent cyclic references?](https://stackoverflow.com/questions/4984381/how-does-a-weak-ptr-prevent-cyclic-references) |  |
| 2533 | 88 | [Calling delete on variable allocated on the stack](https://stackoverflow.com/questions/441831/calling-delete-on-variable-allocated-on-the-stack) |  |
| 2560 | 88 | [Is auto_ptr deprecated?](https://stackoverflow.com/questions/2404115/is-auto-ptr-deprecated) |  |
| 2566 | 88 | [What is the difference between an empty and a null std::shared_ptr in C++?](https://stackoverflow.com/questions/25920681/what-is-the-difference-between-an-empty-and-a-null-stdshared-ptr-in-c) |  |
| 2567 | 88 | [Meaning of int (*) (int *) = 5 (or any integer value)](https://stackoverflow.com/questions/29636819/meaning-of-int-int-5-or-any-integer-value) |  |
| 2568 | 88 | [Creating shared_ptr from raw pointer](https://stackoverflow.com/questions/4665266/creating-shared-ptr-from-raw-pointer) |  |
| 2571 | 88 | [How can I use covariant return types with smart pointers?](https://stackoverflow.com/questions/196733/how-can-i-use-covariant-return-types-with-smart-pointers) |  |
| 2590 | 87 | [Difference between std::function<> and a standard function pointer?](https://stackoverflow.com/questions/9054774/difference-between-stdfunction-and-a-standard-function-pointer) |  |
| 2598 | 87 | [When should I use raw pointers over smart pointers?](https://stackoverflow.com/questions/6675651/when-should-i-use-raw-pointers-over-smart-pointers) |  |
| 2673 | 85 | [Example to use shared_ptr?](https://stackoverflow.com/questions/3476938/example-to-use-shared-ptr) |  |
| 2700 | 85 | [Is a pointer with the right address and type still always a valid pointer since C++17?](https://stackoverflow.com/questions/48062346/is-a-pointer-with-the-right-address-and-type-still-always-a-valid-pointer-since) |  |
| 2709 | 84 | [How to access the contents of a vector from a pointer to the vector in C++?](https://stackoverflow.com/questions/6946217/how-to-access-the-contents-of-a-vector-from-a-pointer-to-the-vector-in-c) |  |
| 2766 | 83 | [Is it ever OK to *not* use free() on allocated memory?](https://stackoverflow.com/questions/22481134/is-it-ever-ok-to-not-use-free-on-allocated-memory) |  |
| 2778 | 83 | [How does weak_ptr work?](https://stackoverflow.com/questions/5671241/how-does-weak-ptr-work) |  |
| 2779 | 83 | [how does malloc understand alignment?](https://stackoverflow.com/questions/8752546/how-does-malloc-understand-alignment) |  |
| 2792 | 83 | [How does dereferencing of a function pointer happen?](https://stackoverflow.com/questions/2795575/how-does-dereferencing-of-a-function-pointer-happen) |  |
| 2815 | 82 | [RAII vs. Garbage Collector](https://stackoverflow.com/questions/44325085/raii-vs-garbage-collector) |  |
| 2821 | 82 | [Can I use NULL as substitution for the value of 0?](https://stackoverflow.com/questions/59437282/can-i-use-null-as-substitution-for-the-value-of-0) |  |
| 2829 | 82 | [What is a dangling pointer?](https://stackoverflow.com/questions/17997228/what-is-a-dangling-pointer) |  |
| 2853 | 82 | [Why does unique_ptr take two template parameters when shared_ptr only takes one?](https://stackoverflow.com/questions/21355037/why-does-unique-ptr-take-two-template-parameters-when-shared-ptr-only-takes-one) |  |
| 2869 | 81 | [Dereference vector pointer to access element](https://stackoverflow.com/questions/1910712/dereference-vector-pointer-to-access-element) |  |
| 2878 | 81 | [Why are NULL pointers defined differently in C and C++?](https://stackoverflow.com/questions/7016861/why-are-null-pointers-defined-differently-in-c-and-c) |  |
| 2886 | 81 | [Definitive list of common reasons for segmentation faults](https://stackoverflow.com/questions/33047452/definitive-list-of-common-reasons-for-segmentation-faults) |  |
| 2891 | 81 | [gsl::not_null<T*> vs. std::reference_wrapper<T> vs. T&](https://stackoverflow.com/questions/33306553/gslnot-nullt-vs-stdreference-wrappert-vs-t) |  |
| 2902 | 80 | [invalid conversion from `void*' to `char*' when using malloc?](https://stackoverflow.com/questions/5099669/invalid-conversion-from-void-to-char-when-using-malloc) |  |
| 2907 | 80 | [C++ inserting unique_ptr in map](https://stackoverflow.com/questions/16923748/c-inserting-unique-ptr-in-map) |  |
| 2911 | 80 | [Does using heap memory (malloc/new) create a non-deterministic program?](https://stackoverflow.com/questions/46298257/does-using-heap-memory-malloc-new-create-a-non-deterministic-program) |  |
| 2926 | 80 | [shared_from_this causing bad_weak_ptr](https://stackoverflow.com/questions/27697973/shared-from-this-causing-bad-weak-ptr) |  |
| 2995 | 78 | [Why not use pointers for everything in C++?](https://stackoverflow.com/questions/1064325/why-not-use-pointers-for-everything-in-c) |  |
| 3001 | 78 | [How to deal with bad_alloc in C++?](https://stackoverflow.com/questions/9456728/how-to-deal-with-bad-alloc-in-c) |  |
| 3012 | 78 | [Is the behavior of subtracting two NULL pointers defined?](https://stackoverflow.com/questions/8128168/is-the-behavior-of-subtracting-two-null-pointers-defined) |  |
| 3015 | 78 | [Iterating through vector<unique_ptr<mytype>> using C++11 for() loops](https://stackoverflow.com/questions/20292682/iterating-through-vectorunique-ptrmytype-using-c11-for-loops) |  |
| 3046 | 77 | [Global memory management in C++ in stack or heap?](https://stackoverflow.com/questions/1169858/global-memory-management-in-c-in-stack-or-heap) |  |
| 3077 | 77 | [Does std::array<> guarantee allocation on the stack only?](https://stackoverflow.com/questions/39548254/does-stdarray-guarantee-allocation-on-the-stack-only) |  |
| 3080 | 77 | [When is an integer<->pointer cast actually correct?](https://stackoverflow.com/questions/7146813/when-is-an-integer-pointer-cast-actually-correct) |  |
| 3102 | 76 | [Object creation on the stack/heap?](https://stackoverflow.com/questions/10157122/object-creation-on-the-stack-heap) |  |
| 3118 | 76 | [How to properly replace global new & delete operators](https://stackoverflow.com/questions/8186018/how-to-properly-replace-global-new-delete-operators) |  |
| 3176 | 75 | [std::shared_ptr initialization: make_shared<Foo>() vs shared_ptr<T>(new Foo)](https://stackoverflow.com/questions/18301511/stdshared-ptr-initialization-make-sharedfoo-vs-shared-ptrtnew-foo) |  |
| 3193 | 75 | [How do I use unique_ptr for pimpl?](https://stackoverflow.com/questions/9020372/how-do-i-use-unique-ptr-for-pimpl) |  |
| 3194 | 75 | [How to get a pointer's value or depointerize it](https://stackoverflow.com/questions/14420257/how-to-get-a-pointers-value-or-depointerize-it) |  |
| 3200 | 75 | [How do you read a segfault kernel log message](https://stackoverflow.com/questions/2179403/how-do-you-read-a-segfault-kernel-log-message) |  |
| 3217 | 75 | [Why does unique_ptr have the deleter as a type parameter while shared_ptr doesn't?](https://stackoverflow.com/questions/6829576/why-does-unique-ptr-have-the-deleter-as-a-type-parameter-while-shared-ptr-doesn) |  |
| 3222 | 74 | [C++ delete vector, objects, free memory](https://stackoverflow.com/questions/10464992/c-delete-vector-objects-free-memory) |  |
| 3226 | 74 | [std::shared_ptr thread safety](https://stackoverflow.com/questions/14482830/stdshared-ptr-thread-safety) |  |
| 3238 | 74 | [Why not call nullptr NULL?](https://stackoverflow.com/questions/32302615/why-not-call-nullptr-null) |  |
| 3242 | 74 | [static_cast with boost::shared_ptr?](https://stackoverflow.com/questions/624854/static-cast-with-boostshared-ptr) |  |
| 3250 | 74 | [placement new and delete](https://stackoverflow.com/questions/6783993/placement-new-and-delete) |  |
| 3254 | 74 | [Why would one replace default new and delete operators?](https://stackoverflow.com/questions/7149461/why-would-one-replace-default-new-and-delete-operators) |  |
| 3258 | 74 | [Should I switch from using boost::shared_ptr to std::shared_ptr?](https://stackoverflow.com/questions/6322245/should-i-switch-from-using-boostshared-ptr-to-stdshared-ptr) |  |
| 3261 | 74 | [Protobuf: Will set_allocated_* delete the allocated object?](https://stackoverflow.com/questions/33960999/protobuf-will-set-allocated-delete-the-allocated-object) |  |
| 3264 | 74 | [How should I write ISO C++ Standard conformant custom new and delete operators?](https://stackoverflow.com/questions/7194127/how-should-i-write-iso-c-standard-conformant-custom-new-and-delete-operators) |  |
| 3278 | 74 | [Is it legal to compare dangling pointers?](https://stackoverflow.com/questions/30694069/is-it-legal-to-compare-dangling-pointers) |  |
| 3281 | 74 | [What is the recommended way to align memory in C++11](https://stackoverflow.com/questions/20791428/what-is-the-recommended-way-to-align-memory-in-c11) |  |
| 3301 | 73 | [std::unique_ptr for C functions that need free](https://stackoverflow.com/questions/27440953/stdunique-ptr-for-c-functions-that-need-free) |  |
| 3312 | 73 | [Finding memory leaks in a C++ application with Visual Studio](https://stackoverflow.com/questions/4790564/finding-memory-leaks-in-a-c-application-with-visual-studio) |  |
| 3331 | 73 | [What is a jump table?](https://stackoverflow.com/questions/48017/what-is-a-jump-table) |  |
| 3351 | 72 | [malloc() vs. HeapAlloc()](https://stackoverflow.com/questions/8224347/malloc-vs-heapalloc) |  |
| 3359 | 72 | [Pointer values are different but they compare equal. Why?](https://stackoverflow.com/questions/18272909/pointer-values-are-different-but-they-compare-equal-why) |  |
| 3362 | 72 | [Dynamically allocating an array of objects](https://stackoverflow.com/questions/255612/dynamically-allocating-an-array-of-objects) |  |
| 3402 | 72 | [Array placement-new requires unspecified overhead in the buffer?](https://stackoverflow.com/questions/8720425/array-placement-new-requires-unspecified-overhead-in-the-buffer) |  |
| 3407 | 72 | ["Downcasting" unique_ptr<Base> to unique_ptr<Derived>](https://stackoverflow.com/questions/21174593/downcasting-unique-ptrbase-to-unique-ptrderived) |  |
| 3447 | 71 | [error: ‘unique_ptr’ is not a member of ‘std’](https://stackoverflow.com/questions/18078153/error-unique-ptr-is-not-a-member-of-std) |  |
| 3468 | 71 | [Why isn't there a std::construct_at in C++17?](https://stackoverflow.com/questions/52966560/why-isnt-there-a-stdconstruct-at-in-c17) |  |
| 3495 | 70 | [Are 'new' and 'delete' getting deprecated in C++?](https://stackoverflow.com/questions/59820879/are-new-and-delete-getting-deprecated-in-c) |  |
| 3532 | 70 | [To GC or Not To GC](https://stackoverflow.com/questions/7575055/to-gc-or-not-to-gc) |  |
| 3556 | 69 | [Error: expected type-specifier before 'ClassName'](https://stackoverflow.com/questions/8845117/error-expected-type-specifier-before-classname) |  |
| 3561 | 69 | [Getting a normal ptr from boost::shared_ptr?](https://stackoverflow.com/questions/505143/getting-a-normal-ptr-from-boostshared-ptr) |  |
| 3566 | 69 | [C++ Array of pointers: delete or delete \[\]?](https://stackoverflow.com/questions/2814188/c-array-of-pointers-delete-or-delete) |  |
| 3580 | 69 | [Does std::vector.clear() do delete (free memory) on each element?](https://stackoverflow.com/questions/594089/does-stdvector-clear-do-delete-free-memory-on-each-element) |  |
| 3603 | 69 | [What is an `int foo::*bar::*`?](https://stackoverflow.com/questions/26200491/what-is-an-int-foobar) |  |
| 3610 | 69 | [C/C++ int\[\] vs int* (pointers vs. array notation). What is the difference?](https://stackoverflow.com/questions/11555997/c-c-int-vs-int-pointers-vs-array-notation-what-is-the-difference) |  |
| 3612 | 69 | [What is the purpose of std::shared_ptr::reset?](https://stackoverflow.com/questions/31438714/what-is-the-purpose-of-stdshared-ptrreset) |  |
| 3629 | 68 | [Difference between pointer to a reference and reference to a pointer](https://stackoverflow.com/questions/1898524/difference-between-pointer-to-a-reference-and-reference-to-a-pointer) |  |
| 3649 | 68 | [What is the use of intptr_t?](https://stackoverflow.com/questions/35071200/what-is-the-use-of-intptr-t) |  |
| 3673 | 68 | [How to access a local variable from a different function using pointers?](https://stackoverflow.com/questions/4570366/how-to-access-a-local-variable-from-a-different-function-using-pointers) |  |
| 3685 | 68 | [What happens to unique_ptr after std::move()?](https://stackoverflow.com/questions/36071220/what-happens-to-unique-ptr-after-stdmove) |  |
| 3689 | 68 | [What is "destroying operator delete" in C++20?](https://stackoverflow.com/questions/67595789/what-is-destroying-operator-delete-in-c20) |  |
| 3703 | 67 | [Where is the 'this' pointer stored in computer memory?](https://stackoverflow.com/questions/16585562/where-is-the-this-pointer-stored-in-computer-memory) |  |
| 3718 | 67 | [What Happens When Stack and Heap Collide](https://stackoverflow.com/questions/1334055/what-happens-when-stack-and-heap-collide) |  |
| 3729 | 67 | [How to get the Object being pointed by a shared pointer?](https://stackoverflow.com/questions/6491955/how-to-get-the-object-being-pointed-by-a-shared-pointer) |  |
| 3759 | 67 | [Why isn't there a std::shared_ptr<T\[\]> specialisation?](https://stackoverflow.com/questions/8947579/why-isnt-there-a-stdshared-ptrt-specialisation) |  |
| 3786 | 66 | [How do I programmatically get the free disk space for a directory in Linux](https://stackoverflow.com/questions/3992171/how-do-i-programmatically-get-the-free-disk-space-for-a-directory-in-linux) |  |
| 3789 | 66 | [C++ Returning Pointers/References](https://stackoverflow.com/questions/2837241/c-returning-pointers-references) |  |
| 3801 | 66 | [dynamic_cast across a shared_ptr?](https://stackoverflow.com/questions/23795265/dynamic-cast-across-a-shared-ptr) |  |
| 3821 | 66 | [Why are the terms "automatic" and "dynamic" preferred over the terms "stack" and "heap" in C++ memory  management?](https://stackoverflow.com/questions/9181782/why-are-the-terms-automatic-and-dynamic-preferred-over-the-terms-stack-and) |  |
| 3822 | 66 | [Does it ever make sense to check if "this" is null?](https://stackoverflow.com/questions/1844005/does-it-ever-make-sense-to-check-if-this-is-null) |  |
| 3832 | 66 | [How is a vector's data aligned?](https://stackoverflow.com/questions/8456236/how-is-a-vectors-data-aligned) |  |
| 3854 | 66 | [The cost of passing by shared_ptr](https://stackoverflow.com/questions/2502394/the-cost-of-passing-by-shared-ptr) |  |
| 3917 | 65 | [How to pass deleter to make_shared?](https://stackoverflow.com/questions/34243367/how-to-pass-deleter-to-make-shared) |  |
| 3935 | 65 | [Difference between boost::scoped_ptr<T> and std::unique_ptr<T>](https://stackoverflow.com/questions/8199812/difference-between-boostscoped-ptrt-and-stdunique-ptrt) |  |
| 3949 | 65 | [Heap corruption under Win32; how to locate?](https://stackoverflow.com/questions/1069/heap-corruption-under-win32-how-to-locate) |  |
| 3951 | 65 | [Can the compiler optimize from heap to stack allocation?](https://stackoverflow.com/questions/47075871/can-the-compiler-optimize-from-heap-to-stack-allocation) |  |
| 3977 | 64 | [Why is the dereference operator (*) also used to declare a pointer?](https://stackoverflow.com/questions/8685514/why-is-the-dereference-operator-also-used-to-declare-a-pointer) |  |
| 3984 | 64 | [Can you obtain the size of an array allocated with new T\[\]?](https://stackoverflow.com/questions/197839/can-you-obtain-the-size-of-an-array-allocated-with-new-t) |  |
| 4000 | 64 | [C++ std::unique_ptr return from function and test for null](https://stackoverflow.com/questions/30293338/c-stdunique-ptr-return-from-function-and-test-for-null) |  |
| 4007 | 64 | [How do I organize members in a struct to waste the least space on alignment?](https://stackoverflow.com/questions/56761591/how-do-i-organize-members-in-a-struct-to-waste-the-least-space-on-alignment) |  |
| 4013 | 64 | [remove unique_ptr from queue](https://stackoverflow.com/questions/14127487/remove-unique-ptr-from-queue) |  |
| 4024 | 64 | [Nullptr and checking if a pointer points to a valid object](https://stackoverflow.com/questions/11279715/nullptr-and-checking-if-a-pointer-points-to-a-valid-object) |  |
| 4026 | 64 | [What is shared_ptr's aliasing constructor for?](https://stackoverflow.com/questions/27109379/what-is-shared-ptrs-aliasing-constructor-for) |  |
| 4051 | 63 | [How to delete a folder in C++?](https://stackoverflow.com/questions/734717/how-to-delete-a-folder-in-c) |  |
| 4054 | 63 | [Can the C++ `new` operator ever throw an exception in real life?](https://stackoverflow.com/questions/2497151/can-the-c-new-operator-ever-throw-an-exception-in-real-life) |  |
| 4060 | 63 | [C++11: Replace all non-owning raw pointers with std::shared_ptr()?](https://stackoverflow.com/questions/8338570/c11-replace-all-non-owning-raw-pointers-with-stdshared-ptr) |  |
| 4067 | 63 | [C++, is it possible to call a constructor directly, without new?](https://stackoverflow.com/questions/2494471/c-is-it-possible-to-call-a-constructor-directly-without-new) |  |
| 4070 | 63 | [How to create two classes in C++ which use each other as data?](https://stackoverflow.com/questions/4964482/how-to-create-two-classes-in-c-which-use-each-other-as-data) |  |
| 4087 | 63 | [How to get memory usage under Windows in C++](https://stackoverflow.com/questions/282194/how-to-get-memory-usage-under-windows-in-c) |  |
| 4089 | 63 | [What does "int* p=+s;" do?](https://stackoverflow.com/questions/50598177/what-does-int-p-s-do) |  |
| 4097 | 63 | [Why is so much space allocated on the stack?](https://stackoverflow.com/questions/15806673/why-is-so-much-space-allocated-on-the-stack) |  |
| 4099 | 63 | [C vs C++ struct alignment](https://stackoverflow.com/questions/33835569/c-vs-c-struct-alignment) |  |
| 4130 | 63 | [Why are are std::allocator's construct and destroy functions deprecated in c++17?](https://stackoverflow.com/questions/39414610/why-are-are-stdallocators-construct-and-destroy-functions-deprecated-in-c17) |  |
| 4143 | 62 | [Does a std::map where the key is a pointer dereference pointers, or do you need a custom comparator?](https://stackoverflow.com/questions/25122932/does-a-stdmap-where-the-key-is-a-pointer-dereference-pointers-or-do-you-need) |  |
| 4160 | 62 | [Is memory allocation a system call?](https://stackoverflow.com/questions/6530355/is-memory-allocation-a-system-call) |  |
| 4162 | 62 | [clearing a vector of pointers](https://stackoverflow.com/questions/12795196/clearing-a-vector-of-pointers) |  |
| 4172 | 62 | [Do smart pointers work with arrays allocated using new T\[\]?](https://stackoverflow.com/questions/6713484/do-smart-pointers-work-with-arrays-allocated-using-new-t) |  |
| 4194 | 62 | [How to print function pointers with cout?](https://stackoverflow.com/questions/2064692/how-to-print-function-pointers-with-cout) |  |
| 4211 | 62 | [Comparing STL strings that use different allocators](https://stackoverflow.com/questions/12805771/comparing-stl-strings-that-use-different-allocators) |  |
| 4213 | 62 | [Are new and delete still useful in C++14?](https://stackoverflow.com/questions/30762994/are-new-and-delete-still-useful-in-c14) |  |
| 4239 | 61 | [What will happen when I call a member function on a NULL object pointer?](https://stackoverflow.com/questions/2533476/what-will-happen-when-i-call-a-member-function-on-a-null-object-pointer) |  |
| 4252 | 61 | [Memory alignment in C-structs](https://stackoverflow.com/questions/5435841/memory-alignment-in-c-structs) |  |
| 4308 | 61 | [Why does C++11 contain an odd clause about comparing void pointers?](https://stackoverflow.com/questions/54362209/why-does-c11-contain-an-odd-clause-about-comparing-void-pointers) |  |
| 4315 | 60 | [C++ read the whole file in buffer](https://stackoverflow.com/questions/18816126/c-read-the-whole-file-in-buffer) |  |
| 4332 | 60 | [C++ object created with new, destroyed with free(); How bad is this?](https://stackoverflow.com/questions/4061514/c-object-created-with-new-destroyed-with-free-how-bad-is-this) |  |
| 4358 | 60 | [Check for null in std::shared_ptr](https://stackoverflow.com/questions/22220512/check-for-null-in-stdshared-ptr) |  |
| 4377 | 60 | [Should I worry about the alignment during pointer casting?](https://stackoverflow.com/questions/13881487/should-i-worry-about-the-alignment-during-pointer-casting) |  |
| 4426 | 59 | [Could I ever want to access the address zero?](https://stackoverflow.com/questions/2761360/could-i-ever-want-to-access-the-address-zero) |  |
| 4438 | 59 | [How do I create an array of pointers?](https://stackoverflow.com/questions/620843/how-do-i-create-an-array-of-pointers) |  |
| 4470 | 59 | [C++ - pointer array to Vector?](https://stackoverflow.com/questions/7278347/c-pointer-array-to-vector) |  |
| 4477 | 59 | [Is make_shared really more efficient than new?](https://stackoverflow.com/questions/9302296/is-make-shared-really-more-efficient-than-new) |  |
| 4478 | 59 | [Will new return NULL in any case?](https://stackoverflow.com/questions/550451/will-new-return-null-in-any-case) |  |
| 4481 | 59 | [Understanding "corrupted size vs. prev_size" glibc error](https://stackoverflow.com/questions/49628615/understanding-corrupted-size-vs-prev-size-glibc-error) |  |
| 4483 | 59 | [shared_ptr<> is to weak_ptr<> as unique_ptr<> is to... what?](https://stackoverflow.com/questions/17536731/shared-ptr-is-to-weak-ptr-as-unique-ptr-is-to-what) |  |
| 4484 | 59 | [Difference between std::uninitialized_copy & std::copy?](https://stackoverflow.com/questions/30158192/difference-between-stduninitialized-copy-stdcopy) |  |
| 4491 | 59 | [Making std::vector allocate aligned memory](https://stackoverflow.com/questions/12942548/making-stdvector-allocate-aligned-memory) |  |
| 4500 | 59 | [Does std::vector *have* to move objects when growing capacity? Or, can allocators "reallocate"?](https://stackoverflow.com/questions/8003233/does-stdvector-have-to-move-objects-when-growing-capacity-or-can-allocator) |  |
| 4512 | 59 | [How JVM stack, heap and threads are mapped to physical memory or operation system](https://stackoverflow.com/questions/16264118/how-jvm-stack-heap-and-threads-are-mapped-to-physical-memory-or-operation-syste) |  |
| 4515 | 59 | [Recommended usage of std::unique_ptr](https://stackoverflow.com/questions/15476907/recommended-usage-of-stdunique-ptr) |  |
| 4528 | 58 | [Do all pointers have the same size in C++?](https://stackoverflow.com/questions/71870205/do-all-pointers-have-the-same-size-in-c) |  |
| 4544 | 58 | [Why is there a memory leak in this program and how can I solve it, given the constraints (using malloc and free for objects containing std::string)?](https://stackoverflow.com/questions/75600524/why-is-there-a-memory-leak-in-this-program-and-how-can-i-solve-it-given-the-con) |  |
| 4547 | 58 | [Increment void pointer by one byte? by two?](https://stackoverflow.com/questions/6449935/increment-void-pointer-by-one-byte-by-two) |  |
| 4570 | 58 | [Dynamic casting for unique_ptr](https://stackoverflow.com/questions/11002641/dynamic-casting-for-unique-ptr) |  |
| 4581 | 58 | [How does the custom deleter of std::unique_ptr work?](https://stackoverflow.com/questions/8274451/how-does-the-custom-deleter-of-stdunique-ptr-work) |  |
| 4582 | 58 | [Does dynamic memory allocation differ in C and C++ in popular implementations?](https://stackoverflow.com/questions/7443782/does-dynamic-memory-allocation-differ-in-c-and-c-in-popular-implementations) |  |
| 4584 | 58 | [C++ How to allocate memory dynamically on stack?](https://stackoverflow.com/questions/6335023/c-how-to-allocate-memory-dynamically-on-stack) |  |
| 4585 | 58 | [How to delete the default constructor?](https://stackoverflow.com/questions/10474417/how-to-delete-the-default-constructor) |  |
| 4616 | 58 | [creating a shared_ptr from unique_ptr](https://stackoverflow.com/questions/18889843/creating-a-shared-ptr-from-unique-ptr) |  |
| 4641 | 57 | [What is ** in C++?](https://stackoverflow.com/questions/644981/what-is-in-c) |  |
| 4644 | 57 | [Is there a reason to call delete in C++ when a program is exiting anyway?](https://stackoverflow.com/questions/677812/is-there-a-reason-to-call-delete-in-c-when-a-program-is-exiting-anyway) |  |
| 4647 | 57 | [Is there any reason to check for a NULL pointer before deleting?](https://stackoverflow.com/questions/615355/is-there-any-reason-to-check-for-a-null-pointer-before-deleting) |  |
| 4648 | 57 | [Segmentation fault at glGenVertexArrays( 1, &vao );](https://stackoverflow.com/questions/8302625/segmentation-fault-at-glgenvertexarrays-1-vao) |  |
| 4657 | 57 | [How do shared pointers work?](https://stackoverflow.com/questions/2802953/how-do-shared-pointers-work) |  |
| 4688 | 57 | [NULL pointer with boost::shared_ptr?](https://stackoverflow.com/questions/621220/null-pointer-with-boostshared-ptr) |  |
| 4694 | 57 | [How to profile memory usage?](https://stackoverflow.com/questions/4690800/how-to-profile-memory-usage) |  |
| 4706 | 57 | [Why would code explicitly call a static method via a null pointer?](https://stackoverflow.com/questions/25719244/why-would-code-explicitly-call-a-static-method-via-a-null-pointer) |  |
| 4738 | 56 | [How to capture a unique_ptr into a lambda expression?](https://stackoverflow.com/questions/8236521/how-to-capture-a-unique-ptr-into-a-lambda-expression) |  |
| 4748 | 56 | [unique_ptr boost equivalent?](https://stackoverflow.com/questions/2953530/unique-ptr-boost-equivalent) |  |
| 4752 | 56 | [What is the difference between "new" and "malloc" and "calloc" in C++?](https://stackoverflow.com/questions/807939/what-is-the-difference-between-new-and-malloc-and-calloc-in-c) |  |
| 4791 | 56 | [track C++ memory allocations](https://stackoverflow.com/questions/910172/track-c-memory-allocations) |  |
| 4802 | 56 | [Who deletes the memory allocated during a "new" operation which has exception in constructor?](https://stackoverflow.com/questions/1674980/who-deletes-the-memory-allocated-during-a-new-operation-which-has-exception-in) |  |
| 4818 | 56 | [Should I use shared_ptr or unique_ptr](https://stackoverflow.com/questions/5576922/should-i-use-shared-ptr-or-unique-ptr) |  |
| 4835 | 55 | [What is the difference between char a\[\] = ?string?; and char *p = ?string?;?](https://stackoverflow.com/questions/9460260/what-is-the-difference-between-char-a-string-and-char-p-string) |  |
| 4837 | 55 | [How to read/write arbitrary bits in C/C++](https://stackoverflow.com/questions/11815894/how-to-read-write-arbitrary-bits-in-c-c) |  |
| 4841 | 55 | [Pointer vs Variable speed in C++](https://stackoverflow.com/questions/6919380/pointer-vs-variable-speed-in-c) |  |
| 4847 | 55 | [Any reason to overload global new and delete?](https://stackoverflow.com/questions/1152511/any-reason-to-overload-global-new-and-delete) |  |
| 4885 | 55 | [Class members that are objects - Pointers or not? C++](https://stackoverflow.com/questions/3871429/class-members-that-are-objects-pointers-or-not-c) |  |
| 4907 | 55 | [What's your convention for typedef'ing shared_ptr?](https://stackoverflow.com/questions/2717436/whats-your-convention-for-typedefing-shared-ptr) |  |
| 4912 | 55 | [How to enable_shared_from_this of both parent and derived](https://stackoverflow.com/questions/657155/how-to-enable-shared-from-this-of-both-parent-and-derived) |  |
| 4939 | 55 | [Memory Allocation Profiling in C++](https://stackoverflow.com/questions/700097/memory-allocation-profiling-in-c) |  |
| 4968 | 54 | [Function does not change passed pointer C++](https://stackoverflow.com/questions/11842416/function-does-not-change-passed-pointer-c) |  |
| 4973 | 54 | [How do you determine the size of an object in C++?](https://stackoverflow.com/questions/937773/how-do-you-determine-the-size-of-an-object-in-c) |  |
| 4976 | 54 | [Use of observer_ptr](https://stackoverflow.com/questions/31862412/use-of-observer-ptr) |  |
| 4999 | 54 | [Double free or corruption after queue::push](https://stackoverflow.com/questions/14063791/double-free-or-corruption-after-queuepush) |  |
