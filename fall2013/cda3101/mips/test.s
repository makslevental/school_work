
.data 

chico: .word	1,2,3,4,5,6,7,8,9,10

.text

main:

	la $a0, chico 			# load address of chico array into $a0, 2 instructions
	li $t0, 0				# initialize t0 = 0, 2 instructions
	li $v0, 0				# v0 = 0
	li $t9, 0				# t9 is the loop slt var
	li $t8, 0				# t8 is the counter var
	
loop:
	slti $t9, $t8, 10		# $t9 = 1 while t8 < 100
	beq $t9, $zero, endloop
	lw $t0, 0($a0)			# load ith entry of chico array into $t0
	add $v0, $v0, $t0		# v0 = v0 + t0
	addi $a0, $a0, 4
	addi $t8, $t8, 1
	j loop
endloop:
	sw $v0, 0($a0)			# store sum , v0, into word legnth just outside of end of array