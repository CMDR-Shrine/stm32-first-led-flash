#!/bin/sh
set -eu

elf=${1:?usage: check_firmware.sh firmware.elf firmware.bin}
bin=${2:?usage: check_firmware.sh firmware.elf firmware.bin}

fail()
{
    printf 'FAIL: %s\n' "$1" >&2
    exit 1
}

[ -f "$elf" ] || fail "missing ELF: $elf"
[ -f "$bin" ] || fail "missing binary: $bin"

machine=$(llvm-readelf -h "$elf" | awk -F: '/Machine:/ {gsub(/^[ \t]+/, "", $2); print $2}')
[ "$machine" = "ARM" ] || fail "ELF machine is '$machine', expected ARM"

vector_address=$(llvm-readelf -S "$elf" | awk '$3 == ".isr_vector" {print $5}')
[ "$vector_address" = "08000000" ] || fail ".isr_vector is at 0x$vector_address"

stack_address=$(llvm-nm "$elf" | awk '$3 == "_estack" {print $1}')
[ "$stack_address" = "20005000" ] || fail "_estack is at 0x$stack_address"

reset_address=$(llvm-nm "$elf" | awk '$3 == "Reset_Handler" {print $1}')
[ -n "$reset_address" ] || fail "Reset_Handler is absent"

main_address=$(llvm-nm "$elf" | awk '$3 == "main" {print $1}')
[ -n "$main_address" ] || fail "main is absent"

undefined=$(llvm-nm -u "$elf")
[ -z "$undefined" ] || fail "firmware has undefined symbols: $undefined"

binary_size=$(wc -c < "$bin")
[ "$binary_size" -le 65536 ] || fail "binary exceeds 64 KiB"

printf 'PASS: ARM ELF\n'
printf 'PASS: vector table at 0x%s\n' "$vector_address"
printf 'PASS: stack top at 0x%s\n' "$stack_address"
printf 'PASS: Reset_Handler at 0x%s\n' "$reset_address"
printf 'PASS: main at 0x%s\n' "$main_address"
printf 'PASS: no undefined symbols\n'
printf 'PASS: binary is %s bytes (limit 65536)\n' "$binary_size"
