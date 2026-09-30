# ZacAcademy: First Bare-Metal Flash

This is one cumulative guided project for the STM32F103C8T6 Blue Pill. You will
build a blinking PC13 LED from an almost-empty `main.c`, then work backwards
through the compiler, reset sequence, vector table, linker, and flashing process
until every byte has a reason to exist.

The finished program uses no STM32 HAL, CMSIS, framework, runtime library, or
operating system. It accesses the hardware through registers described in the
chip documentation.

The course assumes basic programming experience, junior-level Python, and some C
syntax. It does not assume embedded experience. The foundation lesson bridges
from Python's managed runtime to freestanding C before you touch a register.

## Project Shape

```text
main.c          learner-owned application, extended lesson by lesson
startup.c       supplied boot plumbing, studied in Lesson 07
linker.ld       supplied memory layout, studied in Lesson 08
Makefile        terminal-only build, inspection, and flash commands
docs/           datasheet/manual/schematic/tool index and engineering workflow
lessons/        the route; start at Foundation 00 and do it in order
notes/          your observations and answers, including the first board log
solutions/      the verified blinker; inspect only after your own attempt
build/          generated objects, ELF, binary, HEX, map, and disassembly
```

## Hardware

| ST-Link | Blue Pill |
|---|---|
| 3.3 V | 3.3 V |
| GND | GND |
| SWDIO | PA13 |
| SWCLK | PA14 |
| NRST | optional |

Keep `BOOT0` at `0`. Do not connect the ST-Link 5 V pin to a 3.3 V pin.

## Workflow

Open Neovim from this directory:

```sh
nvim .
```

The recurring terminal commands are:

```sh
make           # compile and link
make inspect   # show the sections and important symbols
make disasm    # generate build/blink.disasm
make flash     # program, verify, and start the board
make check     # perform final structural firmware checks
```

`make flash` requires the connected ST-Link and OpenOCD. All other commands work
without the board attached.

## Start

Begin with [`lessons/00_c_without_a_runtime`](lessons/00_c_without_a_runtime/README.md),
then continue to Lesson 01. Do not copy the final solution forward. Each lesson
gives one assignment, its documentation, an observable result, and a defence
question. Your code remains in the root project and later lessons build on it.

Embedded hardware cannot report whether your eyes saw an LED, so some submissions
combine a build check with a manual observation. Report that observation and your
answer to the defence question before moving on.
