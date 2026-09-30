#include "bits.h"

uint32_t set_bit(uint32_t value, uint32_t bit)
{
    /* TODO: preserve value and set exactly one bit. */
    (void)bit;
    value = value | (1 << bit);

    return value;
}

uint32_t clear_bit(uint32_t value, uint32_t bit)
{
    /* TODO: preserve value and clear exactly one bit. */
    (void)bit;
    return value;
}

uint32_t replace_nibble(uint32_t value, uint32_t shift, uint32_t nibble)
{
    /* TODO: replace four selected bits and preserve the other 28. */
    (void)shift;
    (void)nibble;
    return value;
}

