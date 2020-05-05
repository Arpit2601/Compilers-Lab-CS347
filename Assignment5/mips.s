.data
_temp0:		.word 0
_x.int.1:		.word 0
_temp1:		.word 0
_temp2:		.word 0
_temp3:		.word 0
_temp4:		.word 0
.text
main : 
li	$t0, 1
sw	$t0, _temp0
lw	$t0, _temp0
sw	$t0, _x.int.1
lw	$t1, _x.int.1
li	$t2, 1
sub	$t0, $t1, $t2
sw	$t0, _temp1
beq	$t0, label_1
li	$t2, 2
sub	$t0, $t1, $t2
sw	$t0, _temp1
beq	$t0, label_2
label_3 : 
lw	$t0, _x.int.1
sw	$t0, _temp2
lw	$t1, _temp2
li	$v0, 1
move	$a0, $t1
syscall
j	label_0
j	label_0
label_1 : 
lw	$t0, _x.int.1
sw	$t0, _temp3
lw	$t1, _temp3
li	$v0, 1
move	$a0, $t1
syscall
j	label_0
label_2 : 
lw	$t0, _x.int.1
sw	$t0, _temp4
lw	$t1, _temp4
li	$v0, 1
move	$a0, $t1
syscall
label_0 : 
jr	$ra
