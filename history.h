/* history.h */

#define MAX_HISTORY_SIZE 20

int printHistory();
int addToHistory(int argc, char* argv[]);
int retrieveHistory(char* argv[]);
int saveHistory();
int loadHistory();