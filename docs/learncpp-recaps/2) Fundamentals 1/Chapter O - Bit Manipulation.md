# Chapter O Recap - Bit Manipulation

This recap is organized in a two-pass format. Pass 1 is fast and beginner-friendly. Pass 2 keeps the complete technical detail for reference and deeper study.

## Pass 1 - Beginner View

### Key Ideas in Simple Language

- Use unsigned integers or `std::bitset` when doing bit manipulation - avoid signed operands
- `std::bitset` is convenient for individual bit operations, but bitwise operators with masks are needed for manipulating multiple bits at once
- The four essential mask operations: test (`&`), set (`|=`), reset (`&= ~`), flip (`^=`)
- Define bit masks with meaningful names (e.g., `isHappy`, `option_viewed`) rather than generic names like `mask0`
- Bits shifted off the end of a value during a shift operation are permanently lost
- `~` and `<<` are width-sensitive - when using bitwise operators on types smaller than `int`, use `static_cast` to convert results back to the narrower type
- Two's complement ensures there is only one representation of zero and simplifies hardware arithmetic for negative numbers
- De Morgan's law applies to bitwise operations: `~(a | b)` is equivalent to `~a & ~b`

### 3 Tiny Examples

1.

```cpp
#include <bitset>
std::bitset<8> bits{ 0b0000'0101 }; // bits 0 and 2 set
bits.set(3);      // turn on bit 3
bits.reset(0);    // turn off bit 0
bits.flip(2);     // toggle bit 2
std::cout << bits.test(3);  // true
std::cout << bits << '\n';  // 00001000 (after all operations)
```

2.

```cpp
unsigned int x{ 0b1100 };
std::cout << (x << 1) << '\n'; // 0b11000 (24) - left shift
std::cout << (x >> 1) << '\n'; // 0b0110  (6)  - right shift
std::cout << (~x) << '\n';      // flips all bits
std::cout << (x & 0b1010) << '\n'; // 0b1000 (AND)
std::cout << (x | 0b0011) << '\n'; // 0b1111 (OR)
std::cout << (x ^ 0b1010) << '\n'; // 0b0110 (XOR)
```

3.

```cpp
constexpr unsigned int mask0{ 1 << 0 }; // 0b0001
constexpr unsigned int mask1{ 1 << 1 }; // 0b0010

unsigned int flags{ 0 };
flags |= mask0;                  // set bit 0
flags &= ~mask1;                 // clear bit 1
flags ^= mask0;                  // toggle bit 0
if (flags & mask0) { }           // test bit 0
```

### 3 Common Mistakes

- Skipping compiler warnings.
- Using chapter features without understanding prerequisites.
- Not testing edge cases.

## Pass 2 - Technical View

### Formal Terminology (Glossary)

- **Bit flag**: Using individual bits of an object as independent Boolean values (on/off).
- **Bit position**: Bits are numbered right to left, starting at 0.
- **`std::bitset`**: A convenient class for bit manipulation with member functions (`test`, `set`, `reset`, `flip`, `count`, `any`, `all`, `none`).
- **Bitwise operators**: `<<` (left shift), `>>` (right shift), `~` (NOT), `&` (AND), `|` (OR), `^` (XOR).
- **Bit mask**: A predefined set of bits used to select which bits a bitwise operation affects.
- **Two's complement**: The standard method for representing signed integers in binary - invert all bits and add 1 to get the negative representation.
- **Integral promotion**: Bitwise operators promote operands smaller than `int` to `int` or `unsigned int`, which can cause surprising results.

### Section-by-Section Detail

### O.1 - Bit flags and bit manipulation via std::bitset

- A **Boolean** needs only 1 bit but wastes a full byte - **bit flags** pack multiple Booleans into a single integer
- `std::bitset` provides named member functions - `test()`, `set()`, `reset()`, `flip()` - for safe individual-bit manipulation
- `std::bitset` is optimized for **speed**, not memory - its size rounds up to `sizeof(size_t)`, so it may waste space
- When **memory** matters, use **bitwise operators** on unsigned integers directly instead of `std::bitset`
- Bits are numbered right-to-left starting at **position 0** - `bits.set(3)` sets the fourth bit from the right

