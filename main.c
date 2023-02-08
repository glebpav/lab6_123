#include <stdlib.h>
#include <stdio.h>
#include "myFunctions.h"

int main() {
    printf("Please, input string: ");
    char thisChar = getchar();
    char lastChar = '\0';
    while (thisChar != EOF) {
        List *bcell = createList();

        while (thisChar != '\n') {

            // clear double spaces and tabs
            if (thisChar == '\t') thisChar = ' ';
            if (!(thisChar == ' ' && lastChar == ' ')) {
                int check = addNode(bcell, thisChar);
                if (check == 1) {
                    printf("Error");
                    return 1;
                }
            }
            lastChar = thisChar;
            thisChar = getchar();
        }

        clearSpaces(bcell);
        printList(bcell);
        int wordsHelperArraySize;
        WordHelper *wordsHelperArray = findWords(bcell, &wordsHelperArraySize);

        findRequiredWords(wordsHelperArray, wordsHelperArraySize);

        printf("Gotten table: \n");
        for (int i = 0; i < wordsHelperArraySize; ++i) {
            printf("word: \"%s\", charSet: \"%s\", isExist: %d\n", wordsHelperArray[i].word,
                   wordsHelperArray[i].sortedCharSet, wordsHelperArray[i].isWordExist);
        }

        freeList(bcell);
        printf("Please, input string: ");
        thisChar = getchar();
    }
    return 1;
}

