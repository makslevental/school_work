.data
array: .space 160 
.text
main:
addi $t1,$zero,1
addi $t2,$zero,2
la $s6, array

li $a0, 4
jal druk #call druk
j end
druk: #druk(n)

bne $a0,$zero, test1
li $v0, 0
jr $ra
test1:
bne $a0,$t1, test2  #t1 = 1
li $v0, 2
jr $ra
test2:
bne $a0,$t2, body  #t2 = 2
li $v0, 7
jr $ra

body:

addi $a0,$a0,-1   #decrement n

#calling druk(n-1), including storing stack frame
addi $sp,$sp,-8 
sw $ra,0($sp)
sw $a0,4($sp)
jal druk
#returning from druk(n-1) call, a0 is n-1 
lw $ra,0($sp)
lw $a0,4($sp)
addi $sp,$sp,8 

#7*druk(n-1)
li $s0,0
add $s0,$zero,$v0     #s0+druk(n-1)
add $s0,$s0,$v0     #s0+druk(n-1)
add $s0,$s0,$v0     #s0+druk(n-1)
add $s0,$s0,$v0     #s0+druk(n-1)
add $s0,$s0,$v0     #s0+druk(n-1)
add $s0,$s0,$v0     #s0+druk(n-1)
add $s0,$s0,$v0     #s0+druk(n-1)

addi $a0,$a0,-1   #decrement n

#calling druk(n-2), including storing stack frame
addi $sp,$sp,-12 #
sw $ra,0($sp)
sw $a0,4($sp)
sw $s0,8($sp)
jal druk
#returning from druk(n-1) call, a0 is n-2, s0 = 7*druk(n-1) 
lw $ra,0($sp)
lw $a0,4($sp)
lw $s0,8($sp)
addi $sp,$sp,12

li $s1, 1
sllv $s1, $s1, $v0    # 2^druk(n-2)

addi $a0,$a0,-1   #decrement n

#calling druk(n-3), including storing stack frame
addi $sp,$sp,-16 #
sw $ra,0($sp)
sw $a0,4($sp)
sw $s0,8($sp)
sw $s1,12($sp)
jal druk
#returning from druk(n-1) call, a0 is n-2, s0 = 7*druk(n-1) 
lw $ra,0($sp)
lw $a0,4($sp)
lw $s0,8($sp)
lw $s1,12($sp)
addi $sp,$sp,16


li $t3, 3 				#
li $t4, 0 				#
li $s2, 1 				#

beq $v0,$zero,zero
beq $v0,$t4, one
 						#
loop:					#
beq $t4, $v0, endloop 	#
mult  $s2,$t3			#
mflo $s2				# loop to carry out 3^druk(n-3)
addi $t4,$t4,1          #
j loop                  #

zero:
li $s2,1
j endloop
one:
li $s2,3

endloop:

li $v0,0
add $v0,$v0,$s0
add $v0,$v0,$s1
add $v0,$v0,$s2

jr $ra

end: