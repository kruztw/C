#include <stdio.h>

int main()
{
    int array[10] = {[0 ... 3] = 1, [4 ... 9] = 2};
    for (int i = 0; i < sizeof(array)/sizeof(array[0]); i++)
        printf("array[%d] = %d\n", i, array[i]);
}
