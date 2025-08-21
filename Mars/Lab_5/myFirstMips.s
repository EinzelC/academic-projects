.data
.text
addi $t0, $s0, 0
addi $t1, $t0, -7
addu $t2, $t1, $t0
addi $t3, $t2, 2
addu $t4, $t3, $t2
addi $t5, $t4, -28
subu $t6, $t4, $t5
addi $t7, $t6, 12 

addi, $a0, $t7, 0
li $v0, 1
syscall
li $v0, 10
syscall