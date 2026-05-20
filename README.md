# The Terry Header
> You run them over, that's what you do.

`terry.h` provides shorter primitive types, bitwise operations, assert, and limits.

We require C23. We utilize the __has_extension builtin for type builtin availability.

Install with `# PREFIX=/usr make`

## [<assert.h>](https://en.cppreference.com/c/header/assert) and [<limits.h>](https://en.cppreference.com/c/header/limits)

These are included for your benefit and for guarantees.

## [<stdbit.h>](https://en.cppreference.com/c/header/stdbit)

All stdc_ prefixes from the generic operations have been removed.

## Fixed Sized Types

Floats/_Decimal types will not work under Clang 21 almost certainly, see the below macros.
Clang pretends to support C23 however their support is lackluster at this moment (2026-05-01).

Table for ease:
| Type(s)                                                | Category                                | Requirements / Notes                                                                                                                               |
|--------------------------------------------------------|-----------------------------------------|------------------------------------------------------------------------------------------------------------------------------------                |
| `iN`, `sN`, `IN`, `SN`<br>*(N = 8, 16, 32, 64, 128)*   | Fixed‑width binary signed integer       | All forms are type‑identical.                                                                                                                      |
| `uN`, `UN`<br>*(N = 8, 16, 32, 64, 128)*               | Fixed‑width binary unsigned integer     | 128 can be missing under the rare condition of `__STDC_IEC_60559_TYPES__` missing and long double != 128 bits.                                     |
| `i16x`, `s16x`, `u16x`, `I16x`, `S16x`, `U16x`         | Binary integer (≥16 bits)               | Identical to `int`.                                                                                                                                |
| `fN`, `FN`<br>*(N = 32, 64, 128)*                      | IEEE 754 Floating‑Point                 | Best effort provision without depending on compiler builtins.<br>Provides `FLOAT_COMMON=202605L` for *N=32,64* `FLOAT_128=202605L` for *N=128*.    |
| `f80`, `F80`                                           | Extended binary floating‑point (80‑bit) | Requires `__float80` compiler extension<br>Provides macro `FLOAT_80=202605L`                                                                       |
| `dN`, `DN`<br>*(N = 32, 64, 128)*                      | Decimal floating‑point                  | Provides macro `DECIMAL_COMMON=202605L`                                                                                                            |
| `schar`                                                | Signed character primitive              | No size guarantees.                                                                                                                                |
| `uchar`                                                | Unsigned character primitive            | No size guarantees.<br>`uchar != char` for strings/arrays.                                                                                         |

Note that Clang 21 is missing common decimal support at this moment of 2026-05.

## License

[terry](https://github.com/BasedProject/terry) was composed by [AGVXOV](https://github.com/agvxov) & [Emil Williams](https://github.com/8e8m) for the benefit of noone.

Any source within the bounds of this project excluding already clearly marked code, is marked [CC0 1.0 Universal](https://creativecommons.org/publicdomain/zero/1.0/).
There is no warranty under any circumstance, use librandom at your own detriment.

![(CC)](https://mirrors.creativecommons.org/presskit/icons/cc.svg)
![(0)](https://mirrors.creativecommons.org/presskit/icons/zero.svg)
