/* main.c */

#include <stdio.h>
#include <string.h>
#include "parser.h"

int main ( int argc, char* argv[] ) {

    /* Shell Execution Outline */
    /* Find the user home directory from the environment */

    /* Set current working directory to user home directory */

    /* Save the current path */

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
            status = 70;
            break; // break if CTRL+D
        }
        
        if (strcmp(inp, "\n") == 0) continue; // reprompts if empty line
        
        inp[strcspn(inp, "\n")] = 0; // removes newline from end

        // Executes input and returns exit code
        status = shell_exec(inp, NULL);

        if (status == 70) break; // custom final exit code
    }

    /* End while */
    /* Save history */

    /* Save aliases */

    /* Restore original path */

    /* Exit */
    return status;
}