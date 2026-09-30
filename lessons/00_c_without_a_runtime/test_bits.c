#include "bits.h"

#include <stdint.h>
#include <stdio.h>

static int failures;

static void check(const char *group, uint32_t actual, uint32_t expected)
{
    if (actual != expected) {
        printf("FAIL: %s: got 0x%08x, expected 0x%08x\n",
               group, (unsigned)actual, (unsigned)expected);
        ++failures;
    }
}

int main(void)
{
    check("set_bit", set_bit(0x00000000u, 4u), 0x00000010u);
    check("set_bit", set_bit(0x00000020u, 4u), 0x00000030u);
    if (failures == 0) {
        puts("PASS: set_bit");
    }

    int before = failures;
    check("clear_bit", clear_bit(0x0000001fu, 4u), 0x0000000fu);
    check("clear_bit", clear_bit(0x0000000fu, 4u), 0x0000000fu);
    if (failures == before) {
        puts("PASS: clear_bit");
    }

    before = failures;
    check("replace_nibble", replace_nibble(0xffffffffu, 20u, 0x2u),
          0xff2fffffu);
    check("replace_nibble", replace_nibble(0x12345678u, 8u, 0xabu),
          0x12345b78u);
    if (failures == before) {
        puts("PASS: replace_nibble");
    }

    return failures == 0 ? 0 : 1;
}