```cpp
#include <bitset>
std::bitset<8> bits{ 0b0000'0101 }; // bits 0 and 2 set
bits.set(3);      // turn on bit 3
bits.reset(0);    // turn off bit 0
bits.flip(2);     // toggle bit 2
std::cout << bits.test(3);  // true
std::cout << bits << '\n';  // 00001000 (after all operations)
```

→ _See [01_BitFlagsWithBitset](../solutions/Chapter_O_Bit_Manipulation/01_BitFlagsWithBitset) for `std::bitset` bit manipulation._

### O.2 - Bitwise operators

- C++ provides six **bitwise operators** - `<<` (left shift), `>>` (right shift), `~` (NOT), `&` (AND), `|` (OR), `^` (XOR)
- **Shifting** moves bits left or right - bits that fall off the end are permanently lost (shifting is **not** rotation)
- `&` returns 1 only where **both** bits are 1 - `|` returns 1 where **either** is 1 - `^` returns 1 where bits **differ**
- **Assignment variants** (`<<=`, `>>=`, `&=`, `|=`, `^=`) modify the left operand in place
- Avoid bitwise operators on **signed** operands - right-shifting signed values is **implementation-defined**, and left-shifting into the sign bit is **undefined behavior**

```cpp
unsigned int x{ 0b1100 };
std::cout << (x << 1) << '\n'; // 0b11000 (24) - left shift
std::cout << (x >> 1) << '\n'; // 0b0110  (6)  - right shift
std::cout << (~x) << '\n';      // flips all bits
std::cout << (x & 0b1010) << '\n'; // 0b1000 (AND)
std::cout << (x | 0b0011) << '\n'; // 0b1111 (OR)
std::cout << (x ^ 0b1010) << '\n'; // 0b0110 (XOR)
```

→ _See [02_BitwiseOperators](../solutions/Chapter_O_Bit_Manipulation/02_BitwiseOperators) for all six bitwise operators and their assignment variants._

**Bitwise Operators At A Glance:**

| Operator | Name        | Effect                         | Example (4-bit)              |
| -------- | ----------- | ------------------------------ | ---------------------------- | ------- | ---------------- |
| `<<`     | Left shift  | Shifts bits left, fills with 0 | `0b0011 << 1` - `0b0110`     |
| `>>`     | Right shift | Shifts bits right              | `0b0110 >> 1` - `0b0011`     |
| `~`      | Bitwise NOT | Flips all bits                 | `~0b1100` - `0b0011`         |
| `&`      | Bitwise AND | 1 only if both bits are 1      | `0b1100 & 0b1010` - `0b1000` |
| `        | `           | Bitwise OR                     | 1 if either bit is 1         | `0b1100 | 0b1010`-`0b1110` |
| `^`      | Bitwise XOR | 1 if bits differ               | `0b1100 ^ 0b1010` - `0b0110` |

> **Warning:** Avoid bitwise operations on signed integers - the behavior of `>>` on negative values is implementation-defined, and `~` on small unsigned types triggers integral promotion.

### O.3 - Bit manipulation with bitwise operators and bit masks

- A **bit mask** uses 1s to mark which bits to affect and 0s to mask out the rest
- The four essential mask operations - **test** (`flags & mask`), **set** (`flags |= mask`), **reset** (`flags &= ~mask`), **flip** (`flags ^= mask`)
- Masks can be defined with **binary literals**, **hex literals**, or the **left-shift** operator (`1 << n`)
- Bit flags save memory when many objects share the same set of flags - also useful for passing multiple on/off options as a **single parameter**
- Give masks **meaningful names** (e.g., `isHappy`, `option_viewed`) rather than generic names like `mask0`

```cpp
constexpr unsigned int mask0{ 1 << 0 }; // 0b0001
constexpr unsigned int mask1{ 1 << 1 }; // 0b0010

unsigned int flags{ 0 };
flags |= mask0;                  // set bit 0
flags &= ~mask1;                 // clear bit 1
flags ^= mask0;                  // toggle bit 0
if (flags & mask0) { }           // test bit 0
```

