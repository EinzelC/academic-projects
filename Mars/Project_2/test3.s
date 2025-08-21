.data 

orig: .space 100	# In terms of bytes (25 elements * 4 bytes each)
sorted: .space 100

str0: .asciiz "Enter the number of assignments (between 1 and 25): "
str1: .asciiz "Enter score: "
str2: .asciiz "Original scores: "
str3: .asciiz "Sorted scores (in descending order): "
str4: .asciiz "Enter the number of (lowest) scores to drop: "
str5: .asciiz "Average (rounded down) with dropped scores removed: "
str6: .asciiz "All scores dropped!\n"
newline: .asciiz "\n"
space: .asciiz " "

.text 

main: 
	addi $sp, $sp -4
	sw $ra, 0($sp)
	
input_num:
	la $a0, str0 
	li $v0, 4 
	syscall 
	li $v0, 5	# Read the number of scores from user
	syscall
	
	# Handle invalid number of scores
	blez $v0, input_num    # if <= 0, ask again
	li $t0, 25
	bgt $v0, $t0, input_num # if > 25, ask again 
	
	move $s0, $v0	# $s0 = numScores
	move $t0, $0
	la $s1, orig	# $s1 = orig
	la $s2, sorted	# $s2 = sorted
	
loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	# Read elements from user
	syscall
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in
	
	# Copy original to sorted array for sorting
	move $t0, $0
copy_loop:
	sll $t1, $t0, 2
	add $t2, $s1, $t1
	add $t3, $s2, $t1
	lw $t4, 0($t2)
	sw $t4, 0($t3)
	addi $t0, $t0, 1
	bne $t0, $s0, copy_loop
	
	move $a0, $s0
	jal selSort	# Call selSort to perform selection sort in original array
	
	li $v0, 4 
	la $a0, str2 
	syscall
	move $a0, $s1	# More efficient than la $a0, orig
	move $a1, $s0
	jal printArray	# Print original scores
	li $v0, 4 
	la $a0, str3 
	syscall 
	move $a0, $s2	# More efficient than la $a0, sorted
	move $a1, $s0
	jal printArray	# Print sorted scores
	
input_drop:
	li $v0, 4 
	la $a0, str4 
	syscall 
	li $v0, 5	# Read the number of (lowest) scores to drop
	syscall
	
	# Handle invalid number of scores to drop
	bltz $v0, input_drop    # if < 0, ask again
	bgt $v0, $s0, input_drop # if > numScores, ask again
	
	beq $v0, $s0, all_dropped # if drop == numScores
	
	move $a1, $v0
	sub $a1, $s0, $a1	# numScores - drop
	move $a0, $s2
	li $v0, 0
	jal calcSum	# Call calcSum to RECURSIVELY compute the sum of scores that are not dropped
	
	# Compute and print average
	div $v0, $a1
	mflo $t0	# average (integer division)
	
	li $v0, 4
	la $a0, str5
	syscall
	li $v0, 1
	move $a0, $t0
	syscall
	li $v0, 4
	la $a0, newline
	syscall
	j end
	
all_dropped:
	li $v0, 4
	la $a0, str6
	syscall
	
end:	lw $ra, 0($sp)
	addi $sp, $sp 4
	li $v0, 10 
	syscall
	
	
# printArray takes in an array and its size as arguments. 
# It prints all the elements in one line with a newline at the end.
printArray:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	
	move $s0, $a0	# array address
	move $t0, $0	# counter
	
print_loop:
	beq $t0, $a1, print_done
	sll $t1, $t0, 2
	add $t1, $s0, $t1
	lw $a0, 0($t1)
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, space
	syscall
	addi $t0, $t0, 1
	j print_loop
	
print_done:
	li $v0, 4
	la $a0, newline
	syscall
	
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	addi $sp, $sp, 8
	jr $ra
	
	
# selSort takes in the number of scores as argument. 
# It performs SELECTION sort in descending order and populates the sorted array
selSort:
	addi $sp, $sp, -16
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	
	move $s0, $a0	# n
	la $s1, sorted	# array
	move $t0, $0	# i = 0
	
outer_loop:
	addi $t1, $t0, 1	# j = i+1
	move $t2, $t0		# maxIndex = i
	bge $t0, $s0, sort_done
	
inner_loop:
	bge $t1, $s0, end_inner
	sll $t3, $t1, 2
	add $t3, $s1, $t3
	lw $t4, 0($t3)		# arr[j]
	sll $t5, $t2, 2
	add $t5, $s1, $t5
	lw $t6, 0($t5)		# arr[maxIndex]
	bge $t4, $t6, new_max
	addi $t1, $t1, 1
	j inner_loop
	
new_max:
	move $t2, $t1		# maxIndex = j
	addi $t1, $t1, 1
	j inner_loop
	
end_inner:
	# Swap arr[i] and arr[maxIndex]
	sll $t3, $t0, 2
	add $t3, $s1, $t3
	lw $t4, 0($t3)		# arr[i]
	sll $t5, $t2, 2
	add $t5, $s1, $t5
	lw $t6, 0($t5)		# arr[maxIndex]
	sw $t6, 0($t3)
	sw $t4, 0($t5)
	
	addi $t0, $t0, 1
	j outer_loop
	
sort_done:
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	addi $sp, $sp, 16
	jr $ra
	
	
# calcSum takes in an array and its size as arguments.
# It RECURSIVELY computes and returns the sum of elements in the array.
calcSum:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	sw $a1, 8($sp)
	
	# Base case: if size == 0, return 0
	beqz $a1, base_case
	
	# Recursive case: return arr[0] + calcSum(arr+1, size-1)
	lw $t0, 0($a0)		# arr[0]
	addi $a0, $a0, 4	# arr+1
	addi $a1, $a1, -1	# size-1
	add $v0, $v0, $t0	# return value + arr[0]
	jal calcSum

	j return
	
base_case:
	# li $v0, 0
	
return:
	lw $ra, 0($sp)
	lw $a0, 4($sp)
	lw $a1, 8($sp)
	addi $sp, $sp, 12
	jr $ra
