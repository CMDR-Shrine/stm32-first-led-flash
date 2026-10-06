# Lesson 03: Configure PC13 as an Output

## Where We Are

GPIOC now receives a clock, but PC13 still has its reset configuration. On an
STM32F1, each pin uses a four-bit `MODE`/`CNF` field. Pins 8 through 15 live in
the port's configuration-high register.

## Bit-Field Contract

Configure PC13 as:

- general-purpose output;
- push-pull;
- maximum output speed 2 MHz.

Derive the four-bit field from the `MODEy` and `CNFy` tables in RM0008. PC13 is
the sixth four-bit field in `GPIOx_CRH`, because that register begins at pin 8.
Preserve the other seven pin configurations.

## Assignment

Edit only `main.c`, after the RCC write.

1. Derive the GPIOC base address and `CRH` offset from RM0008.
2. Clear all four PC13 configuration bits.
3. Set only the bits required by the contract above.
4. Leave the infinite loop in place.

Do not write the output-level registers yet. Configuring the pin as an output
already enables its driver: it will drive the level stored in the output-data
register (`GPIOx_ODR`). Configuration and output level are separate settings.

## Documentation

- [RM0008 reference manual](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101-103-105-107-stm32f100-series-armbased-32bit-mcus-stmicroelectronics.pdf): §9.1 GPIO behavior and §9.2.2 `GPIOx_CRH`
- [STM32F103x8/xB datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf): PC13 pin characteristics

## Commands

```
make
make disasm
```

Expected result: the build passes. After flashing and reset, the LED may already
light: `GPIOx_ODR` resets to zero, and enabling PC13's push-pull output makes it
drive that low level. The board's LED is active-low. This is an effect of enabling
the output driver, not evidence that we explicitly wrote an output level.

Verify the configuration by reading `GPIOC_CRH` with the debugger. PC13's field
must match your chosen configuration, and the other fields must match their
values before your write. Lesson 04 will explicitly control the output level.

Defence question: why must the code clear the four-bit field before setting the
new value rather than only OR-ing in the desired bits?
