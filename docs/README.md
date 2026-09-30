# Engineering Documents and How to Use Them

Embedded work begins by collecting the documents for the exact component and
board. Do not try to read every page front to back. Start with a question, choose
the document that owns that question, then record the section or table that
supports the decision.

## Document Set

| Document | Use it for | First useful sections |
|---|---|---|
| [DS5319: STM32F103x8/xB datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf) | Part variants, pinout, package, memory sizes, voltage/current limits, electrical characteristics | §2.3.7 clocks/startup, §2.3.8 boot modes, §3 pinouts, §4 memory map, §5 electrical characteristics |
| [RM0008: STM32F10xxx reference manual](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101-103-105-107-stm32f100-series-armbased-32bit-mcus-stmicroelectronics.pdf) | STM32 peripheral behavior, register addresses, fields, reset values, and allowed sequences | §3 memory map, §7 RCC, §9 GPIO |
| [PM0056: Cortex-M3 programming manual](https://www.st.com/resource/en/programming_manual/pm0056-stm32f10xxx20xxx21xxxl1xxxx-cortex-m3-programming-manual-stmicroelectronics.pdf) | Processor registers, reset/exception model, vector table, instruction set, SysTick, and core peripherals | §2 programmer's model, §2.3 exception model, §3 instruction set, §4 core peripherals |
| [ES096: STM32F103x8/B errata](https://www.st.com/resource/en/errata_sheet/es096-stm32f101x8b-stm32f102x8b-and-stm32f103x8b-mediumdensity-device-limitations-stmicroelectronics.pdf) | Cases where silicon differs from the datasheet/reference manual | Read identification first; search for each peripheral before relying on it |
| [Common Blue Pill schematic](https://stm32-base.org/assets/pdf/boards/original-schematic-STM32F103C8T6-Blue_Pill.pdf) | Board connections: LED, resistor, crystal, USB, regulator, boot jumpers, and SWD header | Trace VCC3V3 through the LED/resistor to PC13 |
| [OpenOCD user guide](https://openocd.org/doc/html/index.html) | Probe configuration, target control, flash programming, and debug commands | Debug Adapter Configuration and Flash Commands |
| [Clang cross-compilation guide](https://clang.llvm.org/docs/CrossCompilation.html) | Target triple, CPU selection, and freestanding cross-compilation | Target Triple and CPU/FPU/ABI |
| [LLD linker-script guide](https://lld.llvm.org/ELF/linker_script.html) | How input sections and symbols are placed in MCU memories | Symbols and section placement |
| [ISO C11 committee draft](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf) | Integer types, shifts, bitwise operations, pointers, and `volatile` | §6.2.6, §6.5, §6.7.3, §7.20.1 |

The Blue Pill is a third-party board family, not one tightly controlled ST board
design. Its schematic is evidence for a common layout, not a guarantee about
every clone. Confirm the chip marking, component placement, and important nets on
the physical board. The observed PC13 LED and 3.26 V probe voltage are part of
this project's evidence.

## Which Document Answers the Question?

- “Can PC13 safely source this current?” → datasheet electrical characteristics.
- “Which bits configure PC13?” → RM0008 GPIO chapter.
- “Why are the first two flash words special?” → PM0056 exception model.
- “Why is the onboard LED active-low?” → board schematic.
- “Does this silicon revision have a peripheral bug?” → ES096 errata.
- “What does `--target=arm-none-eabi` mean?” → Clang documentation.
- “Why did bytes land at `0x08000000`?” → linker script plus LLD docs.
- “How did the ST-Link erase/program it?” → OpenOCD docs.

## Normal First-Bring-Up Checklist

1. Read the exact package marking and record the board revision.
2. Inspect for solder bridges, orientation mistakes, and supply shorts before
   power.
3. Read the schematic; identify power, ground, reset, boot straps, SWD, clock,
   and the first observable output.
4. Check supply limits in the datasheet; power the board and measure or observe
   the target voltage.
5. Connect SWD and ask the probe to identify the core and device without writing
   flash.
6. Read the datasheet, reference manual, programming manual, and relevant errata
   sections for the one feature being brought up.
7. Build the smallest change with one observable claim.
8. Inspect the ELF, map, and disassembly; program it, verify readback, and record
   the result.
9. Change one variable at a time when diagnosing a failure.

This course follows that checklist. The first successful session is preserved in
`notes/first_session.md`; new observations belong in the lesson notes rather than
remaining only in terminal scrollback.

