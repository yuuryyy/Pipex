#include <libc.h>

int main()
{
        char *c = "youssra";

   int i = 0;
   while (c[++i])
        printf("%c", c[i]);
}
