file = main

mac:
	riscv32-unknown-elf-gcc tests/$(file).c -o out/$(file).out -Os -nostartfiles
win:
	riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 tests/$(file).c -o out/$(file).out -Os -nostartfiles -nodefaultlibs -nostdlib
clean:
	rm out/*.out