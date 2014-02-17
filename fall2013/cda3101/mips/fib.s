.globl main
main:
.data

array: .space 100

.text

	li $t0, 2				# initialize counter var
	li $v0, 0				# initialize return var
	li $a0, 101				# arg0 for sum
	la $a1,	array
	li $t1, 1
	sw $t1, 0($a1)
	sw $t1, 4($a1)
	addi, $a1, $a1, 8

	jal fib

fib:
	slt $t9, $t0, $a0
	beq $t9, $zero, el
loop:
	
	lw $t8, -4($a1)
	lw $t7, -8($a1)
	add $t6, $t7, $t8
	sw $t6, 0($a1)
	addi, $t0, $t0, 1
	addi, $a1, $a1, 4
	j loop						
el:
	jr $ra