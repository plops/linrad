#include <stdio.h>
#include "osnum.h"
#include "globdef.h"
#include "uidef.h"
#include "screendef.h"

extern unsigned char color_scale[];
extern unsigned char svga_palette[];

#define TEST_CHECK(cond, msg) do { \
    if (!(cond)) { \
        printf("    [FAIL] %s:%d: %s\n", __FILE__, __LINE__, msg); \
        return 1; \
    } \
} while(0)

int run_palette_tests(void) {
    printf("Running Palette tests...\n");

    /* svga_palette is an RGB triplet array; index 0 = palette entry 0 = black */
    TEST_CHECK(svga_palette[0] == 0x00, "palette[0] R must be 0 (black)");
    TEST_CHECK(svga_palette[1] == 0x00, "palette[0] G must be 0 (black)");
    TEST_CHECK(svga_palette[2] == 0x00, "palette[0] B must be 0 (black)");

    /* color_scale[21] == 15: index 21 in the color_scale lookup table maps
     * to palette entry 15 (white), marking the end of the base color ramp */
    TEST_CHECK(color_scale[0] == 0, "color_scale[0] must be 0 (first entry)");
    TEST_CHECK(color_scale[21] == 15,
               "color_scale[21] must be 15 (end of base color ramp)");
    
    printf("  [PASS] test_palette\n");
    return 0;
}
