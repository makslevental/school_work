# calculates munster numbers 0 - 5. munster(6) causes overflow

.data

array:  .word  1,2,0,0,0
.text
 
 
main: 
 
	jal munster 	
 	j end

munster: 
	la $s0, array   		# load address of array into $s0
	addi $s0, $s0, 8
	li $t1, 2       		# initialize counter var to 2 because 0th index and 
							# 1st index of array already contain entries

loop:
	slt $t0,$t1, 5 			# loop test condition, $t0 = 0 when $t1 == 5
	beq $t0, $zero, endloop # branch to endloop when $t0 == 0

	lw $s1, -4($s0)			# M(i-1)
	lw $s2, -8($s0) 		# M(i-2)
	li $s3, 1
	sllv $s3, $s3, $s1 		# $s3 = 1 << $s1
	sub $s3, $s3, $s2 		# $s3 = $s3 - $s2

	sw $s3, 0($s0)

	addiu $s0, $s0, 4 # increment array address
	addiu $t1, $t1, 1 # increment loop var
	j loop

endloop:
	jr 	$ra 		# return

end: