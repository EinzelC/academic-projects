# Title: Demo code for CSE 031 Lecture 20 (Spring 2025)
# Author: Santosh Chandrasekhar

.data
m:		.word -8
n: 		.word 16
o: 		.word 8
newline:	.asciiz "\n"
prompt1:	.asciiz "m = -8\nm = m << 3 (using sll): "
prompt2:	.asciiz "\nm = m >> 2 (using sra): "
prompt3:	.asciiz "\nm = m >> 2 (using srl): "
prompt4:	.asciiz "\n\nn = 16\nn = n << 27 (using sll): "
prompt5:	.asciiz "\n\nn = 16, o = 8\nHigh order 32 bits of n * o: "
prompt6:	.asciiz "\nLow order 32 bits of n * o: "
prompt7:	.asciiz "\nRemainder of n / o: "
prompt8:	.asciiz "\nQuotient of n / o: "

.text
main: 	lw $s2, m # Pseudo instruction to set $s2 = m
		  # This is an alternative for la $t0, m followed by lw $s2, 0($t0)

	la $a0, prompt1 # Print prompt1
	li $v0, 4 
	syscall
	
	sll $s2, $s2, 3	# $s2 = $s2 * 2^3
	move $a0, $s2 # Print the value in $s2
	li $v0, 1
	syscall
	
	la $a0, prompt2 # Print prompt2
	li $v0, 4 
	syscall
	
	sra $s2, $s2, 2	# $s2 = $s2 / 2^2
	move $a0, $s2 # Print the value in $s2
	li $v0, 1
	syscall
	
	la $a0, prompt3 # Print a prompt3
	li $v0, 4 
	syscall
	
	srl $s2, $s2, 2	 # $s2 = $s2 / 2^2 
	                 # srl ignores the sign bit so this will produce an unexpected result
	move $a0, $s2 # Print the value in $s2
	li $v0, 1
	syscall
	
	la $a0, prompt4 # Print a prompt4
	li $v0, 4 
	syscall
	
	lw $s2, n
	sll $s2, $s2, 27 # Left shifting n 
	move $a0, $s2 # Print the value in $s2
	li $v0, 1
	syscall
	
	# Multiplication demo
	lw $s3, n
	lw $s4, o
	
	mult $s3, $s4 # Result (product) goes into a special 64 bit register
	
	la $a0, prompt5 # Print a prompt5
	li $v0, 4 
	syscall
	
	mfhi $a0 # Move high order 32 bits of product to $a0 and print it
	li $v0, 1
	syscall
	
	la $a0, prompt6 # Print a prompt6
	li $v0, 4 
	syscall				
	
	mflo $a0 # Move low order 32 bits of product to $a0 and print it
	li $v0, 1
	syscall
	
	# Division demo
	div $s3, $s4
	
	la $a0, prompt7 # Print a prompt7
	li $v0, 4 
	syscall
	
	mfhi $a0 # Move remainder to $a0 and print it
	li $v0, 1
	syscall
	
	la $a0, prompt8 # Print a prompt8
	li $v0, 4 
	syscall				
	
	mflo $a0  # Move quotient to $a0 and print it
	li $v0, 1
	syscall
	
	li $v0, 10 # Terminate the program
	syscall			

