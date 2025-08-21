# Title: Demo code for CSE 031 Lecture 18 (Spring 2025)
# Author: Santosh Chandrasekhar

.data # Define the program data.
str1: .asciiz "Please enter a number: " # The string to print. Asciiz means it is null-terminated
str2: .asciiz "f (= g + h if i == j, = g - h otherwise): "
str3: .asciiz "\nValue of i << 31: "
newline: .asciiz "\n"
g:	.word 2000
h:	.word 4500

.text # Define the program instructions.
main: # Label to define the main program.

	#print input prompt
	li $v0, 4
	la $a0, str1
	syscall
	li $v0, 5	# Read input (i) from user
	syscall
	move $s3, $v0	# $s3 represents i

	li $v0, 4 	# Print input prompt
	la $a0, str1 
	syscall
	li $v0, 5	# Read input (j) from user
	syscall
	move $s4, $v0	# $s4 represents j

	la $t0, g	# Load address labelled as g into $t0 (this is where 10 is stored)
	lw $s1, 0($t0)	# $s1 = g. Fetch the value stored at address in $t0 into $s1
	        	
	la $t0, h
	lw $s2, 0($t0)	# $s2 = h

	beq $s3, $s4, True	# Check if i == j and if so, jump to the address labelled as True
	subu $s0, $s1, $s2	# f = g – h (false)
	j   Fin			# goto Fin (Need to jump over the next statement)
True: 	addu $s0, $s1, $s2	# f = g + h (true)

Fin:	li $v0, 4	# Print ouput prompt
	la $a0, str2 
	syscall
	addi $a0, $s0, 0 # Print out value of f
	li $v0, 1		 
	syscall	
	
	li $v0, 4	# Print a newline
	la $a0, newline 
	syscall
	li $v0, 4	# Print output prompt
	la $a0, str3
	syscall
	sll $a0, $s3, 31
	li $v0, 1		 
	syscall	
	
	li $v0, 10 # Load a 10 (halt) into $v0
	syscall # The program ends
