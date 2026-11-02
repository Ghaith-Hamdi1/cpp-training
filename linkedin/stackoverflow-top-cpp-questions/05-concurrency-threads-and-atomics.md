# Concurrency, threads and atomics

[Back to all topics](README.md)

165 questions.

Source: the 5,000 most voted questions tagged `c++` (the first 100 pages of 50 at <https://stackoverflow.com/questions/tagged/c%2b%2b?tab=votes&pagesize=50>), fetched on 2026-11-02 through the Stack Exchange API, sorted by votes. The lowest score included is 54 votes. Ties within the same score can be in a slightly different order than the website.

| Rank | Votes | Question | |
|---:|---:|---|---|
| 16 | 2,233 | [C++11 introduced a standardized memory model. What does it mean? And how is it going to affect C++ programming?](https://stackoverflow.com/questions/6319146/c11-introduced-a-standardized-memory-model-what-does-it-mean-and-how-is-it-g) |  |
| 153 | 572 | [Programmatically find the number of cores on a machine](https://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine) |  |
| 164 | 552 | [std::unique_lock<std::mutex> or std::lock_guard<std::mutex>?](https://stackoverflow.com/questions/20516773/stdunique-lockstdmutex-or-stdlock-guardstdmutex) |  |
| 207 | 470 | [What is std::promise?](https://stackoverflow.com/questions/11004273/what-is-stdpromise) |  |
| 215 | 459 | [What is the usefulness of `enable_shared_from_this`?](https://stackoverflow.com/questions/712279/what-is-the-usefulness-of-enable-shared-from-this) |  |
| 254 | 410 | [Start thread with member function](https://stackoverflow.com/questions/10673585/start-thread-with-member-function) |  |
| 277 | 389 | [Simple example of threading in C++](https://stackoverflow.com/questions/266168/simple-example-of-threading-in-c) |  |
| 289 | 375 | [std::lock_guard or std::scoped_lock?](https://stackoverflow.com/questions/43019598/stdlock-guard-or-stdscoped-lock) |  |
| 376 | 318 | [What exactly is std::atomic?](https://stackoverflow.com/questions/31978324/what-exactly-is-stdatomic) |  |
| 518 | 255 | [Is local static variable initialization thread-safe in C++11?](https://stackoverflow.com/questions/8102125/is-local-static-variable-initialization-thread-safe-in-c11) |  |
| 610 | 228 | [Mutex example / tutorial?](https://stackoverflow.com/questions/4989451/mutex-example-tutorial) |  |
| 654 | 219 | [When should I use std::thread::detach?](https://stackoverflow.com/questions/22803600/when-should-i-use-stdthreaddetach) |  |
| 695 | 210 | [What happens to a detached thread when main() exits?](https://stackoverflow.com/questions/19744250/what-happens-to-a-detached-thread-when-main-exits) |  |
| 702 | 208 | [Thread pooling in C++11](https://stackoverflow.com/questions/15752659/thread-pooling-in-c11) |  |
| 736 | 202 | [How do I terminate a thread in C++11?](https://stackoverflow.com/questions/12207684/how-do-i-terminate-a-thread-in-c11) |  |
| 748 | 201 | [Is Meyers' implementation of the Singleton pattern thread safe?](https://stackoverflow.com/questions/1661529/is-meyers-implementation-of-the-singleton-pattern-thread-safe) |  |
| 757 | 200 | [What is the difference between packaged_task and async](https://stackoverflow.com/questions/18143661/what-is-the-difference-between-packaged-task-and-async) |  |
| 760 | 199 | [What does the thread_local mean in C++11?](https://stackoverflow.com/questions/11983875/what-does-the-thread-local-mean-in-c11) |  |
| 777 | 197 | [C++11 std::thread vs Posix threads](https://stackoverflow.com/questions/13134186/c11-stdthread-vs-posix-threads) |  |
| 786 | 195 | [Why is volatile not considered useful in multithreaded C or C++ programming?](https://stackoverflow.com/questions/2484980/why-is-volatile-not-considered-useful-in-multithreaded-c-or-c-programming) |  |
| 794 | 194 | [Is incrementing an int effectively atomic in specific cases?](https://stackoverflow.com/questions/39393850/is-incrementing-an-int-effectively-atomic-in-specific-cases) |  |
| 855 | 186 | [fork() branches more than expected?](https://stackoverflow.com/questions/11132868/fork-branches-more-than-expected) |  |
| 884 | 182 | [Futures vs. Promises](https://stackoverflow.com/questions/12620186/futures-vs-promises) |  |
| 893 | 180 | [How to use the C socket API in C++ on z/OS](https://stackoverflow.com/questions/25/how-to-use-the-c-socket-api-in-c-on-z-os) |  |
| 896 | 180 | [When to use volatile with multi threading?](https://stackoverflow.com/questions/4557979/when-to-use-volatile-with-multi-threading) |  |
| 937 | 174 | [How can I catch a Ctrl-C event?](https://stackoverflow.com/questions/1641182/how-can-i-catch-a-ctrl-c-event) |  |
| 962 | 171 | [What is the closest thing Windows has to fork()?](https://stackoverflow.com/questions/985281/what-is-the-closest-thing-windows-has-to-fork) |  |
| 974 | 170 | [Significance of -pthread flag when compiling](https://stackoverflow.com/questions/2127797/significance-of-pthread-flag-when-compiling) |  |
| 1003 | 167 | [C++ terminate called without an active exception](https://stackoverflow.com/questions/7381757/c-terminate-called-without-an-active-exception) |  |
| 1080 | 159 | [Is it smart to replace boost::thread and boost::mutex with c++11 equivalents?](https://stackoverflow.com/questions/7241993/is-it-smart-to-replace-boostthread-and-boostmutex-with-c11-equivalents) |  |
| 1145 | 153 | [C++0x has no semaphores? How to synchronize threads?](https://stackoverflow.com/questions/4792449/c0x-has-no-semaphores-how-to-synchronize-threads) |  |
| 1213 | 147 | [Does async(launch::async) in C++11 make thread pools obsolete for avoiding expensive thread creation?](https://stackoverflow.com/questions/14351352/does-asynclaunchasync-in-c11-make-thread-pools-obsolete-for-avoiding-expen) |  |
| 1217 | 146 | [When do I really need to use atomic<bool> instead of bool?](https://stackoverflow.com/questions/16320838/when-do-i-really-need-to-use-atomicbool-instead-of-bool) |  |
| 1218 | 146 | [What are coroutines in C++20?](https://stackoverflow.com/questions/43503656/what-are-coroutines-in-c20) |  |
| 1289 | 141 | [Windows threading: _beginthread vs _beginthreadex vs CreateThread C++](https://stackoverflow.com/questions/331536/windows-threading-beginthread-vs-beginthreadex-vs-createthread-c) |  |
| 1402 | 133 | [What do each memory_order mean?](https://stackoverflow.com/questions/12346487/what-do-each-memory-order-mean) |  |
| 1431 | 131 | [Spinlock versus Semaphore](https://stackoverflow.com/questions/195853/spinlock-versus-semaphore) |  |
| 1489 | 128 | [How to check if a std::thread is still running?](https://stackoverflow.com/questions/9094422/how-to-check-if-a-stdthread-is-still-running) |  |
| 1499 | 127 | [How can I propagate exceptions between threads?](https://stackoverflow.com/questions/233127/how-can-i-propagate-exceptions-between-threads) |  |
| 1517 | 126 | [Understanding std::atomic::compare_exchange_weak() in C++11](https://stackoverflow.com/questions/25199838/understanding-stdatomiccompare-exchange-weak-in-c11) |  |
| 1519 | 126 | [Does const mean thread-safe in C++11?](https://stackoverflow.com/questions/14127379/does-const-mean-thread-safe-in-c11) |  |
| 1527 | 125 | [How to get integer thread id in c++11](https://stackoverflow.com/questions/7432100/how-to-get-integer-thread-id-in-c11) |  |
| 1583 | 122 | [Are C++11 thread_local variables automatically static?](https://stackoverflow.com/questions/22794382/are-c11-thread-local-variables-automatically-static) |  |
| 1587 | 122 | [How should I deal with mutexes in movable types in C++?](https://stackoverflow.com/questions/29986208/how-should-i-deal-with-mutexes-in-movable-types-in-c) |  |
| 1609 | 121 | [Do I have to acquire lock before calling condition_variable.notify_one()?](https://stackoverflow.com/questions/17101922/do-i-have-to-acquire-lock-before-calling-condition-variable-notify-one) |  |
| 1612 | 120 | [Example for boost shared_mutex (multiple reads/one write)?](https://stackoverflow.com/questions/989795/example-for-boost-shared-mutex-multiple-reads-one-write) |  |
| 1628 | 120 | [Get the status of a std::future](https://stackoverflow.com/questions/10890242/get-the-status-of-a-stdfuture) |  |
| 1723 | 115 | [When to use std::async vs std::threads?](https://stackoverflow.com/questions/25814365/when-to-use-stdasync-vs-stdthreads) |  |
| 1731 | 114 | [What is SOCK_DGRAM and SOCK_STREAM?](https://stackoverflow.com/questions/5815675/what-is-sock-dgram-and-sock-stream) |  |
| 1802 | 112 | [How do stackless coroutines differ from stackful coroutines?](https://stackoverflow.com/questions/28977302/how-do-stackless-coroutines-differ-from-stackful-coroutines) |  |
| 1826 | 110 | [std::thread calling method of class](https://stackoverflow.com/questions/10998780/stdthread-calling-method-of-class) |  |
| 1844 | 110 | [Understanding std::hardware_destructive_interference_size and std::hardware_constructive_interference_size](https://stackoverflow.com/questions/39680206/understanding-stdhardware-destructive-interference-size-and-stdhardware-cons) |  |
| 1866 | 108 | [Why does code mutating a shared variable across threads apparently NOT suffer from a race condition?](https://stackoverflow.com/questions/41816495/why-does-code-mutating-a-shared-variable-across-threads-apparently-not-suffer-fr) |  |
| 1929 | 106 | [Confused when boost::asio::io_service run method blocks/unblocks](https://stackoverflow.com/questions/15568100/confused-when-boostasioio-service-run-method-blocks-unblocks) |  |
| 1936 | 106 | [Why should I use std::async?](https://stackoverflow.com/questions/17963172/why-should-i-use-stdasync) |  |
| 1950 | 106 | [Detecting TCP Client Disconnect](https://stackoverflow.com/questions/283375/detecting-tcp-client-disconnect) |  |
| 2001 | 104 | [How can I get the IP address of a (Linux) machine?](https://stackoverflow.com/questions/212528/how-can-i-get-the-ip-address-of-a-linux-machine) |  |
| 2055 | 102 | [Calling pthread_cond_signal without locking mutex](https://stackoverflow.com/questions/4544234/calling-pthread-cond-signal-without-locking-mutex) |  |
| 2181 | 98 | [Are C++ Reads and Writes of an int Atomic?](https://stackoverflow.com/questions/54188/are-c-reads-and-writes-of-an-int-atomic) |  |
| 2188 | 97 | [pthread function from a class](https://stackoverflow.com/questions/1151582/pthread-function-from-a-class) |  |
| 2195 | 97 | [Reader/Writer Locks in C++](https://stackoverflow.com/questions/244316/reader-writer-locks-in-c) |  |
| 2210 | 97 | [Must I call atomic load/store explicitly?](https://stackoverflow.com/questions/18850752/must-i-call-atomic-load-store-explicitly) |  |
| 2251 | 95 | [I've heard i++ isn't thread safe, is ++i thread-safe?](https://stackoverflow.com/questions/680097/ive-heard-i-isnt-thread-safe-is-i-thread-safe) |  |
| 2269 | 95 | [C++11 thread-safe queue](https://stackoverflow.com/questions/15278343/c11-thread-safe-queue) |  |
| 2286 | 95 | [c++, std::atomic, what is std::memory_order and how to use them?](https://stackoverflow.com/questions/9553591/c-stdatomic-what-is-stdmemory-order-and-how-to-use-them) |  |
| 2337 | 93 | [Is there a production ready lock-free queue or hash implementation in C++](https://stackoverflow.com/questions/1164023/is-there-a-production-ready-lock-free-queue-or-hash-implementation-in-c) |  |
| 2340 | 93 | [Does the C++ volatile keyword introduce a memory fence?](https://stackoverflow.com/questions/26307071/does-the-c-volatile-keyword-introduce-a-memory-fence) |  |
| 2358 | 92 | [What's the difference between "static" and "dynamic" schedule in OpenMP?](https://stackoverflow.com/questions/10850155/whats-the-difference-between-static-and-dynamic-schedule-in-openmp) |  |
| 2379 | 92 | [Should mutexes be mutable?](https://stackoverflow.com/questions/4127333/should-mutexes-be-mutable) |  |
| 2381 | 92 | [What are the correct link options to use std::thread in GCC under linux?](https://stackoverflow.com/questions/8649828/what-are-the-correct-link-options-to-use-stdthread-in-gcc-under-linux) |  |
| 2476 | 90 | [Pass multiple arguments into std::thread](https://stackoverflow.com/questions/20340750/pass-multiple-arguments-into-stdthread) |  |
| 2500 | 89 | [How do you implement a singleton efficiently and thread-safely?](https://stackoverflow.com/questions/2576022/how-do-you-implement-a-singleton-efficiently-and-thread-safely) |  |
| 2505 | 89 | [Are stackless C++20 coroutines a problem?](https://stackoverflow.com/questions/57163510/are-stackless-c20-coroutines-a-problem) |  |
| 2510 | 89 | [Where is the lock for a std::atomic?](https://stackoverflow.com/questions/50298358/where-is-the-lock-for-a-stdatomic) |  |
| 2511 | 89 | [Portable way of setting std::thread priority in C++11](https://stackoverflow.com/questions/18884510/portable-way-of-setting-stdthread-priority-in-c11) |  |
| 2582 | 87 | [Concurrency: Atomic and volatile in C++11 memory model](https://stackoverflow.com/questions/8819095/concurrency-atomic-and-volatile-in-c11-memory-model) |  |
| 2594 | 87 | [C++11: Why does std::condition_variable use std::unique_lock?](https://stackoverflow.com/questions/13099660/c11-why-does-stdcondition-variable-use-stdunique-lock) |  |
| 2655 | 86 | [std::thread - naming your thread](https://stackoverflow.com/questions/10121560/stdthread-naming-your-thread) |  |
| 2660 | 86 | [Is armadillo solve() thread safe?](https://stackoverflow.com/questions/30063240/is-armadillo-solve-thread-safe) |  |
| 2733 | 84 | [When to use recursive mutex?](https://stackoverflow.com/questions/2415082/when-to-use-recursive-mutex) |  |
| 2831 | 82 | [Circular lock-free buffer](https://stackoverflow.com/questions/871234/circular-lock-free-buffer) |  |
| 2854 | 82 | [What does the \[\[carries_dependency\]\] attribute mean?](https://stackoverflow.com/questions/6411270/what-does-the-carries-dependency-attribute-mean) |  |
| 2883 | 81 | [Why is the != operator not allowed with OpenMP?](https://stackoverflow.com/questions/13312679/why-is-the-operator-not-allowed-with-openmp) |  |
| 2889 | 81 | [difference between standard's atomic bool and atomic flag](https://stackoverflow.com/questions/39329311/difference-between-standards-atomic-bool-and-atomic-flag) |  |
| 2909 | 80 | [How do you implement Coroutines in C++](https://stackoverflow.com/questions/121757/how-do-you-implement-coroutines-in-c) |  |
| 2913 | 80 | [The actor model: Why is Erlang/OTP special? Could you use another language?](https://stackoverflow.com/questions/8107612/the-actor-model-why-is-erlang-otp-special-could-you-use-another-language) |  |
| 2932 | 80 | [how to make an application thread safe?](https://stackoverflow.com/questions/5125241/how-to-make-an-application-thread-safe) |  |
| 2955 | 79 | [Parallel Loops in C++](https://stackoverflow.com/questions/36246300/parallel-loops-in-c) |  |
| 2994 | 78 | [Best C/C++ Network Library](https://stackoverflow.com/questions/118945/best-c-c-network-library) |  |
| 3059 | 77 | [How would you implement a basic event-loop?](https://stackoverflow.com/questions/658403/how-would-you-implement-a-basic-event-loop) |  |
| 3084 | 77 | [What is the performance penalty of C++11 thread_local variables in GCC 4.8?](https://stackoverflow.com/questions/13106049/what-is-the-performance-penalty-of-c11-thread-local-variables-in-gcc-4-8) |  |
| 3103 | 76 | [How much overhead is there when creating a thread?](https://stackoverflow.com/questions/3929774/how-much-overhead-is-there-when-creating-a-thread) |  |
| 3107 | 76 | [C++: Simple return value from std::thread?](https://stackoverflow.com/questions/7686939/c-simple-return-value-from-stdthread) |  |
| 3123 | 76 | [How can I distinguish between high- and low-performance cores/threads in C++?](https://stackoverflow.com/questions/68444429/how-can-i-distinguish-between-high-and-low-performance-cores-threads-in-c) |  |
| 3129 | 76 | [How to support both IPv4 and IPv6 connections](https://stackoverflow.com/questions/1618240/how-to-support-both-ipv4-and-ipv6-connections) |  |
| 3134 | 76 | [How does OpenMP handle nested loops?](https://stackoverflow.com/questions/13357065/how-does-openmp-handle-nested-loops) |  |
| 3159 | 75 | [How to implement multithread safe singleton in C++11 without using <mutex>](https://stackoverflow.com/questions/11711920/how-to-implement-multithread-safe-singleton-in-c11-without-using-mutex) |  |
| 3172 | 75 | [Why is the volatile qualifier used through out std::atomic?](https://stackoverflow.com/questions/2479067/why-is-the-volatile-qualifier-used-through-out-stdatomic) |  |
| 3206 | 75 | [std::this_thread::yield() vs std::this_thread::sleep_for()](https://stackoverflow.com/questions/11048946/stdthis-threadyield-vs-stdthis-threadsleep-for) |  |
| 3232 | 74 | [Multithreading program stuck in optimized mode but runs normally in -O0](https://stackoverflow.com/questions/58516052/multithreading-program-stuck-in-optimized-mode-but-runs-normally-in-o0) |  |
| 3296 | 73 | [How to create a thread pool using boost in C++?](https://stackoverflow.com/questions/19500404/how-to-create-a-thread-pool-using-boost-in-c) |  |
| 3333 | 73 | [How do memory_order_seq_cst and memory_order_acq_rel differ?](https://stackoverflow.com/questions/12340773/how-do-memory-order-seq-cst-and-memory-order-acq-rel-differ) |  |
| 3400 | 72 | [What happens when an exception goes unhandled in a multithreaded C++11 program?](https://stackoverflow.com/questions/7272093/what-happens-when-an-exception-goes-unhandled-in-a-multithreaded-c11-program) |  |
| 3409 | 72 | [How do "acquire" and "consume" memory orders differ, and when is "consume" preferable?](https://stackoverflow.com/questions/19609964/how-do-acquire-and-consume-memory-orders-differ-and-when-is-consume-prefe) |  |
| 3442 | 71 | [How to increase thread priority in pthreads?](https://stackoverflow.com/questions/3649281/how-to-increase-thread-priority-in-pthreads) |  |
| 3453 | 71 | [How to get IP address of boost::asio::ip::tcp::socket?](https://stackoverflow.com/questions/601763/how-to-get-ip-address-of-boostasioiptcpsocket) |  |
| 3570 | 69 | [Using Boost.Lockfree queue is slower than using mutexes](https://stackoverflow.com/questions/43540943/using-boost-lockfree-queue-is-slower-than-using-mutexes) |  |
| 3659 | 68 | [C++ mutex and const correctness](https://stackoverflow.com/questions/3239905/c-mutex-and-const-correctness) |  |
| 3664 | 68 | [Differences between Conditional variables, Mutexes and Locks](https://stackoverflow.com/questions/1055398/differences-between-conditional-variables-mutexes-and-locks) |  |
| 3670 | 68 | [How to estimate the thread context switching overhead?](https://stackoverflow.com/questions/304752/how-to-estimate-the-thread-context-switching-overhead) |  |
| 3676 | 68 | [Does std::atomic<std::string> work appropriately?](https://stackoverflow.com/questions/16876410/does-stdatomicstdstring-work-appropriately) |  |
| 3721 | 67 | [Multithreading and multicore differences](https://stackoverflow.com/questions/11835046/multithreading-and-multicore-differences) |  |
| 3745 | 67 | [What's the best way to lock multiple std::mutex'es?](https://stackoverflow.com/questions/17113619/whats-the-best-way-to-lock-multiple-stdmutexes) |  |
| 3761 | 67 | [Are there any concurrent containers in C++11?](https://stackoverflow.com/questions/7817364/are-there-any-concurrent-containers-in-c11) |  |
| 3762 | 67 | [What's the difference between notify_all() and notify_one() of std::condition_variable?](https://stackoverflow.com/questions/9015748/whats-the-difference-between-notify-all-and-notify-one-of-stdcondition-va) |  |
| 3823 | 66 | [How to print pthread_t](https://stackoverflow.com/questions/1759794/how-to-print-pthread-t) |  |
| 3824 | 66 | [Why don't compilers merge redundant std::atomic writes?](https://stackoverflow.com/questions/45960387/why-dont-compilers-merge-redundant-stdatomic-writes) |  |
| 3863 | 66 | [OpenMP: are local variables automatically private?](https://stackoverflow.com/questions/6358375/openmp-are-local-variables-automatically-private) |  |
| 3872 | 66 | [Waiting for multiple futures?](https://stackoverflow.com/questions/19225372/waiting-for-multiple-futures) |  |
| 3889 | 65 | [std::mutex vs std::recursive_mutex as class member](https://stackoverflow.com/questions/14498892/stdmutex-vs-stdrecursive-mutex-as-class-member) |  |
| 3898 | 65 | [why do I need std::condition_variable?](https://stackoverflow.com/questions/16350473/why-do-i-need-stdcondition-variable) |  |
| 3938 | 65 | [When to use promise over async or packaged_task?](https://stackoverflow.com/questions/17729924/when-to-use-promise-over-async-or-packaged-task) |  |
| 3950 | 65 | [What does `std::kill_dependency` do, and why would I want to use it?](https://stackoverflow.com/questions/7150395/what-does-stdkill-dependency-do-and-why-would-i-want-to-use-it) |  |
| 3957 | 65 | [Why is there no C++11 threadsafe alternative to std::localtime and std::gmtime?](https://stackoverflow.com/questions/25618702/why-is-there-no-c11-threadsafe-alternative-to-stdlocaltime-and-stdgmtime) |  |
| 4029 | 64 | [Will (and should) there be sockets in C++11?](https://stackoverflow.com/questions/6638213/will-and-should-there-be-sockets-in-c11) |  |
| 4102 | 63 | [Why is integer assignment on a naturally aligned variable atomic on x86?](https://stackoverflow.com/questions/36624881/why-is-integer-assignment-on-a-naturally-aligned-variable-atomic-on-x86) |  |
| 4108 | 63 | [How to use SQLite in a multi-threaded application?](https://stackoverflow.com/questions/1680249/how-to-use-sqlite-in-a-multi-threaded-application) |  |
| 4120 | 63 | [Boost.ASIO-based HTTP client library (like libcurl)](https://stackoverflow.com/questions/2251361/boost-asio-based-http-client-library-like-libcurl) |  |
| 4202 | 62 | [Are child processes created with fork() automatically killed when the parent is killed?](https://stackoverflow.com/questions/395877/are-child-processes-created-with-fork-automatically-killed-when-the-parent-is) |  |
| 4227 | 61 | [How to easily make std::cout thread-safe?](https://stackoverflow.com/questions/14718124/how-to-easily-make-stdcout-thread-safe) |  |
| 4228 | 61 | [How to execute a functor or a lambda in a given thread in Qt, GCD-style?](https://stackoverflow.com/questions/21646467/how-to-execute-a-functor-or-a-lambda-in-a-given-thread-in-qt-gcd-style) |  |
| 4265 | 61 | [Are C/C++ fundamental types atomic?](https://stackoverflow.com/questions/35226128/are-c-c-fundamental-types-atomic) |  |
| 4266 | 61 | [What causes runtime error message: std::system_error - operation not permitted, including mult-threading?](https://stackoverflow.com/questions/17274032/what-causes-runtime-error-message-stdsystem-error-operation-not-permitted) |  |
| 4268 | 61 | [How can I get the IP Address of a local computer?](https://stackoverflow.com/questions/122208/how-can-i-get-the-ip-address-of-a-local-computer) |  |
| 4270 | 61 | [Delayed start of a thread in C++ 11](https://stackoverflow.com/questions/25524775/delayed-start-of-a-thread-in-c-11) |  |
| 4304 | 61 | [Can I use std::async without waiting for the future limitation?](https://stackoverflow.com/questions/21531096/can-i-use-stdasync-without-waiting-for-the-future-limitation) |  |
| 4345 | 60 | [What is different between join() and detach() for multi threading in C++?](https://stackoverflow.com/questions/37015775/what-is-different-between-join-and-detach-for-multi-threading-in-c) |  |
| 4393 | 60 | [What's the difference between sockaddr, sockaddr_in, and sockaddr_in6?](https://stackoverflow.com/questions/18609397/whats-the-difference-between-sockaddr-sockaddr-in-and-sockaddr-in6) |  |
| 4405 | 60 | [C++0x thread interruption](https://stackoverflow.com/questions/2790346/c0x-thread-interruption) |  |
| 4409 | 60 | [any good and simple RPC library for inter-process calls?](https://stackoverflow.com/questions/5398673/any-good-and-simple-rpc-library-for-inter-process-calls) |  |
| 4464 | 59 | [C++11 equivalent to boost shared_mutex](https://stackoverflow.com/questions/14306797/c11-equivalent-to-boost-shared-mutex) |  |
| 4474 | 59 | [What is std::jthread in c++20?](https://stackoverflow.com/questions/62325679/what-is-stdjthread-in-c20) |  |
| 4504 | 59 | [std::scoped_lock or std::unique_lock or std::lock_guard?](https://stackoverflow.com/questions/58443465/stdscoped-lock-or-stdunique-lock-or-stdlock-guard) |  |
| 4509 | 59 | [Why is the destructor of a future returned from `std::async` blocking?](https://stackoverflow.com/questions/23455104/why-is-the-destructor-of-a-future-returned-from-stdasync-blocking) |  |
| 4525 | 58 | [How to allocate thread local storage?](https://stackoverflow.com/questions/6021273/how-to-allocate-thread-local-storage) |  |
| 4606 | 58 | [How to atomically update a maximum value?](https://stackoverflow.com/questions/16190078/how-to-atomically-update-a-maximum-value) |  |
| 4608 | 58 | [What does std::thread.join() do?](https://stackoverflow.com/questions/15148057/what-does-stdthread-join-do) |  |
| 4619 | 58 | [Do I need a mutex for reading?](https://stackoverflow.com/questions/1525189/do-i-need-a-mutex-for-reading) |  |
| 4633 | 57 | [fork() and output](https://stackoverflow.com/questions/9364410/fork-and-output) |  |
| 4655 | 57 | [What is lock-free multithreaded programming?](https://stackoverflow.com/questions/14011849/what-is-lock-free-multithreaded-programming) |  |
| 4656 | 57 | [C++ Parallelization Libraries: OpenMP vs. Thread Building Blocks](https://stackoverflow.com/questions/615264/c-parallelization-libraries-openmp-vs-thread-building-blocks) |  |
| 4664 | 57 | [Is it safe to fork from within a thread?](https://stackoverflow.com/questions/6078712/is-it-safe-to-fork-from-within-a-thread) |  |
| 4701 | 57 | [Why should I use non-blocking or blocking sockets?](https://stackoverflow.com/questions/10654286/why-should-i-use-non-blocking-or-blocking-sockets) |  |
| 4708 | 57 | [Building error using cmake: cannot find -lpthreads](https://stackoverflow.com/questions/31948521/building-error-using-cmake-cannot-find-lpthreads) |  |
| 4749 | 56 | [What is process and thread?](https://stackoverflow.com/questions/2319924/what-is-process-and-thread) |  |
| 4750 | 56 | [Acquire/Release versus Sequentially Consistent memory order](https://stackoverflow.com/questions/14861822/acquire-release-versus-sequentially-consistent-memory-order) |  |
| 4757 | 56 | [What are the "things to know" when diving into multi-threaded programming in C++](https://stackoverflow.com/questions/2118090/what-are-the-things-to-know-when-diving-into-multi-threaded-programming-in-c) |  |
| 4816 | 56 | [How to use std::atomic<> effectively for non-primitive types?](https://stackoverflow.com/questions/13885617/how-to-use-stdatomic-effectively-for-non-primitive-types) |  |
| 4827 | 56 | [How to perform atomic operations on Linux that work on x86, arm, GCC and icc?](https://stackoverflow.com/questions/2287451/how-to-perform-atomic-operations-on-linux-that-work-on-x86-arm-gcc-and-icc) |  |
| 4831 | 56 | [Java thread leaks when calling back from native thread via JNI](https://stackoverflow.com/questions/20325792/java-thread-leaks-when-calling-back-from-native-thread-via-jni) |  |
| 4832 | 56 | [Using C++11 futures: Nested calls of std::async crash: Compiler/Standard library bug?](https://stackoverflow.com/questions/28604461/using-c11-futures-nested-calls-of-stdasync-crash-compiler-standard-library) |  |
| 4883 | 55 | [Will main() catch exceptions thrown from threads?](https://stackoverflow.com/questions/7730502/will-main-catch-exceptions-thrown-from-threads) |  |
| 4951 | 55 | [Why does Windows 10 start extra threads in my program?](https://stackoverflow.com/questions/34822072/why-does-windows-10-start-extra-threads-in-my-program) |  |
| 4989 | 54 | [Is std::vector or boost::vector thread safe?](https://stackoverflow.com/questions/9042571/is-stdvector-or-boostvector-thread-safe) |  |
| 4996 | 54 | [std::lock_guard example, explanation on why it works](https://stackoverflow.com/questions/35252119/stdlock-guard-example-explanation-on-why-it-works) |  |
