#include <stdio.h>

int bruteForce(int n)
{
    int result1 = -1;
    int result2 = -1;
    if(n == 1)
    {
        return 0;
    }
    if(n% 3 == 0)
    {
       result1 = n/3; 
    }
    if(n%2 == 0)
    {
        result2 = n/2;
    }
    if(result1 && result2 == -1)
    {
        return (1+bruteForce(n-1));
    }
    if(result2<result1)
    {
        return (1+bruteForce(result2));
    }
    else
    {
        return (1+bruteForce(result1));
    }

    
}

int greedy(int n)
{
    if(n % 3 == 0)
    {
        return (greedy(n/3) + 1);
    }
    if(n % 2 == 0)
    {
        return (greedy(n/2) + 1);
    }
    if(n != 1)
    {
        return (greedy(n-1) + 1);
    }
    return 0;
}

int main()
{
    printf("\nBingBong Schritte: %d \n", greedy(37));
    printf("\nBingBong Schritte: %d \n", bruteForce(37));
    return 1;
}