→ _See [03_BitMasks](../solutions/Chapter_O_Bit_Manipulation/03_BitMasks) for the four essential mask operations · [04_BitFlagsRealWorld](../solutions/Chapter_O_Bit_Manipulation/04_BitFlagsRealWorld) for a real-world multi-flag example._

**The Four Essential Mask Operations (TSRF):**

| Operation | Expression       | Purpose             | Result          |
| --------- | ---------------- | ------------------- | --------------- | ------------ |
| **Test**  | `flags & mask`   | Check if bit is set | Non-zero if set |
| **Set**   | `flags           | = mask`             | Turn bit on     | Bit is now 1 |
| **Reset** | `flags &= ~mask` | Turn bit off        | Bit is now 0    |
| **Flip**  | `flags ^= mask`  | Toggle bit          | 1 or 0          |

```cpp
constexpr std::uint8_t option_bold{ 0b0000'0001 };
constexpr std::uint8_t option_italic{ 0b0000'0010 };

std::uint8_t flags{ 0 };
flags |= option_bold;                  // Set bold
flags |= option_italic;               // Set italic
bool isBold{ (flags & option_bold) != 0 }; // Test bold
flags &= ~option_italic;              // Reset italic
flags ^= option_bold;                 // Flip bold
```

### O.4 - Converting integers between binary and decimal representation

- **Binary** uses base-2 - each digit represents a power of 2 - to convert to decimal, sum each bit × its positional power
- **Decimal → binary** method 1 - repeatedly divide by 2 and collect remainders (read bottom-to-top)
- **Decimal → binary** method 2 - subtract the largest fitting power of 2, writing 1 for each used and 0 for each skipped
- **Two's complement** represents negatives by inverting all bits and adding 1 - the **sign bit** (leftmost) is 0 for positive, 1 for negative
- The variable's **type** determines whether its binary value is interpreted as signed or unsigned - same bit pattern, different meaning

```cpp
// Binary to decimal: 0b1011 = 8 + 2 + 1 = 11
// Decimal to binary: 13 → 1101 (13/2=6 R1, 6/2=3 R0, 3/2=1 R1, 1/2=0 R1)
// Two's complement (-5 in 8-bit): 0000'0101 → invert → 1111'1010 → +1 → 1111'1011
```

→ _See [05_BinaryDecimalConversion](../solutions/Chapter_O_Bit_Manipulation/05_BinaryDecimalConversion) for binary ↔ decimal conversion and two's complement._

### Edge Cases and Caveats

❌ Using bitwise operators on signed integers:

```cpp
int x = -1;
int y = x >> 1; // ❌ implementation-defined for signed types
```

✅ Always use unsigned types or `std::bitset`.

---

❌ Forgetting integral promotion:

```cpp
std::uint8_t mask = 0xFF;
auto result = ~mask; // ❌ promoted to int → result is 0xFFFFFF00, not 0x00
```

✅ Cast back to the intended type:

```cpp
auto result = static_cast<std::uint8_t>(~mask); // ✅
```

---

❌ Confusing logical and bitwise operators:

```cpp
if (a & b) {} // bitwise AND - not the same as
if (a && b) {} // logical AND ❌ mixing them up causes subtle bugs
```

✅ `&&`/`||` are logical (whole values); `&`/`|` are bitwise (each bit).

---

❌ Shifting bits off the end:

```cpp
std::uint8_t x = 0b1100'0000;
x <<= 3; // ❌ top 3 bits are lost - shifting is not rotation
```

✅ Be aware that shifted-out bits are gone forever.

---

❌ Assuming `std::bitset` saves memory:

```cpp
std::bitset<8> flags; // ❌ typically uses 4 or 8 bytes, not 1
```

✅ `std::bitset` prioritizes speed over compactness.

---

❌ Forgetting `~` when clearing bits:

```cpp
flags &= mask; // ❌ clears everything EXCEPT mask bits
```

✅ Invert the mask:

```cpp
flags &= ~mask; // ✅ clears the mask bits
```

---

❌ Off-by-one with bit positions:

```cpp
unsigned int bit1 = 1 << 1; // ❌ this is bit position 1 (value 2), not position 0
```

✅ Bit positions start at 0 (rightmost). `1 << 0` = value 1.

