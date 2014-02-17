.data
array: .space 160 
.text
.globl main
main:

li $a0, 2
la $s6, array
addi $t1,$zero,1
addi $t2,$zero,2
jal druk #call druk

j end



druk:

addi $sp,$sp,-16 #save in stack
sw $ra,0($sp)
sw $s0,4($sp)
sw $s1,8($sp)
sw $s2,12($sp)

add $s0,$a0,$zero

beq $s0,$zero,return00
beq $s0,$t1,return01  #t1 = 1
beq $s0,$t2,return02  #t2 = 2
j body
return00:
jal return0
j body
return01:
jal return1
j body
return02:
jal return2

body:

addi $a0,$s0,-1       #pass n-1 arg to next call

jal druk

add $s1,$zero,$v0     #s1+druk(n-1)
add $s1,$zero,$v0     #s1+druk(n-1)
add $s1,$zero,$v0     #s1+druk(n-1)
add $s1,$zero,$v0     #s1+druk(n-1)
add $s1,$zero,$v0     #s1+druk(n-1)
add $s1,$zero,$v0     #s1+druk(n-1)
add $s1,$zero,$v0     #s1+druk(n-1)

addi $a0,$s0,-2       #pass n-2 arg to next call

jal druk              #v0=druk(n-2)

li $s2, 1
sllv $s2, $s1, $v0    # 2^druk(n-2)

addi $a0,$s0,-3       #pass n-3 arg to next call

jal druk               #v0=druk(n-3)

li $t3, 3
li $t4, 1
li $t5, 1

loop:					#
beq $t4, $v0, endloop 	#
mult  $t5,$t3			#
mflo $t5				# loop to carry out 3 exponentiation
addi $t4,$t4,1          #
j loop                  #

endloop:

li $v0, 0
add $v0,$v0,$s1       #v0+$s1 which contains 7* term
add $v0,$v0,$s2       #v0+$s2 which contains 2^ term
add $v0,$v0,$t5       #v0+$t5 which contains 3^ term

exitdruk:

lw $ra,0($sp)       #read registers from stack
lw $s0,4($sp)
lw $s1,8($sp)
lw $s2,12($sp)
addi $sp,$sp,16       #bring back stack pointer
sw $v0, 0($s6)
addi $s6, $s6, 4
jr $ra

return2:
	li $v0,7
	j exitdruk
return1:
	li $v0,2
 	j exitdruk
return0:
	li $v0,0
	j exitdruk

end: