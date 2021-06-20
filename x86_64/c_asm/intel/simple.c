////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Description                                                                                       //
//      This is the very basic example to show how to embed assembly code in intel style in C         //
//                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////
// usage                                                                                              //
//      gcc simple.c -o simple -masm=intel                                                            //
//      ./simple                                                                                      //
//                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

void say_hi(){

	char msg1[] = "hi\n";
	int rtn_val;

	// write(stdout, msg, 3)
	__asm__ volatile (                      // volatile : assembly it, don't ignore !! (For optimization , sometimes code will be ignore.)
		"mov rdi,  1;"
		"mov rsi, %1;"
		"mov rdx,  3;"
		"mov rax,  1;"
		"syscall;"
		"mov dword ptr [%0], eax;"
		:"=m"(rtn_val)                  // output  # note: "=r" (write to register) may cause segfault, we only want to write to memory , so use "=m".
		:"r"(msg1)                      // input
		:"rax","rdi", "rsi", "rdx"      // clobber (tells compiler wchich "registers" were edited.)
	);

	printf("return value: %d\n", rtn_val);
}

int main()
{
	say_hi();
}
