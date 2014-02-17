.globl main
main:

.data 

array: .word	1,-2,3,-4,-5,-6,7,-8,9,10


.text

	li $s0, 1				# initialize $s0 to one 
	sll	 $s0, $s0, 31		# for use with extracting most sig dig
	li $t0, 0				# initialize counter var
	li $v0, 0
	li $v1, 0
	la $a0, array
	jal PENO

PENO:
	slti $t9, $t0, 1
	beq $t9, $zero, el
	
loop:
	lw	$a1, 0($a0)
	and $t1, $s0, $a1		# extract most sig dig of arg0
	bne $t1, $zero, nega	# if dig is 1 then arg0 is negative and 
	add $v0, $v0, $a1	
	addi $a0, $a0, 4
	addi $t0, $t0, 1
	j PENO						
nega:						
	add $v1, $v1, $a1
	addi $a0, $a0, 4
	addi $t0, $t0, 1
	j PENO
el:
	jr $ra