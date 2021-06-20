/////////////////////////////////////////////////////////////////////////////////////////////
// Description                                                                             //
// 		This is the very basic example to show how to link elf file by yourself.           //
//      But actually, we link nothing :p                                                   //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
// Usage                                                                                   //
// 		gcc -c -fno-builtin -masm=intel simple.c                                           //
// 		ld -static -T easy.lds -o simple simple.o                                          //
//      ./simple                                                                           //
//      echo $?     <- should be 88                                                        //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////

char *msg = "hi\n";

void say_hi()
{
	// write(stdout, str, 3)
	asm(
		"mov rdi, 1;"
		"mov rsi, %0;"
		"mov rdx, 3;"
		"mov rax, 1;"
		"syscall;"
		::"r"(msg):"rdi", "rsi", "rdx", "rax"
	);
}

void exit()
{
	// exit(88)
	asm(
		"mov rdi, 88;"
		"mov rax, 0x3c;"
		"syscall;"
		);
}

void entry()
{
	say_hi();
	exit();
}