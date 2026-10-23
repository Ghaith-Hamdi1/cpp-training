/* Quiz questions for the 'wire' topic. Loaded by 11-wire-formats-quiz.html. */
CT.quizData.wire = {
  id: 'wire',
  questions: [
    { sec: 's1', q: 'Why is `auto* t = reinterpret_cast<const Sample*>(buf);` a poor way to parse a received message?',
      opts: ['It is slower than copying the bytes one field at a time each time', 'Aliasing (UB), misalignment, padding mismatch, and byte order', 'reinterpret_cast does not compile when it is applied to arrays', 'It always crashes at run time on every platform and compiler'], a: 1,
      why: 'Each of the four is a separate way to go wrong, and the compiler may not warn about any of them. Check the length, then copy each field out with memcpy or assemble it with shifts.' },

    { sec: 's2', q: 'What does this print?',
      code: String.raw`
std::uint8_t a = 200, b = 100;
std::cout << (a + b);
`,
      opts: ['44', '300', '255', 'It does not compile'], a: 1,
      why: 'Both operands are promoted to int before the addition, so the sum is 300. Only when you store it back into a uint8_t would it wrap to 44.' },

    { sec: 's2', q: 'Which expression clears bit `n` of the unsigned value `x`?',
      opts: ['`x | (1u << n)`', '`x & ~(1u << n)`', '`x ^ (1u << n)`', '`x & (1u << n)`'], a: 1,
      why: '`1u << n` has only bit n set; `~` inverts it so every bit EXCEPT n is set; AND keeps everything else and zeroes bit n. The first sets it, the third toggles it, the last tests it.' },

    { sec: 's2', q: 'Which expression tests whether the unsigned value `x` is a power of two?',
      opts: ['`x % 2 == 0`', '`x != 0 && (x & (x - 1)) == 0`', '`x & 1`', '`x >> 1 == 0`'], a: 1,
      why: 'A power of two has exactly one bit set. Subtracting 1 flips that bit and all the bits below it, so x & (x - 1) is 0 only when there was a single set bit. The x != 0 test excludes 0.' },

    { sec: 's2', q: 'What does `x &= x - 1;` do?',
      opts: ['Clears the lowest set bit', 'Clears the highest set bit', 'Toggles every bit', 'Decrements x by one'], a: 0,
      why: 'Subtracting 1 turns the lowest set bit into 0 and every bit below it into 1; ANDing with the original clears that lowest set bit. Repeating until x is 0 counts the set bits.' },

    { sec: 's2', q: 'Why should bytes from a buffer be read as `unsigned char` or `std::uint8_t` rather than plain `char`?',
      opts: ['Plain char is slower to load from memory than unsigned char', 'Plain char may be signed, so 0xFF widens to -1', 'Plain char cannot be used as an array index in C++', 'unsigned char takes less memory than plain char'], a: 1,
      why: 'Whether char is signed is implementation-defined. Widening a signed char with the top bit set sign-extends, which corrupts shifts and comparisons. Unsigned types behave the same everywhere.' },

    { sec: 's3', q: 'On a typical 64-bit platform (4-byte int, alignment 4), what is `sizeof(S)`?',
      code: String.raw`
struct S { char a; int b; char c; };
`,
      opts: ['6', '8', '12', '16'], a: 2,
      why: 'a is at offset 0, then 3 padding bytes so b starts at 4, then c at 8, then 3 bytes of tail padding so the size is a multiple of the alignment (4): 12. Ordering the members int, char, char gives 8.' },

    { sec: 's3', q: 'How can you shrink a struct without changing its members and without packing?',
      opts: ['Declare every member of the struct volatile so it is not padded', 'Order the members from largest to smallest alignment', 'Make every member of the struct const to remove the padding', 'Declare the struct inline in a header to shrink it'], a: 1,
      why: 'Padding appears between a small member and a larger one that needs stricter alignment. Putting the widest members first leaves the small ones together at the end, so far less padding is needed.' },

    { sec: 's3', q: 'What is a real cost of `#pragma pack(1)`?',
      opts: ['The struct always becomes larger because of extra marker bytes', 'Members may be unaligned: slower, maybe a fault, and references are unsafe', 'It disables inheritance for the packed struct and for its members', 'It silently changes the byte order of every integer member in it'], a: 1,
      why: 'Removing padding means an int can start at any address. x86 tolerates that at a speed cost; other CPUs may trap, and binding a reference to a packed member is undefined behavior. Read the wire with memcpy and keep ordinary structs in the program.' },

    { sec: 's4', q: 'The 32-bit value `0x12345678` is stored on a little-endian CPU. In which order are its bytes in memory (lowest address first)?',
      opts: ['12 34 56 78', '78 56 34 12', '34 12 78 56', '21 43 65 87'], a: 1,
      why: 'Little-endian stores the least significant byte first: 78, then 56, 34 and finally 12. Big-endian (network byte order) would store 12 34 56 78.' },

    { sec: 's4', q: 'What is network byte order?',
      opts: ['Little-endian: least significant byte first', 'Big-endian: most significant byte first', 'Whatever byte order the sender\'s CPU uses', 'Alphabetical byte order of the field names'], a: 1,
      why: 'Internet protocols use big-endian so every host agrees. Individual protocols may differ, so read the protocol specification, and convert explicitly when bytes enter the program.' },

    { sec: 's4', q: 'What is the portable way to read a big-endian `uint32_t` from `const unsigned char* p`?',
      opts: ['*reinterpret_cast<const uint32_t*>(p), a direct pointer read', 'Assemble it from the bytes with shifts, widening each byte to uint32_t', '(uint32_t)p, a C-style cast applied to the pointer itself', 'std::stoi(p), after converting p to text with a stream'], a: 1,
      why: 'Building the value from individual bytes does not depend on the CPU\'s byte order, alignment or aliasing rules. Widening each byte to uint32_t first avoids signed-promotion surprises.' },

    { sec: 's5', q: 'Which statement about strict aliasing is correct?',
      opts: ['Any pointer type may be used to read any other object type freely', 'Access objects through their own type; only char types and std::byte may alias', 'Aliasing only matters for floating-point types and pointers to them', 'It is only a compiler warning and never causes undefined behavior'], a: 1,
      why: 'Accessing an object through an unrelated type is undefined behavior, and the optimizer assumes it never happens. Viewing an object as bytes (char, unsigned char, std::byte) is the allowed exception.' },

    { sec: 's5', q: 'What does this print (IEEE-754 float)?',
      code: String.raw`
std::cout << std::hex << std::bit_cast<std::uint32_t>(1.0f);
`,
      opts: ['1', '3f800000', '0', 'It does not compile'], a: 1,
      why: 'std::bit_cast (C++20) reinterprets the object representation without undefined behavior, for types of the same size that are trivially copyable. The bits of 1.0f are 0x3f800000.' },

    { sec: 's5', q: 'In C++, what about reading a different union member than the one last written (type punning)?',
      opts: ['It is guaranteed to work in every compiler and standard', 'It is undefined behavior (GCC allows it as an extension)', 'It is only an error when the members are floating-point', 'It is implementation-defined but always safe to rely on'], a: 1,
      why: 'C permits it; C++ does not. Use std::memcpy or std::bit_cast instead, which are portable and compile to the same code.' },

    { sec: 's6', q: 'Why prefer `std::from_chars` over `std::stoi` when parsing protocol messages?',
      opts: ['It handles many more number formats than stoi does', 'It does not allocate, throw or use the locale', 'It is shorter to type than the std::stoi call', 'stoi does not exist for 64-bit integer types'], a: 1,
      why: 'stoi needs a std::string and throws on bad input; from_chars works on a character range, returns an error code and the position where it stopped, and is locale-independent. All three matter on a hot path.' },

    { sec: 's6', q: 'When is a `std::string_view` into a receive buffer dangerous?',
      opts: ['Never: views are always safe to keep around for any amount of time', 'When the buffer is reused, overwritten or freed while the view is in use', 'Only for strings longer than 15 characters stored in the buffer', 'Whenever the view is passed by value to another function or thread'], a: 1,
      why: 'A view holds a pointer and a length, not the text. If the buffer is reused for the next packet, the view now shows different bytes. Copy out what you need before the buffer changes.' },

    { sec: 's7', q: 'What does this print?',
      code: String.raw`
std::cout << std::boolalpha << (0.1 + 0.2 == 0.3);
`,
      opts: ['true', 'false', 'It does not compile', 'Undefined behavior'], a: 1,
      why: '0.1 and 0.2 have no exact binary representation, so their sum is 0.30000000000000004, which is not the double nearest 0.3. Money amounts stored as integer units do not have this problem.' },

    { sec: 's7', q: 'Which representation is best for money amounts on a hot path?',
      opts: ['double, because it has the widest range', 'float, because it is the fastest', 'An integer count of units (a scaled int64_t)', 'A std::string holding the decimal text'], a: 2,
      why: 'Integer units are exact and deterministic, compare with ==, and parse straight from text. Watch overflow when multiplying by quantity, and fix the rounding rule in one place.' },

    { sec: 's8', q: 'You expect sequence number 102 and receive 105. What does that mean?',
      opts: ['A duplicate of an earlier message, so it can safely be ignored', 'A gap: 103 and 104 are missing, so buffer 105 and request a resend', 'In order: it is the next message and can be processed right now', 'The counter has wrapped around back to a small number'], a: 1,
      why: 'A higher number than expected means messages were lost. Processing 105 immediately would give an inconsistent state, so hold it and recover the missing range.' },

    { sec: 's8', q: 'How do you compare 32-bit sequence numbers safely across wrap-around?',
      opts: ['received < expected, compared as plain unsigned numbers', 'static_cast<int32_t>(received - expected) and look at the sign', 'Convert both numbers to double first and then compare them', 'Compare their decimal text representations as strings'], a: 1,
      why: 'Unsigned subtraction wraps modulo 2^32, and reading the result as signed gives the shortest distance. It stays correct as long as the values are within 2^31 of each other; plain < breaks the moment the counter wraps.' }
  ]
};
