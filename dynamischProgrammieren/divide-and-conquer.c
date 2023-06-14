#include <stdio.h>

int binarySearch(int arr[], int lowerIndexBound, int upperIndexBound, int key);

int main()
{
    int testArray[] = {1, 2, 3, 4, 5, 6, 7};
    int searched = 2;
    int index = binarySearch(testArray, 0, 6, searched);
    printf("%d is found at position %d\n", searched, index);
}

int binarySearch(int arr[], int lowerIndexBound, int upperIndexBound, int key)
{

    int center = (upperIndexBound + lowerIndexBound) / 2;
    if((lowerIndexBound == upperIndexBound && arr[lowerIndexBound] == key ))
    {
        return lowerIndexBound;
    }
    else 
    {
        return -1;
    }
    if(arr[center] > key)
    {
        return binarySearch(arr, lowerIndexBound, center +1, key);
    }
    else
    {
        return binarySearch(arr, center -1, upperIndexBound, key);
    }
}