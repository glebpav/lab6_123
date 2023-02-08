#ifndef LAB6_123_MYFUNCTIONS_H
#define LAB6_123_MYFUNCTIONS_H

#include "stdbool.h"

typedef struct Node {
    char symbol;
    struct Node *next;
} Node;

typedef struct List {
    struct Node *head;
    struct Node *tail;
} List;

typedef struct WordHelper {
    char *word;
    char *sortedCharSet;
    bool isWordExist;
} WordHelper;

WordHelper *findWords(List *list, int *wordsCount);

List *createList();

void printList(const List *list);

int addNode(List *list, char symbol);

void freeList(List *list);

void clearSpaces(List *list);

char *getSortedSet(char *inputStr);

void findRequiredWords(WordHelper *wordsArray, int wordsArraySize)

#endif //LAB6_123_MYFUNCTIONS_H
