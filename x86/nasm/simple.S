section .text
global main

main:                ; exit(88)
    mov ebx, 88
    mov eax, 1
    int 0x80
