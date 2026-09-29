# Regular Expressions

(Slides 83–84)

- Regular expression is a kind of language that allows pattern matching

**Quantifiers**

| Char | Description |
|---|---|
| `.` | Matches any character, ex: `a.b` matches `anb`, `aab` ... |
| `?` | The preceding element is present zero or one occurence, ex: `ab?c` matches `abc`, `ac` |
| `*` | The preceding element is present zero or more occurences, ex: `ab*c` matches `abc`, `ac`, `abbbbc` |
| `+` | The preceding element is present one or more occurences, ex: `ab+c` matches `abc`, `abbbbc` |
| `{n}` | The preceding element occurs exactly n times, ex: `ab{3}c` matches `abbbc` |
| `{min,max}` | The preceding element occurs between min and max occurences |
| `{,max}` | The preceding element occurs up to max occurences |
| `{min,}` | The preceding element occurs at least min times |

**Anchors, groups, character classes**

| Char | Description |
|---|---|
| `\|` | OR: ex: `gr(e\|a)y` matches `gray` or `grey` |
| `[c1-c2]` | Matches range of chars between c1 and c2, `a[a-zA-Z]b` matches `avb`, `aEb`, `axb`, `aXb` .... |
| `[c1c2c3]` | Matches one of c1, c2 or c3, `a[bcd]e` matches `abe` and `ace` |
| `[^c1-c2]` / `[^c1c2]` | Same as above, but any character that is NOT specified between brackets `[]` |
| `^` | Matches the starting position in string |
| `$` | Matches the end position in string |
| `()` | Define groups. It won't affect the regex but can be used by `regex_search` to get position |
| `[[:w:]]` | Matches an alphanumeric character including `_` |
| `[[:alnum:]]` | Matches an alphanumeric character (many other character classes are defined — see documentation) |
| `[[:s:]]` | White spaces |
| `\` | Escape character |

*(The per-row alignment of `[[:w:]]`, `[[:alnum:]]` and `[[:s:]]` against their descriptions was reconstructed from column-preserving extraction and is a best-effort mapping — see Conversion notes.)*

- From the previous table, we have to combine all tools to be able to get a pattern to match
- In the standard library, the file `<regex>` represents the regex support library
  - `std::regex`: a class that holds a regular expression
  - `std::regex_match`: attempts to match a complete string to the regex template
  - `std::regex_search`: attempts to match a part of a string to the regex template
  - `std::regex_replace`: attempts to replace matching regex pattern by a given string

```cpp
// Source: Examples/03_CPP_Standard_Library/14_regular_expressions/59_regex.cpp
#include <iostream>
#include <regex>
#include <string>

int main()
{
    std::regex pattern ("(t(e|s)t)+");
    std::string str("This is a tet string tst tst");

    bool match = std::regex_match(str, pattern);
    if (match)
    {
        std::cout << "Matched" << std::endl;
    }
    else 
    {
        std::cout << "Not matched" << std::endl;
    }

    std::smatch smatch;

    match = std::regex_search(str, smatch, pattern);
    if (match)
    {
        std::cout << "Matched " << smatch[0] << "-" << smatch[1].str() << std::endl;
    }
    else 
    {
        std::cout << "Not matched" << std::endl;
    }

    std::sregex_iterator itr(str.begin(), str.end(), pattern);

    for (std::sregex_iterator end; itr != end; itr++)
    {
        std::cout << "With iterator match " << itr->str() << std::endl; 
    }

    return 0;
}
```

---

