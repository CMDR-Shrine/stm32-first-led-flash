#include <stdint.h>

/* Supplied course plumbing. You will study every part in Lesson 07. */

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);
void Reset_Handler(void);
static void Default_Handler(void);

/* Cortex-M3 exception table. Peripheral interrupts remain disabled. */
__attribute__((used, section(".isr_vector"), aligned(256)))
const uintptr_t vector_table[] = {
    (uintptr_t)&_estack,
    (uintptr_t)Reset_Handler,
    (uintptr_t)Default_Handler, /* NMI */
    (uintptr_t)Default_Handler, /* HardFault */
    (uintptr_t)Default_Handler, /* MemManage */
    (uintptr_t)Default_Handler, /* BusFault */
    (uintptr_t)Default_Handler, /* UsageFault */
    0u, 0u, 0u, 0u,
    (uintptr_t)Default_Handler, /* SVCall */
    (uintptr_t)Default_Handler, /* Debug monitor */
    0u,
    (uintptr_t)Default_Handler, /* PendSV */
    (uintptr_t)Default_Handler, /* SysTick */
};

void Reset_Handler(void)
{
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    while (dst < &_edata) {
        *dst++ = *src++;
    }

    for (dst = &_sbss; dst < &_ebss; ++dst) {
        *dst = 0u;
    }

    (void)main();
    for (;;) {
    }
}

static void Default_Handler(void)
{
    for (;;) {
    }
}
