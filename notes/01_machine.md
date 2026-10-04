# Lesson 01 Notes: Meet the Machine

Fill these in from the official documentation. Include the document section or
table beside each answer.
- apbr2 bus thing address offset: 0x0C
- RCC (reset and clock constrol) Boundary addr is: 0x4002 1000 - 0x4002 13FF
- Exact MCU marking: **STM32F103CBT6**
- Processor core: Arm® 32-bit Cortex®-M3 CPU core 
- Instruction set used by this project: Thumb instruction set
- Flash start address: 0x0800 0000 n [DS5319, §4 “Memory mapping”](<https://www.st.com/resource/en/datasheet/stm32f103c8.pdf>)
- Guaranteed flash size for the CB part: 128 Kbytes [DS5319, Table 2](<https://www.st.com/resource/en/datasheet/stm32f103c8.pdf>).  
- SRAM start address: its here s 0x2000 0000    [DS5319, Table 2](<https://www.st.com/resource/en/datasheet/stm32f103c8.pdf>) 
- SRAM size: 20Kbytes
- Initial clock source after reset: internal RC 8 MHz oscillator isselected as the default CPU clock on reset [DS5319, §2.3.7 “Clocks and startup](<https://www.st.com/resource/en/datasheet/stm32f103c8.pdf>)
- Initial clock frequency: 8Mhz [DS5319, §2.3.7 “Clocks and startup](<https://www.st.com/resource/en/datasheet/stm32f103c8.pdf>)
- Onboard LED pin: pc13
- Electrical level that turns the LED on: it needs 0 v.
    - 3.3 V > resistor > LED > PC13 > GPIO transistor > ground
    - pc13 is inside the cpu, its a transistor that can connect to ground

## Build observations

- ELF entry-point address:
- Address of `.isr_vector`:
- Initial stack-pointer value:
- Address of `Reset_Handler`:
- Address of `main`:

## Defence answer

Why can an x86-64 laptop compile a program that it cannot itself execute?


q1: size is 4K for the blink.bin, 8k for the blink.elf not sure what he elf is, i though the bin was the binary

q2: entry point addr is 0x8000051 and vector table is at 08000000

q3: the reset handler is 08000050 and the estack is 20005000, and main is at 080000ac



Defence question: why can an x86-64 laptop compile a program that it cannot execute

simple, we have a special compiler to take our c code and then translate it to assembely/machine instructions

the compiler decides the format not my computers x86 instruciton set

its like saying 'why can a doctor make a cloan of a sheep if he himself is not a sheep'

one does not need to be a sheep to clone/create one, same goes for computers and C




