#include <stdlib.h>
#include <stdio.h>
#include "myFunctions.h"

int main() {
    printf("Please, input string: ");
    char thisChar = getchar();
    char lastChar = '\0';
    while (thisChar != EOF) {
        List *list = createList();

        while (thisChar != '\n') {

            // clear double spaces and tabs
            if (thisChar == '\t') thisChar = ' ';
            if (!(thisChar == ' ' && lastChar == ' ')) {
                int check = addNode(list, thisChar);
                if (check == 1) {
                    printf("Error");
                    return 1;
                }
            }
            lastChar = thisChar;
            thisChar = getchar();
        }

       /* if (list == NULL) {
            continue;
        }
        if (list->head == NULL) {
            freeList(list);
            continue;
        }*/

        clearSpaces(list);
        printList(list);
        int wordsHelperArraySize;
        WordHelper *wordsHelperArray = findWords(list, &wordsHelperArraySize);

        findRequiredWords(wordsHelperArray, wordsHelperArraySize);

        printf("Gotten table: \n");
        for (int i = 0; i < wordsHelperArraySize; ++i) {
            printf("word: \"%s\", charSet: \"%s\", isExist: %d\n", wordsHelperArray[i].word,
                   wordsHelperArray[i].sortedCharSet, wordsHelperArray[i].isWordExist);
        }

        // generating and printing output string
        char* outputStr = generateOutputString(wordsHelperArray, wordsHelperArraySize);
        printf("output string is: \"%s\"\n", outputStr);

        free(outputStr);
        freeWordArray(wordsHelperArray, wordsHelperArraySize);
        freeList(list);
        printf("Please, input string: ");
        thisChar = getchar();
    }
    return 1;
}

