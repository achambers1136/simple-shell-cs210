#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#define MAX_TOKENS 50
#define MAX_ALIASES 10

char* aliases[MAX_ALIASES];
char* aliasValues[MAX_ALIASES][MAX_TOKENS];
int aliasHead = 0;
int aliasTail = -1;
int aliasSize = 0;


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
        }
    }
    return argc;
}


int alias(int argc, char* argv[]) {
    if (aliasTail == -1) aliasTail = 0; // init
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
    return 0;
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
            printf("Alias removed. \n");
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
        printf("Alias removed. \n");
        return 0;
    }
    printf("Alias not found. \n");
    return 1;
}

/*void print_alias(){
    if(aliases[0][0] == NULL){
        printf("There are no aliases");
        return;
    }
    for(int i = 0; i<10; i++){
        if(aliases[i][0] != NULL){
            printf("Alias: %s", aliases[i][0]);
            printf("Command: %s", aliases[i][1]);
        }
    }
    return;
}*/
