#include <stdio.h>

int main()
{
    #ifdef _PATH     // 沒加這行且 gcc 沒加 -D _path=xxx 會噴錯
        puts(_PATH);
    #endif
}
