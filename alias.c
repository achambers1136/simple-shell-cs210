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
        int h = aliasHead;
        while(h != aliasTail){
            printf("checking alias %s\n", aliases[h]);
            if (strcmp(aliases[h], argv[i]) == 0){
                printf("alias found\n");
                int count = 0;
                for(;;){
                    if(aliasValues[h][count] == NULL){
                        break;
                    }else{
                        count++;
                    }
                }
                argc = spliceIntoArr(argv, argc, aliasValues[h], count, i);
            }
            h = (h + 1) % MAX_ALIASES;
        }
        if (strcmp(aliases[aliasTail], argv[i]) == 0){
            int count = 0;
            for(;;){
                if(aliasValues[aliasTail][count] == NULL){
                    break;
                }else{
                    count++;
                }
            }
            printf("%d, %s, %d, %d", argc, aliasValues[aliasTail][0], count, i);
            //argc = spliceIntoArr(argv, argc, aliasValues[aliasTail], count, i);
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
    fprintArr(stdout, aliases);
    return 0;
}

/*
char unalias(char* alias){
    if(aliases[0][0] != NULL){
        for(int i=0; i<10; i++){
            if(aliases[i][0] == alias){
                for(int x=9; x>i; x--){
                    if(aliases[x][0] != NULL){
                        aliases[i][0] = aliases[x][0];
                        aliases[i][1] = aliases[x][1];
                        aliases[x][0] = NULL;
                        aliases[x][1] = NULL;
                        return 1;
                    }
                }
                aliases[i][0] = NULL;
                aliases[i][1] = NULL;
                return 1;
            }
        } 
    }
    return 2; //return code 2 when requested alias for deletion not present in array
}


void print_alias(){
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
}
*/
