# A very basic example for how to use nasm to compile assembly code.

## Commands

nasm simple.S -o simple.o -felf64

ld simple.o -o simple -m elf_x86_64

./simple

echo $?
