# Lesson 01: Meet the Machine

## Where We Are

Before changing a register, establish what machine is actually connected and
what the existing build plumbing produces. The starter `main.c` deliberately
does nothing forever; that is still a valid bare-metal program.

## Assignment

Do not edit firmware in this lesson.

1. Run the build and inspect the reported file size.
2. Run the ELF inspection command and find the entry point, vector table,
   initial stack value, `Reset_Handler`, and `main`.
3. Complete `notes/01_machine.md` from the documentation and command output.
4. Do not copy values from `solutions/`.

This lesson distinguishes three things that are easy to blur together: the
STM32 chip, its Cortex-M3 processor core, and the Blue Pill circuit board.

## Documentation

- [`docs/README.md`](../../docs/README.md): document roles and bring-up checklist
- [STM32F103 documentation index](https://www.st.com/en/microcontrollers-microprocessors/stm32f103/documentation.html)
- [STM32F103x8/xB datasheet](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)
- [RM0008 reference manual](https://www.st.com/resource/en/reference_manual/cd00171190-stm32f101-103-105-107-stm32f100-series-armbased-32bit-mcus-stmicroelectronics.pdf)
- [Clang cross-compilation guide](https://clang.llvm.org/docs/CrossCompilation.html)

Use DS5319 §2.3.7, §2.3.8, §3, and §4. Use RM0008 §7 for the reset clock. The active-low onboard LED is a
board-level fact: confirm it from the board wiring or measurement, because the
MCU datasheet cannot describe what a third-party board connects to PC13.

## Commands

Run:

```sh
make clean
make
```

Submit your observations:

```sh
make inspect
```

## Expected Observation

The project builds an ARM ELF, binary, and HEX file without warnings. No LED
change is expected because `main` contains no peripheral writes.

Defence question: why can an x86-64 laptop compile a program that it cannot
itself execute?
