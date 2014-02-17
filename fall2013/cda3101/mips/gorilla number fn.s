.globl main

.data
en: 	.asciiz "n = "
eol: 	.asciiz "\n"
.text
 
 
main: 
	la 	$a0, en # print "n = "
	li 	$v0, 4 	#
	syscall 	#
	li $v0, 5 	# read integer
	syscall 	#
	move $a0, $v0 	# $a0 = $v0
	jal fac 	# $v0 = fib(n)
	move $a0, $v0 	# $a0 = fib(n)
	li $v0, 1 	# print int
	syscall 	#
	la $a0, eol 	# print "\n"
	li $v0, 4 	#
	syscall 	#
 	li $s0, 2
 	li $s1, 1
fac: 
	bne $a0, $s0, gen # if $a0<>0, goto generic case
	bne $a0, $s1, gen
	or  $v0, $zero, $a0 	# else set result $v0 = $a0
	jr 	$ra 		# return
gen:
	addiu $sp, $sp, -12 	# make room for 2 registers on stack
	sw $ra, 4($sp) 	# save return address register $ra
	sw $a0, 0($sp) 	# save argument register $a0=n
	
	addiu 	$a0, $a0, -1 	# $a0 = n-1
	jal fac 		# $v0 = fac(n-1)
		
	or  $t0, $zero, $v0
	sw $t0, 8($sp)

	addiu 	$a0, $a0, -1 	# $a0 = n-1
	jal fac 		# $v0 = fac(n-1)

	lw 	$a0, 0($sp) 	# restore $a0=n
	lw 	$ra, 4($sp) 	# restore $ra
	lw  $t0, 8($sp)
	addiu 	$sp, $sp, 12
	add $v0, $t0, $v0

	jr 	$ra 		# return