.globl main
main:
.data
arr: .word 2,3,5,1
.text
la $t7, arr       	#t7 =addr of arr     
addi $t0,$zero,100 	#a  =100
addi $t1,$zero,0  	#b  =0
addi $t2,$zero,0  	#c  =0
addi $t3,$zero,20  	#t3 =20
SL:
mult $t1,$t3
mflo $t4          	#t4 =b*20
slt  $t5,$t4,$t0  	#t5 =1 if b*20<a
beq  $t5,$zero,EL
slti $t5,$t2,4    	#t5 =1 if c<4
beq  $t5,$zero,EL
sll  $t6,$t2,2    	#t6 =c*4
add  $t6,$t7,$t6  	#t6 =arr+c*4
lw   $t1, 0($t6)  	#b  =arr[c]
addi $t2,$t2,1    	#c  =c+1
j SL
EL:
