# Title: Demo code for CSE 031 Lecture 20 (Spring 2025)
# Author: Santosh Chandrasekhar

.data # Define the program data.
prompt1:	.asciiz "Please enter a number: "

.text # Define the program instructions.
main:	la $a0, prompt1		# print input prompt
	li $v0, 4	
	syscall
	li $v0, 5		# read input (x) from user
	syscall
	move $s0, $v0		# $s0 = x

	la $a0, prompt1		# print input prompt 
	li $v0, 4 	
	syscall
	li $v0, 5		# read input (y) from user
	syscall
	move $s1, $v0		# $s1 = y

	add $a0, $zero, $s0	# set 1st arg of foo to x
	add $a1, $zero, $s1	# set 2nd arg of foo to y

	jal foo			# call foo(x, y)

	# recall that args (arguments) are values that are passed when calling a function
	# and params (parameters) are variables receiving the arg values

	add $a0, $zero, $v0	# Print result returned by foo()
	la $v0, 1
	syscall
	
	j END			# jump to end of code
	
# assume the params of foo are named x ($a0) and y ($a1)
foo: 	addi $sp, $sp, -8	# make space on stack
	sw $ra, 4($sp)	 	# save ret addr (as call to mult will overwrite this)
	sw $a1, 0($sp)	 	# save y (as it will be needed later to calc foo's ret value)
	
	add $a1, $a0, $a1	# set 2nd arg of bar to x + y (overwriting $a1 is okay as we saved it earlier)
	
	jal bar 	  	# call bar(x, x + y)
	
	lw $a1, 0($sp)	 	# restore y
	
	add $v0, $v0, $a1 	# set return value of foo() to bar() + y
	
	lw $ra, 4($sp)	 	# restore ret addr
	addi $sp, $sp, 8  	# restore stack
	jr $ra 			# return to main()

# assume the params of mult are named x ($a0) and x ($a1)
bar:	mult $a0, $a1		# multiply x * (x + y)
	mflo $v0		# set the return value to the low order 32-bits of (x * x)
	jr $ra 			# return to sumSquare()	

END:	li $v0, 10 		# load a 10 (halt) into $v0
	syscall 		# the program ends
