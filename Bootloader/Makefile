all:
	nasm ourbootloader.asm -f bin -o boot.bin
run:
	qemu-system-x86_64 boot.bin
clean:
	rm boot.bin
