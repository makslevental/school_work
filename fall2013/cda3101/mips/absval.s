main:

	li $s0, 1		# initialize $t0 to one 
	sll	 $s0, $s0, 31		# for use with extracting most sig dig

	li $a0, 10
	jal ABS

	li $a0, -5
	jal ABS

ABS:
	and $t1, $s0, $a0		# extract most sig dig of arg0
	bne $t1, $zero, nega	# if dig is 1 then arg0 is negative and 
	add $v0, $zero, $a0
	jr $ra
							
nega:						
	nor $v0, $a0, $a0    	# bit negate the arg since it's negative
	addi $v0, $v0, 1        # add 1 because that's the process
	jr $ra					# return