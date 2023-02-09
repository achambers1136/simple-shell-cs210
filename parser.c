/* parser.c */

#include <stdio.h>
#include <string.h>

int parseDelimiterArray(char* arr[], char* str, char* delims) {
    char* split;
    char* rest = str;
    int n;

    while ((split = strtok_r(rest, delims, &rest)))
        arr[n++] = split;
    
    return n;
}