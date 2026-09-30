# Lesson 06: Follow the Toolchain

## Where We Are

The application works. Now trace how two C files become bytes in flash. This
lesson changes notes, not firmware behavior.

## Artifact Contract

You must be able to distinguish:

| Artifact | Role |
|---|---|
| `.c` | Human-authored C source |
| `.o` | Relocatable machine code and metadata for one source file |
| `.elf` | Linked addresses, executable sections, symbols, and debug data |
| `.map` | Text report of the linker's placement decisions |
| `.bin` | Flat loadable bytes without symbols or addresses |
| `.hex` | Addressed textual representation of loadable bytes |

## Assignment

1. Read each compiler and linker invocation printed by `make clean && make`.
2. Generate the disassembly and locate `Reset_Handler`, `main`, the RCC address,
   and the GPIOC address.
3. Compare the byte size of `.elf` and `.bin`; explain why they differ.
4. Complete `notes/06_toolchain.md`.

## Documentation

- [Clang cross-compilation guide](https://clang.llvm.org/docs/CrossCompilation.html)
- [LLVM toolchain overview](https://clang.llvm.org/docs/Toolchain.html)
- [llvm-objdump command guide](https://llvm.org/docs/CommandGuide/llvm-objdump.html)

## Commands

```sh
make clean
make
make inspect
make disasm
nvim build/blink.disasm
nvim build/blink.map
```

Expected result: you can point from each meaningful C operation to corresponding
Cortex-M3 instructions or literal data.

Defence question: why is the ELF entry point not enough, by itself, to make a
Cortex-M3 begin there after reset?

