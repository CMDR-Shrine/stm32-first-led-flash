# Lesson 04: Explicitly Turn the LED Off and On

## Where We Are

PC13 is an output, and the LED may already be on because the output-data register
resets to zero. This lesson makes the output level an explicit choice: first turn
the LED off, verify that state, then change your program to turn it on.

GPIO offers bit-set and bit-reset registers. Writing a one to a selected command
bit changes the corresponding output-data bit; writing zero does nothing. These
are atomic operations: the hardware changes the selected output without a
separate read and write of the complete output-data register.

The Blue Pill's onboard LED is active-low: current flows when PC13 is driven low.
This is a property of the board wiring, not of GPIO in general.

## Assignment

Edit only `main.c`.

1. Keep Lesson 03's push-pull configuration. Find the GPIO bit-set register
   (`GPIOx_BSRR`) address and the `BS13` field description in RM0008.
2. After configuring PC13, write the command that sets its output-data bit to
   one. Keep the infinite loop. Build and flash: the active-low LED should stay
   off once initialization finishes. A brief flash during startup is possible.
3. Explain why a high output turns this LED off before continuing.
4. Find the GPIO bit-reset register (`GPIOx_BRR`) address and its pin-13 field.
   Change the output command to drive PC13 low. Build and flash again: the LED
   should remain on. Preserve your configuration and other learner code.

Do not add a delay or blinking yet.

## Documentation

- [RM0008 reference manual](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101-103-105-107-stm32f100-series-armbased-32bit-mcus-stmicroelectronics.pdf): §9.2.5 `GPIOx_BSRR` and §9.2.6 `GPIOx_BRR`
- [Common Blue Pill schematic](https://stm32-base.org/assets/pdf/boards/original-schematic-STM32F103C8T6-Blue_Pill.pdf): trace VCC3V3 through the LED/resistor to PC13
- [STM32F103x8/xB datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf): GPIO output limits

## Commands

Run:

```sh
make
```

Submit on hardware:

```sh
make flash
```

Expected observations: the first version explicitly leaves the PC13 LED off;
the second explicitly leaves it on. These are two separate build/flash checks,
not an automatic off/on sequence. No delay or timer is needed yet.

Defence question: why does writing `1` to a reset-register bit drive the output
low instead of storing the number one as the pin's output level?