---

### Hands-On Code Projects

| #   | Project                        | Concept                                                                                       |
| --- | ------------------------------ | --------------------------------------------------------------------------------------------- |
| 01  | `01_BitFlagsWithBitset`        | Using `std::bitset` for individual bit manipulation (`test`, `set`, `reset`, `flip`, `count`) |
| 02  | `02_BitwiseOperators`          | The six bitwise operators: `<<`, `>>`, `~`, `&`, `\|`, `^` and their assignment variants      |
| 03  | `03_BitMasks`                  | Defining bit masks and the four essential mask operations (test, set, reset, flip)            |
| 04  | `04_BitFlagsRealWorld`         | Real-world use case: passing multiple options to a function via bit flags                     |
| 05  | `05_BinaryDecimalConversion`   | Converting between binary and decimal, and two's complement for signed integers               |
| 06  | `06_IntegralPromotionPitfalls` | How integral promotion affects `~` and `<<` on narrow types, and how to fix it                |
| 07  | `07_CommonPitfalls`            | Logical vs bitwise operators, signed operand issues, off-by-one bit positions, shift loss     |

> **Path:** `solutions/Chapter_O_Bit_Manipulation/01_BitFlagsWithBitset/main.cpp` … `07_CommonPitfalls/main.cpp`

### Quick Reference

| Operation   | Syntax           | Example                                |
| ----------- | ---------------- | -------------------------------------- |
| Left shift  | `x << n`         | `1 << 3` → `0b1000` (8)                |
| Right shift | `x >> n`         | `8 >> 2` → `0b10` (2)                  |
| NOT         | `~x`             | `~0b1010` → `0b0101` (width-dependent) |
| AND         | `x & y`          | `0b1100 & 0b1010` → `0b1000`           |
| OR          | `x \| y`         | `0b1100 \| 0b1010` → `0b1110`          |
| XOR         | `x ^ y`          | `0b1100 ^ 0b1010` → `0b0110`           |
| Test bit    | `flags & mask`   | Non-zero = bit is set                  |
| Set bit     | `flags \|= mask` | Turn on selected bits                  |
| Clear bit   | `flags &= ~mask` | Turn off selected bits                 |
| Flip bit    | `flags ^= mask`  | Toggle selected bits                   |
| bitset test | `bits.test(pos)` | Returns bool                           |
| bitset set  | `bits.set(pos)`  | Sets bit at pos                        |

## Mastery Check

### Test Yourself

Try each question from memory first. Then expand the answer to self-check depth and accuracy.

1. Why should bitwise operations use unsigned types?

<details>
<summary>Show answer</summary>

**Direct answer:** Bitwise operations on signed integers have implementation-defined or undefined behavior. Right-shifting a signed negative value is implementation-defined (arithmetic vs. logical shift), and left-shifting into or past the sign bit is undefined behavior. Unsigned integers have well-defined behavior for all bitwise operations.

**Detailed explanation:**
The C++ standard only guarantees predictable results for bitwise operations on unsigned types. Signed integers use two's complement on most platforms, but the standard doesn't mandate how shifting interacts with the sign bit. Using unsigned types eliminates all ambiguity. `std::bitset` also uses unsigned semantics internally.

</details>

2. What is integral promotion and how does it affect `~` on `uint8_t`?

<details>
<summary>Show answer</summary>

**Direct answer:** Integral promotion widens types smaller than `int` (like `uint8_t`) to `int` before performing arithmetic or bitwise operations. When you apply `~` to a `uint8_t` value `0b0000'0101`, it first promotes to a 32-bit `int`, then flips _all 32 bits_, producing `0xFFFFFFFA` - not the expected 8-bit result `0b1111'1010`. This causes unexpected results when using the result in comparisons or masks.

**Detailed explanation:**
The fix is to cast the result back to the intended type or mask it:

```cpp
std::uint8_t flags{ 0b0000'0101 };

// WRONG - ~flags is a 32-bit int with upper bits set
if (flags & ~flags) { }

// RIGHT - mask to 8 bits
std::uint8_t mask{ static_cast<std::uint8_t>(~flags) };

// Or use an explicit mask
flags &= static_cast<std::uint8_t>(~(1 << 2));
```

