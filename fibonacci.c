#include <stdio.h>
#include <stdlib.h>


int fibonacciRecursive(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
    }
}
int fibonacciIterative(int n)
{
    if (n <= 1)
    {
        return n;
    }
    else
    {
        int prev1 = 0;
        int prev2 = 1;
        int fib = 0;

        for (int i = 2; i <= n; i++)
        {
            fib = prev1 + prev2;
            prev1 = prev2;
            prev2 = fib;
        }

        return fib;
    }
}
int main(int argc, char *argv[])
{
    FILE *in = stdin;
    long amount = 55;
    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (argc == 2)
    {
        
         amount = atoi(argv[1]);
        in = fopen(argv[1], "r");
        if (!in)
        {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    printf("%d , \n", fibonacciIterative(amount));
    printf("%d , \n", fibonacciRecursive(amount));
    if (in != stdin)
    {
        fclose(in);
    }
    exit(EXIT_SUCCESS);
}
