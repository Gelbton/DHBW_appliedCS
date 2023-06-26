
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int *arr, int low, int high)
{
    int pivotIndex = (low + high) / 2;
    int pivotValue = arr[pivotIndex];

    int temp = arr[high];
    arr[high] = arr[pivotIndex];
    arr[pivotIndex] = temp;

    int smallerPartitionIndex = low;
    for (int currentIndex = low; currentIndex < high; currentIndex++)
    {
        if (arr[currentIndex] < pivotValue)
        {
            temp = arr[smallerPartitionIndex];
            arr[smallerPartitionIndex] = arr[currentIndex];
            arr[currentIndex] = temp;
            smallerPartitionIndex++;
        }
    }

    temp = arr[smallerPartitionIndex];
    arr[smallerPartitionIndex] = arr[high];
    arr[high] = temp;

    return smallerPartitionIndex;
}
int quickSort(int *arr, int lo, int hi)
{
    if (lo < hi)
    {
        int pivotIndex = partition(arr, lo, hi);
        quickSort(arr, lo, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, hi);
    }
    return 0;
}

int readInputToArray(FILE *in, int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        fscanf(in, "%d", &arr[i]);
    }
}

int main(int argc, char *argv[])
{
    FILE *in = stdin;

    if (argc > 2)
    {
        fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (argc == 2)
    {
        in = fopen(argv[1], "r");
        if (!in)
        {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    long long time1, time2;
    const int size = 100000;
    int testArr[size];

    readInputToArray(in, testArr, size);
    time1 = clock;
    quickSort(testArr, 0, size);
    time2 = clock;
    int duration = time2 - time1;
    printf("%d \n", duration);

    if (in != stdin)
    {
        fclose(in);
    }
    exit(EXIT_SUCCESS);
}