</details>

3. What is the difference between `&` and `&&`?

<details>
<summary>Show answer</summary>

**Direct answer:** `&` is the bitwise AND operator - it compares each pair of bits in two integers and returns `1` only where both bits are `1`. `&&` is the logical AND operator - it evaluates two boolean expressions and short-circuits (skips the right operand if the left is `false`). They operate on completely different levels: `&` works on individual bits, `&&` works on truth values.

**Detailed explanation:**
A common bug is accidentally using `&` instead of `&&` in a conditional. `&` does not short-circuit and treats its operands as bit patterns, not booleans. `if (x & y)` computes the bitwise AND and checks if the result is non-zero - which may give unexpected results. Similarly, `|` (bitwise OR) and `||` (logical OR) are distinct operators.

```cpp
int a{ 5 };   // 0b0101
int b{ 3 };   // 0b0011
int c{ a & b }; // 0b0001 = 1 (bitwise AND)

bool x{ true };
bool y{ false };
bool z{ x && y }; // false (logical AND, short-circuits)
```

</details>

4. How do you set, clear, and toggle a specific bit?

<details>
<summary>Show answer</summary>

**Direct answer:** Set a bit with `flags |= mask`, clear it with `flags &= ~mask`, and toggle it with `flags ^= mask`. To test whether a bit is set, use `flags & mask` (non-zero means the bit is set).

**Detailed explanation:**
A bit mask is a value with specific bits set to `1` to indicate which bits to operate on. Masks are commonly defined using the left-shift operator (`1 << n` for bit n), binary literals, or hex literals. These four operations - set, clear, toggle, test - are the building blocks of all bit manipulation.

```cpp
constexpr unsigned int mask0{ 1 << 0 };  // bit 0: 0b0001
constexpr unsigned int mask2{ 1 << 2 };  // bit 2: 0b0100

unsigned int flags{ 0 };
flags |= mask0;          // set bit 0   → 0b0001
flags |= mask2;          // set bit 2   → 0b0101
flags &= ~mask0;         // clear bit 0 → 0b0100
flags ^= mask2;          // toggle bit 2 → 0b0000

if (flags & mask2) { }   // test bit 2 (false here)
```

</details>

5. What is the difference between `std::bitset` and raw bit manipulation?

<details>
<summary>Show answer</summary>

**Direct answer:** `std::bitset` provides a clean interface with named member functions (`test()`, `set()`, `reset()`, `flip()`) and is easier to read and less error-prone. Raw bitwise operations on unsigned integers are more flexible, can be used with any integer size, and use less memory. `std::bitset` is optimized for speed but rounds its size up to `sizeof(size_t)`, so it may waste memory compared to using the smallest fitting unsigned integer.

**Detailed explanation:**
Use `std::bitset` when readability and safety matter and you have a fixed number of flags. Use raw bitwise operators when you need tight memory control, need to interface with hardware or APIs that use integer flags, or need to manipulate bits in non-bitset types. `std::bitset` also provides convenient I/O (`<<` prints binary representation) and `count()`/`any()`/`none()` utilities.

```cpp
std::bitset<8> bits{ 0b0000'0101 };
bits.set(3);              // set bit 3
bits.flip(0);             // toggle bit 0
bool b{ bits.test(2) };   // test bit 2 (true)
std::cout << bits;        // prints "00001100"
```

</details>

6. Why is bit shifting not the same as rotation?

<details>
<summary>Show answer</summary>

**Direct answer:** When you shift bits left or right, the bits that fall off the end are permanently lost and zeros (or sign bits for signed right-shift) fill the vacated positions. In a rotation, bits that fall off one end wrap around to the other end - no data is lost. C++ provides shift operators (`<<`, `>>`) but has no built-in rotation operator.

**Detailed explanation:**
Shifting is a one-way operation: `0b1100 << 2` gives `0b0000` (for an 8-bit type) - the two high bits are gone. A rotation would produce `0b0011` instead. C++20 introduced `std::rotl()` and `std::rotr()` in `<bit>` for rotation operations. Shifting by the number of bits in the type or more is undefined behavior.

