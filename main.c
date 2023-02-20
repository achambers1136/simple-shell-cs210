/* main.c */

#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "executor.h"

int main ( int argc, char* argv[] ) {

    /* Shell Execution Outline */
    /* Find the user home directory from the environment */

    /* Set current working directory to user home directory */

    /* Save the current path */

    /* Load history */

    /* Load aliases */

    printf("$w4g$h311 initialised.\n\n");
    int status = 0;
    int rejecting = 0; // bool to track if shell should loop until end of excessive input to reject all

    /* Do while shell has not terminated */
    while(1) {
        /* Display prompt */
        if (!rejecting) printf("> ");
        char inp[512];

        /* Read and parse user input */

        // Reading 

        if (fgets(inp, 512, stdin) == NULL) {
            printf("^D\n");
            status = 70; break; // break if CTRL+D
        }
        
        if (strcmp(inp, "\n") == 0) continue; // reprompts if empty line
        
        char* newline_ptr = strstr(inp, "\n");
        if (newline_ptr == NULL) {
            rejecting = 1;                                                      // begins rejection if no newline (ie input > 512 chars)
            continue; 
        } else if (rejecting == 1) { 
            rejecting = 0;                                                      // finish rejection if newline is present but still within rejection loop
            fprintf(stderr, "ERROR: Input exceeds character limit (512).\n");
            continue;
        }

        inp[strcspn(inp, "\n")] = 0; // removes newline from end

        // Parsing

        char* tokens[50];   // stores tokenised command split by delimiters
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

    /* Save aliases */

    /* Restore original path */

    /* Exit */
    return status;
}