#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int num;
    while(scanf("%d", &num) != EOF)
    {
        num = num*2;
        printf("%d", num);
        printf("\n");
    }

   exit(EXIT_SUCCESS);
   return 0;
}
