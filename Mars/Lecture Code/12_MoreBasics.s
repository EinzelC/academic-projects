# Title: Demo code for CSE 031 Lecture 16 (Spring 2025)
# Author: Santosh Chandrasekhar

.data # Define the program data.

a:	 .word 	 10
newline: .asciiz "\n"
list:	 .word 	 1, 2, 3, 4, 5, 6 # An array of integers

.text # Define the program instructions.
main:	# Label to define the main program.

	# One way to load data onto $s1 and $s2
	li $s1, 10		
	li $s2, 5

	#Another way to set the set values of $s1 and $s2 is to first build the program, 
	#then set $s1 and $s2 using the pane on the right displaying register values, then running 
	#the program

	addu $s3, $s1, $s2	#Register $s3 now holds the sum of $s1 and $s2

	#addi $a0, $s3, 0	#Load the value $s3 to be printed into $a0

	#Two other ways to load the value $s3 into $a0
	#add $a0, $s3, $zero
	move $a0, $s3

	li $v0, 1 # Load 1 into $v0 to indicate printing of an integer
	syscall # Syscall reads the value in $v0, sees that it is 1, so it expects $a0 to 
		# contain the target VALUE that is then printed.
	
	la $a0, newline
	li $v0, 4
	syscall
	
	la $t0, list	# Have $t0 point to the beginning of the array
	lw $a0, 12($t0) # Load the value list[3] to be printed into $a0
	li $v0, 1	# Load 1 into $v0 to indicate printing of an integer
	syscall	# Syscall reads the value in $v0, sees that it is 1, so it expects $a0 to 
		# contain the target VALUE that is then printed.

	sw $a0, 20($t0) # Store the value in $a0 at list[5]
	
	#print a newline
	li $v0, 4  # Load 4 into $v0 to indicate a print string
	la $a0, newline	# Load the address labelled as newline into $a0. This is where the
		     	# string "\n" is stored
	syscall # Syscall reads the value in $v0, sees that it is 4, so it expects $a0 to 
		# contain the ADDRESS of the null-terminated string (newline) that is then 
		# printed
	
	lw $a0, 20($t0) # Load the value list[5] to be printed into $a0
	li $v0, 1	# Load 1 into $v0 to indicate printing of an integer
	syscall	# Syscall reads the value in $v0, sees that it is 1, so it expects $a0 to 
		# contain the target VALUE that is then printed.
	
	j list
	
	li $v0, 10 # Load a 10 (halt) into $v0
	syscall # The program ends
