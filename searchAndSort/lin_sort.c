#include <stdio.h>
#include <stdlib.h>

void insertionSort(int* arr, int len)
{
    long long time1, time2;
    time1 = GetUSecClock();
    int i, j, key;
    for (i = 1; i < len; i++)
    {
        key = arr[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (arr[j] > key)
            {
                arr[j + 1] = arr[j];
            }
            else
            {
                break;
            }
        }
        arr[j + 1] = key;
    }
}





int printList(int* arr, int len)
{
    printf("\n");
    for(int i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}

int main()
{
    int test[] = {4, 13, 12, 1, 55, 293, 3, 187, 15};
    int len = 9;
    insertionSort(test, len);
    printList(test, len);

    return 0;
}
