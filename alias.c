#include <stdio.h>
#include <string.h>


char array[10][2];


char check_alias(char* s){
    for(int i =0; i< 10; i++){
        if (array[i][0] == s){
            return array[i][1];
        }
    }

    return "NONE";

}


char alias(char* alias, char* cmd){
    for(int i= 0; i < 10; i++){
        if(array[i][0] == NULL){
            array[i][0] = alias;
            array[i][1] = cmd;
            return "Finisce";
        }
        
    }
    return "Too many aliases";
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
                        return "Alias Removed";
                    }
                }
                array[i][0] == NULL;
                array[i][1] == NULL;
                return "Alias Removed";
            }
        } 
    }
    return "No such Alias exists";
}


void print_alias(){
    if(array[0][0] == NULL){
        printf("There are no aliases");
    }
    for(int i = 0; i<10; i++){
    }
}