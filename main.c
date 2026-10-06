#include <stdint.h>

uint32_t clear_bit(uint32_t value, uint32_t bit)
{
    value = value & ~(1u << bit);
    return value ;
}

uint32_t set_bit(uint32_t value, uint32_t bit)
{
    value = value | (1u << bit);
    return value;
}

uint32_t replace_nibble(uint32_t value, uint32_t shift, uint32_t nibble)
{
    // 15 in binary is 1111, make sense?
    // clears values in rage, leaves outer safe
    value = value & ~(15u << shift);
    nibble = nibble & 15u;
    return value | (nibble << shift);
}


int main(void)
{
    for (;;) {
        uint32_t RCC_BASE = 0x40021000;
        uint32_t RCC_APB2ENR = RCC_BASE + 0x18;
        // so it has a value is 32 bits long
        // we go to bit 4 in the value. we can change it!
        // volatile is done a lot in hardware, it prevents C compiler from optomizing it away
        // setting to 1 and then turing off looks useless to the C compiler
        // but even though the value is not read, it is affecting the hardware clock
        // it might see *reg = 1 ... *reg = 0 and then only keep *reg = 0
        // clock is never turned on!! 
        volatile uint32_t *reg = (volatile uint32_t *) RCC_APB2ENR;
        *reg = set_bit(*reg,4u);

        /// now the clock is on... PC13
        /// Port C pin 13!
        /// Port C is: between 0x4001 1000 - 0x4001 13FF GPIO Port C
        /// we are using CRH (conf register high)
        /// controlls pins 8-15
        /// each pin gets 4 bits
        /// GPIOC_CRH = gen purp input output group C, confi register high
        uint32_t START_PORT_C = 0x40011000;
        uint32_t GPIOC_CRH = START_PORT_C + 0x04;
        // we are at the right place in memory now, 
        // time to mess with the value 20 bits from the start

        // create a pointer to the address: we use a cast, to tell
        // (volatile uint32_t *) GPIOC_CRH;  tells C that the value of GPIOC_CRH is
        // to be treated as a pointer not an int. We cast from int to pointer
        volatile uint32_t *pc13_config_reg = (volatile uint32_t *) GPIOC_CRH;
        // then actually read the hardware register with *, and change its value to bla bla bla 0000 bla bla bla
        *pc13_config_reg = replace_nibble(*pc13_config_reg,20u,0u);

        // now config the cleared pc13_config_reg see table 20 of RM0008
        // 2 u = 0010
        // 00 = gpo push pull
        // 10 = max speed 2mhz
        // 0010 = 2u boom!
        uint32_t PC13_CONFIG = 2u;
        // actually we could just have made one call, replacing 0u with 2u
        // the func clears the bits anyway! but dw
        *pc13_config_reg = replace_nibble(*pc13_config_reg,20u,PC13_CONFIG);

        // now to toggle it on/off: we go to Port bit set/reset register at 0x10
        // BS13, 13th bit, sets the ODR bit
        // BR13 the 29th bit, resets ODR the bit
        // port bit set/reset register below
        uint32_t GPIOx_BSRR = START_PORT_C + 0x10;
        volatile uint32_t *gpio_bsrr_reg = (volatile uint32_t *) GPIOx_BSRR;
        // this turns it off!!!!
        // brining up pc13 to 3.3 v while 3.3 v is at the other side == off!
       *gpio_bsrr_reg = set_bit(*gpio_bsrr_reg, 13u); // turn off 

//        *gpio_bsrr_reg = set_bit(*gpio_bsrr_reg, 29u); // turn on





        
    }
}
