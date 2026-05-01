#ifndef TERRY_H
#define TERRY_H

#if 0
   Promises the most accurate primitives as are allowable by (recent) compiler version and C standard.
   Primitivie types:
   signed int : i8>i128, s8>s128
   unsigned int : u8>u128
   float  : f32
   double : f64
   long double : f128

   NO_128_TYPES will be defined when i128, s128, u128 are absent.

   All floating bitmarked types will have F<NUM>_PRECISE defined
   if they are specified to that precise number of bits.

   Tested to work with gcc 14.2.0 and clang 19.1.7 on Debian // XXX: auto tests / auto comment
   Backwards compat for gcc 14.2.0
   Not robustly tested, please report issues.

   --- Definitions ---

   // XXX too *many* macros

   Defining the following will change behavior within the typesystem.
   the IMPRECISE groupings will always be provided with their respective types are present in full.

#define TERRY_FLOAT_IMPRECISE       /* supergroup of the below two groups */
#define TERRY_SMALL_FLOAT_IMPRECISE /* groups the two below together */
#define FLOAT_IS_F32
#define DOUBLE_IS_F64
#define TERRY_LARGE_FLOAT_IMPRECISE /* groups the two below together */
#define LONG_DOUBLE_IS_F80
#define LONG_DOUBLE_IS_F128
#define NO_128_TYPES                // 128 bit wide types are not available
#endif

/* XXX:
 * this construct:
 *      #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
 * is useless.
 * if the __STDC_VERSION__ macro is not defined,
 * the condition will still be falsely,
 * but i DO want to spam the user with warnings about their dumb compiler
 */

// --------
// Integers
// --------

#include <stdint.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#if __STDC_VERSION__ >= 202311L
    typedef signed   _BitInt(128) i128;
    typedef signed   _BitInt(128) s128;
    typedef unsigned _BitInt(128) u128;
#else
# if __SIZEOF_INT128__ 	/* compiler specific macro */
/* XXX: this produces no warnings for me either way, why did you add this guard here?
 */
//#    pragma GCC diagnostic push
//#    pragma GCC diagnostic ignored "-Wpedantic"
//#    pragma GCC diagnostic pop
     typedef signed   __int128 i128;
     typedef signed   __int128 s128;
     typedef unsigned __int128 u128;
# else
#    define NO_128_TYPES
# endif
#endif


// ------
// Floats
// ------


/* XXX:
 *  documentation, you bloody ToS violation
 */
#if !(defined(__STDC_IEC_60559_BFP__) && defined(__STDC_IEC_60559_TYPES__))
#define TERRY_FLOAT_IMPRECISE
#endif

/* > You can treat floats like _Float32, and doubles like _Float64, however *THEY ARE NOT THE SAME THING*. */
/* > go ask WG14 for the "why." GCC/Clang may complain but will work as expected. */
/* XXX:
 * what do you mean they are not the same thing?
 *      // @BAKE gcc -o $*.out $@ -Wall -Wpedantic -Wextra
 *      signed main(void) {
 *          float a = 1.2;
 *          _Float32 b = 1.2;
 *          a = b;
 *          b = a;
 *
 *          double c = 1.2;
 *          _Float64 d = 1.2;
 *          c = d;
 *          d = c;
 *
 *          return 0;
 *      }
 *
 * anon@anon872387634598 ~> bake f.c
 * bake: gcc -o f.out f.c -Wall -Wpedantic -Wextra
 * output:
 *
 * ---
 * under what circumstances does it show?
 */

/* XXX:
 *  i have not the faintest clue where you got half of these builtin types from, halp
 */
#if (__STDC_VERSION__ >= 202000L && defined(__GNUC__) && !defined(__clang__)) \
||  __STDC_VERSION__ >= 202311L
# if defined(FLOAT_IS_F32) || defined(TERRY_SMALL_FLOAT_IMPRECISE)
    typedef float f32;
# else
#   define F32_PRECISE
    typedef _Float32 f32;
# endif

# if defined(DOUBLE_IS_F64) || defined(TERRY_LARGE_FLOAT_IMPRECISE)
    typedef double f64;
# else
#   define F64_PRECISE
    typedef _Float64 f64;
# endif

# if defined(__GNUC__) && !defined(__clang__)
#   define F80_PRECISE
    typedef __float80 f80;
# else
    #define LONG_DOUBLE_IS_F80
    typedef long double f80;
# endif

# if defined(LONG_DOUBLE_IS_F128) || defined(TERRY_LARGE_FLOAT_IMPRECISE)
    typedef long double f128;
# else
#   define F128_PRECISE
    typedef _Float128 f128;
# endif
#else
/* > the below f32/64 definitions may behave erratically, as float != f32 && double != f64.
 * > We're just doing this for the sake of defining something that will *probably* work in most cases.
 * > Use newer C versions. */
/* XXX:
 * for the love of God (WHICH ONE? AAAAAAAAAAAAAAAAAAAAAAAAA), dont.
 * im not deleting this yet so that you dont add it back behind my back
 */
# if defined(__GNUC__) && !defined(__clang__)
#   define TERRY_SMALL_FLOAT_IMPRECISE

#   define FLOAT_IS_F32
    typedef float  f32;
#   define DOUBLE_IS_F64
    typedef double f64;

#   if defined(LONG_DOUBLE_IS_F80)
      typedef long double  f80;
#   else
#     define F80_PRECISE
      typedef __float80 f80;
#   endif

#   if defined(LONG_DOUBLE_IS_F128)
      typedef long double  f128;
#   else
#     define F128_PRECISE
      typedef __float128 f128;
#   endif
# else
#   define TERRY_FLOAT_IMPRECISE
#   define TERRY_SMALL_FLOAT_IMPRECISE
#   define TERRY_LARGE_FLOAT_IMPRECISE
#   define FLOAT_IS_F32
    typedef float  f32;
#   define DOUBLE_IS_F64
    typedef double f64;
    /* Usually 10-bytes with 128-bit alignment */
#   define LONG_DOUBLE_IS_F80
    typedef long double f80;
#   define LONG_DOUBLE_IS_F128
    typedef long double f128;
# endif
#endif
#endif

// --------
// Decimals
// --------

#if __STDC_VERSION__ >= 202311L
    typedef _Decimal32  d32
    typedef _Decimal64  d64
    typedef _Decimal128 d128
#endif

// ------------------
// Bitwise operations
// ------------------

static inline
uint32_t random_rol32(uint32_t x, unsigned int n) {
    return (n &= 31) ? (x << n) | (x >> (32 - n)) : x;
}

static inline
uint64_t random_rol64(uint64_t x, unsigned int n) {
    return (n &= 63) ? (x << n) | (x >> (64 - n)) : x;
}

static inline
uint32_t random_ror32(uint32_t x, unsigned int n) {
    return (n &= 31) ? (x >> n) | (x << (32 - n)) : x;
}
