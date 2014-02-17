# calculates drucker numbers 0 - 4. drucker(5) causes overflow

.data

array: .word 0,0,0,0,0 		# only need 5 element array

.text

main:

	addi $t1,$zero,1 	# vars used in recursive druk to compare argument against
	addi $t2,$zero,2 	# if arg == 1 then druk will return 2. if arg == 2 then druk returns 7

	la $s6, array    	# load address of storage array

	# loop to pass arguments to druk(n)
	loop1:
		
		slt $t5,$t6, 5 			 # loop test condition, $t6 = i and loop runs i < 5
		beq $t5, $zero, endloop1 # branch to endloop when $t6 = i = 5

		move $a0,$t6 			 # copies $t6 = i into argument for druk

		jal druk 				 # call druk
		sw $v0, 0($s6)           # stores result from druk in array
		addiu $s6, $s6, 4 		 # increment array address
		addiu $t6, $t6, 1 		 # increment loop var i++

		j loop1					 # rerun loop

	endloop1:

j end 	# jump past druk function


druk:	#druk(n)

	bne $a0,$zero, test1		 # if arg != 0 branch to next test.
	li $v0, 0					 # else druk returns 0
	jr $ra						
	test1:
	bne $a0,$t1, test2  		 # if arg != 1 branch to next test. 
	li $v0, 2 					 # else druk returns 2
	jr $ra
	test2:
	bne $a0,$t2, body  			 # if arg != 2 branch main body of druk
	li $v0, 7                    # else druk returns 7
	jr $ra

	body:

		addi $a0,$a0,-1   			 # decrement arg to arg-1

		# call druk(arg-1), including storing stack frame

		addi $sp,$sp,-8 
		sw $ra,0($sp)
		sw $a0,4($sp)

		jal druk

		# returning from druk(arg-1) call, a0 is restored to n-1 

		lw $ra,0($sp)
		lw $a0,4($sp)
		addi $sp,$sp,8 

		# block used to compute 7*druk(arg-1), which was returned in $v0

		li $s0,0			  # initialize $s0 to 0
		add $s0,$zero,$v0     # $s0 = 0 + druk(n-1)
		add $s0,$s0,$v0       # $s0 = $s0 + druk(n-1)
		add $s0,$s0,$v0       # $s0 = $s0 + druk(n-1)
		add $s0,$s0,$v0       # $s0 = $s0 + druk(n-1)
		add $s0,$s0,$v0       # $s0 = $s0 + druk(n-1)
		add $s0,$s0,$v0       # $s0 = $s0 + druk(n-1)
		add $s0,$s0,$v0       # $s0 = $s0 + druk(n-1)

		addi $a0,$a0,-1   	  # decrement arg for next druk call to arg-2

		# calling druk(n-2), including storing stack frame

		addi $sp,$sp,-12 #
		sw $ra,0($sp)
		sw $a0,4($sp)
		sw $s0,8($sp)

		jal druk

		# returning from druk(arg-2) call, a0 is restored t0 n-2, and s0 to 7*druk(arg-1) 

		lw $ra,0($sp)
		lw $a0,4($sp)
		lw $s0,8($sp)
		addi $sp,$sp,12

		# bitshifting left in order to compute 2^druk(arg-2)

		li $s1, 1           # bitshift 1
		sllv $s1, $s1, $v0  # by number of bits return from druk(arg-2) call, which is stored in $v0  

		addi $a0,$a0,-1    # decrement arg for next druk call to arg-3

		#calling druk(n-3), including storing stack frame

		addi $sp,$sp,-16 #
		sw $ra,0($sp)
		sw $a0,4($sp)
		sw $s0,8($sp)
		sw $s1,12($sp)

		jal druk

		#returning from druk(n-3) call, a0 is restored n-3, s0 to 7*druk(arg-1) and s1 to 2^druk(arg-2) 

		lw $ra,0($sp)
		lw $a0,4($sp)
		lw $s0,8($sp)
		lw $s1,12($sp)
		addi $sp,$sp,16

		# loop to carry out 3^druk(arg-3)

		li $t3, 3 				# $t3 initialized to base of exponentiation, 3
		li $t4, 0 				# $t4 = i is the counter var for the loop
		li $s2, 1 				# $s2 is what will be multiplied by 3

		loop:					#
		beq $t4, $v0, endloop 	# loop runs $t4 = i < $v0
		mult  $s2,$t3			# $s2 = 1 * $t3 = 1 * 3 etc.
		mflo $s2				# move lower 32 bits of 1*3*3 etc back into $s2
		addi $t4,$t4,1          # increment counter
		j loop                  

		endloop:

		add $v0,$zero,$s0		# $v0 = 0 + $s0
		add $v0,$v0,$s1			# $v0 = $v0 + $s1
		add $v0,$v0,$s2			# $v0 = $v0 + $s2

		jr $ra					# return from call

end: