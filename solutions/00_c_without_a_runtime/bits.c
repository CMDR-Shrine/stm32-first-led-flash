#include "bits.h"

uint32_t set_bit(uint32_t value, uint32_t bit)
{
    return value | (1u << bit);
}

uint32_t clear_bit(uint32_t value, uint32_t bit)
{
    return value & ~(1u << bit);
}

uint32_t replace_nibble(uint32_t value, uint32_t shift, uint32_t nibble)
{
    const uint32_t mask = 0xFu << shift;
    return (value & ~mask) | ((nibble & 0xFu) << shift);
}
