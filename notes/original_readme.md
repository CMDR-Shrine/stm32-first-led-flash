29/09/2026
board is STM32F103C8T6

I soldered up all the header cables with my new pinecil v2
Then wired up the stm32 to my programmer, plugged it in got green light for power
It also has a pc13 light, that aint light up tho

I also found this [info]("https://microcontrollerslab.com/stm32f103c8t6-blue-pill-pinout-peripherals-programming-features/")
    - I confirmed that pin PC13 is an led!
    - apparently its Risc architecture
    - Lets try to get it to flash first
    - 72mhz cpu
    - 64/128 kb flash mem
    - it also has like 2 boot modes??
    - also looks like it does have abitilty to transmit data over micro usb too?

## First bare-metal program: blink PC13

This project deliberately uses no HAL, CMSIS, framework, runtime library, or
operating system. `startup.c` supplies the vector table and reset code,
`linker.ld` describes the chip's flash/RAM, and `main.c` writes peripheral
registers directly.

### ST-Link SWD wiring

With power disconnected while changing wires:

| ST-Link | Blue Pill |
|---------|-----------|
| 3.3 V   | 3.3 V     |
| GND     | GND       |
| SWDIO   | PA13      |
| SWCLK   | PA14      |
| NRST (optional) | R/NRST |

Keep the board's `BOOT0` jumper at `0`. Do not connect the ST-Link's 5 V pin to
a 3.3 V pin.

### Build and flash

Edit in Neovim:

```sh
nvim main.c
```

Build using Clang's bare-metal ARM target:

```sh
make
```

Flash and reset through the ST-Link (requires `openocd`):

```sh
make flash
```

The output files are placed in `build/`. The LED is wired active-low, so a low
PC13 output turns it on. The chip starts from its internal 8 MHz oscillator;
the delay is intentionally just an approximate busy loop for this first test.
