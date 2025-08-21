# Title: Demo code for CSE 031 Lecture 18 (Spring 2024)
# Author: Santosh Chandrasekhar

.data # Define the program data.
prompt:	.asciiz "Sum of a and b: "
a:	.word 10
b:	.word 5

.text # Define the program instructions.
main:	la $a0, prompt # print prompt1
	li $v0, 4 
	syscall
	
	la  $t0, a
	lw  $s0, ($t0) 		# $s0 = a
	
	lw $s1, b 		# pseudo instruction to set $s1 = b (a quicker way)
	
	# Set up arguments to sum 		
	add  $a0, $s0, $zero 	# set 1st arg of sum to a
	move $a1, $s1	 	# pseudo instruction to set 2nd arg of sum to b (a quicker way)
	
	jal sum 		# call sum(a, b)
	
	add $a0, $v0, $zero 	# return value assumed to be in $v0. Copy it to $a0 to print
	li $v0, 1
	syscall 
	
	j END			# jump to end of code

sum:	add $v0, $a0, $a1	# set return value to the sum of the two input parameters 
	jr  $ra			# return to main()

END:	li $v0, 10 		# load a 10 (halt) into $v0
	syscall 		# the program ends
