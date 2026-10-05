#include <stdint.h>



uint32_t set_bit(uint32_t value, uint32_t bit)
{
    // using | or means we keep original value and update desired bit
    // simply doing 1u << bit would erase all other values!
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


        // just the RCC BASE Reset/clock controll at 7.3.1 ish in the manual
        // https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101-103-105-107-stm32f100-series-armbased-32bit-mcus-stmicroelectronics.pdf
        uint32_t RCC_BASE = 0x40021000;
        
        // AHB peripheral clock enable register 
        // thats a 32 bit register
        uint32_t RCC_APB2ENR = RCC_BASE + 0x0C ;

        // so it has a value is 32 bits long
        // we go to bit 4 in the value. we can change it!
        // volatile is done a lot in hardware, it prevents C compiler from optomizing it away
        // setting to 1 and then turing off looks useless to the C compiler
        // but even though the value is not read, it is affecting the hardware clock
        // it might see *reg = 1 ... *reg = 0 and then only keep *reg = 0
        // clock is never turned on!! 
        volatile uint32_t *reg = (volatile uint32_t *) RCC_APB2ENR;

        // tldr, we go to addr, it has a big value, we change a part of it = clock now on
        // now lets flip this bit..ch
        *reg = set_bit(*reg,4u);

        
    }
}
