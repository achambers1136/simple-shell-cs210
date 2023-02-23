/* parser.c */

#include <stdio.h>
#include <string.h>
#define MAX_TOKENS 50

int parseDelimiterArray(char* arr[], char* str, char* delims) {
    char* split = NULL;
    int n = 0;

    while ((split = strtok_r(str, delims, &str))) {
        if (n == MAX_TOKENS) {
            fprintf(stderr, "ERROR: Exceeded token limit (%d). Total number of commands/arguments cannot exceed this value.\n", MAX_TOKENS);
            arr[MAX_TOKENS - 1] = NULL;
            return -1;
        }

        arr[n++] = strdup(split);
    }
    
    arr[n] = NULL; // add NULL pointer to end of array
    
    return n;
}