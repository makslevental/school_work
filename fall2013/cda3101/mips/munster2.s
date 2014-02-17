.data

array:  .space  160 # 160 bytes array to store munster numbers
error: 	.asciiz "overflow"
.text
 
 
main: 
 
	jal munster 	
 	j end

munster: 
	la $s0, array # load address of array into $s0

	li $s1, 1      #
	sw $s1, 0($s0) # load 1 into the first index of array
	addi $s0, $s0, 4

	li $s1, 2        #
	sw $s1, 0($s0)   # load 2 into the second index of array
	addi $s0, $s0, 4 #

	li $t1, 2       # initialize counter var
loop:
	slt $t0,$t1, 40 # loop test condition, $t0 = 0 when $t1 == 40
	beq $t0, $zero, endloop # branch to endloop when $t0 == 0

	lw $s1, -4($s0)	# M(i-1)
	lw $s2, -8($s0) # M(i-2)
	li $s3, 1
	sllv $s3, $s3, $s1 # $s3 = 1 << $s1
	subu $s3, $s3, $s2 # $s3 = $s3 - $s2

	li $s4, 1				# initialize $s0 to one 
	sll	 $s4, $s4, 31		# for use with extracting most sig dig
	and $s5, $s4, $s3		# extract most sig dig of $s3
	bne $s5, $zero, trap	# if dig is 1 then $s3 is negative then overflow

	sw $s3, 0($s0)

	addiu $s0, $s0, 4 # increment array address
	addiu $t1, $t1, 1 # increment loop var
	j loop

endloop:
	jr 	$ra 		# return

trap:
	la $a0, error 	# print "\n"
	li $v0, 4 	#
	syscall 	#
end: