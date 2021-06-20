/////////////////////////////////////////////////////////////////////////////////////////////
// Description                                                                             //
// 		This is the very basic example to show how to link elf file by yourself.           //
//      But actually, we link nothing :p                                                   //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////
// Usage                                                                                   //
// 		gcc -c -fno-builtin -masm=intel simple.c -m32                                      //
// 		ld -static -T easy.lds -o simple simple.o -m elf_i386                              //
//      ./simple                                                                           //
//      echo $?     <- should be 88                                                        //
//                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////

char *msg = "hi\n";

void say_hi()
{
	// write(stdout, str, 3)
	asm(
		"mov ebx, 1;"
		"mov ecx, %0;"
		"mov edx, 3;"
		"mov eax, 4;"
		"int 0x80;"
		::"r"(msg):"eax", "ebx", "ecx", "edx"
	);
}

void exit()
{
	// exit(88)
	asm(
		"mov ebx, 88;"
		"mov eax, 1;"
		"int 0x80;"
		);
}

void entry()
{
	say_hi();
	exit();
}