 .data
 
 even: .word 0
 odd: .word 0
 input: .word 0
 prompt: .asciiz "Enter a number: "
 printEven: .asciiz "Sum of even numbers is: "
 printOdd: .asciiz "Sum of odd numbers is: "
 newLine: .asciiz "\n"
 
 .text 
 
 loop: 
 	li $v0, 4
	la $a0, prompt
	syscall
	
	li $v0, 5
	syscall
	sw $v0, input
	
	lw $t0, input
	
	beq $t0, $zero, print
	
	sra $t1, $t0, 1       
        sll $t2, $t1, 1        
        sub $t3, $t0, $t2      
    
        beq $t3, $zero, addEven
        
addOdd:
	lw $s0, odd
	add $s0, $s0, $t0
	sw $s0, odd
	j loop
addEven:
	lw $s1, even
	add $s1, $s1, $t0
	sw $s1, even
	j loop
print: 
 	li $v0, 4
	la $a0, printEven
	syscall

	li $v0, 1
	lw $a0, even
	syscall
	
	li $v0, 4
	la $a0, newLine
	syscall
	
	li $v0, 4
	la $a0, printOdd
	syscall

	li $v0, 1
	lw $a0, odd
	syscall
	
	li $v0, 4
	la $a0, newLine
	syscall
	
end: 
	li $v0, 10
	syscall
	