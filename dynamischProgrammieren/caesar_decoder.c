#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int calcShift(int sample[], int cypher[]);

int main(int argc, char *argv[])
{
    FILE *in = stdin;

    if (argc > 3)
    {
        fprintf(stderr, "Usage: %s [<file>] [<file>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (argc == 3)
    {
        in = fopen(argv[1], "r");
        if (!in)
        {
            perror(argv[0]);
            fclose(in);
            exit(EXIT_FAILURE);
        }
        in = fopen(argv[2], "r");
        if (!in)
        {
            perror(argv[0]);
            fclose(in);
            exit(EXIT_FAILURE);
        }
    }
    /* Here: Read from in with (e.g.) fgets(), ... */

    int sampleLetters[25]; // store letter count for each index
    int cypherLetters[25];

    for(int i = 0; i<26; i++)
    {
        sampleLetters[i] = 0;
        cypherLetters[i] = 0;
    }

    char currentChar;
    int currentCharIndex;

    fopen(argv[1], "r"); //count chars in sample
    while ((currentChar = fgetc(in)) != EOF)
    {
        if (isalpha(currentChar))
        {
            currentCharIndex = (int)tolower(currentChar) - 'a';
            sampleLetters[currentCharIndex] = sampleLetters[currentCharIndex] + 1; // increment amount of letters
        }
    }

    fclose(in);
    in = fopen(argv[2], "r");
    fopen(argv[2], "r"); //count chars in cypher
    while ((currentChar = fgetc(in)) != EOF) 
    {
        if (isalpha(currentChar))
        {
            currentCharIndex = (int)tolower(currentChar) - 'a';
            cypherLetters[currentCharIndex] = cypherLetters[currentCharIndex] + 1; // increment amount of letters
            //printf("%d \n", cypherLetters[currentCharIndex]); 
        }
    }
    int shift = calcShift(sampleLetters, cypherLetters);
    printf("\nSolution>> Encode: %d *** Decode: %d \n", shift, 26-shift);

    if (in != stdin)
    {
        fclose(in);
    }
    exit(EXIT_SUCCESS);
}
int calcShift(int sample[], int cypher[])
{
    double highestSimilarity = 0;
    int shift;
    double fractionTop;
    double fractionBottomLeft;
    double fractionBottomRight;
    for (int i = 1; i < 26; i++)
    {
        fractionBottomLeft = 0;
        fractionBottomRight = 0;
        fractionTop = 0;
        double newSimilarity;
        for (int j = 0; j < 26; j++)
        {
            fractionTop += sample[j] * cypher[(j + i) % 26]; // constructs sum
            fractionBottomLeft += pow(sample[j], 2);
            fractionBottomRight += pow(cypher[(j + i) % 26],2);
            
        }
        //printf("BruchOben: %ld", fractionTop);
        //printf("BruchUnten: %lf\n", (sqrt(fractionBottomLeft) * sqrt(fractionBottomRight)));
        newSimilarity = fractionTop / (sqrt(fractionBottomLeft) * sqrt(fractionBottomRight));
        //printf("Kosinus-Aehnlichkeit: %lf\n", newSimilarity);
        //printf("alteAehnlichkeit: %lf \n", highestSimilarity);
        if (newSimilarity > highestSimilarity)
        {
            highestSimilarity = newSimilarity;
            shift = i;
            //printf("shift: %d \n", shift);
        }
    }
    return shift;
}
