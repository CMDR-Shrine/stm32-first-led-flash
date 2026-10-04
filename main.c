#include <stdint.h>



uint32_t set_bit(uint32_t value, uint32_t bit)
{
    value = value | (1u << bit);

    return value;
}


int main(void)
{
    /* Lesson 01 starts here. This is valid firmware that does nothing yet. */
    for (;;) {
        // we use volatile to prevent the c compiler from optomizing it away
        // rn its seens as useless
        // we are rn enabling the clock btw by flipping a bit i read from the manual


        // kinda cray ik, but lets go


        // just the RCC BASE Reset/clock controll at 7.3 in the manual
        uint32_t RCC_BASE = 0x40021000;
        
        // AHB peripheral clock enable register 
        // thats a 32 bit register
        uint32_t RCC_APB2ENR = RCC_BASE + 0x0C ;

        // so it has a value is 32 bits long
        // we go to bit 4 in the value. we can change it!
        volatile uint32_t *reg = (volatile uint32_t *) RCC_APB2ENR;

        // tldr, we go to addr, it has a big value, we change a part of it = clock now on
        // now lets flip this bit..ch
        *reg = set_bit(*reg,4u);
    }
}
