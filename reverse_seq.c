#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) 
{
    char buffer[BUFFER_SIZE];
    int length = 0;
    int* numbers = NULL;
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) 
    {
        int num;
        if (sscanf(buffer, "%d", &num) != 1) 
        {
            continue;
        }
        numbers = realloc(numbers, sizeof(int) * (length + 1));
        numbers[length] = num;
        length++;
    }

    for (int i = 0; i < length / 2; i++) 
    {
        int temp = numbers[i];
        numbers[i] = numbers[length - 1 - i];
        numbers[length - 1 - i] = temp; 
    }

    for (int i = 0; i < length; i++) 
    {
        printf("%d\n", numbers[i]);
    }

    return 0;
}
