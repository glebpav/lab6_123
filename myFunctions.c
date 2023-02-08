#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "myFunctions.h"

List *createList() {
    return (List *) calloc(1, sizeof(List));
}

void printList(const List *list) {
    Node *ptr = list->head;
    printf("\"");
    while (ptr) {
        printf("%c", ptr->symbol);
        ptr = ptr->next;
    }
    printf("\"\n");
}

int addNode(List *list, char symbol) {
    Node *new = (Node *) malloc(sizeof(Node));
    if (!new) {
        return 1;
    }
    new->symbol = symbol;
    new->next = NULL;

    // if list is empty past it as the first and the last
    if (!list->head) {
        list->head = new;
        list->tail = new;
    }
    // is list is not empty past it as the last
    else {
        list->tail->next = new;
        list->tail = new;
    }
    return 0;
}

void freeList(List *list) {
    Node *ptr = list->head;
    Node *ptr_pred;
    while (ptr) {
        ptr_pred = ptr;
        ptr = ptr->next;
        free(ptr_pred);
    }
    free(list);
}

void clearSpaces(List *list) {

    if (list->head == NULL) return;

    // clear space at first position
    if (list->head->symbol == ' ') {
        list->head = list->head->next;
    }

    // clear space at last position
    Node *thisNode = list->head;
    Node *lastNode = NULL;
    while (thisNode->next != NULL) {
        lastNode = thisNode;
        thisNode = thisNode->next;
    }
    if (thisNode->symbol == ' ') lastNode->next = NULL;
}

int charComparator(const void *a, const void *b) {
    return *(char *) a - *(char *) b;
}

char *getSortedSet(char *inputStr) {
    if (inputStr == NULL) return NULL;
    if (strlen(inputStr) == 0) return NULL;
    char *duplicateInputStr = strdup(inputStr);
    // sorting chars in word
    qsort(duplicateInputStr, strlen(duplicateInputStr), sizeof(duplicateInputStr[0]), charComparator);
    // deleting same chars
    for (int i = 0; i < strlen(duplicateInputStr) - 1; i++) {
        if (duplicateInputStr[i] == duplicateInputStr[i + 1]) {
            for (int j = i; j < strlen(duplicateInputStr); ++j) duplicateInputStr[j] = duplicateInputStr[j + 1];
            i -= 1;
        }
    }
    return duplicateInputStr;
}

WordHelper *findWords(List *list, int *wordsCount) {

    bool startOfNewWord = false;
    *wordsCount = 0;
    char *word = calloc(100, sizeof(char));
    WordHelper *wordsHelperArray = NULL;
    Node *thisNode = list->head;

    while (thisNode != NULL) {
        if (thisNode->symbol == ' ') {
            startOfNewWord = true;
        }

        // if this is the first letter of word
        if (startOfNewWord) {
            wordsHelperArray = (WordHelper *) realloc(wordsHelperArray, (*wordsCount + 1) * sizeof(WordHelper));
            wordsHelperArray[*wordsCount].word = strdup(word);
            wordsHelperArray[*wordsCount].sortedCharSet = getSortedSet(word);
            wordsHelperArray[*wordsCount].isWordExist = true;
            free(word);
            word = calloc(100, sizeof(char));
            *wordsCount += 1;
        }
            // if it isn't this first letter of word
        else {
            word[strlen(word)] = thisNode->symbol;
        }

        startOfNewWord = false;
        thisNode = thisNode->next;
    }

    wordsHelperArray = (WordHelper *) realloc(wordsHelperArray, (*wordsCount + 1) * sizeof(WordHelper));
    wordsHelperArray[*wordsCount].word = strdup(word);
    wordsHelperArray[*wordsCount].sortedCharSet = getSortedSet(word);
    wordsHelperArray[*wordsCount].isWordExist = true;
    *wordsCount += 1;

    free(word);
    return wordsHelperArray;
}

void findRequiredWords(WordHelper *wordsArray, int wordsArraySize) {
    for (int i = 0; i < wordsArraySize; ++i) {
        if (!wordsArray[i].isWordExist) continue;
        for (int j = i + 1; j < wordsArraySize; ++j) {
            if (strcmp(wordsArray[i].sortedCharSet, wordsArray[j].sortedCharSet) == 0) {
                wordsArray[i].isWordExist = false;
                wordsArray[j].isWordExist = false;
            }
        }
    }
}

char *generateOutputString(WordHelper *wordsArray, int wordsArraySize) {
    char *outputStr = calloc(5, sizeof(char));
    int outputStrLen = 0;
    for (int i = 0; i < wordsArraySize; ++i) {
        if (wordsArray[i].isWordExist) {
            outputStr = realloc(outputStr, (strlen(wordsArray[i].word) + outputStrLen + 2) * sizeof(char));
            if (strlen(wordsArray[i].word) != 0) outputStr = strcat(outputStr, wordsArray[i].word);
            outputStr = strcat(outputStr, " ");
            outputStrLen = strlen(outputStr);
        }
    }
    outputStr[strlen(outputStr) - 1] = '\0';
    return outputStr;
}

void freeWordArray(WordHelper *wordsHelperArray, int arraySize) {
    for (int i = 0; i < arraySize; ++i) {
        free((wordsHelperArray)[i].word);
        free((wordsHelperArray)[i].sortedCharSet);
    }
    free(wordsHelperArray);
}
