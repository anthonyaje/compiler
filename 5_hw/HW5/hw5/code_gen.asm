_global_label:
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
li $8, 12
li $9, 1
li $10, 2
add $9, $9, $10
li $10, 3
mul $9, $9, $10
li $10, 4
li $11, 5
div $10, $10, $11
sub $9, $9, $10
li $10, 1
mul $10, $10, -1
add $9, $9, $10
sub $8, $fp, $8
sw $9, 0($8)
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
_m1: .asciiz "\n"
.text
li $v0, 4
la $a0, _m1
syscall
li $8, 4
li $9, 1
sub $8, $fp, $8
sw $9, 0($8)
li $8, 8
li $9, 2
sub $8, $fp, $8
sw $9, 0($8)
li $8, 12
li $9, 3
sub $8, $fp, $8
sw $9, 0($8)
li $8, 12
li $9, 4
sub $9, $fp, $9
lw $9, 0($9)
li $10, 8
sub $10, $fp, $10
lw $10, 0($10)
mul $9, $9, $10
li $10, 12
sub $10, $fp, $10
lw $10, 0($10)
li $11, 4
mul $10, $10, $11
sub $9, $9, $10
li $10, 5
sub $9, $9, $10
sub $8, $fp, $8
sw $9, 0($8)
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
_m2: .asciiz "\n"
.text
li $v0, 4
la $a0, _m2
syscall
li $8, 24
li.s $f1, 1.000000
li.s $f2, 2.000000
add.s $f1, $f1, $f2
li.s $f1,0.000000
j _f_exit0
_f_label0:
li.s $f1,0.000000
_f_exit0:
li.s $f2, 3.000000
mul.s $f1, $f1, $f2
li.s $f1,0.000000
j _f_exit1
_f_label1:
li.s $f1,0.000000
_f_exit1:
li.s $f2, 4.000000
li.s $f3, 5.000000
div.s $f2, $f2, $f3
li.s $f2,0.000000
j _f_exit2
_f_label2:
li.s $f2,0.000000
_f_exit2:
sub.s $f1, $f1, $f2
li.s $f1,0.000000
j _f_exit3
_f_label3:
li.s $f1,0.000000
_f_exit3:
li.s $f2, 1.000000
li.s $f3, 0.000000
mul.s $f2, $f2, $f3
add.s $f1, $f1, $f2
li.s $f1,0.000000
j _f_exit4
_f_label4:
li.s $f1,0.000000
_f_exit4:
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 24
sub $8, $fp, $8
l.s $f1, 0($8)
li $8, 24
sub $8, $fp, $8
l.s $f1, 0($8)
li $v0, 2
mov.s $f12, $f1
syscall
.data
_m3: .asciiz "\n"
.text
li $v0, 4
la $a0, _m3
syscall
li $8, 16
li.s $f1, 1.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 20
li.s $f1, 2.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 24
li.s $f1, 3.000000
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 24
li $9, 16
sub $9, $fp, $9
l.s $f1, 0($9)
li $9, 20
sub $9, $fp, $9
l.s $f2, 0($9)
mul.s $f1, $f1, $f2
li.s $f1,0.000000
j _f_exit5
_f_label5:
li.s $f1,0.000000
_f_exit5:
li $9, 24
sub $9, $fp, $9
l.s $f2, 0($9)
li.s $f3, 4.000000
mul.s $f2, $f2, $f3
li.s $f2,0.000000
j _f_exit6
_f_label6:
li.s $f2,0.000000
_f_exit6:
sub.s $f1, $f1, $f2
li.s $f1,0.000000
j _f_exit7
_f_label7:
li.s $f1,0.000000
_f_exit7:
li.s $f2, 5.000000
sub.s $f1, $f1, $f2
li.s $f1,0.000000
j _f_exit8
_f_label8:
li.s $f1,0.000000
_f_exit8:
sub $8, $fp, $8
s.s $f1, 0($8)
li $8, 24
sub $8, $fp, $8
l.s $f1, 0($8)
li $8, 24
sub $8, $fp, $8
l.s $f1, 0($8)
li $v0, 2
mov.s $f12, $f1
syscall
.data
_m4: .asciiz "\n"
.text
li $v0, 4
la $a0, _m4
syscall
li $8, 12
li $9, 1
li $10, 2
sgt $9, $9, $10
sub $8, $fp, $8
sw $9, 0($8)
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
_m5: .asciiz "\n"
.text
li $v0, 4
la $a0, _m5
syscall
li $8, 12
li $9, 2
li $10, 2
sge $9, $9, $10
sub $8, $fp, $8
sw $9, 0($8)
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
_m6: .asciiz "\n"
.text
li $v0, 4
la $a0, _m6
syscall
li $8, 12
li $9, 1
li $10, 2
slt $9, $9, $10
sub $8, $fp, $8
sw $9, 0($8)
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
_m7: .asciiz "\n"
.text
li $v0, 4
la $a0, _m7
syscall
li $8, 12
li $9, 2
li $10, 2
sle $9, $9, $10
sub $8, $fp, $8
sw $9, 0($8)
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
_m8: .asciiz "\n"
.text
li $v0, 4
la $a0, _m8
syscall
li $8, 12
li $9, 1
li $10, 2
sne $9, $9, $10
sub $8, $fp, $8
sw $9, 0($8)
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
_m9: .asciiz "\n"
.text
li $v0, 4
la $a0, _m9
syscall
li $8, 12
li $9, 1
li $10, 2
seq $9, $9, $10
sub $8, $fp, $8
sw $9, 0($8)
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
_m10: .asciiz "\n"
.text
li $v0, 4
la $a0, _m10
syscall
li $8, 12
li.s $f1, 1.000000
li.s $f2, 2.000000
c.le.s $f1, $f2
bc1f _f_label9
li.s $f1,0.000000
j _f_exit9
_f_label9:
li.s $f1,0.000000
_f_exit9:
sub $8, $fp, $8
sw $101, 0($8)
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
_m11: .asciiz "\n"
.text
li $v0, 4
la $a0, _m11
syscall
li $8, 12
li.s $f1, 1.000000
li.s $f2, 2.000000
c.lt.s $f1, $f2
bc1t _f_label10
li.s $f1,0.000000
j _f_exit10
_f_label10:
li.s $f1,0.000000
_f_exit10:
sub $8, $fp, $8
sw $101, 0($8)
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
_m12: .asciiz "\n"
.text
li $v0, 4
la $a0, _m12
syscall
li $8, 12
li.s $f1, 1.000000
li.s $f2, 2.000000
c.eq.s $f1, $f2
bc1f _f_label11
li.s $f1,0.000000
j _f_exit11
_f_label11:
li.s $f1,0.000000
_f_exit11:
sub $8, $fp, $8
sw $101, 0($8)
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
_m13: .asciiz "\n"
.text
li $v0, 4
la $a0, _m13
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
_framesize_of_main: .word 240
.data
.text
