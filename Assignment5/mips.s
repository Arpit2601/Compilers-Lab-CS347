.data
_temp0:		.word 0
_x.float.1:		.float 0.0
.text
main : 
li	$t0, 1
sw	$t0, _temp0
lw	$t0, _temp0
sw	$t0, _x.float.1
jr	$ra
