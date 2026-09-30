# Lesson 05: Blink with a Busy Loop

## Where We Are

A steady LED proves clocking, pin configuration, register addressing, flashing,
and boot all work. Blinking adds time and repeated state changes.

For this first version, timing may be an imprecise busy loop. The chip is still
using its reset-default internal oscillator; exact timing belongs in a later
timer lesson.

## Function Contract

```c
static void delay(volatile uint32_t count)
```

The function repeatedly consumes work until `count` reaches zero. It returns
nothing and touches no peripheral. The generated code must retain the loop under
optimization.

## Assignment

Edit only `main.c`.

1. Add the delay function above `main`.
2. Derive the GPIO bit-set register address.
3. Replace the final empty loop with four repeated actions: LED on, delay, LED
   off, delay.
4. Choose a count that makes both states visible; then build and flash.

## Documentation

- [RM0008 reference manual](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101-103-105-107-stm32f100-series-armbased-32bit-mcus-stmicroelectronics.pdf): §7 RCC reset clock and §9.2 GPIO registers
- [Clang language extensions](https://clang.llvm.org/docs/LanguageExtensions.html): inline assembly, if you choose to use a `nop`

## Commands

```sh
make
make flash
```

Expected observation: the PC13 LED alternates visibly between on and off and
continues without host involvement.

Defence question: why is this delay unsuitable when accurate timing or useful
work during the wait is required?
