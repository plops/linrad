#include <stdio.h>
#include <string.h>
#include "vernr.h"

#define TEST_CHECK(cond, msg) do { \
    if (!(cond)) { \
        printf("    [FAIL] %s:%d: %s\n", __FILE__, __LINE__, msg); \
        return 1; \
    } \
} while(0)

int run_vernr_tests(void) {
    printf("Running Version Number tests...\n");
    TEST_CHECK(PROGRAM_NAME != NULL, "PROGRAM_NAME must not be NULL");
    TEST_CHECK(strncmp(PROGRAM_NAME, "Linrad-", 7) == 0,
               "PROGRAM_NAME must start with 'Linrad-'");
    TEST_CHECK(GENPARM_VERNR > 0, "GENPARM_VERNR must be > 0");
    TEST_CHECK(DLL_VERSION_NUMBER > 0, "DLL_VERSION_NUMBER must be > 0");
    printf("  [PASS] test_vernr (Program Name: %s)\n", PROGRAM_NAME);
    return 0;
}
