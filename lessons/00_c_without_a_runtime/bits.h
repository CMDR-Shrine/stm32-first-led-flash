#ifndef LESSON_00_BITS_H
#define LESSON_00_BITS_H

#include <stdint.h>

uint32_t set_bit(uint32_t value, uint32_t bit);
uint32_t clear_bit(uint32_t value, uint32_t bit);
uint32_t replace_nibble(uint32_t value, uint32_t shift, uint32_t nibble);

#endif

