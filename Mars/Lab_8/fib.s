        .data
# n:      .word 13
input: 	.word 0
ask: 	.asciiz "Please enter a number: "
        .text
main: 	add     $t0, $0, $zero
	addi    $t1, $zero, 1
	
	la $a0, ask
	li $v0, 4
	syscall
	
	li $v0, 5
	syscall
	sw $v0, input
	
	lw      $t3, input
		
fib: 	beq     $t3, $0, finish
	add     $t2,$t1,$t0
	move    $t0, $t1
	move    $t1, $t2
	subi    $t3, $t3, 1
	j       fib
		
finish: addi    $a0, $t0, 0
	li      $v0, 1		
	syscall			
	li      $v0, 10		
	syscall			

