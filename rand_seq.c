#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        int amount = atoi(argv[1]);
        const int MAXNUM = 1000;
		const int MAXITEMS = 10000;
		if(amount >= MAXITEMS )
		{
			exit(EXIT_FAILURE);
		}
        for(int i = 0; i < amount; i++) 
        {
			int output = (int) (random() % MAXNUM);
			printf("%d", output);
			printf("\n");
        }
    }
    else
    {
        exit(EXIT_FAILURE);
        return 1;
    }
    exit(EXIT_SUCCESS);
    return 0;
}
