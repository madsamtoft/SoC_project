file = main

make:
	riscv32-unknown-elf-gcc $(file).c -o $(file).out
nolib:
	riscv32-unknown-elf-gcc $(file).c -o $(file).out -Os -nodefaultlibs -nostdlib
nostart:
	riscv32-unknown-elf-gcc $(file).c -o $(file).out -Os -nostartfiles
clean:
	rm *.out