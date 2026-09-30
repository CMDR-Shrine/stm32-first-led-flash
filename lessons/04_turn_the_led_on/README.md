# Lesson 04: Turn the LED On

## Where We Are

PC13 is an output, so the program can now produce its first visible effect. GPIO
offers atomic bit-set and bit-reset registers, allowing one pin to change without
a read-modify-write of the complete output register.

The Blue Pill's onboard LED is active-low: current flows when PC13 is driven low.
This is a property of the board wiring, not of GPIO in general.

## Assignment

Edit only `main.c`.

1. Derive the GPIO bit-reset register address from the GPIO register map.
2. Write a one at the position corresponding to pin 13.
3. Keep the final infinite loop so the state remains observable.
4. Build and flash the program.

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

Expected observation: the onboard PC13 LED remains steadily lit after the
software reset.

Defence question: why does writing `1` to a reset-register bit drive the output
low instead of storing the number one as the pin's output level?
