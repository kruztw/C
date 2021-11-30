#include <stdio.h>
#include <locale.h>

int main ()
{
   printf("Locale is: %s\n", setlocale(LC_ALL, NULL));
}
