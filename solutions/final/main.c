#include <stdint.h>

/* STM32F103 register addresses, taken directly from the reference manual. */
#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018u)
#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004u)
#define GPIOC_BSRR  (*(volatile uint32_t *)0x40011010u)
#define GPIOC_BRR   (*(volatile uint32_t *)0x40011014u)

#define RCC_IOPCEN  (1u << 4)
#define LED_PIN     13u

static void delay(volatile uint32_t count)
{
    while (count-- != 0u) {
        __asm__ volatile ("nop");
    }
}

int main(void)
{
    /* Supply a clock to GPIO port C. */
    RCC_APB2ENR |= RCC_IOPCEN;

    /* PC13 is configured by bits 23:20 of CRH.
     * MODE13 = 10: output, maximum speed 2 MHz
     * CNF13  = 00: general-purpose push-pull
     */
    GPIOC_CRH &= ~(0xFu << 20);
    GPIOC_CRH |=  (0x2u << 20);

    for (;;) {
        /* The Blue Pill LED is active-low. */
        GPIOC_BRR = (1u << LED_PIN);  /* PC13 low:  LED on  */
        delay(800000u);
        GPIOC_BSRR = (1u << LED_PIN); /* PC13 high: LED off */
        delay(800000u);
    }
}

