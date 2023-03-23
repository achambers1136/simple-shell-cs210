/* alias.c */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "parser.h"

#define MAX_ALIASES 10

char* aliases[MAX_ALIASES];
char* aliasValues[MAX_ALIASES][MAX_TOKEN_ARR];
int aliasHead = 0;
int aliasTail = -1;
int aliasSize = 0;

int printAlias() {
  if (aliasTail == -1) {
    printf("Nothing to show!\n\n");
    return 0;
  }

  int h = aliasHead;
  while (h != aliasTail) {
    printf("%s: ", aliases[h]);
    fprintArr(stdout, aliasValues[h]);
    printf("\n");
    h = (h + 1) % MAX_ALIASES;
  }
  printf("%s: ", aliases[aliasTail]);
  fprintArr(stdout, aliasValues[aliasTail]); // prints final line
  printf("\n\n");
  return 0; 
}

int check_alias(int argc, char* argv[]){
    if(aliasTail == -1) return argc; // init
    for(int i = 0; i < argc; i++){
        //check all but tail
        int h = aliasHead;
        while(h != aliasTail){
            if (strcmp(aliases[h], argv[i]) == 0){
                int count = arrLength(aliasValues[h]);
                if(argc == 1){
                    argc = count;
                    copyNTArr(aliasValues[h], argv, count);
                }else{
                    argc = spliceIntoArr(argv, argc, aliasValues[h], count, i);
                }
                return check_alias(argc, argv);
            }
            h = (h + 1) % MAX_ALIASES;
        }

        //check tail
        if (strcmp(aliases[aliasTail], argv[i]) == 0){
            int count = arrLength(aliasValues[aliasTail]);
            if(argc == 1){
                argc = count;
                copyNTArr(aliasValues[aliasTail], argv, count);
            }else{
                argc = spliceIntoArr(argv, argc, aliasValues[aliasTail], count, i);
            }
            return check_alias(argc, argv);
        }
    }
    return argc;
}

int unalias(int argc, char* argv[]) {
    if (aliasTail == -1) return 0; // init
    int h = aliasHead;
    while(h != aliasTail){
        if (strcmp(aliases[h], argv[1]) == 0){
            aliases[h] = NULL;
            aliasValues[h][0] = NULL;
            aliasSize--;
            aliasTail = (aliasTail - 1);
            if(aliasTail < 0 && aliasSize != 0) aliasTail = MAX_ALIASES - 1;
            printf("Alias removed. o7\n");
            return 0;
        }
        h = (h + 1) % MAX_ALIASES;
    }
    if (strcmp(aliases[aliasTail], argv[1]) == 0){
        aliases[aliasTail] = NULL;
        aliasValues[aliasTail][0] = NULL;
        aliasSize--;
        aliasTail = (aliasTail - 1);
        if(aliasTail < 0 && aliasSize != 0) aliasTail = MAX_ALIASES - 1;
        printf("Alias removed. o7\n");
        return 0;
    }
    printf("Alias not found. \n");
    return 1;
}

int alias(int argc, char* argv[]) {
    if(argc == 1) return printAlias();
    else if (argc == 2) {
        printf("Alias requires at least two arguments. \n");
        return 0;
    }

    if(aliasSize > 0) {
        int cont = 0; // flag to continue aliasing
        int h = aliasHead;
        while(h != aliasTail){
            if (strcmp(aliases[h], argv[1]) == 0){
                printf("Alias already exists. Overriding... x \n");
                unalias(argc, argv);
                cont = 1;
                break;
            }
            h = (h + 1) % MAX_ALIASES;
        }

        if (cont != 1) {
            if (strcmp(aliases[aliasTail], argv[1]) == 0){
                printf("Alias already exists. Overriding... x \n");
                unalias(argc, argv);
            }
        }
        
    }

    if (aliasTail == -1) aliasTail = 0; // init
    else if(aliasSize == MAX_ALIASES){
        printf("Aliases full. \n");
        return 0;
    }
    else { 
        aliasTail = (aliasTail + 1) % MAX_ALIASES;
        if (aliasTail == aliasHead) {
            aliasHead = (aliasHead + 1) % MAX_ALIASES;
        }
    }
    
    if (aliasSize != MAX_ALIASES) {
        aliasSize++;
    }

    aliases[aliasTail] = argv[1];
    copyNTArr(&argv[2], aliasValues[aliasTail], argc-2);
    printf("Alias added. o7\n");
    return 0;
}

int saveAliases(){
    char path[512];
    strcpy(path, getenv("HOME"));
    strcat(path, "/.aliases");
    FILE* fptr = fopen(path, "w"); 

    if (aliasTail == -1) return 0; // No aliases.

    int h = aliasHead;
    while (h != aliasTail) {
        fprintf(fptr, "alias %s ", aliases[h]);
        fprintArr(fptr, aliasValues[h]);
        fprintf(fptr, "\n");
        h = (h + 1) % MAX_ALIASES;
    }

    fprintf(fptr, "alias %s ", aliases[aliasTail]);
    fprintArr(fptr, aliasValues[aliasTail]); // writes final line

    fclose(fptr);
    return 0;
}

int loadAliases(){
    char path[512];
    strcpy(path, getenv("HOME"));
    strcat(path, "/.aliases");
    FILE* fptr = fopen(path, "r"); 

    if (fptr == NULL) return 1; // file does not exist

    char buffer[512]; // stores each line of file over loop
    while(fgets(buffer, sizeof(buffer), fptr) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0; // removes newline from end

        char* argv[MAX_TOKENS + 1];
        int argc = parseDelimiterArray(argv, buffer, " ");
        alias(argc, argv);
    }

    fclose(fptr);
    return 0;   
}
