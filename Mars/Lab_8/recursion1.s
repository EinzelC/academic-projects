.data
prompt:		.asciiz "Please enter a number: "
newline:	.asciiz "\n"

.text
main:
	#ask for input
	li $v0, 4
	la $a0, prompt
	syscall
	
	#get input
	li $v0, 5
	syscall
	move $a0, $v0
	
	jal recursion
	
	#print result 
	move $a0, $v0
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	
	#exit
	li $v0, 10
	syscall
	
recursion:
	# save return address and input variable
	addi $sp, $sp, -16
	sw $ra, 12($sp)
	sw $a0, 8($sp)
	
	# check if m == -1
	li $t0, -1
	beq $a0, $t0, return_3
	
	# check if m <= -2
    	li $t0, -2
    	ble $a0, $t0, less_than_neg2
    	
    	# Else case. recursion(m-3)
    	lw $a0, 8($sp)
    	addi $a0, $a0, -3
    	jal recursion
    	sw $v0, 4($sp) #store result of recursion(m-3)
    	
    	# recursion(m-2)
    	lw $a0, 8($sp)
    	addi $a0, $a0, -2
    	jal recursion
    	sw $v0, 0($sp) #store result of recursion (m-2)
    	
    	# original m
    	lw $t0, 8($sp)
    	
    	# Combine results: recursion(m-3) + m + recursion(m-2)
    	lw $t1, 4($sp)
    	lw $t2, 0($sp)
    	add $v0, $t1, $t0
    	add $v0, $v0, $t2
    	
    	j end_recur

return_3:
	li $v0, 3
	j end_recur
	
less_than_neg2:
	# m < -2
    	li $t0, -2
    	blt $a0, $t0, return_2

    	# (m == -2) return 1
    	li $v0, 1 
    	j end_recur
    	
return_2:
	# return -2
	li $v0, 2

end_recur:
	#restore $ra and pop stack
	lw $ra, 12($sp)
	addi $sp, $sp, 16
	jr $ra
