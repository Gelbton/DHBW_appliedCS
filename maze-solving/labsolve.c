#include <stdio.h>
#include <stdlib.h>

#define MAXCOLS 256
#define MAXROWS 256

typedef struct labyrinth
{
    char map[MAXCOLS+2][MAXROWS];
    long costs[MAXCOLS][MAXROWS];
    int maxrow;
    int startx;
    int starty;
    int treasureX;
    int treasureY;
} labyrinth, *labyrinth_p;

int main(int argc, char *argv[])
{
   FILE *in = stdin;

   if(argc > 2)
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
   
   if(in!=stdin)
   {
      fclose(in);
   }
   exit(EXIT_SUCCESS);
}

struct labyrinth scanMaze(FILE* maze)
{
   labyrinth newLab;
}

int verifyMaze(FILE* map)
{
    FILE* in = fopen(map, "r");
    if(!in)
    {
        return -1;
    }
    while(fgetc)
}
