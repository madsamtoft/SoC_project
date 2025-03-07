make:
	riscv32-unknown-elf-gcc test.c -o test.out
	riscv32-unknown-elf-objcopy -O binary test.out test.bin
