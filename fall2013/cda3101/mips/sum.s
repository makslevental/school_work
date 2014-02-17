.globl main
main:

.text

	li $t0, 0				# initialize counter var
	li $v0, 0				# initialize return var
	li $a0, 101				# arg0 for sum

	jal sum

sum:
	slt $t9, $t0, $a0
	beq $t9, $zero, el
	
loop:
	add $v0, $v0, $t0
	addi $t0, $t0, 1
	j sum						
el:
	jr $ra