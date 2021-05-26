#include <stdio.h>

const char cat[] = {0xf0, 0x9f, 0x90, 0x88, '\0'};
const char shark[] = {0xF0, 0x9F, 0xA6, 0x88, '\0'};
const char dice[] = {0xF0, 0x9F, 0x8E, 0xB2, '\0'};
const char alien[] = {0xF0, 0x9F, 0x91, 0xBE, '\0'};
const char ghost[] = {0xF0, 0x9F, 0x91, 0xBB, '\0'};

int main()
{
    printf("%s", cat);
    printf("%s", shark);
    printf("%s", dice);
    printf("%s", alien);
    printf("%s", ghost);
}
