#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_HISTORY_SIZE 20

char** history;
int history_size = 0;
int current_index = MAX_HISTORY_SIZE - 1;

void sanitizeString(char* str) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isprint(str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

//this does not work lmao
void printHistory() {
    printf("History:\n");
    int end = current_index;
    int start = (current_index + 1) % MAX_HISTORY_SIZE;
    for (int i = end - 1; i >= start; i--) {
        if (history[i] != NULL) {
            printf("%d: %s\n", i - start + 1, history[i]);
        }
    }
}

void addToHistory(int argc, char* argv[]) {
  // Check if the command the user has entered is "history"
  if (strcmp(argv[0], "history") == 0) {
    printHistory();
  }else {
    // If the user has not entered "history", whatever the user has entered will be added to history
    if (history == NULL) {
      // Allocate memory for history
      history = malloc(MAX_HISTORY_SIZE * sizeof(char*));
      for (int i = 0; i < MAX_HISTORY_SIZE; i++) {
        history[i] = NULL;
      }
    }
    int total_length = 0;
    for (int i = 0; i < argc; i++) {
        total_length += strlen(argv[i]) + 1;
    }
    char* buffer = malloc(total_length * sizeof(char));
    buffer[0] = '\0'; 

    for (int i = 0; i < argc; i++) {
      sanitizeString(argv[i]);
      strcat(buffer, argv[i]);
      strcat(buffer, " ");
    }

    buffer[strlen(buffer) - 1] = '\0';

    if (history_size < MAX_HISTORY_SIZE) {
      history[history_size] = buffer;
      //test bs ignore: printf("The following has just been added to history: %s\n", history[history_size]);
      history_size++;
      }else {
        free(history[current_index]);
        history[current_index] = buffer;
        //test bs ignore: printf("The following has just been added to history: %s\n", history[current_index]);
        current_index = (current_index + 1) % MAX_HISTORY_SIZE;
        if (current_index == 0) {
          current_index = MAX_HISTORY_SIZE - 1;
          }else {
            current_index--;
            }
      }
  }
}





