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

void printArray(char* arr[]) {
  int t = 0;
  while (arr[t] != NULL) {
    printf("%s ", arr[t]);
    t++;
  }
}

int printHistory() {
  if (tail == -1) {
    printf("Nothing to show!\n");
    return 0;
  }

  int h = head;
  int index = 1;
  while (h != tail) {
    printf("!%d: ", index);
    printArray(history[h]);
    printf("\n");
    h = (h + 1) % MAX_HISTORY_SIZE;
    index++;
  }
  printf("!%d: ", index);
  printArray(history[tail]);
  printf("\n");
  return 0; 
}

void copyArr(char* source[], char* dest[], int count) {
  // copy 'count' times +1 to include null terminator
  for (int i=0; i <= count; i++) {
    dest[i] = source[i];
  }
}

int addToHistory(int argc, char* argv[]) {

  if (tail == -1) tail = 0; // init
  else {
    tail = (tail + 1) % MAX_HISTORY_SIZE;

    if (tail == head) {
      head = (head + 1) % MAX_HISTORY_SIZE;
    }
  }

  copyArr(argv, history[tail], argc);

}

int retrieveHistory(int argc, char* argv[]) {
  if (strcspn(argv[1], "!") == 0) {
    
  }
}
