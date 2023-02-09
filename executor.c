/* executor.c */

#include <stdio.h>
#include <string.h>

int shell_exec(int argc, char* argv[]) {
    if (argc < 0) return 1; // err
    if (argc == 0) return 0;

    /* While the command is a history invocation or alias then replace it with the 
        appropriate command from history or the aliased command respectively */

    /* If command is built-in invoke appropriate function */
    if (strcmp(argv[0], "exit") == 0) return 70;

    /* Else execute command as an external process */

    return 0; // default
}