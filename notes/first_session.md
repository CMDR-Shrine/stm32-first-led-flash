# First Session Board Log

29/09/2026

Board is STM32F103C8T6.

I soldered up all the header cables with my new Pinecil V2. Then I wired the
STM32 to my programmer, plugged it in, and got a green light for power. It also
has a PC13 light, but that was not lit.

Things found before the first flash:

- PC13 is connected to an LED.
- The chip contains an Arm Cortex-M3 RISC processor.
- It can run at up to 72 MHz.
- The family has 64/128 KiB flash variants.
- It has multiple boot modes.
- The board exposes USB, though USB requires firmware and is not the first goal.

First successful tool result:

```text
STLINK V2J23S4
Target voltage: about 3.25 V
Cortex-M3 r2p0 detected
device id: 0x20030410
reported flash size: 128 KiB
Programming Finished
Verified OK
```

The initial working blinker was 288 bytes. It is preserved in
`solutions/final/`; the root `main.c` was then returned to a blank learner
starting point.

Before beginning the course, all 128 flash pages reported by the probe were
erased individually. The first words at `0x08000000` and last words near
`0x08020000` both read back as `0xffffffff`. With no valid reset vector, the core
entering HardFault is the expected blank-device state. The ST-Link probe firmware
was not modified.
