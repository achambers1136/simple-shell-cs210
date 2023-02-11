/* parser.c */

#include <stdio.h>
#include <string.h>

int parseDelimiterArray(char* arr[], char* str, char* delims) {
    char* split = NULL;
    int n = 0;

    while ((split = strtok_r(str, delims, &str)))
        arr[n++] = strdup(split);

    arr[n] = NULL;
    
    if (n > 50) {
        fprintf(stderr, "ERROR: Exceeded token limit (50). Total number of commands/arguments cannot exceed this value.\n");
        return -1;
    }
    
    return n;
}