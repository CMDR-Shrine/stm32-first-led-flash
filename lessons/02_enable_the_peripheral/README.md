# Lesson 02: Memory-Mapped I/O and RCC

## Where We Are

The processor can execute code, but GPIO port C is not yet clocked. STM32 saves
power by disabling many peripheral clocks after reset. Before GPIOC can respond,
its enable bit in the Reset and Clock Control peripheral must be set.

## Register Contract

Use RM0008 to derive, rather than copy blindly:

| Question | Where to find it |
|---|---|
| RCC base address | Memory map |
| APB2ENR offset | RCC register map |
| GPIOC enable bit | RCC APB2 peripheral clock enable register |

The register access must be 32-bit and `volatile`. The update must preserve all
unrelated bits.

## Assignment

Edit only `main.c`.

1. Include the standard fixed-width integer types.
2. Create a direct expression for the RCC APB2 enable register using its base
   address plus offset.
3. In `main`, set the GPIOC enable bit with a read-modify-write operation.
4. Keep the final infinite loop.

Do not configure PC13 yet. No visible LED result is expected.

## Documentation

- [RM0008 reference manual](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101-103-105-107-stm32f100-series-armbased-32bit-mcus-stmicroelectronics.pdf): §3.3 memory map, §7.3 RCC registers, and §7.3.7 `RCC_APB2ENR`
- [ISO C11 committee draft](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf): section 6.7.3, type qualifiers and `volatile`

## Commands

Run and submit:

```sh
make
make disasm
nvim build/blink.disasm
```

Find the RCC address in the disassembly's literal data before reporting the
lesson complete.

Defence question: what incorrect optimization could be legal if the peripheral
pointer were not `volatile`?
