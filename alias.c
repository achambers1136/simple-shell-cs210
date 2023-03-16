#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"
#define MAX_TOKENS 50
#define MAX_ALIASES 10

char* aliases[MAX_ALIASES];
char* aliasValues[MAX_ALIASES][MAX_TOKENS];


int check_alias(int args, char* cmd[]){
    bool changes = false;
    for(int i = 0; i < args; i++){
        for(int x =0; x< 10; x++){
            if (strcmp(aliases[x][0], cmd[i]) == 0){
                cmd[i] = aliases[x][1];
                return 0;
            }
        }
    }
    return 1;
}


char alias(int args, char* cmd[]){
    for(int i= 0; i < 10; i++){
        if(aliases[i][0] == NULL){
            aliases[i][0] = strdup(cmd[1]);
            aliases[i][1] = strdup(cmd[2]);
            return 1;
        }
        
    }
    return 2; //return code 2 for trying to add an alias when aliases are full...
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

int testAlias(char* argv[], int argc){
    char* inp[] = {"alias", "ls", "ls -l"};

    return spliceIntoArr(argv, argc, inp, 3, 1);
}
