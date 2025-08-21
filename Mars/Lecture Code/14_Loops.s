# Title: Demo code for CSE 031 Lecture 18 (Spring 2025)
# Author: Santosh Chandrasekhar

.data # Define the program data.
greeting:	.asciiz "Hello World\n" # A string
prompt1:	.asciiz "Contents of array:\n"
prompt2:	.asciiz "\nAscii Characters of Hello:\n"
newline:	.asciiz "\n"
A:		.word 1, 2, 3, 4, 5 # An array of integers

.text # Define the program instructions.
main: 	la $a0, prompt1 # Print prompt1
	li $v0, 4 
	syscall 
	
	la $s5, A # Load starting address of array into $s5
	
	
	add $t0, $zero, $zero # i = 0
	li $a0, 10
	sw $a0, 16($s5) # Store 10 in A[4]
	
Loop1:	sll $t1, $t0, 2 # $t1 = 4 * i (offset = index * 4)
	addu $t1, $t1, $s5 # $t1 = addr A + 4*i	(target addr. = base addr. + offset)
	lw $a0, $t1($s5) # $a0 = A[i] (fetch from target address)
	li $v0, 1 # Print A[i] 
	syscall 
	la $a0, newline # Print a newline
	li $v0, 4 
	syscall 
	addi $t0, $t0, 1 # i = i + 1
	bne $t0, 5, Loop1 # Loop if i != 5
	
	la $a0, prompt2 # Print prompt2
	li $v0, 4 
	syscall 
			
	la  $t0, greeting # Load starting address of greeting ino $t0
	add $t1, $zero, $zero # i = 0
Loop2:	addu $t2, $t0, $t1 # $t2 = Address of greeting + i (i.e., address of greeting[i])
	lbu  $a0, ($t2) # Get character at address $t2 into $a0 (i.e., $a0 = greeting[i])
	addi $t1, $t1, 1 # i = i + 1
	li  $v0, 1 # Print ascii value of character stored in $a0 
	syscall 
	la $a0, newline # Print a newline
	li $v0, 4 
	syscall 	
	bne $t1, 5, Loop2 # Loop if i != 5
	
	li $v0, 10 # Load a 10 (halt) into $v0.
	syscall # The program ends.

