# Chapter 28 Recap - Input and Output (IO)

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Prefer manipulators (e.g. `std::hex`) over raw flag manipulation (`setf` / `unsetf`) - they handle mutually exclusive flags automatically
- `setw()` is **not persistent** - it only applies to the very next output operation
- Use `std::getline()` (free function) to read full lines into `std::string`; the member `getline()` works with C-style char arrays
- `get()` does **not** consume the newline, while `getline()` does - mixing them up causes subtle bugs
- Always check whether a file opened successfully before using it (test the stream with `if (!stream)`)
- After a failed extraction, call `clear()` to reset error flags, then `ignore()` to discard bad input
- Use `'\n'` instead of `std::endl` for performance - `std::endl` forces a buffer flush
- When reusing a `stringstream`, call both `str("")` and `clear()`

### 3 Tiny Examples

1.

```cpp
std::cout << "Output\n";  // stdout (buffered)
std::cerr << "Error!\n";  // stderr (unbuffered)
std::clog << "Log msg\n"; // stderr (buffered)
```

2.

```cpp
std::string line;
std::getline(std::cin, line); // reads until \n, discards it
char ch;
std::cin.get(ch);             // reads 1 char, leaves delimiter
```

3.

```cpp
std::cout << std::hex << 255 << '\n';          // ff
std::cout << std::setw(10) << "hello" << '\n'; // right-justified
std::cout << std::setprecision(2) << 3.14159;  // 3.1
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Stream** - A sequence of bytes accessed sequentially; abstracts away the underlying device (keyboard, file, network, etc.)
- **Input stream (`istream`)** - Holds input from a producer (e.g. keyboard); uses the extraction operator (`>>`)
- **Output stream (`ostream`)** - Holds output for a consumer (e.g. monitor); uses the insertion operator (`<<`)
- **Standard streams** - `cin`, `cout`, `cerr` (unbuffered error), `clog` (buffered error)
- **Manipulators** - Objects inserted into streams to change formatting (e.g. `std::setw`, `std::hex`, `std::setprecision`)
- **Flags** - Boolean-style settings on streams toggled with `setf()` / `unsetf()`
- **Format groups** - Mutually exclusive flag sets (e.g. `basefield` contains `dec`, `hex`, `oct`)
- **String streams** (`istringstream`, `ostringstream`, `stringstream`) - Streams backed by strings instead of devices
- **Stream state flags** - `goodbit`, `badbit`, `eofbit`, `failbit` - indicate stream health
- **Input validation** - Checking user input for correctness (string-based or numeric-based)
- **File streams** (`ifstream`, `ofstream`, `fstream`) - Streams connected to files on disk
- **File modes** - Flags like `ios::app`, `ios::binary`, `ios::trunc` that control how files are opened
- **File pointer** - Tracks the current read/write position; manipulated with `seekg()` / `seekp()`

### Section-by-Section Detail

### 28.1 - Input and output (I/O) streams

- **Streams** are sequential byte sequences that abstract away the underlying data source or destination (keyboard, file, network, etc.).
- Four predefined standard streams: `cin` (input), `cout` (buffered output), `cerr` (unbuffered error), `clog` (buffered error).
- The `ios` base class provides common functionality (formatting flags, stream state) inherited by all stream classes.
- Inheritance hierarchy: `ios_base` → `ios` → `istream`/`ostream` → `iostream`, each level adding capabilities.

```cpp
std::cout << "Output\n";  // stdout (buffered)
std::cerr << "Error!\n";  // stderr (unbuffered)
std::clog << "Log msg\n"; // stderr (buffered)
```

→ _See [01_StreamHierarchy](../solutions/Chapter_28_IO/01_StreamHierarchy)_

### 28.2 - Input with istream

- The **extraction operator** (`>>`) skips leading whitespace by default and stops at the next whitespace character.
- `get()` reads one character including whitespace but **leaves the delimiter** in the stream - `getline()` extracts and **discards** it.
- The free function `std::getline()` reads into `std::string`; the member `getline()` works with C-style `char` arrays.
- Utility functions: `ignore()` discards characters, `peek()` looks without extracting, `unget()`/`putback()` return characters to the stream.
- Use `setw()` to prevent **buffer overflows** when reading into C-style character arrays.

```cpp
std::string line;
std::getline(std::cin, line); // reads until \n, discards it
char ch;
std::cin.get(ch);             // reads 1 char, leaves delimiter
```

→ _See [02_InputWithIstream](../solutions/Chapter_28_IO/02_InputWithIstream)_

> **Input Functions Compared**
>
> | Function                 | Reads                    | Skips leading WS? | Stops at                 | Consumes delimiter? |
> | ------------------------ | ------------------------ | ----------------- | ------------------------ | ------------------- |
> | `cin >> x`               | One token                | Yes               | Next whitespace          | No (leaves it)      |
> | `cin.get(ch)`            | One char                 | No                | N/A (single char)        | N/A                 |
> | `cin.getline(buf, n)`    | Up to `n-1` chars        | No                | `'\n'` (or custom delim) | Yes                 |
> | `std::getline(cin, str)` | Entire line              | No                | `'\n'` (or custom delim) | Yes                 |
> | `cin.ignore(n, delim)`   | Discards up to `n` chars | No                | `delim`                  | Yes                 |
> | `cin.peek()`             | Looks at next char       | No                | N/A                      | No (non-extracting) |

### 28.3 - Output with ostream and ios

- Output formatting uses **flags** (`setf()`/`unsetf()`) or the more convenient **manipulators** from `<iomanip>`.
- Covers boolean display (`std::boolalpha`), number base (`std::hex`, `std::oct`), floating-point notation (`std::fixed`, `std::scientific`, `std::setprecision`), and field width/justification (`std::setw`, `std::left`, `std::right`, `std::setfill`).
- `setw()` is **non-persistent** - it only affects the next output operation - while most other manipulators persist until explicitly changed.
- Prefer **manipulators** over raw `setf()`/`unsetf()` calls - they handle mutually exclusive flag groups automatically and are more readable.

```cpp
std::cout << std::hex << 255 << '\n';          // ff
std::cout << std::setw(10) << "hello" << '\n'; // right-justified
std::cout << std::setprecision(2) << 3.14159;  // 3.1
```

→ _See [03_OutputFormatting](../solutions/Chapter_28_IO/03_OutputFormatting) · [04_SetW_NonPersistent](../solutions/Chapter_28_IO/04_SetW_NonPersistent)_

> **Which Manipulators Are Persistent?**
>
> | Manipulator                                  | Persistent?                   | Scope            |
> | -------------------------------------------- | ----------------------------- | ---------------- |
> | `std::setw(n)`                               | **No** - resets after one use | Next output only |
> | `std::setfill(c)`                            | Yes                           | Until changed    |
> | `std::setprecision(n)`                       | Yes                           | Until changed    |
> | `std::fixed` / `std::scientific`             | Yes                           | Until changed    |
> | `std::hex` / `std::oct` / `std::dec`         | Yes                           | Until changed    |
> | `std::boolalpha`                             | Yes                           | Until changed    |
> | `std::left` / `std::right` / `std::internal` | Yes                           | Until changed    |

### 28.4 - Stream classes for strings

- `std::istringstream`, `std::ostringstream`, and `std::stringstream` (from `<sstream>`) perform **in-memory I/O** backed by strings.
- Insert data with `<<` or `str(string)`; extract with `>>` or retrieve the full buffer with `str()`.
- To **reuse** a stringstream, call both `str("")` (clear buffer) and `clear()` (reset error flags) - omitting either causes subtle bugs.
- String streams are useful for building complex strings incrementally, parsing structured input, and **type-safe** number↔string conversions.

```cpp
std::ostringstream oss;
oss << "Value: " << 42;
std::string result{ oss.str() }; // "Value: 42"
```

→ _See [05_StringStreams](../solutions/Chapter_28_IO/05_StringStreams)_

### 28.5 - Stream states and input validation

- Four **stream state flags**: `goodbit` (healthy), `failbit` (logical error), `badbit` (unrecoverable I/O error), `eofbit` (end of input).
- The stream can be tested directly in a boolean context - `if (stream)` returns `true` when neither `failbit` nor `badbit` is set.
- After a failed extraction, call `clear()` to reset error flags, then `ignore()` to discard the bad input from the buffer.
- **String validation** checks each character against criteria (e.g. `std::ranges::all_of`); **numeric validation** uses extraction + `failbit` checking + `ignore()`.

```cpp
int x;
if (std::cin >> x) { std::cout << "Read: " << x; }
else {
    std::cin.clear();                                     // reset failbit
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```

→ _See [06_StreamStates](../solutions/Chapter_28_IO/06_StreamStates) · [07_InputValidation](../solutions/Chapter_28_IO/07_InputValidation)_

> **Stream State Flags**
>
> | Flag      | Accessor | Meaning                               | Set when                                    |
> | --------- | -------- | ------------------------------------- | ------------------------------------------- |
> | `goodbit` | `good()` | No errors - stream is healthy         | Default state; all other bits clear         |
> | `failbit` | `fail()` | Logical error - last operation failed | Extraction type mismatch, file open failure |
> | `badbit`  | `bad()`  | Unrecoverable I/O error               | Read/write error on underlying device       |
> | `eofbit`  | `eof()`  | End of input reached                  | Extraction attempted past end of stream     |
>
> - `if (stream)` returns `true` when neither `failbit` nor `badbit` is set
> - `clear()` resets all flags to `goodbit`
> - Multiple flags can be set simultaneously (e.g., `eofbit | failbit`)

### 28.6 - Basic file I/O

- `ifstream`, `ofstream`, and `fstream` connect streams to **files on disk** - opened via constructors, `open()`, or RAII.
- **File modes** include `ios::app` (append), `ios::binary` (byte-exact), `ios::trunc` (overwrite) - combinable with `|`.
- Always check that a file opened successfully before using it - `if (!stream)` - since open failures are **silent** by default.
- RAII ensures files are properly closed when the stream goes out of scope; use `'\n'` instead of `std::endl` to avoid costly per-line buffer flushes.

```cpp
std::ifstream infile{"input.txt"};
if (!infile) { std::cerr << "Failed to open\n"; return 1; }
std::string line;
while (std::getline(infile, line))
    std::cout << line << '\n';
```

→ _See [08_BasicFileIO](../solutions/Chapter_28_IO/08_BasicFileIO)_

> **File Mode Flags**
>
> | Flag          | Meaning                                 | Default for                          |
> | ------------- | --------------------------------------- | ------------------------------------ |
> | `ios::in`     | Open for reading                        | `ifstream`                           |
> | `ios::out`    | Open for writing                        | `ofstream`                           |
> | `ios::app`    | Append - all writes go to end           | -                                    |
> | `ios::ate`    | Seek to end on open (but can seek back) | -                                    |
> | `ios::trunc`  | Truncate file to zero length on open    | `ofstream` (when `ios::app` not set) |
> | `ios::binary` | No newline translation; byte-exact I/O  | -                                    |
>
> - Combine with `|`: `ios::in | ios::out | ios::binary`
> - `ofstream` default = `ios::out | ios::trunc` (overwrites)
> - `ofstream` with `ios::app` = append mode (no truncation)

### 28.7 - Random file I/O

- **Random file access** uses `seekg()`/`seekp()` with offset and origin flags (`beg`, `cur`, `end`) and `tellg()`/`tellp()` to query position.
- With `fstream`, a **seek is required** to switch between read and write modes on the same file.
- Avoid writing pointers/addresses to files - they are **meaningless** across different program runs.
- Newline encoding differs across platforms (`\r\n` vs `\n`) → use **binary mode** for reliable seeking.

```cpp
std::fstream file{"data.bin", std::ios::binary | std::ios::in | std::ios::out};
file.seekg(0, std::ios::end);
auto size{ file.tellg() }; // file size in bytes
file.seekg(100, std::ios::beg); // jump to byte 100
```

→ _See [09_RandomFileIO](../solutions/Chapter_28_IO/09_RandomFileIO)_

### Edge Cases and Caveats

❌ Forgetting that `>>` skips whitespace:

```cpp
char ch;
std::cin >> ch; // ❌ skips spaces and newlines
```

✅ Use `get()` or `getline()` when whitespace matters.

---

❌ Using `get()` and wondering why the next read is empty:

```cpp
std::cin.get(ch); // reads 'a'
// ❌ '\n' is still in the buffer → next getline() reads empty
```

✅ Follow `get()` with `ignore()` or use `getline()` instead.

---

❌ Not clearing the stream after failed input:

```cpp
std::cin >> x; // fails on "abc"
// ❌ all subsequent reads silently fail without cin.clear()
```

✅ Clear and ignore:

```cpp
std::cin.clear();
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ✅
```

---

❌ Not discarding bad input with `ignore()`:

```cpp
std::cin.clear();
std::cin >> x; // ❌ bad chars still in buffer → fails again
```

✅ Always `ignore()` after `clear()`.

---

❌ Assuming `setw()` is persistent:

```cpp
std::cout << std::setw(10) << a << b; // ❌ setw only applies to a, not b
```

✅ `setw()` resets after one use - apply it before each output.

---

❌ Using `setf()` for mutually exclusive flags without unsetting the old one:

```cpp
std::cout.setf(std::ios::hex); // ❌ dec may still be active
```

✅ Use the two-parameter form:

```cpp
std::cout.setf(std::ios::hex, std::ios::basefield); // ✅ clears dec first
```

---

❌ Not checking if a file opened successfully:

```cpp
std::ifstream file{"data.txt"};
file >> x; // ❌ silent failure if file didn't open
```

✅ Check:

```cpp
if (!file) { std::cerr << "Failed to open"; return 1; } // ✅
```

---

❌ Using `std::endl` excessively in file output:

```cpp
for (int i = 0; i < 1000; ++i)
    file << i << std::endl; // ❌ flushes every iteration → slow
```

✅ Use `'\n'` instead:

```cpp
file << i << '\n'; // ✅ buffered, much faster
```

---

❌ Calling `exit()` without closing files:

```cpp
std::exit(0); // ❌ destructors won't run, buffered data may be lost
```

✅ Let files go out of scope or explicitly close them before exiting.

---

❌ Seeking in text-mode files:

```cpp
file.seekg(100); // ❌ newline encoding varies by OS → unpredictable
```

✅ Use binary mode for reliable seeking:

```cpp
std::ifstream file{"data.bin", std::ios::binary}; // ✅
```

---

❌ Mixing `>>` and `getline()` without clearing the leftover newline:

```cpp
int n;
std::cin >> n;
std::string line;
std::getline(std::cin, line); // ❌ reads empty - picks up leftover '\n'
```

✅ Ignore the newline first:

```cpp
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
std::getline(std::cin, line); // ✅
```

---

### Hands-On Code Projects

| #   | Project                                                                    | Concept                                                             |
| --- | -------------------------------------------------------------------------- | ------------------------------------------------------------------- |
| 01  | [01_StreamHierarchy](../solutions/Chapter_28_IO/01_StreamHierarchy)       | The iostream class hierarchy and the four standard streams          |
| 02  | [02_InputWithIstream](../solutions/Chapter_28_IO/02_InputWithIstream)     | Reading input with `>>`, `get()`, `getline()`, `ignore()`, `peek()` |
| 03  | [03_OutputFormatting](../solutions/Chapter_28_IO/03_OutputFormatting)     | Formatting output with flags, manipulators, `setw`, `setprecision`  |
| 04  | [04_SetW_NonPersistent](../solutions/Chapter_28_IO/04_SetW_NonPersistent) | Demonstrating that `setw()` only applies to the next output         |
| 05  | [05_StringStreams](../solutions/Chapter_28_IO/05_StringStreams)           | Using `istringstream`, `ostringstream`, and `stringstream`          |
| 06  | [06_StreamStates](../solutions/Chapter_28_IO/06_StreamStates)             | Stream state flags: `goodbit`, `badbit`, `eofbit`, `failbit`        |
| 07  | [07_InputValidation](../solutions/Chapter_28_IO/07_InputValidation)       | Validating input, clearing errors, discarding bad data              |
| 08  | [08_BasicFileIO](../solutions/Chapter_28_IO/08_BasicFileIO)               | File streams: `ifstream`, `ofstream`, file modes, RAII              |
| 09  | [09_RandomFileIO](../solutions/Chapter_28_IO/09_RandomFileIO)             | Random file access with `seekg()`, `seekp()`, `tellg()`, `tellp()`  |
| 10  | [10_CommonPitfalls](../solutions/Chapter_28_IO/10_CommonPitfalls)         | Mixing `>>` and `getline()`, `endl` vs `'\n'`, and other traps      |

> **Path:** `solutions/Chapter_28_IO/01_StreamHierarchy/main.cpp` … `10_CommonPitfalls/main.cpp`

### Quick Reference

| Feature          | Syntax / Usage                           | Notes                         |
| ---------------- | ---------------------------------------- | ----------------------------- |
| Extraction       | `std::cin >> x;`                         | Skips whitespace              |
| getline (string) | `std::getline(std::cin, str);`           | Reads until `\n`, discards it |
| get()            | `std::cin.get(ch);`                      | Reads 1 char, leaves `\n`     |
| ignore()         | `std::cin.ignore(max, '\n');`            | Discards up to delimiter      |
| setw             | `std::cout << std::setw(10) << x;`       | Non-persistent                |
| setprecision     | `std::cout << std::setprecision(3);`     | Persistent                    |
| hex/oct/dec      | `std::cout << std::hex << n;`            | Persistent                    |
| boolalpha        | `std::cout << std::boolalpha;`           | Persistent                    |
| stringstream     | `std::ostringstream oss; oss << x;`      | In-memory I/O                 |
| Clear stream     | `stream.clear(); stream.str("");`        | Reset state + buffer          |
| Open file        | `std::ifstream ifs{"file.txt"};`         | RAII - auto-closes            |
| File mode        | `std::ofstream ofs{"f", std::ios::app};` | Append mode                   |
| seekg / seekp    | `stream.seekg(0, std::ios::beg);`        | Random access                 |
| tellg / tellp    | `auto pos = stream.tellg();`             | Query position                |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. What is the difference between `>>` and `getline()` for reading input?

<details>
<summary>Show answer</summary>

**Direct answer:** `>>` skips leading whitespace and stops at the next whitespace character (reads one "word"). `std::getline()` reads the entire line up to the newline delimiter and discards the newline. Use `>>` for whitespace-delimited tokens, `getline()` for full lines including spaces.

**Detailed explanation:**

```cpp
std::string word, line;

std::cin >> word;                     // reads "Hello" from "Hello World"
std::getline(std::cin, line);         // reads " World" (including leading space)

// istream::getline (for C-strings):
char buf[100];
std::cin.getline(buf, 100);           // reads into char array, limits size

// istream::get():
char ch = std::cin.get();             // reads one char, including whitespace
```

Key difference: `get()` leaves the delimiter in the stream; `getline()` extracts and discards it.

</details>

2. Why must you call both `clear()` and `ignore()` after a failed extraction?

<details>
<summary>Show answer</summary>

**Direct answer:** A failed extraction sets the `failbit` flag, which blocks all subsequent I/O operations. `clear()` resets the error flags so the stream works again. But the bad input is still in the buffer `ignore()` discards it. Without both, either the stream stays stuck, or the same bad input is re-read.

**Detailed explanation:**

```cpp
int x{};
std::cin >> x;   // user types "abc"  extraction fails

// Stream state: failbit set, "abc\n" still in buffer
std::cin.clear();                                          // reset error flags
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard bad input

// Now the stream is ready for new input
std::cin >> x;   // works again
```

</details>

3. Why is `'\n'` preferred over `std::endl` in file output?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::endl` outputs a newline AND flushes the buffer. Flushing forces the data to be written to disk immediately, which is slow. `'\n'` outputs just the newline and lets the buffer flush naturally (when full or when the file is closed). For file I/O with many writes, `std::endl` can be significantly slower.

**Detailed explanation:**

```cpp
std::ofstream file{"output.txt"};

// Slow  flushes after every line:
for (int i{0}; i < 10000; ++i)
    file << "Line " << i << std::endl;   // flush x 10000

// Fast  buffer flushes when full or at close:
for (int i{0}; i < 10000; ++i)
    file << "Line " << i << '\n';        // no unnecessary flushes
```

Use `std::endl` only when you need to guarantee output is visible immediately (e.g., debugging, `std::cerr`).

</details>

4. How do you check if a file was opened successfully?

<details>
<summary>Show answer</summary>

**Direct answer:** Test the stream in a boolean context `if (file)` or `if (!file)`. Alternatively, call `file.is_open()`. Always check before reading/writing; opening a nonexistent file for reading silently fails (no exception by default).

**Detailed explanation:**

```cpp
std::ifstream input{"data.txt"};
if (!input)    // or: if (!input.is_open())
{
    std::cerr << "Failed to open file!\n";
    return 1;
}

// RAII: file closes automatically when 'input' goes out of scope
std::string line;
while (std::getline(input, line))
    std::cout << line << '\n';

// File modes:
std::ofstream out{"log.txt", std::ios::app};   // append mode
std::fstream rw{"data.bin", std::ios::in | std::ios::out | std::ios::binary};
```

</details>

5. What is the difference between text mode and binary mode for file I/O?

<details>
<summary>Show answer</summary>

**Direct answer:** Text mode translates newlines between the platform format (`\r\n` on Windows) and `\n` internally. Binary mode (`std::ios::binary`) performs no translation bytes are read/written exactly as-is. Use binary mode for non-text data and when you need reliable `seekg()`/`seekp()` behavior.

**Detailed explanation:**

```cpp
// Text mode (default): newline translation
std::ofstream text{"file.txt"};
text << "Hello\n";   // on Windows, writes "Hello\r\n" to disk

// Binary mode: no translation
std::ofstream bin{"file.bin", std::ios::binary};
bin.write(reinterpret_cast<const char*>(&myStruct), sizeof(myStruct));

// Random access with seekg/seekp is unreliable in text mode
// because \r\n counts as 2 bytes on disk but 1 byte in memory
std::fstream f{"data.bin", std::ios::in | std::ios::out | std::ios::binary};
f.seekg(10, std::ios::beg);    // reliable in binary mode
```

</details>

6. Why is `setw()` not persistent like other manipulators?

<details>
<summary>Show answer</summary>

**Direct answer:** `setw()` only affects the very next insertion/extraction operation, then resets to 0. This is by design field width is typically different for each output value. All other manipulators (`std::hex`, `std::fixed`, `std::setprecision`, etc.) persist until explicitly changed.

**Detailed explanation:**

```cpp
#include <iomanip>

std::cout << std::setw(10) << "Hello"     // width 10 for this output only
          << "World" << '\n';              // width back to 0

// Output: "     HelloWorld"

// Persistent manipulators:
std::cout << std::hex << 255;    // "ff"
std::cout << 16;                 // still hex: "10"
std::cout << std::dec;           // reset to decimal

// setfill IS persistent:
std::cout << std::setfill('*') << std::setw(10) << 42;  // "********42"
std::cout << std::setw(5) << 7;                           // "****7" (fill persists)
```

</details>

7. What happens if you mix `>>` and `getline()` without clearing the buffer?

<details>
<summary>Show answer</summary>

**Direct answer:** `>>` leaves the newline character `\n` in the buffer after reading. The subsequent `getline()` immediately reads that leftover `\n` as an empty line. Fix: call `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')` between `>>` and `getline()`.

**Detailed explanation:**

```cpp
int age{};
std::string name;

std::cout << "Age: ";
std::cin >> age;              // reads "25", leaves "\n" in buffer

std::cout << "Name: ";
std::getline(std::cin, name); // reads empty string (just the leftover "\n")!

// Fix:
std::cin >> age;
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // discard \n
std::getline(std::cin, name); // now waits for actual input
```

</details>

8. What is the `std::ios::basefield` group and why is the two-parameter `setf()` needed?

<details>
<summary>Show answer</summary>

**Direct answer:** `basefield` is a group of mutually exclusive flags: `std::ios::dec`, `std::ios::hex`, `std::ios::oct`. The two-parameter `setf(flag, group)` sets one flag while clearing the others in the group. Without the group parameter, multiple conflicting flags could be set simultaneously, causing undefined output behavior.

**Detailed explanation:**

```cpp
// One-parameter setf: sets a flag, but doesn't clear conflicting ones
std::cout.setf(std::ios::hex);   // turns on hex, but dec might still be on!

// Two-parameter setf: clears group first, then sets flag
std::cout.setf(std::ios::hex, std::ios::basefield);  // correct

// Easier: use manipulators (they handle the group automatically)
std::cout << std::hex << 255;   // "ff"
std::cout << std::oct << 255;   // "377"
std::cout << std::dec << 255;   // "255"
```

Other flag groups: `floatfield` (fixed/scientific), `adjustfield` (left/right/internal).

</details>

9. What are string streams and when are they useful?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::istringstream`, `std::ostringstream`, and `std::stringstream` (from `<sstream>`) perform I/O against an in-memory string instead of a console or file. Useful for: building complex strings incrementally, parsing structured input, and type-safe number/string conversions.

**Detailed explanation:**

```cpp
#include <sstream>

// Building a string:
std::ostringstream oss;
oss << "Score: " << 42 << " / " << 100;
std::string result = oss.str();   // "Score: 42 / 100"

// Parsing a string:
std::istringstream iss{"10 20 30"};
int a, b, c;
iss >> a >> b >> c;   // a=10, b=20, c=30

// Reusing a stringstream:
oss.str("");       // clear buffer
oss.clear();       // clear error flags  BOTH needed!
oss << "New data";
```

</details>

10. What are `seekg()`, `seekp()`, `tellg()`, and `tellp()` used for?

<details>
<summary>Show answer</summary>

**Direct answer:** `seekg()` sets the read (get) position, `seekp()` sets the write (put) position. `tellg()` and `tellp()` return the current positions. These enable random file access reading/writing at arbitrary positions rather than sequentially. Use binary mode for reliable seeking.

**Detailed explanation:**

```cpp
std::fstream file{"data.bin", std::ios::in | std::ios::out | std::ios::binary};

// Seek to position 100 from beginning:
file.seekg(100, std::ios::beg);

// Seek 10 bytes forward from current position:
file.seekg(10, std::ios::cur);

// Seek to 20 bytes before end:
file.seekg(-20, std::ios::end);

// Get current position:
auto pos = file.tellg();

// Read/write at specific position:
file.seekp(0, std::ios::end);   // seek to end for appending
int val{42};
file.write(reinterpret_cast<const char*>(&val), sizeof(val));
```

When using `fstream` for both reading and writing, you must seek between switching from read to write mode (or vice versa).

</details>
