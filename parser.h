/* parser.h */

int parseDelimiterArray(char* arr[], char* str, char* delims);

void copyArr(char* source[], char* dest[], int count);

int copyArrTilNull(char* source[], char* dest[]);

void fprintArr(FILE* fptr, char* arr[]);