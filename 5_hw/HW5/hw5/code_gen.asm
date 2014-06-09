.data
_glo: .word 0
.text
_global:
li $8, 88
sw $8, _glo
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
j _global
_begin_main:
li $9, 5
li $9, 9
li $9, 200
li $10, 10
sub $9, $fp, $9
sw $10, 0($9)
li $9, 12
li $11, 2
move $10, $11
li $11, 3
li $12, 9
mul $10, $12, $10
add $10, $11, $10
li $11, 4
mul $10, $11, $10
add $9, $9, $10
li $10, 3
sub $9, $fp, $9
sw $10, 0($9)
li $9, 4
li $10, 1
sub $9, $fp, $9
sw $10, 0($9)
li $9, 8
li $10, 0
sub $9, $fp, $9
sw $10, 0($9)
_if1:
li $9, 4
sub $9, $fp, $9
lw $9, 0($9)
li $10, 8
sub $10, $fp, $10
lw $10, 0($10)
sgt $9, $9, $10
beqz $9, _else1
.data
_m1: .asciiz "correct\n"
.text
li $v0, 4
la $a0, _m1
syscall
j _exit1
_else1:
.data
_m2: .asciiz "wrong\n"
.text
li $v0, 4
la $a0, _m2
syscall
_exit1:
_if2:
li $9, 4
sub $9, $fp, $9
lw $9, 0($9)
li $10, 8
sub $10, $fp, $10
lw $10, 0($10)
slt $9, $9, $10
beqz $9, _else2
.data
_m3: .asciiz "wrong\n"
.text
li $v0, 4
la $a0, _m3
syscall
j _exit2
_else2:
.data
_m4: .asciiz "correct\n"
.text
li $v0, 4
la $a0, _m4
syscall
_exit2:
_if3:
li $9, 4
sub $9, $fp, $9
lw $9, 0($9)
li $10, 8
sub $10, $fp, $10
lw $10, 0($10)
seq $9, $9, $10
beqz $9, _else3
.data
_m5: .asciiz "wrong\n"
.text
li $v0, 4
la $a0, _m5
syscall
j _exit3
_else3:
.data
_m6: .asciiz "correct\n"
.text
li $v0, 4
la $a0, _m6
syscall
_exit3:
_if4:
li $9, 4
sub $9, $fp, $9
lw $9, 0($9)
li $10, 8
sub $10, $fp, $10
lw $10, 0($10)
sne $9, $9, $10
beqz $9, _else4
.data
_m7: .asciiz "correct\n"
.text
li $v0, 4
la $a0, _m7
syscall
j _exit4
_else4:
.data
_m8: .asciiz "wrong\n"
.text
li $v0, 4
la $a0, _m8
syscall
_exit4:
li $9, 192
li.s $f10, 1.000000
sub $9, $fp, $9
sw $10, 0($9)
li $9, 196
li.s $f10, 0.000000
sub $9, $fp, $9
sw $10, 0($9)
_if5:
li $9, 192
sub $9, $fp, $9
lw $9, 0($9)
li $10, 196
sub $10, $fp, $10
lw $10, 0($10)
sgt $9, $9, $10
bc1t _f_label0
li $9,0
j _f_exit0
_f_label0:
li $9,1
_f_exit0:
sgt $9, $9, $10
beqz $9, _else5
.data
_m9: .asciiz "correct\n"
.text
li $v0, 4
la $a0, _m9
syscall
j _exit5
_else5:
.data
_m10: .asciiz "wrong\n"
.text
li $v0, 4
la $a0, _m10
syscall
_exit5:
_if6:
li $9, 192
sub $9, $fp, $9
lw $9, 0($9)
li $10, 196
sub $10, $fp, $10
lw $10, 0($10)
slt $9, $9, $10
bc1t _f_label1
li $9,0
j _f_exit1
_f_label1:
li $9,1
_f_exit1:
slt $9, $9, $10
beqz $9, _else6
.data
_m11: .asciiz "wrong\n"
.text
li $v0, 4
la $a0, _m11
syscall
j _exit6
_else6:
.data
_m12: .asciiz "correct\n"
.text
li $v0, 4
la $a0, _m12
syscall
_exit6:
_if7:
li $9, 192
sub $9, $fp, $9
lw $9, 0($9)
li $10, 196
sub $10, $fp, $10
lw $10, 0($10)
sne $9, $9, $10
bc1t _f_label2
li $9,0
j _f_exit2
_f_label2:
li $9,1
_f_exit2:
sne $9, $9, $10
beqz $9, _else7
.data
_m13: .asciiz "correct\n"
.text
li $v0, 4
la $a0, _m13
syscall
j _exit7
_else7:
.data
_m14: .asciiz "wrong\n"
.text
li $v0, 4
la $a0, _m14
syscall
_exit7:
_if8:
li $9, 4
sub $9, $fp, $9
lw $9, 0($9)
li $10, 8
sub $10, $fp, $10
lw $10, 0($10)
and $9, $9, $10
beqz $9, _else8
.data
_m15: .asciiz "wrong\n"
.text
li $v0, 4
la $a0, _m15
syscall
j _exit8
_else8:
_exit8:
_if9:
li $9, 4
sub $9, $fp, $9
lw $9, 0($9)
li $10, 8
sub $10, $fp, $10
lw $10, 0($10)
or $9, $9, $10
beqz $9, _else9
.data
_m16: .asciiz "correct\n"
.text
li $v0, 4
la $a0, _m16
syscall
j _exit9
_else9:
_exit9:
li $9, 4
li $10, 0
sub $9, $fp, $9
sw $10, 0($9)
.data
_m17: .asciiz "\n\nwhile\n\n"
.text
li $v0, 4
la $a0, _m17
syscall
li $9, 200
sub $9, $fp, $9
lw $9, 0($9)
li $9, 200
sub $9, $fp, $9
lw $9, 0($9)
li $v0, 1
move $a0, $9
syscall
_while1:
li $10, 4
sub $10, $fp, $10
lw $10, 0($10)
li $11, 10
slt $10, $10, $11
beqz $10, _while_exit1
.data
_m18: .asciiz "correct: "
.text
li $v0, 4
la $a0, _m18
syscall
li $v0, 1
lw $a0, _glo
syscall
.data
_m19: .asciiz "\n"
.text
li $v0, 4
la $a0, _m19
syscall
li $10, 4
li $11, 4
sub $11, $fp, $11
lw $11, 0($11)
li $12, 1
add $11, $11, $12
sub $10, $fp, $10
sw $11, 0($10)
j _while1
_while_exit1:
_if10:
li $10, 4
sub $10, $fp, $10
lw $10, 0($10)
li $11, 10
seq $10, $10, $11
beqz $10, _else10
.data
_m20: .asciiz "correct\n"
.text
li $v0, 4
la $a0, _m20
syscall
j _exit10
_else10:
_exit10:
li $10, 0
move $v0, $10
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
	lw	$ra, 4($fp)
	add	$sp, $fp, 4
	lw	$fp, 0($fp)
	jr	$ra
.data 
_framesize_of_main: .word 288
.data
.text
     