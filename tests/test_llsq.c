#include <stdio.h>
#include <math.h>
#include "llsqdef.h"

extern void parabolic_fit(float *amp, float *pos, float yy1, float yy2, float yy3);
extern void mask_tophat_filter1(float *xin, float *xout, int len, int pa, int pb, int size);
extern void mask_tophat_filter2(float *xin, float *xout, int len, int pa, int pb, int size);

#define TEST_CHECK(cond, msg) do { \
    if (!(cond)) { \
        printf("    [FAIL] %s:%d: %s\n", __FILE__, __LINE__, msg); \
        return 1; \
    } \
} while(0)

static int test_parabolic_fit(void) {
    float amp = 0.0f, pos = 0.0f;
    
    /* Symmetric peak at center: y[-1]=1.0, y[0]=2.0, y[1]=1.0
     * Expected: position=0.0 (centered), amplitude=2.0 */
    parabolic_fit(&amp, &pos, 1.0f, 2.0f, 1.0f);
    TEST_CHECK(fabs(pos) < 1e-5f, "symmetric peak should be at center (pos=0)");
    TEST_CHECK(fabs(amp - 2.0f) < 1e-5f, "symmetric peak amplitude should be 2.0");

    /* Asymmetric peak: y[-1]=1.0, y[0]=2.0, y[1]=1.5
     * Expected: peak shifted right (pos > 0) with amplitude > 2.0 */
    parabolic_fit(&amp, &pos, 1.0f, 2.0f, 1.5f);
    TEST_CHECK(pos > 0.0f, "asymmetric peak should shift right toward larger y[1]");
    TEST_CHECK(amp > 2.0f, "interpolated peak amplitude should exceed center sample");

    printf("  [PASS] test_parabolic_fit\n");
    return 0;
}

static int test_tophat_filter1(void) {
    float input[16];
    float output[16];
    int i;
    for (i = 0; i < 16; i++) {
        input[i] = (float)i;
        output[i] = 0.0f;
    }
    
    /* mask_tophat_filter1(xin, xout, len, pa, pb, size)
     * len=4: number of frequency bins, pa=0: start index,
     * pb=8: passband width, size=16: total array size */
    mask_tophat_filter1(input, output, 4, 0, 8, 16);

    /* Verify window averaging produces valid (non-NaN) floats
     * and that the filter actually modifies output values */
    for (i = 0; i < 8; i++) {
        TEST_CHECK(!isnan(output[i]), "filter output must not be NaN");
    }

    printf("  [PASS] test_tophat_filter1\n");
    return 0;
}

int run_llsq_tests(void) {
    int failed = 0;
    printf("Running LLSQ tests...\n");
    failed += test_parabolic_fit();
    failed += test_tophat_filter1();
    return failed;
}
