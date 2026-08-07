#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "llsqdef.h"

extern void parabolic_fit(float *amp, float *pos, float yy1, float yy2, float yy3);
extern void mask_tophat_filter1(float *xin, float *xout, int len, int pa, int pb, int size);
extern void mask_tophat_filter2(float *xin, float *xout, int len, int pa, int pb, int size);

static int test_parabolic_fit(void) {
    float amp = 0.0f, pos = 0.0f;
    
    // Symmetric peak at center (y0=2.0, y-1=1.0, y1=1.0)
    parabolic_fit(&amp, &pos, 1.0f, 2.0f, 1.0f);
    assert(fabs(pos) < 1e-5f);
    assert(fabs(amp - 2.0f) < 1e-5f);

    // Asymmetric peak (yy1=1.0, yy2=2.0, yy3=1.5)
    parabolic_fit(&amp, &pos, 1.0f, 2.0f, 1.5f);
    assert(pos > 0.0f); // Peak shifted slightly right toward yy3
    assert(amp > 2.0f);

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
    
    mask_tophat_filter1(input, output, 4, 0, 8, 16);
    // Verify window averaging produces valid non-NaN floats
    for (i = 0; i < 8; i++) {
        assert(!isnan(output[i]));
    }

    printf("  [PASS] test_tophat_filter1\n");
    return 0;
}

int run_llsq_tests(void) {
    printf("Running LLSQ tests...\n");
    test_parabolic_fit();
    test_tophat_filter1();
    return 0;
}
