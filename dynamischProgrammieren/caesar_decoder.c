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
            exit(EXIT_FAILURE);
        }
        fclose(in);
        in = fopen(argv[2], "r");
        if (!in)
        {
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    int sampleLetters[26]; 
    int cypherLetters[26];

    for (int i = 0; i < 26; i++)
    {
        sampleLetters[i] = 0;
        cypherLetters[i] = 0;
    }

    int currentCharIndex;
    int currentChar;

    in = fopen(argv[1], "r"); //open sample
    while ((currentChar = fgetc(in)) != EOF)
    {
        if (isalpha(currentChar))
        {
            currentCharIndex = (int)tolower(currentChar) - 'a';
            sampleLetters[currentCharIndex] += 1;
        }
    }

    fclose(in);
    in = fopen(argv[2], "r"); //open cypher 
    while ((currentChar = fgetc(in)) != EOF)
    {
        if (isalpha(currentChar))
        {
            currentCharIndex = (int)tolower(currentChar) - 'a';
            cypherLetters[currentCharIndex] += 1; 
        }
    }
    int shift = calcShift(sampleLetters, cypherLetters);
    printf("\nSolution>> Encode: %d *** Decode: %d \n", shift, 26 - shift);

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
    long double fractionTop;
    long double fractionBottomLeft;
    long double fractionBottomRight;

    for (int i = 0; i < 26; i++)
    {
        fractionBottomLeft = 0;
        fractionBottomRight = 0;
        fractionTop = 0;
        double newSimilarity;

        for (int j = 0; j < 26; j++)
        {
            fractionTop += sample[j] * cypher[(j + i) % 26]; // constructs sum
            fractionBottomLeft += pow(sample[j], 2);
            fractionBottomRight += pow(cypher[(j + i) % 26], 2);
        }

        newSimilarity = fractionTop / (sqrt(fractionBottomLeft) * sqrt(fractionBottomRight));

        if (newSimilarity > highestSimilarity)
        {
            highestSimilarity = newSimilarity;
            shift = i;
        }
    }

    return shift;
}
