in = main
out = main

make:
	riscv32-unknown-elf-gcc $(file).c -o $(out).out
nolib:
	riscv32-unknown-elf-gcc $(file).c -o $(out).out -Os -nodefaultlibs -nostdlib
nostart:
	riscv32-unknown-elf-gcc $(file).c -o $(out).out -Os -nostartfiles
small:
	riscv32-unknown-elf-gcc $(file).c -o $(out).out -Os -nostartfiles -nodefaultlibs -nostdlib
clean:
	rm *.out