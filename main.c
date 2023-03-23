/* main.c */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "executor.h"
#include "history.h"
#include "alias.h"
#define MAX_INPUT_LENGTH 512

int main ( int argc, char* argv[] ) {

    /* Shell Execution Outline */
    /* Find the user home directory from the environment */
    char* homeDirectory = getenv("HOME");
    
    /* Set current working directory to user home directory */
    char cwd[512];
    if (chdir(homeDirectory) != 0) {
        perror("ERROR: Working directory was unable to be set to home directory: ");
        return 1;
    }

    /* Save the current path */
    char* orgPath = strdup(getenv("PATH"));
    
    /* Load history */
    loadHistory();
    /* Load aliases */
    loadAliases();
    printf("$w4g$h311 initialised.\n\n");
    int status = 0;
    int rejecting = 0; // bool to track if shell should loop until end of excessive input to reject all

    /* Do while shell has not terminated */
    while(1) {
        getcwd(cwd,sizeof(cwd));
        /* Display prompt */
        if (!rejecting) printf("$%s> ", cwd);
        char inp[MAX_INPUT_LENGTH];

        /* Read and parse user input */

        // Reading 

        if (fgets(inp, MAX_INPUT_LENGTH, stdin) == NULL) {
            printf("^D\n");
            status = 70; break; // break if CTRL+D
        }
        
        if (strcmp(inp, "\n") == 0) continue; // reprompts if empty line
        
        char* newline_ptr = strstr(inp, "\n");
        if (newline_ptr == NULL) {
            rejecting = 1;              // begins rejection if no newline (ie input > MAX_INPUT_LENGTH chars)
            continue; 
        } else if (rejecting == 1) { 
            rejecting = 0;              // finish rejection if newline is present but still within rejection loop
            fprintf(stderr, "ERROR: Input exceeds character limit (%d).\n", MAX_INPUT_LENGTH);
            continue;
        }

        inp[strcspn(inp, "\n")] = 0; // removes newline from end

        // Parsing

        char* tokens[MAX_TOKENS + 1];   // stores tokenised command split by delimiters
        int tn = parseDelimiterArray(tokens, inp, " \t\n|><&;"); // get number of tokens within newly filled + tokenised 'tokens' array

        /*for (int i=0; i<tn; i++) {
            printf("[%d] %s\n", i, tokens[i]);//stage1 debug
        }*/
        
        // Execute command
        status = shell_exec(tn, tokens);
        
        if (status == 70) break; // custom final exit code
    }

    /* End while */
    printf("Exiting $w4g$h311...\n");
    /* Save history */
    saveHistory();
    /* Save aliases */
    saveAliases();
    /* Restore original path */
    if (setenv("PATH", orgPath, 1) != 0) {
        perror("ERROR: Original path was unable to be restored: ");
        return 1;
    }
    
    /* Exit */
    return status;
}
