#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int insertionSort(int *arr, int len)
{
    for (int i = 1; i < len; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) // von rechts nach links einsortieren
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
    return 0;
}


/*int printList(int *arr, int len)
{
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }
    return 0;
}*/

int readInputToArray(FILE *in, int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        fscanf(in, "%d", &arr[i]);
    }
    return 0;
}

int main(int argc, char *argv[])
{
   FILE *in = stdin;

   if(argc != 2)
   {
      fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   if(argc == 2)
   {
      in = fopen(argv[1], "r");
      if(!in)
      {
         perror(argv[0]);
         exit(EXIT_FAILURE);
      }
   }   

    long long time1, time2;

    int testArr[100000];

    readInputToArray(in, testArr, 100000);
    time1 = clock;
    insertionSort(testArr, 100000);
    time2 = clock;

    int duration = time2 - time1;
    printf("%d \n", duration);


    if (in != stdin)
    {
        fclose(in);
    }
   if(in!=stdin)
   {
      fclose(in);
   }
   exit(EXIT_SUCCESS);
}
