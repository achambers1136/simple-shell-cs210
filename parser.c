/* parser.c */
#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 50
#define MAX_TOKEN_ARR MAX_TOKENS + 1

/*  Parses a string into an array of strings, using the specified delimiters.
    Returns the number of tokens parsed, or -1 if the number of tokens exceeds the maximum. */
int parseDelimiterArray(char* arr[], char* str, char* delims) {
    char* split = NULL;
    int n = 0;

    while ((split = strtok_r(str, delims, &str))) {
        if (n == MAX_TOKENS) {
            fprintf(stderr, "ERROR: Exceeded token limit (%d). Total number of commands/arguments cannot exceed this value.\n", MAX_TOKENS);
            arr[MAX_TOKENS] = NULL;
            return -1;
        }

        arr[n++] = strdup(split);
    }
    
    arr[n] = NULL; // add NULL pointer to end of array
    
    return n;
}

/*  Copies the contents of one array of strings to another (where c is the number of elements to copy). */
void copyArr(char* source[], char* dest[], int c) {
  for (int i = 0; i < c; i++) {
    dest[i] = strdup(source[i]);
  }
}

/*  Copies the contents of one array of strings to another (where c is the number of elements to copy), and adds a null terminator. */
void copyNTArr(char* source[], char* dest[], int c) {
  copyArr(source, dest, c);
  dest[c] = NULL;
}

/*  Copies the contents of one array of strings to another, until a null-terminator is reached.
    Returns the number of elements copied. */
int copyArrTilNull(char* source[], char* dest[]) {
  int argc = 0;
  while (source[argc] != NULL) {
    dest[argc] = strdup(source[argc]);
    argc++;
  }
  dest[argc] = NULL;
  return argc;
}

/*  Prints an array of strings to the specified file pointer (/stdout), separated by spaces. */
void fprintArr(FILE* fptr, char* arr[]) {
  int t = 0;
  while (arr[t] != NULL) {
    if (t != 0) fprintf(fptr, " "); //don't print space before first element
    fprintf(fptr, "%s", arr[t]);
    t++;
  }
}

int spliceIntoArr(char* arr[], int argc, char* inp[], int inpc, int index){
  if (argc + (inpc - 1) > MAX_TOKENS) {
    fprintf(stderr, "ERROR: Exceeded token limit (%d). Total number of commands/arguments cannot exceed this value.\n", MAX_TOKENS);
    return -1;
  }
  // shift elements to the right
  for (int i = (argc - 1); i > index; i--) {
    arr[i + (inpc-1)] = strdup(arr[i]);
  }
  arr[argc + (inpc-1)] = NULL;
  copyArr(inp, &arr[index], inpc);
  return argc + (inpc-1);
}

int arrLength(char* arr[]){
  int i = 0;
  while(arr[i] != NULL){
    i++;
  }
  return i;
}
