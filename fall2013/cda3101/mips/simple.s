
.data 
.text

main:
# assume b is stored in $t1
# $t2 is the counter var

li $t3,20			# initialize $t3 to 20 in order to compare against in the loop
li $t2,0       		# initialize counter var to 0

loop:
beq $t2,$t3,endloop # if $t2 == $t3 = 20 then break
lw $s1,0($s0)		# load a[i] in $s1
sw $s1,0($t1)		# store $s1 = a[i] at some byte offset from base address $t1 = b ($t1 is incremented below)
addi $s0,$s0,4		# increment $s0, the position a[i] array
addi $t1,$t1,4		# increment $t0, to offset from the base address b
addi $t2,$t2,1
j loop
endloop: