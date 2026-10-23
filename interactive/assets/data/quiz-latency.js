/* Quiz questions for the 'latency' topic. Loaded by 12-low-latency-quiz.html. */
CT.quizData.latency = {
  id: 'latency',
  questions: [
    { sec: 's1', q: 'Why does tail latency matter more than the average for a message pipeline?',
      opts: ['The average cannot be computed for latency data in practice', 'Rare slow cases cause missed deadlines, and the average hides them', 'The tail is always identical to the average, so it adds nothing', 'Only throughput is measured in real systems'], a: 1,
      why: 'A mean of a few hundred nanoseconds can coexist with an occasional stall of tens of microseconds. That one-in-a-thousand stall is what you feel at the end of the pipeline, so you report and minimise percentiles.' },

    { sec: 's1', q: 'Which pair best describes the cost of a hit in the L1 cache versus a miss to main memory?',
      opts: ['About the same', 'About 1 ns versus about 100 ns', 'About 100 ns versus about 1 ns', 'About 1 ms versus about 1 s'], a: 1,
      why: 'A main-memory access is roughly a hundred times slower than an L1 hit (exact numbers vary by CPU). That ratio is why data layout dominates the performance of tight loops.' },

    { sec: 's2', q: 'A run reports: mean 281 ns, p50 200 ns, p99 219 ns, p99.9 80,004 ns. What does it tell you?',
      opts: ['The system is fine: the mean is low, so nobody is ever left waiting', 'Nearly all operations are fast, but about 1 in 1000 is roughly 400 times slower', 'The measurement is wrong: p99.9 can never be larger than the mean', 'p50 should always be equal to the mean of all the samples taken'], a: 1,
      why: 'Percentiles show the shape. p50 and p99 are close to 200 ns, but p99.9 jumped to 80 microseconds: a rare stall (allocation, context switch, page fault). The mean moved only a little.' },

    { sec: 's2', q: 'Why does a microbenchmark need to use the result of the code it times?',
      opts: ['The clock requires the result to be used before it stops', 'The compiler may delete code whose result is unused', 'Using the result makes the timed loop run faster', 'Unused results cause undefined behavior in the program'], a: 1,
      why: 'Dead-code elimination removes work with no observable effect. Store the result in a volatile sink or print a checksum so the measured work is really executed.' },

    { sec: 's2', q: 'Which clock should you use to measure elapsed time for latency?',
      opts: ['`std::chrono::system_clock`', '`std::chrono::steady_clock`', '`time(nullptr)`', '`std::chrono::file_clock`'], a: 1,
      why: 'steady_clock is monotonic: it never jumps backwards when the system time is adjusted. system_clock can be changed by NTP or by hand, which would corrupt an interval.' },

    { sec: 's3', q: 'Why avoid `new` and `malloc` on the hot path?',
      opts: ['They always take several milliseconds for each call that is made', 'The allocator may take a lock or call the kernel, so its cost varies', 'They are not allowed in C++17 and later versions of the standard', 'They corrupt the stack of the calling thread when used in loops'], a: 1,
      why: 'Allocation is usually fast but occasionally very slow, which ruins tail latency. The fix is to allocate everything at startup and reuse it.' },

    { sec: 's3', q: 'How many heap allocations does the loop make?',
      code: String.raw`
std::vector<int> v;
v.reserve(100);
for (int i = 0; i < 100; ++i) v.push_back(i);
`,
      opts: ['0', '1', '100', 'About 7 (one per doubling)'], a: 1,
      why: 'reserve(100) allocates the whole buffer once, so the 100 push_backs never reallocate. Without the reserve the vector would grow by reallocating several times.' },

    { sec: 's3', q: 'In an object pool with a free list, what does `deallocate` do?',
      opts: ['Calls delete on the memory of the slot that is being released', 'Destroys the object and returns its slot to the free list in O(1)', 'Sorts the free list by address after each call to it', 'Hands the memory back to the operating system each time'], a: 1,
      why: 'The pool owns a fixed block. Releasing a slot means linking it onto the front of the free list; the next allocate reuses it. No heap involved, and no fragmentation.' },

    { sec: 's3', q: 'What does placement new do?',
      opts: ['Allocates memory and then constructs an object in it', 'Constructs an object in memory that is already allocated', 'Moves an existing object onto the stack for speed', 'Allocates memory without constructing anything in it'], a: 1,
      why: '`new (address) T(args)` runs the constructor at the given address and allocates nothing. Pools and arenas use it to construct objects inside memory they reserved earlier. You must call the destructor yourself.' },

    { sec: 's3', q: 'What is special about `std::pmr::monotonic_buffer_resource`?',
      opts: ['Allocation bumps a pointer in your buffer; everything is freed at once', 'It is thread-safe by default, using an internal lock for every call', 'It frees each allocation as soon as it is released by the caller', 'It only works for std::string and std::vector objects, nothing else'], a: 0,
      why: 'A monotonic resource never reuses freed memory; it just advances a pointer, so allocation is extremely cheap. When the resource is destroyed or released, everything goes at once. Ideal for per-message scratch data.' },

    { sec: 's4', q: 'A loop reads only one field of a large array of structs. Why can a struct-of-arrays layout be faster?',
      opts: ['Arrays of structs cannot be iterated efficiently by a loop', 'It streams only the bytes the loop needs, so each cache line is used fully', 'It uses less source code than an array of structs would need', 'Struct-of-arrays avoids undefined behavior in the loop body'], a: 1,
      why: 'The CPU loads 64-byte cache lines. With an array of structs the unused fields occupy most of each line; with one array per field the wanted field is packed together, so far less memory traffic is needed.' },

    { sec: 's4', q: 'What is false sharing, and how do you fix it?',
      opts: ['Two threads write one cache line, so it bounces between cores; fix with alignas(64)', 'Two threads share one lock; fix by splitting it into two separate locks', 'A pointer shared by two objects; fix by using shared_ptr everywhere', 'A variable declared in two translation units; fix it with extern'], a: 0,
      why: 'Cores own memory in cache-line units. Independent writers on one line invalidate each other constantly. Padding or aligning hot per-thread data to 64 bytes puts them on separate lines.' },

    { sec: 's4', q: 'Why is a sorted `std::vector` often faster than a `std::map` for a small set of keys?',
      opts: ['It has better asymptotic complexity than a map', 'It is contiguous and cache-friendly, while a map allocates and chases pointers', 'A map cannot store integer keys without writing a custom hash', 'A vector never allocates any memory for its elements'], a: 1,
      why: 'Big-O hides constants. For small and medium sizes the vector shift is cheap and its memory is prefetchable; each map lookup follows pointers to nodes scattered over the heap.' },

    { sec: 's5', q: 'In a table stored as an array indexed by `key - base`, what is the cost of adding a count to a key inside the range?',
      opts: ['O(n)', 'O(log n)', 'O(1)', 'O(n log n)'], a: 2,
      why: 'The key minus the base gives the index directly: one array write, plus updating the tracked highest index if needed. The cost is memory proportional to the key range, and a fallback for keys outside it.' },

    { sec: 's5', q: 'A message says "remove item 7788". Which structure finds that item quickly?',
      opts: ['The array of buckets indexed by key, scanned in full', 'A hash map from item id to its key and count', 'A sorted vector holding only the keys, searched by id', 'A linked list of items in time order, walked from the front'], a: 1,
      why: 'The message carries the id, not the key. A hash map from id to (key, count) is O(1) on average and tells you which bucket to reduce. An open-addressing table avoids a heap node per item.' },

    { sec: 's6', q: 'Why is an SPSC ring buffer capacity usually a power of two?',
      opts: ['The hardware requires it for atomic operations to work', 'The index wrap is counter & (N - 1) instead of a modulo', 'It makes the queue thread-safe on its own, without atomics', 'It avoids false sharing between the two indices'], a: 1,
      why: 'A bit mask is a single cheap instruction. With free-running head and tail counters, `tail - head` is the size and the mask turns a counter into a slot index.' },

    { sec: 's6', q: 'Why are the head and tail indices of an SPSC queue each aligned to a cache line (`alignas(64)`)?',
      opts: ['Producer and consumer write different indices; separate lines avoid false sharing', 'The standard requires it for every atomic variable in a program', 'It makes the queue bigger so that it can hold many more items', 'It makes the indices volatile, so that changes become visible'], a: 0,
      why: 'The consumer writes head and the producer writes tail. If both sit on one cache line, every update by one thread invalidates the other core\'s copy. Separate lines remove that traffic.' },

    { sec: 's6', q: 'A pipeline\'s outgoing queue is full. Which is NOT an acceptable policy?',
      opts: ['Drop the newest message and count it', 'Overwrite the oldest entry', 'Conflate to the latest update per key', 'Let the queue grow without limit'], a: 3,
      why: 'An unbounded queue turns a slow consumer into rising memory use and rising delay, so the data you deliver gets older and older. Bound the queue and choose an explicit policy.' },

    { sec: 's7', q: 'Why avoid exceptions on the hot path?',
      opts: ['They do not work in multithreaded code, because the unwinder is not thread-safe', 'A throw costs microseconds and is hard to predict; error codes are cheaper', 'They are deprecated since C++17 and may be removed later on', 'They always leak memory when they are thrown across a thread'], a: 1,
      why: 'A throw triggers stack unwinding and table lookups. Used for rare, genuine errors they are fine, but on a path that must have steady latency, return a value the caller checks instead.' },

    { sec: 's7', q: 'What is the main latency drawback of a virtual call in a tight loop, and a common alternative?',
      opts: ['It allocates memory on every call to it; use new instead', 'It is an indirect call that cannot inline; use templates or CRTP', 'It copies the object on every call to it; use references', 'It locks a mutex on every call to it; use atomics instead'], a: 1,
      why: 'The target is found at run time through the vtable, so the compiler cannot inline it and the CPU may mispredict the jump. Static polymorphism (templates, CRTP, std::variant) resolves the call at compile time.' },

    { sec: 's7', q: 'How should logging be done from a latency-critical thread?',
      opts: ['Call std::cout directly from the latency-critical thread', 'Push a small record onto a queue; a background thread writes it', 'Open and close the log file for each message', 'Log only when the program exits normally at the end'], a: 1,
      why: 'Formatting and writing involve system calls, allocation and locks, all of which can stall. Recording a few values into a queue is cheap and predictable; the slow work happens on another thread.' },

    { sec: 's8', q: 'What is the trade-off of busy-polling instead of blocking on a condition variable?',
      opts: ['Busy-polling is slower to react and uses much less CPU time', 'Busy-polling reacts almost at once but burns a core; blocking saves CPU', 'There is no trade-off: both approaches cost the same CPU time overall', 'Busy-polling is not allowed together with atomic operations'], a: 1,
      why: 'A sleeping thread must be woken by the scheduler, which takes microseconds. A spinning thread notices new work within nanoseconds, at the price of burning a core. Use it only for the few latency-critical threads.' },

    { sec: 's8', q: 'Why pin a latency-critical thread to a specific CPU core?',
      opts: ['It makes the thread run faster than all of the other threads', 'It stops migration, so caches stay warm and timing is steadier', 'It allows more threads to run than there are cores', 'It disables interrupts on that core entirely'], a: 1,
      why: 'When a thread moves to another core it loses its cached data and must refill it, adding jitter. Affinity keeps it on one core. Do not run more busy threads than cores.' }
  ]
};
