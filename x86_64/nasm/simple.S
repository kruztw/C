section .text
global main

main:                ; exit(88)
    mov rdi, 88
    mov rax, 0x3c
    syscall
