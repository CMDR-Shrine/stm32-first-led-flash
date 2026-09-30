# Foundation 00: C Without a Runtime

## Where We Are

You know basic C and have seen facilities such as `malloc`. On a normal computer,
C usually runs as a process: an operating system loads it, a C runtime prepares
it, and a standard library offers allocation, files, clocks, and output.

This STM32 firmware is compiled as a **freestanding** program with `-nostdlib`.
After reset there is no process, terminal, filesystem, or pre-existing allocator.
There are just processor registers, flash bytes, SRAM bytes, and peripherals.

That does not make dynamic allocation physically impossible. `malloc` is code,
not a CPU instruction. To use it, someone must choose a heap region and supply an
allocator. This first firmware has neither, and a fixed-size blinker does not need
one. We will use compile-time storage and the stack instead.

## Python-to-Freestanding Bridge

| Familiar idea | What changes here |
|---|---|
| Python integer | A `uint32_t` is exactly 32 bits and wraps modulo 2^32 |
| Python object/reference | C exposes typed storage and raw addresses directly |
| Python garbage collection | No runtime tracks object lifetimes or frees memory |
| Python library call | Only functions we compile and link actually exist |
| Exception traceback | A processor fault enters an exception handler |
| `time.sleep()` | No OS scheduler or clock API exists yet |

The operations needed for GPIO are small: shifts position bits, masks select
bits, and AND/OR replace selected fields while preserving everything else.

## Function Contracts

Edit only `bits.c` in this folder.

```c
uint32_t set_bit(uint32_t value, uint32_t bit);
```

Return `value` with bit number `bit` set to one. Preserve every other bit.

```c
uint32_t clear_bit(uint32_t value, uint32_t bit);
```

Return `value` with bit number `bit` cleared to zero. Preserve every other bit.

```c
uint32_t replace_nibble(uint32_t value, uint32_t shift, uint32_t nibble);
```

Replace the four bits beginning at `shift` with the low four bits of `nibble`.
Preserve all other bits. Inputs in the tests use valid shift counts.

Before editing, predict these on paper:

```text
1u << 4
0x0000001fu with bit 4 cleared
0xffffffffu with the four bits at shift 20 replaced by 0x2
```

## Documentation

- [ISO C11 committee draft](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf): sections 6.2.6.1, 6.5.7, 6.5.10, 6.5.12, and 7.20.1.1
- [Clang cross-compilation guide](https://clang.llvm.org/docs/CrossCompilation.html): hosted versus bare-metal target context

## Commands

Run before editing to see a purposeful failure, then rerun after each function:

```sh
make foundation
```

This particular executable runs on your laptop so it can give immediate test
feedback. It rehearses the same C expressions the firmware will later execute on
the Cortex-M3; it is not STM32 firmware.

Expected result after completion:

```text
PASS: set_bit
PASS: clear_bit
PASS: replace_nibble
```

Defence question: why is `malloc` unavailable in our firmware even though it is
part of the C library you used in hosted programs?

