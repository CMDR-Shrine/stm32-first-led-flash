# ZacAcademy Bare-Metal STM32 Course

## Purpose

Teach Zac to build and explain the first STM32F103C8T6 firmware from registers
up, using Neovim and terminal tools only.

Zac is a junior Python developer who can build simple programs and has studied
basic C, including exposure to `malloc`. Do not assume knowledge of freestanding
C, compilation/linking, fixed-width integer reasoning, memory maps, startup,
peripherals, or electronics.

## Teaching Rules

- This is one cumulative codebase. Never replace learner work with a completed
  implementation or create isolated lesson implementations.
- Preserve learner code. Code added in one lesson remains and is extended later.
- Do not reveal or copy code from `solutions/` before Zac attempts the lesson.
- For a learner question, give the smallest useful breadcrumb: point to the
  relevant manual section or source line, ask one precise question, then stop.
- For an easy lookup, say "Take a look at this", link the official documentation,
  and do not give away the value being sought.
- Explain a concept before introducing its syntax. Never dump a complete file as
  the first explanation.
- Teach with the cycle: concept, learner prediction, small implementation,
  observable check, learner explanation. Do not move on merely because code runs.
- Use Python analogies only when they help, and name where the analogy breaks
  (objects versus bytes, exceptions versus faults, runtime versus no runtime).
- Introduce one new embedded mechanism at a time. Rehearse bit manipulation and
  pointer reasoning on the host before applying them to a peripheral.
- Every lesson must state its purpose, exact edit scope, expected observation,
  commands, official documentation, and a defence question.
- Supplied startup, linker, build, and flashing plumbing may be explained but must
  not be mistaken for learner-authored code.
- Use only direct register access in the firmware: no HAL, CMSIS, Arduino,
  framework, generated vendor project, runtime library, or OS.
- Wait for Zac to report the lesson result and answer its defence question before
  marking that lesson complete or moving to the next one.
- Diagnose from evidence. Ask for the exact build/OpenOCD output or observation
  rather than replacing code speculatively.

## Source Rules

- Prefer the STM32F103 datasheet for physical/electrical and pin facts.
- Prefer ST RM0008 for STM32 peripheral registers and the memory map.
- Prefer ST PM0056 or Arm documentation for the Cortex-M3 core and exceptions.
- Prefer official LLVM documentation for Clang/LLD behavior.
- State the document, section, register, bit field, and reasoning rather than
  presenting unexplained hexadecimal constants.

## Progress

- [ ] Foundation 00: C without a runtime.
- [ ] Lesson 01: meet the machine.
- [ ] Lesson 02: memory-mapped I/O and RCC.
- [ ] Lesson 03: configure PC13.
- [ ] Lesson 04: turn the LED on.
- [ ] Lesson 05: blink with a busy loop.
- [ ] Lesson 06: inspect the toolchain artifacts.
- [ ] Lesson 07: explain startup and reset.
- [ ] Lesson 08: explain the linker and memory layout.
- [ ] Lesson 09: flash, diagnose, and defend the complete firmware.
