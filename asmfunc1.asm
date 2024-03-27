section .text
bits 64
default rel

global x8664

x8664:
    push rbp
    mov rbp, rsp
    add rbp, 16

    mov rdi, rcx     
    mov rsi, rdx     
    mov rdx, r8      
    mov rcx, r9      

    xorps xmm0, xmm0  

dot_product_loop:
    movss xmm1, [rsi]  
    movss xmm2, [rdx]  
    mulss xmm1, xmm2   
    addss xmm0, xmm1   

    add rsi, 4         
    add rdx, 4        
    dec rdi
    jnz dot_product_loop

    pop rbp
    ret
