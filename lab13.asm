.text
.globl main
    
main: 
    li $v0, 5
    syscall
    move $s0, $v0 
    
   
    li $v0, 5
    syscall
    move $s1, $v0
    

    move $a0, $s0 
    move $a1, $s1 
    jal iswin
    move $s2, $v0 
    
    
    li $v0, 1 
    move $a0, $s2 
    syscall
    
    li $v0, 10 
    syscall

iswin:
    
    add $v0, $a0, $a1 
    beq $v0, 68, win 
    li $v0, 1
    j end
    
win:
    li $v0, 100 
    
end:
    jr $ra
