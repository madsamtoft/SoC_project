file = main

mac:
	riscv32-unknown-elf-gcc tests/$(file).c -o out/$(file).out -Os -nostartfiles
win:
	riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 tests/$(file).c -o out/$(file).out -O2 -nostartfiles -nodefaultlibs -nostdlib -mno-relax
win-size:
	riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 tests/$(file).c -o out/$(file).out -Os -nostartfiles -nodefaultlibs -nostdlib
win-asm:
	riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 tests/$(file).c -o out/$(file).s -S -O2 -nostartfiles -nodefaultlibs -nostdlib
clean:
	rm out/*.out