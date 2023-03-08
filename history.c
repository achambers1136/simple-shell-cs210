/* history.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_HISTORY_SIZE 20
#define MAX_TOKENS 50

char* history[MAX_HISTORY_SIZE][MAX_TOKENS]; // circular 2D array
int head = 0;
int tail = -1; // initialise to empty history
int size = 0;

void printArr(char* arr[]) {
  int t = 0;
  while (arr[t] != NULL) {
    printf("%s ", arr[t]);
    t++;
  }
}

int printHistory() {
  if (tail == -1) {
    printf("Nothing to show!\n\n");
    return 0;
  }

  int h = head;
  int index = 1;
  while (h != tail) {
    printf("!%d: ", index);
    printArr(history[h]);
    printf("\n");
    h = (h + 1) % MAX_HISTORY_SIZE;
    index++;
  }
  printf("!%d: ", index);
  printArr(history[tail]);
  printf("\n\n");
  return 0; 
}

void copyArr(char* source[], char* dest[], int count) {
  // copy 'count' times +1 to include null terminator
  for (int i=0; i <= count; i++) {
    dest[i] = source[i];
  }
}

int copyArrTilNull(char* source[], char* dest[]) {
  int argc = 0;
  while (source[argc] != NULL) {
    dest[argc] = source[argc];
    argc++;
  }
  dest[argc] = NULL;
  return argc;
}

int addToHistory(int argc, char* argv[]) {

  if (tail == -1) tail = 0; // init
  else {
    tail = (tail + 1) % MAX_HISTORY_SIZE;

    if (tail == head) {
      head = (head + 1) % MAX_HISTORY_SIZE;
    }
  }

  if (size != MAX_HISTORY_SIZE) {
    size++;
  }

  copyArr(argv, history[tail], argc);

}

// Sets argv to specified index and returns number of arguments in history invocation, or -1 if invalid
int retrieveHistory(char* argv[]) {

  if (size == 0) {
    printf("Nothing to show!\n\n");
    return -1;
  }

  // Represents the One-based index of the target invocation,
  // relative to either the head (positive) or tail (negative)
  int targetIndex;

  if (strcmp(argv[0], "!!") == 0) {
    targetIndex = size;
  } else {
    // converts number after "!" into int and stores in targetIndex
    sscanf((argv[0] + 1), "%d", &targetIndex); 
  }

  if (targetIndex < -20 || targetIndex == 0 || targetIndex > 20) {
    printf("Not a valid history invocation!\n\n");
    return -1;
  } else {

    // gets actual index relative to either head or tail
    int index;
    if (targetIndex > 0) index = (head + (targetIndex - 1)) % MAX_HISTORY_SIZE;
    else                 index = (MAX_HISTORY_SIZE + (tail + (targetIndex + 1))) % MAX_HISTORY_SIZE;

    if (index > (size - 1)) {
      printf("History invocation out of range!\n\n");
      return -1;
    } else {
      return copyArrTilNull(history[index], argv);
    }

  }
}
