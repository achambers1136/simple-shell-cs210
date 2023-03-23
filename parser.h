/* parser.h */

#define MAX_TOKENS 50
#define MAX_TOKEN_ARR MAX_TOKENS + 1

int parseDelimiterArray(char* arr[], char* str, char* delims);

void copyArr(char* source[], char* dest[], int c);

void copyNTArr(char* source[], char* dest[], int c);

int copyArrTilNull(char* source[], char* dest[]);

int spliceIntoArr(char* arr[], int argc, char* inp[], int inpc, int index);

void fprintArr(FILE* fptr, char* arr[]);

int arrLength(char* arr[]);
