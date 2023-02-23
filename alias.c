#include <stdio.h>
#include <string.h>
#include <stdbool.h>


char* array[11][2];


char check_alias(char* s[]){
    bool changes = false;
    for(int i = 0; s[i] != NULL; i++){
        for(int x =0; x< 10; x++){
            if (array[x][0] == s[i]){
                s[i] = array[x][1];
                changes = true;
            }
        }
    }
    if(changes){
        return 1;
    }else{
        return 0;
    };
}


char alias(char* alias, char* cmd){
    for(int i= 0; i < 10; i++){
        if(array[i][0] == NULL){
            array[i][0] = alias;
            array[i][1] = cmd;
            return 1;
        }
        
    }
    return 2; //return code 2 for trying to add an alias when aliases are full...
}

char unalias(char* alias){
    if(array[0][0] != NULL){
        for(int i=0; i<10; i++){
            if(array[i][0] == alias){
                for(int x=9; x>i; x--){
                    if(array[x][0] != NULL){
                        array[i][0] = array[x][0];
                        array[i][1] = array[x][1];
                        array[x][0] = NULL;
                        array[x][1] = NULL;
                        return 1;
                    }
                }
                array[i][0] = NULL;
                array[i][1] = NULL;
                return 1;
            }
        } 
    }
    return 2; //return code 2 when requested alias for deletion not present in array
}


void print_alias(){
    if(array[0][0] == NULL){
        printf("There are no aliases");
        return;
    }
    for(int i = 0; i<10; i++){
        if(array[i][0] != NULL){
            printf("Alias: %s", array[i][0]);
            printf("Command: %s", array[i][1]);
        }
    }
    return;
}