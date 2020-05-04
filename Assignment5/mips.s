.data
_temp0:		.word 0
_temp1:		.word 0
_y.int.0:		.word 0
_temp2:		.word 0
_x.int.1:		.word 0
_temp3:		.word 0
_temp4:		.word 0
.text
li	$t0, 1
sw	$t0, _temp0
lw	$t0, _temp0
sw	$t0, _temp1
lw	$t0, _temp1
sw	$t0, _y.int.0
main : 
li	$t0, 1
sw	$t0, _temp2
lw	$t0, _temp2
sw	$t0, _x.int.1
lw	$t0, _x.int.1
sw	$t0, _temp3
lw	$t1, _temp3
bgtz	$t1, label_0
j	label_1
label_0 : 
lw	$t0, _x.int.1
sw	$t0, _temp4
lw	$t1, _temp4
li	$v0, 1
move	$a0, $t1
syscall
label_1 : 
jr	$ra
