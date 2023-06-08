#include <stdio.h>
#include <stdlib.h>

char shiftChar(char c, int shift);

int main(int argc, char *argv[])
{
   FILE *in = stdin;
   if(argc > 3 )
   {
      fprintf(stderr, "Usage: <-k[1-26]> %s [<file>]\n", argv[0]);
      exit(EXIT_FAILURE);
   }

   int key;
   sscanf(argv[1], "-k%d", &key); //extract the key

   if(argc == 3)
   {
      if(key < 1 || key > 26)
      {
         printf("Invalid key value: must be in range of 1 to 26");
         exit(EXIT_FAILURE);
      }
      in = fopen(argv[2], "r");
      if(!in)
      {
         perror(argv[0]);
         exit(EXIT_FAILURE);
      }
   }
   /* Here: Read from in with (e.g.) fgets(), ... */
   char plainChar;
   char cypheredChar;
   while((plainChar = fgetc(in)) != EOF)
   {
      cypheredChar = shiftChar(plainChar, key);
      printf("%c", cypheredChar);
   }
   if(in!=stdin)
   {
      fclose(in);
   }
   exit(EXIT_SUCCESS);
}

char shiftChar(char c, int shift)
{
   char newChar;
   if(c >= 'A' && c <= 'Z')
   {
      newChar = (c - 'A' + shift) % 26 + 'A';
      return newChar;
   }
   if(c >= 'a' && c <= 'z')
   {
      newChar = (c - 'a' + shift) % 26 + 'a';
      return newChar;
   }
   return c;
}
