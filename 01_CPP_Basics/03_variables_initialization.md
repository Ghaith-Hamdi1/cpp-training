# Variables initialization

- Initialization methods:
  - Default: `int i;`
  - Direct: `int i{0};` or `int i(0);`
  - Copy: `int i = 5;` or `int i; i = 5;`
- Always initialize variables upon creation

## Literal suffixes: Integer literals

| Suffix | Type |
|---|---|
| (no suffix) | `int`, `long int`, `long long int` |
| `u` or `U` | `unsigned int`, `unsigned long int`, `unsigned long long int` |
| `l` or `L` | `long int`, `long long int`, `unsigned long int` |
| `ul`, `Ul`, `uL` or `UL` | `unsigned long int`, `unsigned long long int` |
| `ll` or `LL` | `long long int` |

## Literal suffixes: Floating point literals

| Suffix | Type |
|---|---|
| (no suffix) | `double` |
| `f` or `F` | `float` |
| `l` or `L` | `long double` |

- Exponent notation examples: `2E-5L`, `2e-5L`, `2e-5l`, `2E-5l` (all equal to `2 x 10^5`)
- General form: `digits decimal_exponent exponent_sign exponent_value suffix`

---

