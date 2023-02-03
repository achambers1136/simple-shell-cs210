#include <stdio.h>
#include <string.h>

int main ( int argc, char* argv[] ) {

    /* Shell Execution Outline */
    /* Find the user home directory from the environment */

    /* Set current working directory to user home directory */

    /* Save the current path */

    /* Load history */

    /* Load aliases */

    printf("$w4g$h311 initialised.\n\n");

    /* Do while shell has not terminated */
    while(1) {
        /* Display prompt */
        printf("> ");
        char inp[512];
        char* splt; // token splitter
        char* tokens[256];
        int n = 0; // token count

        /* Read and parse user input */
        if (fgets(inp, 512, stdin) == NULL)
            break; // break if CTRL+D

        inp[strcspn(inp, "\n")] = 0; // removes newline from end

        splt = strtok(inp, " \t|><&;"); // split by delimiter chars

        while (splt != NULL) {
            tokens[n] = splt;
            splt = strtok(NULL, " \t|><&;");
            n++;
        }

        //stage1 testing // temp print tokens
        for (int i = 0; i<n; i++) {
            printf("[%d]: '%s'\n", i, tokens[i]);
        }

        /* While the command is a history invocation or alias then replace it with the 
           appropriate command from history or the aliased command respectively */

        /* If command is built-in invoke appropriate function */
        if (n > 0) {
            if (strcmp(tokens[0], "exit") == 0) break; // exit
        }

        /* Else execute command as an external process */

    }

    /* End while */
    /* Save history */

    /* Save aliases */

    /* Restore original path */

    /* Exit */
    return 0;
}