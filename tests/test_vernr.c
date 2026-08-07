#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "vernr.h"

int run_vernr_tests(void) {
    printf("Running Version Number tests...\n");
    assert(PROGRAM_NAME != NULL);
    assert(strncmp(PROGRAM_NAME, "Linrad-", 7) == 0);
    assert(GENPARM_VERNR > 0);
    assert(DLL_VERSION_NUMBER > 0);
    printf("  [PASS] test_vernr (Program Name: %s)\n", PROGRAM_NAME);
    return 0;
}