```cpp
std::uint8_t val{ 0b1100'0001 };
val <<= 2;  // shift: 0b0000'0100 (high bits lost, low bits filled with 0)
// rotation would give: 0b0000'0111 (high bits wrapped to low end)
```

</details>

7. How do bit masks work and why are they useful?

<details>
<summary>Show answer</summary>

**Direct answer:** A bit mask is a value where specific bits are set to `1` to indicate which bits to operate on and the rest are `0`. By combining masks with bitwise operators (`&`, `|`, `^`, `~`), you can selectively test, set, clear, or toggle individual bits without affecting the others. They are useful for packing multiple boolean flags into a single integer, saving memory, and passing many on/off options as a single parameter.

**Detailed explanation:**
Masks can be defined using binary literals (`0b0000'0100`), hexadecimal literals (`0x04`), or the shift operator (`1 << 2`). The shift approach is the most readable and scalable. Bit flags are commonly used in graphics APIs, file permissions, hardware registers, and network protocols where memory efficiency and bitwise-packed options are important.

```cpp
constexpr unsigned int READ    { 1 << 0 };  // 0b001
constexpr unsigned int WRITE   { 1 << 1 };  // 0b010
constexpr unsigned int EXECUTE { 1 << 2 };  // 0b100

unsigned int perms{ READ | WRITE };  // combine flags: 0b011
if (perms & EXECUTE) { }             // test: is EXECUTE set? (no)
perms |= EXECUTE;                    // grant execute: 0b111
perms &= ~WRITE;                     // revoke write: 0b101
```

</details>

8. What is the value of `1 << 0`, `1 << 1`, and `1 << 7`?

<details>
<summary>Show answer</summary>

**Direct answer:** `1 << 0` is `1` (binary `0000'0001`), `1 << 1` is `2` (binary `0000'0010`), and `1 << 7` is `128` (binary `1000'0000`). Each left-shift by `n` produces $2^n$.

**Detailed explanation:**
Left-shifting `1` by `n` positions sets only bit `n`, making it the standard way to create bit masks. The pattern `1 << n` is equivalent to $2^n$ for non-negative `n` less than the bit-width of the type. Be careful not to shift by more than the number of bits in the type - that is undefined behavior. For a 32-bit `int`, shifting by 31 is the maximum safe left-shift of `1`.

```cpp
// Common bit mask definitions:
constexpr unsigned int bit0{ 1 << 0 };  // 1
constexpr unsigned int bit1{ 1 << 1 };  // 2
constexpr unsigned int bit7{ 1 << 7 };  // 128
```

</details>

9. How does two's complement represent negative numbers?

<details>
<summary>Show answer</summary>

**Direct answer:** In two's complement, a negative number is represented by inverting all bits of its positive counterpart and adding `1`. The leftmost (most significant) bit is the sign bit - `0` for positive, `1` for negative. For example, in 8 bits: `5` is `0000'0101`, so `-5` is `1111'1011` (invert → `1111'1010`, add 1 → `1111'1011`).

**Detailed explanation:**
Two's complement is the universal representation for signed integers in modern hardware (and mandated by C++20). Its key advantage is that addition operations work identically for signed and unsigned values at the hardware level. The range for an n-bit signed integer is $-2^{n-1}$ to $2^{n-1}-1$. For 8 bits: -128 to 127.

</details>

10. How do you convert a decimal integer to binary?

<details>
<summary>Show answer</summary>

**Direct answer:** Two methods: (1) Repeatedly divide by 2 and collect the remainders (read from bottom to top). (2) Subtract the largest fitting power of 2, writing `1` for each power used and `0` for each power skipped.

**Detailed explanation:**
Method 1 (division): For 13: 13/2 = 6 R **1**, 6/2 = 3 R **0**, 3/2 = 1 R **1**, 1/2 = 0 R **1** → reading remainders bottom-up: `1101`.

Method 2 (subtraction): For 13: 8 fits (1), remainder 5; 4 fits (1), remainder 1; 2 doesn't fit (0); 1 fits (1) → `1101`.

Both methods produce the same result. Method 2 writes left-to-right and is often more intuitive.

</details>
