#include <stdio.h>
#include <stdlib.h>

int last_lirerr_code = 0;

void lirerr(int errnum) {
    last_lirerr_code = errnum;
    printf("[STUB] lirerr called with code: %d\n", errnum);
}
