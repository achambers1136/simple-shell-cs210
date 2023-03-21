/* executor.c */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "parser.h"
#include "history.h"
#include "alias.h"

int getpath() {
    printf("%s", getenv("PATH"));
    printf("\n\n");
    return 0;
}

int setpath(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "Syntax error.\n\tUsage: setpath [path]\n\n");
        return 1;
    }
    setenv("PATH", argv[1], 1);
    return 0;
}

int cd(int argc, char* argv[]) {
    if (argc <= 1) {
        chdir(getenv("HOME"));
        return 0;
    }
    
    if (chdir(argv[1]) != 0) {
        perror("ERROR: Current working directory was not changed: ");
        return 1;
    }
    return 0;
}

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
        char* rest = getenv("PATH"); // likely replace this with global path once implemented, doesn't contain current dir
        int status = -1;

        // Support for current dir, ideally should be included in path however
        char lpath[512] = "./";
        strcat(lpath, argv[0]);
        status = execv(lpath, argv);

        while ((PATH_spl = strtok_r(rest, ":", &rest)) && status == -1) {
            char* path = strdup(PATH_spl);
            strcat(strcat(path, "/"), argv[0]);
            //printf("[trying %s]\n", path);
            status = execv(path, argv);
        }

        //printf("Child process finished. (status %d)\n", status);
        if (status != 0) {
            fprintf(stderr, "'%s' is not recognised as a file or internal/external command: ", argv[0]);
            perror("\0");
        }
        
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

    if (strcmp(argv[0], "alias") == 0)          return alias(argc, argv);
    else if (strcmp(argv[0], "unalias") == 0)   return unalias(argc, argv);
    argc = check_alias(argc, argv);

    /* While the command is a history invocation or alias then replace it with the 
        appropriate command from history or the aliased command respectively */
    if      (strcspn(argv[0], "!") == 0)        argc = retrieveHistory(argv);
    else if (strcmp(argv[0], "history") == 0)   return printHistory();
    else addToHistory(argc, argv);

    if (argc < 0) return 1;

    /* If command is built-in invoke appropriate function */
    if      (strcmp(argv[0], "exit") == 0)      return 70;
    else if (strcmp(argv[0], "getpath") == 0)   return getpath();
    else if (strcmp(argv[0], "setpath") == 0)   return setpath(argc, argv);
    else if (strcmp(argv[0], "cd") == 0)        return cd(argc, argv);
    else if (strcmp(argv[0], "alias") == 0)     return alias(argc, argv);
    else if (strcmp(argv[0], "unalias") == 0)   return unalias(argc, argv);

    /* Else execute command as an external process */
    else return shell_exec_ext(argc, argv);
}
