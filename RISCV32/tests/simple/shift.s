.text
    lui x10 0xff000
    addi x11 x0 255
	srai x10 x10 8
	slli x11 x11 8
	addi x11 x11 255
	add x12 x10 x11
	addi x17 x0 10
