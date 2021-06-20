# A very basic example for how to use nasm to compile assembly code.

## Commands

nasm simple.S -f elf32 -o simple.o

ld simple.o -o simple -m elf_i386 

./simple

echo $?
