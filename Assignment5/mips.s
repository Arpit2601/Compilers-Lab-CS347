.data
_temp0:		.word 0
_i.int.1:		.word 0
_temp1:		.word 0
_temp2:		.word 0
_temp3:		.word 0
_temp4:		.word 0
_temp5:		.word 0
_temp6:		.word 0
.text
main : 
li	$t0, 0
sw	$t0, _temp0
sw	$t0, _i.int.1
label_0 : 
lw	$t1, _i.int.1
li	$t2, 10
slt	$t3, $t2, $t1
xori	$t0, $t3, 1
s.s	$f0, _temp1
sw	$t0, _temp2
lw	$t1, _temp2
bgtz	$t1, label_1
j	label_2
label_1 : 
l.s	$f0, _i.int.1
s.s	$f0, _temp3
lw	$t1, _temp3
li	$v0, 1
move	$a0, $t1
syscall
lw	$t1, _i.int.1
li	$t2, 1
add	$t0, $t1, $t2
sw	$t0, _temp4
sw	$t0, _temp5
l.s	$f0, _temp5
s.s	$f0, _i.int.1
l.s	$f0, _i.int.1
s.s	$f0, _temp6
j	label_0
label_2 : 
jr	$ra
jr	$ra
