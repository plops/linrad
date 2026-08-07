#include <stdio.h>
#include <assert.h>
#include "osnum.h"
#include "globdef.h"
#include "uidef.h"
#include "screendef.h"

extern unsigned char color_scale[];
extern unsigned char svga_palette[];

int run_palette_tests(void) {
    printf("Running Palette tests...\n");
    // Verify svga_palette index 0 is RGB (0, 0, 0)
    assert(svga_palette[0] == 0x00);
    assert(svga_palette[1] == 0x00);
    assert(svga_palette[2] == 0x00);

    // Verify color_scale table entries
    assert(color_scale[0] == 0);
    assert(color_scale[21] == 15);
    
    printf("  [PASS] test_palette\n");
    return 0;
}
