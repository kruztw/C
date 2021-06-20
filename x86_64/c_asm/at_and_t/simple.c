////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Description                                                                                       //
//		This is the very basic example to show how to embed assembly code in AT&T style in C          //
//                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////
// usage                                                                                              //
// 		gcc simple.c -o simple                                                                        //
//      ./simple                                                                                      //
//                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

/*
without output input register, that is without ':' after the instructions.
%: register
$: constant

with output ...
%%: register
%: output , input
$: constant
*/


void say_hi(){

	char msg1[] = "hi\n";
	int rtn_val;

	// write(stdout, msg, 3)
	__asm__ volatile(         // volatile : assembly it, don't ignore !! (For optimization , sometimes code will be ignore.)
		"mov $1, %%rdi\n\t"
		"mov %1, %%rsi\n\t"
		"mov $3, %%rdx\n\t"
		"mov $1, %%rax\n\t;"
		"syscall\n\t"
		"mov %%eax, %0\n\t"
		:"=m"(rtn_val)			    // output  # note: "=r" (write to register) may cause segfault, we only want to write to memory , so use "=m".
		:"r"(msg1)				    // input
		:"rax","rdi", "rsi", "rdx" 	// clobber (tells compiler wchich "registers" were edited.)
	);

	printf("return value: %d\n", rtn_val);
}

int main()
{
	say_hi();
}