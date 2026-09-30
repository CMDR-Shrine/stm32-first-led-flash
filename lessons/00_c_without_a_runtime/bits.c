#include "bits.h"

uint32_t set_bit(uint32_t value, uint32_t bit)
{
    /* TODO: preserve value and set exactly one bit. */
    value = value | (1u << bit);

    return value;
}

uint32_t clear_bit(uint32_t value, uint32_t bit)
{
    /* TODO: preserve value and clear exactly one bit. */
    // we cant use just &, that would erase all the bits in this case
    // we want to simply snipe the given bit value.
    // we can invert the bitmask with ~
    // eg value: 00000011 target: 00000010 mask: 11111101
    // we and on the mask, it will keep all values appart from target
    value = value & ~(1u << bit);
    
    return value ;
}

uint32_t replace_nibble(uint32_t value, uint32_t shift, uint32_t nibble)
{
    /* TODO: replace four selected bits and preserve the other 28. */
    (void)shift;
    (void)nibble;
    // maybe we could do the same trick?
    // could clear the 4 bits
    // 1111b = 15u = F
    // one hex is 4 bits
    value = value & ~(15u << shift);

    nibble = nibble & 15u;
    value = value | (nibble << shift);
    
    return value;
}

