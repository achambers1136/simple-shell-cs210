/* parser.c */

#include <stdio.h>
#include <string.h>
#define MAX_TOKENS 50

/*  Parses a string into an array of strings, using the specified delimiters.
    Returns the number of tokens parsed, or -1 if the number of tokens exceeds the maximum. */
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

/*  Copies the contents of one array of strings to another.
    Assumes count is the number of elements in the source array, and that they are followed by a null-terminator. */
void copyArr(char* source[], char* dest[], int count) {
  for (int i = 0; i <= count; i++) {
    dest[i] = source[i];
  }
}

/*  Copies the contents of one array of strings to another, until a null-terminator is reached.
    Returns the number of elements copied. */
int copyArrTilNull(char* source[], char* dest[]) {
  int argc = 0;
  while (source[argc] != NULL) {
    dest[argc] = source[argc];
    argc++;
  }
  dest[argc] = NULL;
  return argc;
}

/*  Prints an array of strings to the specified file pointer (/stdout), separated by spaces. */
void fprintArr(FILE* fptr, char* arr[]) {
  int t = 0;
  while (arr[t] != NULL) {
    if (t != 0) fprintf(fptr, " "); // don't print space before first element
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
  /*
  for (int i = (argc + (inpc - 1)) - 1; i >= index; i--) {
    arr[i] = strdup(arr[i - (inpc - 1)]);
  }
  
  for 

  copyArr(inp, &arr[index], inpc);
  
  return argc + (inpc-1);
  */
}