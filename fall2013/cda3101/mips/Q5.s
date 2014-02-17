
.data 
B: .word 4,5,6
A: .word 1,2,3

.text

main:

li $t1,3			# initialize $t1 to 3 in order to compare against in the loop
li $t2,0       		# initialize counter var to 0
la $s0,A			# initialize $s0 at the 0th byte of a
la $s1,B			# initialize $s1 at the 0th byte of b
li $s3,0            # initialize auxiliary var, $s3 will store a[i]*b[i]
li $s6,0            # initialize accumulator var, $s6 will store dot product
loop:
beq $t2,$t1,endloop # if $t2 == $t1 = 3 then break
lw $s4,0($s0)		# load a[i] in $s4
lw $s5,0($s1)		# load b[i] in $s5
mult $s4,$s5		# multiply $s4 * $s5 = a[i] * b[i]
mflo $s3			# move lowest bits of a[i] * b[i] to $s3. safe because 6*3 is the largest product
add $s6, $s6,$s3
addi $s0,$s0,4		# increment $s0, the position a[i] array
addi $s1,$s1,4		# increment $s0, the position b[i] array
addi $t2,$t2,1
j loop
endloop: