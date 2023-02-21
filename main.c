/* main.c */

#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "executor.h"
#include <stdlib.h>
#include <unistd.h>


int main ( int argc, char* argv[] ) {

    /* Shell Execution Outline */
    /* Save the current path */
    char* orgPath = strdup(getenv("PATH"));
    /* Find the user home directory from the environment */
    char* homeDirectory = getenv("HOME");
    /* Set current working directory to user home directory */
    int ch = chdir(homeDirectory);
    if (ch == 0){
        printf("current working directory is %s\n", homeDirectory);
    }    else{
        printf("uh oh current working directory has not been set to home ");
    }
    
    /* Load history */

    /* Load aliases */

    printf("$w4g$h311 initialised.\n\n");
    int status = 0;

    /* Do while shell has not terminated */
    while(1) {
        /* Display prompt */
        printf("> ");
        char inp[512];

        /* Read and parse user input */
        if (fgets(inp, 512, stdin) == NULL) {
            printf("^D\n");
            status = 70; break; // break if CTRL+D
        }
        
        if (strcmp(inp, "\n") == 0) continue; // reprompts if empty line
        
        inp[strcspn(inp, "\n")] = 0; // removes newline from end

        char* cmds[50];                                 // stores commands split by ';'
        int cn = parseDelimiterArray(cmds, inp, ";");   // gets number of tokens within newly filled + tokenised 'cmds' array

        for (int i=0; i<cn; i++) {
            printf("[%d] %s\n", i, cmds[i]);//stage1 debug

            char* tokens[50];   // stores tokenised command split by delimiters
            int tn = parseDelimiterArray(tokens, cmds[i], " \t\n|><&"); // get number of tokens within newly filled + tokenised 'tokens' array

            for (int j=0; j<tn; j++) {
                printf("[%d][%d] %s\n", i, j, tokens[j]);//stage1 debug
            }
            
            // Execute command
            status = shell_exec(tn, tokens);
        }

        if (status == 70) break; // custom final exit code
    }

    /* End while */
    printf("Exiting $w4g$h311...\n");
    /* Save history */

    /* Save aliases */

    /* Restore original path */
    if (setenv("PATH", orgPath,1)==0){
        printf(getenv("PATH"));
        printf("\n");
        }else{
            printf("Original path has not been restored")
        }
    
    
    /* Exit */
    return status;
}


