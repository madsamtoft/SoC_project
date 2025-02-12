addi x10 x0 10
addi x11 x0 20
beq a0, a1, e
blt a0, a1, b

a:
	addi x10 x0 3
	addi x11 x0 4
	blt x10 x11 f
b:
	blt x10 x11 d
c:
	blt x10 x11 a
d:
	blt x10 x11 c
e:
	addi x10 x0 1
	addi x11 x0 2
f:
	addi x12 x10 0
	addi x17 x0 10
