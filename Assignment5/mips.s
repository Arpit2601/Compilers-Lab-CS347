.data
_b.int.1:		.word 0
_p.int.1:		.word 0
_q.int.1:		.word 0
_x.int.1:		.word 0
_temp0:		.word 0
_temp1:		.word 0
_temp2:		.word 0
_temp3:		.word 0
_temp4:		.word 0
_temp5:		.word 0
_temp6:		.word 0
_temp7:		.word 0
_temp8:		.word 0
_temp9:		.word 0
_y.int.1:		.word 0
_r.int.1:		.word 0
_temp10:		.word 0
_temp11:		.word 0
_temp12:		.word 0
_temp13:		.word 0
_temp14:		.word 0
.text
_fib_.1 : 
li	$t0, 0
sw	$t0, _b.int.1
li	$t0, 0
sw	$t0, _p.int.1
li	$t0, 0
sw	$t0, _q.int.1
lw	$t1, _x.int.1
li	$t2, 1
slt	$t3, $t1, $t2
slt	$t4, $t2, $t1
or	$t5, $t3, $t4
xori	$t0, $t5, 1
sw	$t0, _temp0
lw	$t0, _temp0
sw	$t0, _temp1
lw	$t1, _temp1
bgtz	$t1, label_0
j	label_1
label_0 : 
li	$t0, 1
sw	$t0, _temp2
lw	$t0, _temp2
sw	$t0, _b.int.1
lw	$t0, _b.int.1
sw	$t0, _temp3
label_1 : 
addi	$sp,$sp,-4
sw	$ra,0($sp)
addi	$sp,$sp,-4
lw	$t8, _b.int.1
sw	$t8,0($sp)
addi	$sp,$sp,-4
lw	$t8, _p.int.1
sw	$t8,0($sp)
addi	$sp,$sp,-4
lw	$t8, _q.int.1
sw	$t8,0($sp)
addi	$sp,$sp,-4
lw	$t8, _x.int.1
sw	$t8,0($sp)
lw	$t8, x-1
sw	$t8, _x.int.1
jal	_fib_.1
lw	$t8,0($sp)
sw	$t8, _x.int.1
addi	$sp,$sp,4
lw	$t8,0($sp)
sw	$t8, _q.int.1
addi	$sp,$sp,4
lw	$t8,0($sp)
sw	$t8, _p.int.1
addi	$sp,$sp,4
lw	$t8,0($sp)
sw	$t8, _b.int.1
addi	$sp,$sp,4
lw	$ra,0($sp)
addi	$sp,$sp,4
sw	$v0, _temp4
jr	$ra
lw	$t0, _temp4
sw	$t0, _temp5
lw	$t0, _temp5
sw	$t0, _b.int.1
lw	$t0, _b.int.1
sw	$t0, _temp6
lw	$t1, _b.int.1
lw	$t2, _x.int.1
mult	$t1, $t2
mflo	$t0
sw	$t0, _temp7
lw	$t0, _temp7
sw	$t0, _temp8
lw	$t0, _temp8
sw	$t0, _b.int.1
lw	$t0, _b.int.1
sw	$t0, _temp9
jr	$ra
jr	$ra
main : 
li	$t0, 0
sw	$t0, _y.int.1
li	$t0, 0
sw	$t0, _r.int.1
li	$t0, 5
sw	$t0, _temp10
lw	$t0, _temp10
sw	$t0, _y.int.1
lw	$t0, _y.int.1
sw	$t0, _temp11
addi	$sp,$sp,-4
sw	$ra,0($sp)
addi	$sp,$sp,-4
lw	$t8, _r.int.1
sw	$t8,0($sp)
addi	$sp,$sp,-4
lw	$t8, _y.int.1
sw	$t8,0($sp)
lw	$t8, y
sw	$t8, _x.int.1
jal	_fib_.1
lw	$t8,0($sp)
sw	$t8, _y.int.1
addi	$sp,$sp,4
lw	$t8,0($sp)
sw	$t8, _r.int.1
addi	$sp,$sp,4
lw	$ra,0($sp)
addi	$sp,$sp,4
sw	$v0, _temp12
jr	$ra
lw	$t0, _temp12
sw	$t0, _temp13
lw	$t0, _temp13
sw	$t0, _r.int.1
lw	$t0, _r.int.1
sw	$t0, _temp14
jr	$ra
