/* executor.c */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "parser.h"

int shell_exec_ext(int argc, char* argv[]) {
    if (argc < 0) return 1;
    if (argc == 0) return 0;

    pid_t res = fork();

    if (res < 0) {
        fprintf(stderr, "Couldn't spawn a child process.\n");
        return 1;
    }

    if (res == 0) {
        char* PATH_spl;
        char* rest = getenv("PATH"); // likely replace this with global path once implemented, doesn't support current dir
        int status = -1;

        while ((PATH_spl = strtok_r(rest, ":", &rest)) && status == -1) {
            char* path = strdup(PATH_spl);
                  path = strcat( strcat(path, "/"), argv[0] );
            //printf("[trying %s]\n", path);
            status = execv(path, argv);
        } 

        //printf("Child process finished. (status %d)\n", status);
        if (status != 0) fprintf(stderr, "'%s' is not recognised as a file or internal/external command.\n", argv[0]);
        exit(status);
    } else {
        wait(NULL);
        printf("\n");
    }

    return 0;
}

int shell_exec(int argc, char* argv[]) {
    if (argc < 0) return 1; // err
    if (argc == 0) return 0;

    /* While the command is a history invocation or alias then replace it with the 
        appropriate command from history or the aliased command respectively */

    /* If command is built-in invoke appropriate function */
    if (strcmp(argv[0], "exit") == 0) return 70;

    /* Else execute command as an external process */
    else return shell_exec_ext(argc, argv);
}