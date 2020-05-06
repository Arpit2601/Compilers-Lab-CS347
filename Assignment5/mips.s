.data
_alpha.int.1:		.word 0
_beta.int.1:		.word 0
_temp0:		.word 0
_als.int.1:		.word 0
_temp1:		.word 0
_temp2:		.word 0
_temp3:		.word 0
_temp4:		.word 0
_z.int.1:		.word 0
_temp5:		.word 0
_t.int.1:		.word 0
_temp6:		.word 0
_q.int.1:		.word 0
_temp7:		.word 0
_temp8:		.word 0
_temp9:		.word 0
.text
_func2_.1 : 
li	$t0, 0
sw	$t0, _alpha.int.1
li	$t0, 0
sw	$t0, _beta.int.1
jr	$ra
jr	$ra
_func_.1 : 
li	$t0, 1
sw	$t0, _temp0
lw	$t0, _temp0
sw	$t0, _als.int.1
lw	$t0, _als.int.1
sw	$t0, _temp1
lw	$t1, _als.int.1
li	$t2, 1
slt	$t3, $t1, $t2
slt	$t4, $t2, $t1
or	$t5, $t3, $t4
xori	$t0, $t5, 1
sw	$t0, _temp2
lw	$t0, _temp2
sw	$t0, _temp3
lw	$t1, _temp3
bgtz	$t1, label_0
j	label_1
label_0 : 
label_1 : 
jr	$ra
jr	$ra
main : 
li	$t0, 2
sw	$t0, _temp4
lw	$t0, _temp4
sw	$t0, _z.int.1
li	$t0, 2
sw	$t0, _temp5
lw	$t0, _temp5
sw	$t0, _t.int.1
li	$t0, 3
sw	$t0, _temp6
lw	$t0, _temp6
sw	$t0, _q.int.1
lw	$t0, _q.int.1
sw	$t0, _temp7
lw	$t1, _temp7
li	$v0, 1
move	$a0, $t1
syscall
addi	$sp,$sp,-4
sw	$ra,0($sp)
addi	$sp,$sp,-4
lw	$t8, _q.int.1
sw	$t8,0($sp)
addi	$sp,$sp,-4
lw	$t8, _t.int.1
sw	$t8,0($sp)
addi	$sp,$sp,-4
lw	$t8, _z.int.1
sw	$t8,0($sp)
lw	$t8, 4
sw	$t8, _als.int.1
jal	_func_.1
lw	$t8,0($sp)
sw	$t8, _z.int.1
addi	$sp,$sp,4
lw	$t8,0($sp)
sw	$t8, _t.int.1
addi	$sp,$sp,4
lw	$t8,0($sp)
sw	$t8, _q.int.1
addi	$sp,$sp,4
lw	$ra,0($sp)
addi	$sp,$sp,4
sw	$v0, _temp8
jr	$ra
lw	$t0, _temp8
sw	$t0, _temp9
jr	$ra
