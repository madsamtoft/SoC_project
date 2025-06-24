file = main

win:
	riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 tests/$(file).c -o out/$(file).out -O2 -nostartfiles -nodefaultlibs -nostdlib -L. -lgcc
pong-win:
	riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 programs/pong.c -o out/programs/pong.out -O2 -nostartfiles -nodefaultlibs -nostdlib -L. -lgcc
pong2-win:
	riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 programs/pong2.c -o out/programs/pong2.out -O2 -nostartfiles -nodefaultlibs -nostdlib -L. -lgcc
pongKey-win:
	riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 programs/pongKey.c -o out/programs/pongKey.out -O2 -nostartfiles -nodefaultlibs -nostdlib -L. -lgcc

mac:
	riscv32-unknown-elf-gcc tests/$(file).c -o out/$(file).out -O3 -nostartfiles
pong-mac:
	riscv32-unknown-elf-gcc programs/pong.c -o out/programs/pong.out -O2 -nostartfiles
pong2-mac:
	riscv32-unknown-elf-gcc programs/pong2.c -o out/programs/pong2.out -O2 -nostartfiles
pongKey-mac:
	riscv32-unknown-elf-gcc programs/pongKey.c -o out/programs/pongKey.out -O2 -nostartfiles
snake-mac:
	riscv32-unknown-elf-gcc programs/snake.c -o out/programs/snake.out -O2 -nostartfiles

clean:
	rm out/*.out