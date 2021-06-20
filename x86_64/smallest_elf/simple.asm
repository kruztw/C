;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; References:                                                                             ;;
;;             https://blog.stalkr.net/2014/10/tiny-elf-3264-with-nasm.html                ;;
;;                                                                                         ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;	Usage: 																			       ;;
;;         nasm -f bin simple.asm -o simple											       ;;
;;         chmod +x ./simple                                                               ;;
;;         ./simple 																       ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; notes                                                                                   ;;
;; 		  	$  : current position                                                          ;;
;;			$$ : start address of current section                                          ;;
;;			dw dd dq : http://www.tortall.net/projects/yasm/manual/html/nasm-pseudop.html  ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


BITS 64
	org 0x400000 ; started virtual address

ehdr:										; ELF64_Ehdr
	db 0x7f, "ELF", 2, 1, 1, 0			 	; magic number (Class), Data, Version, OS/ABI, ABI Version
	times 8 db 0							; padding (8 0's)
	dw 2									; e_type
	dw 0x3e									; e_machine
	dd 1									; e_version
	dq _start								; e_entry
	dq phdr - $$							; e_phoff
	dq 0									; e_shoff
	dd 0									; e_flags
	dw ehdrsize								; e_ehsize
	dw phdrsize								; e_phentsize
	dw 1									; e_phnum
	dw 0									; e_shentsize
	dw 0									; e_shnum
	dw 0									; e_shstrndx
	ehdrsize equ $ - ehdr

phdr:										; ELF64_Phdr
	dd 1									; p_type
	dd 5									; p_flags
	dq 0									; p_offset
	dq $$									; p_vaddr
	dq $$									; p_paddr
	dq filesize								; p_filesz
	dq filesize								; p_memsz
	dq 0x1000								; align
	phdrsize equ $ - phdr

main:
	_start:
		mov rdi, 1
		mov rsi, 'hello'
		push rsi
		mov rsi, rsp
		mov rdx, 5
		mov rax, 1
		syscall           					; write(1, "hello", 5)
		xor rdi, rdi
		mov rax, 60							; exit(0)
		syscall

filesize equ $ - $$