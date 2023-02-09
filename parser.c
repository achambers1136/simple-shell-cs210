/* parser.c */

#include <stdio.h>
#include <string.h>

int parseDelimiterArray(char* arr[], char* str, char* delims) {
    char* split;
    char* rest = str;
    int n;

    while ((split = strtok_r(rest, delims, &rest)))
        arr[n++] = split;
    
    if (n > 50) {
        printf("ERROR: Exceeded token limit (50). Total number of commands/arguments cannot exceed this value.\n");
        return -1;
    }
    
    return n;
}