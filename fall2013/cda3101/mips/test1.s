.data 

src_array:	.space	100
dest_array: .space	100

main:

	la $a0, src_array		# allocate space for src_array
	la $a1, dest_array		# allocate space for dest_array
	addi $t0, $zero, $t0	# initialize $t0 to zero, counter var
	addi $t1, $zero, $t1	# initialize $t1 to zero, holder var
	addi $t9, $zero, $t9	# initialize slt var to zero

loop:

	slti $t9, $t0, 100
	beq, $t0, $zero, endloop
	lw $t1, 0($a0)			# lw from src_array
	sw $t1, 0($a1)			# sw to dest_array
	addi $a0, $a0, 4		# increment src_array index by 4 bytes
	addi $a1, $a1, 4		# incrememnt dest_array index by 4 bytes
	addi $t0, $t0, 1 		# incrememnt counter var by 1
	j loop
	
endloop:


