_global_label:
.data
_INT: .word 0
.text
.data
_FLOAT: .word 0
.text
li $8, 2
.data
_INTA: .word 0
.text
li $8, 2
.data
_FLOATA: .word 0
.text
.data
_g1: .word 0
.text
.data
_g2: .word 0
.text
.data
_g3: .word 0
.text
.data
_g4: .word 0
.text
li $8, 2
.data
_g5: .word 0
.text
li $8, 2
.data
_g6: .word 0
.text
li $8, 2
.data
_g7: .word 0
.text
li $8, 2
.data
_g8: .word 0
.text
.data
_g9: .word 0
.text
.data
_g10: .word 0
.text
j _begin_main
main:
# prologue sequence
	sw	$ra, 0($sp)
	sw	$fp, -4($sp)
	add	$fp, $sp, -4
	add	$sp, $sp, -8
	lw	$2, _framesize_of_main
	sub	$sp,$sp,$2
	sw	$4,48($sp)
	sw	$5,44($sp)
	sw	$6,40($sp)
	sw	$7,36($sp)
	sw	$8,32($sp)
	sw	$9,28($sp)
	sw	$10,24($sp)
	sw	$11,20($sp)
	sw	$12,16($sp)
	sw	$13,12($sp)
	sw	$14,8($sp)
	sw	$15,4($sp)
	sw	$16,52($sp)
	sw	$17,56($sp)
	sw	$18,60($sp)
	sw	$19,64($sp)
	sw	$20,68($sp)
	sw	$21,72($sp)
	sw	$22,76($sp)
	sw	$23,80($sp)
	sw	$24,84($sp)
	sw	$25,88($sp)
	s.s	$f0, 92($sp)
	s.s	$f1, 96($sp)
	s.s	$f2, 100($sp)
	s.s	$f3, 104($sp)
	s.s	$f4, 108($sp)
	s.s	$f5, 112($sp)
	s.s	$f6, 116($sp)
	s.s	$f7, 120($sp)
	s.s	$f8, 124($sp)
	s.s	$f9, 128($sp)
	s.s	$f10, 132($sp)
	s.s	$f11, 136($sp)
	s.s	$f12, 140($sp)
	s.s	$f13, 144($sp)
	s.s	$f14, 148($sp)
	s.s	$f15, 152($sp)
	s.s	$f16, 156($sp)
	s.s	$f17, 160($sp)
	s.s	$f18, 164($sp)
	s.s	$f19, 168($sp)
	s.s	$f20, 172($sp)
	s.s	$f21, 176($sp)
	s.s	$f22, 180($sp)
	s.s	$f23, 184($sp)
	s.s	$f24, 188($sp)
	s.s	$f25, 192($sp)
	s.s	$f26, 196($sp)
	s.s	$f27, 200($sp)
	s.s	$f28, 204($sp)
	s.s	$f29, 208($sp)
	s.s	$f30, 212($sp)
	s.s	$f31, 216($sp)
j _global_label
_begin_main:
li $8, 2
li $8, 2
li $8, 2
li $8, 2
li $8, 1
sw $8, _g1
li.s $f1, 2.000000
s.s $f1, _g2
li $8, 3
sw $8, _g3
li.s $f1, 4.000000
s.s $f1, _g4
li $8, 5
mtc1 $8, $f1
cvt.s.w $f1, $f1
s.s $f1, _g5
li $8, 55
mtc1 $8, $f1
cvt.s.w $f1, $f1
s.s $f1, _g5
li.s $f1, 6.000000
s.s $f1, _g6
li.s $f1, 66.000000
s.s $f1, _g6
li $8, 7
mtc1 $8, $f1
cvt.s.w $f1, $f1
s.s $f1, _g7
li $8, 77
mtc1 $8, $f1
cvt.s.w $f1, $f1
s.s $f1, _g7
li.s $f1, 8.000000
s.s $f1, _g8
li.s $f1, 88.000000
s.s $f1, _g8
li $8, 9
mtc1 $8, $f1
cvt.s.w $f1, $f1
s.s $f1, _g9
li $8, 99
mtc1 $8, $f1
cvt.s.w $f1, $f1
s.s $f1, _g9
li.s $f1, 10.000000
s.s $f1, _g10
li.s $f1, 100.000000
s.s $f1, _g10
li $8, 4
li $9, 1
sub $8, $fp, $8
sw $9, 0($8)
li $8, 8
li.s $f1, 2.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 12
li $9, 3
sub $8, $fp, $8
sw $9, 0($8)
li $8, 16
li.s $f1, 4.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 20
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li $9, 5
sub $8, $fp, $8
sw $9, 0($8)
li $8, 20
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li $9, 55
sub $8, $fp, $8
sw $9, 0($8)
li $8, 28
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li.s $f1, 6.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 28
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li.s $f1, 66.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 36
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li $9, 7
sub $8, $fp, $8
sw $9, 0($8)
li $8, 36
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li $9, 77
sub $8, $fp, $8
sw $9, 0($8)
li $8, 44
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li.s $f1, 8.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 44
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li.s $f1, 88.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 52
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li $9, 99
sub $8, $fp, $8
sw $9, 0($8)
li $8, 56
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li.s $f1, 10.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 56
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
li.s $f1, 100.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $v0, 1
lw $a0, _g1
syscall
.data
_m1: .asciiz "\n"
.text
li $v0, 4
la $a0, _m1
syscall
li $v0, 2
l.s $f12, _g2
syscall
.data
_m2: .asciiz "\n"
.text
li $v0, 4
la $a0, _m2
syscall
li $v0, 1
lw $a0, _g3
syscall
.data
_m3: .asciiz "\n"
.text
li $v0, 4
la $a0, _m3
syscall
li $v0, 2
l.s $f12, _g4
syscall
.data
_m4: .asciiz "\n"
.text
li $v0, 4
la $a0, _m4
syscall
li $v0, 2
l.s $f12, _g5
syscall
.data
_m5: .asciiz "\n"
.text
li $v0, 4
la $a0, _m5
syscall
li $v0, 2
l.s $f12, _g5
syscall
.data
_m6: .asciiz "\n"
.text
li $v0, 4
la $a0, _m6
syscall
li $v0, 2
l.s $f12, _g6
syscall
.data
_m7: .asciiz "\n"
.text
li $v0, 4
la $a0, _m7
syscall
li $v0, 2
l.s $f12, _g6
syscall
.data
_m8: .asciiz "\n"
.text
li $v0, 4
la $a0, _m8
syscall
li $v0, 2
l.s $f12, _g7
syscall
.data
_m9: .asciiz "\n"
.text
li $v0, 4
la $a0, _m9
syscall
li $v0, 2
l.s $f12, _g7
syscall
.data
_m10: .asciiz "\n"
.text
li $v0, 4
la $a0, _m10
syscall
li $v0, 2
l.s $f12, _g8
syscall
.data
_m11: .asciiz "\n"
.text
li $v0, 4
la $a0, _m11
syscall
li $v0, 2
l.s $f12, _g8
syscall
.data
_m12: .asciiz "\n"
.text
li $v0, 4
la $a0, _m12
syscall
li $v0, 2
l.s $f12, _g9
syscall
.data
_m13: .asciiz "\n"
.text
li $v0, 4
la $a0, _m13
syscall
li $v0, 2
l.s $f12, _g9
syscall
.data
_m14: .asciiz "\n"
.text
li $v0, 4
la $a0, _m14
syscall
li $v0, 2
l.s $f12, _g10
syscall
.data
_m15: .asciiz "\n"
.text
li $v0, 4
la $a0, _m15
syscall
li $v0, 2
l.s $f12, _g10
syscall
.data
_m16: .asciiz "\n"
.text
li $v0, 4
la $a0, _m16
syscall
li $8, 4
sub $8, $fp, $8
lw $8, 0($8)
li $8, 4
sub $8, $fp, $8
lw $8, 0($8)
li $v0, 1
move $a0, $8
syscall
.data
_m17: .asciiz "\n"
.text
li $v0, 4
la $a0, _m17
syscall
li $8, 8
sub $8, $fp, $8
l.s $f1, 0($8)
li $8, 8
sub $8, $fp, $8
l.s $f1, 0($8)
li $v0, 2
mov.s $f12, $f1
syscall
.data
_m18: .asciiz "\n"
.text
li $v0, 4
la $a0, _m18
syscall
li $8, 12
sub $8, $fp, $8
lw $8, 0($8)
li $8, 12
sub $8, $fp, $8
lw $8, 0($8)
li $v0, 1
move $a0, $8
syscall
.data
_m19: .asciiz "\n"
.text
li $v0, 4
la $a0, _m19
syscall
li $8, 16
sub $8, $fp, $8
l.s $f1, 0($8)
li $8, 16
sub $8, $fp, $8
l.s $f1, 0($8)
li $v0, 2
mov.s $f12, $f1
syscall
.data
_m20: .asciiz "\n"
.text
li $v0, 4
la $a0, _m20
syscall
li $8, 20
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
lw $8, 0($8)
li $8, 20
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
lw $8, 0($8)
li $v0, 1
move $a0, $8
syscall
.data
_m21: .asciiz "\n"
.text
li $v0, 4
la $a0, _m21
syscall
li $8, 20
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
lw $8, 0($8)
li $8, 20
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
lw $8, 0($8)
li $v0, 1
move $a0, $8
syscall
.data
_m22: .asciiz "\n"
.text
li $v0, 4
la $a0, _m22
syscall
li $8, 28
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $8, 28
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $v0, 2
mov.s $f12, $f1
syscall
.data
_m23: .asciiz "\n"
.text
li $v0, 4
la $a0, _m23
syscall
li $8, 28
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $8, 28
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $v0, 2
mov.s $f12, $f1
syscall
.data
_m24: .asciiz "\n"
.text
li $v0, 4
la $a0, _m24
syscall
li $8, 36
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
lw $8, 0($8)
li $8, 36
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
lw $8, 0($8)
li $v0, 1
move $a0, $8
syscall
.data
_m25: .asciiz "\n"
.text
li $v0, 4
la $a0, _m25
syscall
li $8, 36
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
lw $8, 0($8)
li $8, 36
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
lw $8, 0($8)
li $v0, 1
move $a0, $8
syscall
.data
_m26: .asciiz "\n"
.text
li $v0, 4
la $a0, _m26
syscall
li $8, 44
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $8, 44
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $v0, 2
mov.s $f12, $f1
syscall
.data
_m27: .asciiz "\n"
.text
li $v0, 4
la $a0, _m27
syscall
li $8, 44
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $8, 44
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $v0, 2
mov.s $f12, $f1
syscall
.data
_m28: .asciiz "\n"
.text
li $v0, 4
la $a0, _m28
syscall
li $8, 52
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
lw $8, 0($8)
li $8, 52
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
lw $8, 0($8)
li $v0, 1
move $a0, $8
syscall
.data
_m29: .asciiz "\n"
.text
li $v0, 4
la $a0, _m29
syscall
li $8, 56
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $8, 56
li $10, 0
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $v0, 2
mov.s $f12, $f1
syscall
.data
_m30: .asciiz "\n"
.text
li $v0, 4
la $a0, _m30
syscall
li $8, 56
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $8, 56
li $10, 1
move $9, $10
li $10, 4
mul $9, $10, $9
add $8, $8, $9
sub $8, $fp, $8
l.s $f1, 0($8)
li $v0, 2
mov.s $f12, $f1
syscall
.data
_m31: .asciiz "\n"
.text
li $v0, 4
la $a0, _m31
syscall
li $8, 0
move $v0, $8
j _end_main
# epilogue sequence
_end_main:
	lw	$8,32($sp)
	lw	$9,28($sp)
	lw	$10,24($sp)
	lw	$11,20($sp)
	lw	$12,16($sp)
	lw	$13,12($sp)
	lw	$14,8($sp)
	lw	$15,4($sp)
	lw	$16,52($sp)
	lw	$17,56($sp)
	lw	$18,60($sp)
	lw	$19,64($sp)
	lw	$20,68($sp)
	lw	$21,72($sp)
	lw	$22,76($sp)
	lw	$23,80($sp)
	lw	$24,84($sp)
	lw	$25,88($sp)
	lw	$4,48($sp)
	lw	$5,44($sp)
	lw	$6,40($sp)
	lw	$7,36($sp)
	l.s	$f0, 92($sp)
	l.s	$f1, 96($sp)
	l.s	$f2, 100($sp)
	l.s	$f3, 104($sp)
	l.s	$f4, 108($sp)
	l.s	$f5, 112($sp)
	l.s	$f6, 116($sp)
	l.s	$f7, 120($sp)
	l.s	$f8, 124($sp)
	l.s	$f9, 128($sp)
	l.s	$f10, 132($sp)
	l.s	$f11, 136($sp)
	l.s	$f12, 140($sp)
	l.s	$f13, 144($sp)
	l.s	$f14, 148($sp)
	l.s	$f15, 152($sp)
	l.s	$f16, 156($sp)
	l.s	$f17, 160($sp)
	l.s	$f18, 164($sp)
	l.s	$f19, 168($sp)
	l.s	$f20, 172($sp)
	l.s	$f21, 176($sp)
	l.s	$f22, 180($sp)
	l.s	$f23, 184($sp)
	l.s	$f24, 188($sp)
	l.s	$f25, 192($sp)
	l.s	$f26, 196($sp)
	l.s	$f27, 200($sp)
	l.s	$f28, 204($sp)
	l.s	$f29, 208($sp)
	l.s	$f30, 212($sp)
	l.s	$f31, 216($sp)
	lw	$ra, 4($fp)
	add	$sp, $fp, 4
	lw	$fp, 0($fp)
	jr	$ra
.data 
_framesize_of_main: .word 272
.data
.text
