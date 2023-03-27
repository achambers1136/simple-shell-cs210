/* alias.h */

#define MAX_ALIASES 10

int printAlias();

int parseAliases(int argc, char* argv[]);

int unalias(int argc, char* argv[]);

int add_alias(char* alias, char* value[], int valc);

char alias(int argc, char* argv[]);

int saveAliases();

int loadAliases();