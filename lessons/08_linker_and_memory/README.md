# Lesson 08: Linker and Memory

## Where We Are

The compiler produces relocatable pieces; it does not know the final physical
addresses. `linker.ld` tells LLD which memories exist and where each section must
live.

## Memory Contract

Explain every output section and symbol in `linker.ld`:

- `FLASH` begins at the STM32 flash alias used for normal boot.
- `RAM` begins at the SRAM address and has the C8 device's documented size.
- `.isr_vector` is retained even when section garbage collection is enabled.
- `.text` and read-only data execute/read from flash.
- `.data` runs from SRAM but has an initial image stored in flash.
- `.bss` reserves zero-initialized SRAM without consuming flash-file bytes.
- `_estack` is one address beyond the highest byte of SRAM because the stack
  grows downward.

## Assignment

Do not change addresses merely to make a check pass. Derive each from the
datasheet and match it against `linker.ld`, `build/blink.map`, and
`make inspect`. Add explanatory comments to the linker script in your own words
where the purpose was previously unclear.

## Documentation

- [STM32F103x8/xB datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf): memory map and memory sizes
- [LLD ELF linker documentation](https://lld.llvm.org/ELF/linker_script.html)
- [GNU linker-script command language](https://sourceware.org/binutils/docs/ld/Scripts.html) (the syntax LLD implements)

## Commands

```sh
make clean
make inspect
nvim linker.ld build/blink.map
```

Expected result: flash sections occupy addresses beginning at `0x08000000`; RAM
sections and the stack use the `0x20000000` region without overlap.

Defence question: why does `.data` use `> RAM AT > FLASH`, while `.bss` is marked
`NOLOAD`?

