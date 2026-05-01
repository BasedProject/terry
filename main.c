#if 0
@BAKE echo
echo GCC generation...
gcc -Wall -Wextra -Wpedantic -std=c23 -o $*.out $@
echo CLANG generation...
clang -Wall -Wextra -Wpedantic -std=c23 -o $*.out $@
@STOP
#endif
#include "terry.h"
#include <stdio.h>
signed main(void) {
  u128 a; (void) a;
  f32 b; (void) b;
  f80 c; (void) c;
  d32 d; (void) d;
  return 0;
}
