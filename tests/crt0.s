.global _start
_start:
    li x2, 0x7FF0
    jal x1, main

endLoop:
    nop
    jal x0, endLoop
    nop
