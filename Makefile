TARGET   := blink
BUILD    := build
CC       := clang
HOST_CC  := clang
OBJCOPY  := llvm-objcopy
SIZE     := llvm-size
READELF  := llvm-readelf
OBJDUMP  := llvm-objdump
NM       := llvm-nm

CPUFLAGS := --target=arm-none-eabi -mcpu=cortex-m3 -mthumb
CFLAGS   := $(CPUFLAGS) -std=c11 -Os -g3 -ffreestanding \
            -fno-builtin -fdata-sections -ffunction-sections \
            -fno-unwind-tables -fno-asynchronous-unwind-tables \
            -Wall -Wextra -Werror
LDFLAGS  := $(CPUFLAGS) -fuse-ld=lld -nostdlib \
            -Wl,-T,linker.ld -Wl,-Map,$(BUILD)/$(TARGET).map \
            -Wl,--gc-sections

SOURCES  := startup.c main.c
OBJECTS  := $(SOURCES:%.c=$(BUILD)/%.o)

.PHONY: all clean flash size inspect disasm check foundation

all: $(BUILD)/$(TARGET).bin $(BUILD)/$(TARGET).hex size

foundation: | $(BUILD)
	$(HOST_CC) -std=c11 -O0 -g3 -Wall -Wextra -Werror \
		lessons/00_c_without_a_runtime/bits.c \
		lessons/00_c_without_a_runtime/test_bits.c \
		-o $(BUILD)/foundation
	$(BUILD)/foundation

$(BUILD):
	mkdir -p $@

$(BUILD)/%.o: %.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/$(TARGET).elf: $(OBJECTS) linker.ld
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD)/$(TARGET).hex: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

size: $(BUILD)/$(TARGET).elf
	$(SIZE) $<

inspect: $(BUILD)/$(TARGET).elf
	$(READELF) -h -S $<
	$(NM) -n $<

disasm: $(BUILD)/$(TARGET).disasm

$(BUILD)/$(TARGET).disasm: $(BUILD)/$(TARGET).elf
	$(OBJDUMP) -d -s $< > $@
	@echo "wrote $@"

check: $(BUILD)/$(TARGET).bin
	sh tools/check_firmware.sh $(BUILD)/$(TARGET).elf $(BUILD)/$(TARGET).bin

# For an ST-Link connected over SWD. OpenOCD must be installed.
# Writing AIRCR requests a Cortex-M software reset, so NRST need not be wired.
flash: $(BUILD)/$(TARGET).elf
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg \
		-c "init" -c "halt" -c "program $< verify" \
		-c "mww 0xE000ED0C 0x05FA0004" -c "shutdown"

clean:
	rm -rf $(BUILD)
