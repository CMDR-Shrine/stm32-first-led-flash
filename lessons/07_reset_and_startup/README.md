# Lesson 07: Reset and Startup

## Where We Are

`main` never appears by magic. After reset, a Cortex-M3 reads two words from the
vector table: its initial main stack pointer and the address of its reset handler.
The supplied `startup.c` establishes that path and prepares C's RAM state.

## Startup Contract

Trace these responsibilities in `startup.c`:

1. Place the vector table in its named input section.
2. Put the top of SRAM in vector slot zero.
3. Put a Thumb reset-handler address in vector slot one.
4. Copy initialized `.data` values from their flash image into SRAM.
5. Zero the `.bss` region.
6. Call `main`; never depend on it returning.
7. Trap unexpected exceptions in a handler that is easy to halt and inspect.

## Assignment

Do not alter behavior first. Open `startup.c` beside the generated disassembly
and linker map. Annotate your own notes with the source line and addresses for
each responsibility above. Then temporarily add one initialized global and one
zero-initialized global to `main.c`, rebuild, and observe how `.data` and `.bss`
change. Remove the experiment afterward.

## Documentation

- [PM0056 Cortex-M3 programming manual](https://www.st.com/resource/en/programming_manual/pm0056-stm32f10xxx20xxx21xxxl1xxxx-cortex-m3-programming-manual-stmicroelectronics.pdf): §2 programmer's model and §2.3 exception model
- [Arm Cortex-M3 resources](https://developer.arm.com/community/arm-community-blogs/b/architectures-and-processors-blog/posts/arm-mcu-resources---documentation)

## Commands

```sh
make clean
make inspect
make disasm
```

Expected result: vector slot zero contains the end of SRAM, and slot one points
at `Reset_Handler` with its Thumb-state bit set.

Defence question: why does initialized writable data occupy space in both flash
and SRAM?
