.data
_x.float.1:		.float 0.0
_temp0:		.word 0
.text
main : 
li.s	$f0, 0.0
s.s	$f0, _x.float.1
l.s	$f0, _x.float.1
li	$v0, 6
syscall
mov.s	$f0,$f0
s.s	$f0,_x.float.1
l.s	$f0, _x.float.1
s.s	$f0, _temp0
l.s	$f0, _temp0
li	$v0, 2
mov.s	$f12, $f0
syscall
jr	$ra
