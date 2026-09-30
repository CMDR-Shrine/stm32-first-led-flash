# Lesson 06 Notes: Toolchain

- Which command translates each `.c` file?
- Why does it use `--target=arm-none-eabi`?
- What does `-mcpu=cortex-m3` permit the compiler to emit?
- What is contained in an `.o` file?
- What extra information does the `.elf` contain compared with `.bin`?
- Which tool places sections at their final addresses?
- Which file records the linker's placement decisions?
- Which output is actually written into flash?

## Defence answer

Why is the firmware's ELF entry point not enough, by itself, to make a
Cortex-M3 begin there after reset?

