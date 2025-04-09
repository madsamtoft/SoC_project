in = main

make:
	riscv32-unknown-elf-gcc tests/$(file).c -o out/$(file).out
nolib:
	riscv32-unknown-elf-gcc tests/$(file).c -o out/$(file).out -Os -nodefaultlibs -nostdlib
nostart:
	riscv32-unknown-elf-gcc tests/$(file).c -o out/$(file).out -Os -nostartfiles
small:
	riscv32-unknown-elf-gcc tests/$(file).c -o out/$(file).out -Os -nostartfiles -nodefaultlibs -nostdlib
clean:
	rm out/*.out