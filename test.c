/* @BAKE echo
    echo GCC generation...
    gcc -Wall -Wextra -Wpedantic -std=c23 -o $*.out $@
    echo CLANG generation...
    clang -Wall -Wextra -Wpedantic -std=c23 -o $*.out $@
   @STOP
*/

#include "terry.h"
#include <stdio.h>
signed main(void) {
  printf("%ld\n", __STDC_VERSION__);
  u128 a; (void) a;
  f32 b; (void) b;
  f80 c; (void) c;
  /* d32 d; (void) d; */
  return 0;
}
