# Chapter 5 - Constants and Strings

This chapter covers constant variables (`const`, `constexpr`), compile-time evaluation, numeral systems, magic numbers, `std::string`, and `std::string_view`.

## Projects

| #   | Folder                       | Topic                                                                     |
| --- | ---------------------------- | ------------------------------------------------------------------------- |
| 01  | `01_ConstVariables`          | Declaring `const` variables, initialization rules, `const` vs `#define`   |
| 02  | `02_Literals`                | Literal types, type suffixes, C-style string literals                     |
| 03  | `03_NumeralSystems`          | Decimal, octal, hexadecimal, binary literals, digit separators            |
| 04  | `04_AsIfRuleAndOptimization` | As-if rule, constant folding, constant propagation, dead code elimination |
| 05  | `05_ConstantExpressions`     | Constant expressions, `const` integral vs non-integral behavior           |
| 06  | `06_ConstexprVariables`      | `constexpr` guarantee, `constexpr` vs `const`, compile-time constants     |
| 07  | `07_MagicNumbers`            | Replacing magic numbers with named `constexpr` constants                  |
| 08  | `08_StdStringBasics`         | `std::string` creation, operations, `length()`, concatenation             |
| 09  | `09_StringInput`             | `std::getline()`, `std::ws`, multi-word input, leftover newline pitfall   |
| 10  | `10_StdStringView`           | `std::string_view` basics, read-only access, function parameters          |
| 11  | `11_StringViewDangling`      | Dangling views, ownership vs viewing, undefined behavior pitfalls         |
| 12  | `12_StringViewOperations`    | `remove_prefix()`, `remove_suffix()`, `constexpr std::string_view`        |
| 13  | `13_CommonPitfalls`          | Float/double narrowing, accidental octal, `const` non-integral traps      |
