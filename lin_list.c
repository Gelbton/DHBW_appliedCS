#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int STRMAX = 255;
typedef struct lin_list
{
    char *payload;
    struct lin_list *next;

} LinListCell, *LinList_p;

LinList_p LinListAllocCell(char *payload)
{

    LinListCell *newCell = malloc(sizeof(LinListCell));
    newCell->next = NULL;
    newCell->payload = strdup(payload);
    return newCell;
}
void LinListFreeCell(LinList_p junk)
{
    free(junk->payload);
    free(junk);
}
void freeLastElement(LinList_p junk) // hilfsmethode
{
    LinList_p currentPointer = junk;
    LinList_p prevPointer = NULL;
    while (currentPointer->next)
    {
        prevPointer = currentPointer;
        currentPointer = currentPointer->next;
    }
    if (prevPointer)
    {
        free(currentPointer->payload);
        free(currentPointer);
        prevPointer->next = NULL;
    }
    else
    {
        free(currentPointer->payload);
        free(currentPointer);
    }
}

void LinListFree(LinList_p junk)
{
    while (junk)
    {
        freeLastElement(junk);
    }
}

LinList_p LinListInsertFirst(LinList_p anchor, LinList_p newcell)
{
    LinList_p tempPointer = anchor;
    anchor = newcell;
    newcell->next = tempPointer;
    return anchor;
}

LinList_p LinListExtractFirst(LinList_p anchor)
{
    if (!anchor)
    {
        return NULL;
    }

    LinList_p tempPointer = anchor;
    LinListCell *firstCell = anchor->next;

    if (firstCell)
    {
        free(firstCell->payload);
        anchor->next = firstCell->next;

        free(firstCell);
    }

    return tempPointer;
}

LinList_p LinListFind(LinList_p list, char *vergleiche)
{
    for (LinListCell *i = list; i; i = i->next)
    {
        if (strcmp(vergleiche, i->payload) == 0)
        {
            return i;
        }
    }
    return NULL;
}

void LinListPrint(LinList_p list)
{
    if (!list)
    {
        return;
    }
    printf("%s", list->payload);
    LinListPrint(list->next);
}
LinList_p LinListRevert(LinList_p anchor)
{
    if (anchor == NULL || anchor->next == NULL)
    {
        return anchor;
    }

    LinList_p reversed = LinListRevert(anchor->next);
    anchor->next->next = anchor;
    anchor->next = NULL;

    return reversed;
}
void LinkedListPrintReverse(LinList_p list)
{
    if (!list)
    {
        return;
    }
    LinkedListPrintReverse(list->next);
    printf("%s", list->payload);
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
            perror(argv[1]);
            exit(EXIT_FAILURE);
        }
    }

    char input[STRMAX];
    LinList_p anchor = NULL;

    while (fgets(input, sizeof(input), in))
    {
        if (LinListFind(anchor, input))
        {
            continue; // Duplikate ueberspringen
        }
        anchor = LinListInsertFirst(anchor, LinListAllocCell(input));
    }

    if (in != stdin)
    {
        fclose(in);
    }
    LinkedListPrintReverse(anchor);

    exit(EXIT_SUCCESS);
}