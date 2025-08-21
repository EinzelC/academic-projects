.data

n: .word 25
prompt: .asciiz "Enter a number: "
str1: .asciiz "Less than\n"
str2: .asciiz "Less than or equal to \n"
str3: .asciiz "Greater than\n"
str4: .asciiz "Greater than or equal to\n"
input: .word 0

.text
main:
    li $v0, 4
    la $a0, prompt
    syscall
    
    li $v0, 5
    syscall
    sw $v0, input
    
    lw $t0, input    
    lw $t1, n         
    
    #blt $t0, $t1, else
    blt $t1, $t0, else
    #la $a0, str4
    la $a0, str2
    j print
    
else: 
    #la $a0, str1
    la $a0, str3
    
print:
    li $v0, 4
    syscall
    
exit:
    li $v0, 10
    syscall
