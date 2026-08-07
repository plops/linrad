#include <stdio.h>

extern int run_llsq_tests(void);
extern int run_vernr_tests(void);
extern int run_palette_tests(void);

int main(void) {
    printf("=========================================\n");
    printf("  LINRAD AUTOMATED TEST SUITE RUNNER\n");
    printf("=========================================\n\n");
    
    int failed = 0;
    
    failed += run_vernr_tests();
    failed += run_palette_tests();
    failed += run_llsq_tests();
    
    printf("\n=========================================\n");
    if (failed == 0) {
        printf("  ALL TESTS PASSED SUCCESSFULLY!\n");
        printf("=========================================\n");
        return 0;
    } else {
        printf("  TEST SUITE FAILED (%d failures)\n", failed);
        printf("=========================================\n");
        return 1;
    }
}
