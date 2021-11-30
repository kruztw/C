// .mo: /usr/local/share/locale/ru/LC_MESSAGES/gcc.mo

#include <stdio.h>
#include <stdlib.h>
#include <libintl.h>

int main()
{
    bindtextdomain("gcc", "."); // 從 ./ 找 gcc.mo
    textdomain("gcc");          // 使用 gcc.mo 為 textdomain (我不清楚 .mo 是什麼東東)
    printf("max multibytes for one char is %ld\n", __ctype_get_mb_cur_max());
}
