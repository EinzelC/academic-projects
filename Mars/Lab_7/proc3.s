.data
x:	.word 2
y:	.word 4
z:	.word 6
string:	.asciiz "p + q: "
newline: .asciiz "\n"

.text
main:	la $t0, x
	lw $s0, 0($t0)
	la $t0, y
	lw $s1, 0($t0)
	la $t0, z
	lw $s2, 0($t0)
	
	jal foo
	
	#z = x + y + z + foo(x,y,z)
	addu $t0, $s0, $s1
	addu $t0, $t0, $v1
	addu $s2, $s2, $t0
	
	addi $a0, $s2, 0
	li $v0, 1
	syscall
	
	la $a0, newline
	li $v0, 4
	syscall
	
	j end
	
foo:	addiu $sp, $sp -16
	sw $s0, 0($sp)
	sw $s1, 4($sp)
	sw $s2, 8($sp)
	sw $ra, 12($sp)
	
	addu $a0, $s0, $s2
	addu $a1, $s1, $s2
	addu $a2, $s0, $s1
	
	jal bar
	
	subu $a0, $s0, $s2
	subu $a1, $s1, $s0
	addu $a2, $s1, $s1
	
	addi $s0, $v0, 0
	
	jal bar
	
	addi $s1, $v0, 0
	
	addu $v1, $s0, $s1
	
	la $a0, string
	li $v0, 4
	syscall
	
	addi $a0, $v1, 0
	li $v0, 1
	syscall
	
	la $a0, newline
	li $v0, 4
	syscall
	
	lw $s0, 0($sp)
	addiu $sp, $sp 4
	
	lw $s1, 0($sp)
	addiu $sp, $sp 4
	
	lw $s2, 0($sp)
	addiu $sp, $sp 4
	
	lw $ra, 0($sp)
	addiu $sp, $sp 4
	
	jr $ra
	
bar:	subu $t0, $a1, $a0
	sllv $v0, $t0, $a2
	jr $ra

end:
	li $v0, 10
	syscall
