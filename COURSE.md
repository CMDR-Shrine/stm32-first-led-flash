# Cumulative Course Route

## Outcome

Build, flash, inspect, and explain a bare-metal LED blinker for the
STM32F103C8T6. The point is not merely to reproduce a working binary: you should
be able to defend every register write and describe how execution reaches it.

| Lesson | Area changed | New capability | Evidence |
|---|---|---|---|
| 00 | `lessons/00_.../bits.c` | Transfer basic C knowledge to fixed-width bits and addresses | Host-side bit-operation tests pass |
| 01 | `notes/01_machine.md` | Identify the chip, core, memories, and boot path | Built blank firmware and completed board facts |
| 02 | `main.c` | Perform a deliberate memory-mapped register write | GPIOC clock enabled in code |
| 03 | `main.c` | Configure PC13 as a push-pull output | Correct CRH bit field in the binary |
| 04 | `main.c` | Explicitly control an active-low output | Verify LED off, then on, in separate flashes |
| 05 | `main.c` | Create a visible state change over time | PC13 LED blinks continuously |
| 06 | `notes/06_toolchain.md` | Trace C through object, ELF, and raw binary | Disassembly and section map explained |
| 07 | `startup.c` | Explain reset, stack, vectors, `.data`, and `.bss` | Reset-to-`main` path defended |
| 08 | `linker.ld` | Place code and data in physical memories | ELF addresses matched to the memory map |
| 09 | whole project | Program, verify, diagnose, and defend it | Structural checks pass and board blinks |

## One Persistent Flow

```text
host-side C rehearsal: integers -> masks -> shifts -> pointer model
  ->
reset
  -> CPU loads stack pointer and Reset_Handler from the vector table
  -> Reset_Handler prepares RAM and calls main
  -> main enables the GPIOC peripheral clock
  -> main configures PC13 as an output
  -> main repeatedly drives PC13 low and high
  -> compiler turns C into Cortex-M3 Thumb instructions
  -> linker places vectors/code in flash and data/stack in SRAM
  -> OpenOCD asks the ST-Link to write and verify flash
```

## Graduation Standard

The final program must build without warnings, contain a vector table at
`0x08000000`, use SRAM ending at `0x20005000`, have no unresolved symbols or
host libraries, verify through OpenOCD, and visibly blink the onboard PC13 LED.
You must also be able to explain why the LED is active-low and why `volatile` is
required for peripheral access.

## Learning Rhythm

Each new layer follows the same cycle:

```text
concept -> predict -> implement -> run/observe -> explain
```

The course uses familiar Python comparisons where they clarify a concept, but it
does not pretend Python objects and C storage are equivalent. Hardware lessons
change only one new mechanism at a time.
