////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Description                                                                                       //
//		This is the very basic example to show how to embed assembly code in AT&T style in C          //
//                                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////
// usage                                                                                              //
// 		gcc simple.c -o simple -m32                                                                   //
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
		"mov $1, %%ebx\n\t"
		"mov %1, %%ecx\n\t"
		"mov $3, %%edx\n\t"
		"mov $4, %%eax\n\t;"
		"int $0x80\n\t"
		"mov %%eax, %0\n\t"
		:"=m"(rtn_val)			    // output  # note: "=r" (write to register) may cause segfault, we only want to write to memory , so use "=m".
		:"r"(msg1)				    // input
		:"eax","ebx", "ecx", "edx" 	// clobber (tells compiler wchich "registers" were edited.)
	);

	printf("return value: %d\n", rtn_val);
}

int main()
{
	say_hi();
}