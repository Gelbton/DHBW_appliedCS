#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCOLS 256
#define MAXROWS 256
#define LARGEVAL 10000

typedef struct labyrinth
{
   char map[MAXCOLS + 2][MAXROWS];
   long costs[MAXCOLS][MAXROWS];
   int maxrow;
   int startx;
   int starty;
   int treasureX;
   int treasureY;
} labyrinth, *labyrinth_p;

labyrinth calcCosts(labyrinth maze)
{
   for (int i = 0; i < MAXCOLS; i++)
   {
      for (int j = 0; j < MAXROWS; j++)
      {
         switch (maze.map[i][j])
         {
         case ' ':
            maze.costs[i][j] = 1;
            break;

         case '#':
            maze.costs[i][j] = LARGEVAL;
            break;

         case 'S':
            maze.costs[i][j] = 0;
            break;

         case 'E':
            maze.costs[i][j] = 1;
            break;
         }
      }
   }
   return maze;
}

labyrinth scanMaze(FILE *maze)
{
   labyrinth newLab;
   newLab.startx = -1;
   newLab.starty = -1;
   newLab.treasureX = -1;
   newLab.treasureY = -1;
   char row[MAXCOLS + 2];
   int columns = 0;

   while (fgets(row, sizeof(row), maze))
   {
      strcpy(newLab.map[columns], row);
      if (strchr(row, 'S')) // checks for correct start
      {
         if (newLab.startx == -1)
         {
            newLab.startx = strchr(row, 'S') - row;
            newLab.starty = columns;
         }
         else
         {
            perror("\nInvalid maze format: Has more than one start\n");
            exit(EXIT_FAILURE);
         }
      }
      if (strchr(row, 'X')) // checks for correct goal
      {
         if (newLab.treasureX == -1)
         {
            newLab.treasureX = strchr(row, 'X') - row;
            newLab.treasureY = columns;
         }
         else
         {
            perror("\nInvalid maze format: Has more than one goal\n");
            exit(EXIT_FAILURE);
         }
      }
      columns++;
   }

   newLab.maxrow = columns;
   memset(newLab.costs, -1, sizeof(newLab.costs));
   newLab = calcCosts(newLab);
   return newLab;
}

int solveMaze(labyrinth_p maze, int row, int col)
{
   int dx[] = {1, -1, 0, 0};
   int dy[] = {0, 0, 1, -1};

   char current = maze->map[col][row];
   printf("Current: %c \n", current);
   
   if (current == 'X')
   {
      return 1; 
   }

   if (row >= 0 && row < MAXROWS && col >= 0 && col < MAXCOLS)
   {
      if (current == ' ' || current == 'S')
      {
         maze->map[col][row] = '.'; 
         printf("Current pos: %d %d\n", row, col);
         
         for (int i = 0; i < 4; i++)
         {
            int newRow = row + dx[i];
            int newCol = col + dy[i];
            int success = solveMaze(maze, newRow, newCol);
            
            if (success)
               return 1;  //success
         }
         
         maze->map[col][row] = ' ';  
      }
   }

   return 0;  //failure
}


int printMaze(labyrinth maze)
{
   for (int i = 0; i < maze.maxrow; i++)
   {
      printf("%s", maze.map[i]);
   }
   return 0;
}

int main(int argc, char *argv[])
{
   FILE *in = stdin;

   if (argc > 3)
   {
      fprintf(stderr, "Usage: %s [<file>]\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   if (argc >= 2)
   {
      in = fopen(argv[1], "r");
      if (!in)
      {
         perror(argv[0]);
         exit(EXIT_FAILURE);
      }
   }


   labyrinth lab = scanMaze(in);
   printf("Start position: (%d, %d)\n", lab.startx, lab.starty);
   printf("Treasure position: (%d, %d)\n", lab.treasureX, lab.treasureY);

   printMaze(lab);
   printf("\nAND THIS IS THE SOLUTION\n");
   solveMaze(&lab, lab.starty, lab.startx);
   printMaze(lab);

   if (in != stdin)
   {
      fclose(in);
   }
   exit(EXIT_SUCCESS);
}
