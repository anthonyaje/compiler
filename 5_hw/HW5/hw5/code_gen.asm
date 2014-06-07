.data
_global: .word 0
.text
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
li $4, 6
li $4, 7
li $4, 10
li $4, 4
li $5, 5
sub $4, $fp, $4
sw $5, 0($4)
li $4, 8
li $5, 11
sub $4, $fp, $4
sw $5, 0($4)
li $4, 8
sub $4, $fp, $4
lw $4, 0($4)
sw $4, _global
li $4, 12
li $6, 3
move $5, $6
li $6, 2
li $7, 7
mul $5, $7, $5
add $5, $6, $5
li $6, 3
li $7, 10
mul $5, $7, $5
add $5, $6, $5
li $6, 4
mul $5, $6, $5
add $4, $4, $5
lw $5, _global
sub $4, $fp, $4
sw $5, 0($4)
li $4, 4
li $5, 12
li $7, 3
move $6, $7
li $7, 2
li $8, 7
mul $6, $8, $6
add $6, $7, $6
li $7, 3
li $8, 10
mul $6, $8, $6
add $6, $7, $6
li $7, 4
mul $6, $7, $6
add $5, $5, $6
sub $5, $fp, $5
lw $5, 0($5)
sub $4, $fp, $4
sw $5, 0($4)
li $4, 4
sub $4, $fp, $4
lw $4, 0($4)
move $v0, $4
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
_framesize_of_main: .word 1776
.data
.text
     