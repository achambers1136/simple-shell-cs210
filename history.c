#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_HISTORY_SIZE 20

char** history;
int history_size = 0;
int current_index = 0;

/*void printHistory() {
  //prints the contents of history in ascending order(does not work rn plz ignore)
  for (int i = current_index; i < MAX_HISTORY_SIZE + current_index; i++) {
    if (history[i] != NULL) {
      printf("%d: %s\n", i, history[i]);
    }
  }
}*/

void addToHistory(int argc, char* argv[]) {
  //check if the command the user has entered is "history"
  if (strcmp(argv[0], "history") == 0) {
    printHistory();
  }else {
    //if the user has not entered "history", whatever the user has entered will be added to history
    if (history == NULL) {
      //allocate memory for history
      history = malloc(MAX_HISTORY_SIZE * sizeof(char*));
      for (int i = 0; i < MAX_HISTORY_SIZE; i++) {
        history[i] = NULL;
      }
    }

    //copy into buffer
    char* buffer = malloc(argc * sizeof(char));
    for (int i = 0; i < argc; i++) {
      strcat(buffer, argv[i]);
      strcat(buffer, " ");
    }

    //add the buffer to history
    if (history_size < MAX_HISTORY_SIZE) {
      history[history_size] = buffer;
      history_size++;
    }else {
      history[current_index] = buffer;
      current_index = (current_index + 1) % MAX_HISTORY_SIZE;
    }
  }
}