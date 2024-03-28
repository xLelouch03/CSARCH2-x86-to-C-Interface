section .text
bits 64
default rel

global x8664

x8664:
    push rbp
    mov rbp, rsp
    add rbp, 16

    xor r10, r10
dot_product_loop:
    cmp r10, rcx
    jae done

    xorps xmm1, xmm1
    xorps xmm2, xmm2
    movss xmm1, [rdx+r10*4]
    movss xmm2, [r8+r10*4]
    mulss xmm1, xmm2   
    addss xmm0, xmm1

    inc r10
    jmp dot_product_loop

done:
    movss [r9], xmm0
    pop rbp
    ret
