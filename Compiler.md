## Use the [RISC-V GCC Toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain)
### Build the RISC-V Toolchain from Source
```(bash)
git clone --recursive https://github.com/riscv-collab/riscv-gnu-toolchain
cd riscv-gnu-toolchain
./configure --prefix=/opt/riscv --with-arch=rv32i --with-abi=ilp32
sudo make -j$(nproc)
```
*Mac equivalent to `nproc` is `sysctl -n hw.physicalcpu`*


or use GNU
```(bash)
gmake -j$(sysctl -n hw.cpu)
```

**Windows**: Use wsl to run

#### Errors
Possible errors include problems when cloning repository (delete and try again), missing libraries, etc.

We encountered newlib not properly being installed in the process, but the compiler itself working. Due to this newlib was compiled seperately:
```(bash)
cd ~/riscv-gnu-toolchain
sudo gmake newlib
gmake install-newlib
ls /opt/riscv/riscv32-unknown-elf/lib
```

Where `crt0.o`, `libc.a`, and `libgloss.a` should be in this directory.


## Compile code for rv32i
Compile to `.out` and/or `.bin`
```(bash)
riscv32-unknown-elf-gcc test.c -o test.out
riscv32-unknown-elf-objcopy -O binary test.out test.bin
```


