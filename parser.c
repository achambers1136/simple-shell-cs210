/* parser.c */

#include <stdio.h>
#include <string.h>

/*
    char* inp   Input string containing commands (or several commands split by ';')
    char* rest  Pointer used by strtok_r in string splitting (NULL for new call)
*/
int shell_exec( char* inp, char* rest ) {
    char* cmd = inp; // semicolon splitter, stores current command for this call
    
    // on initial call
    if (rest == NULL) {
        rest = inp;                         // set rest to reference to string
        cmd = strtok_r(rest, ";", &rest);   // start splitting by semicolon
    }

    char* splt;                 // delimiter splitter
    char* delim = " \t\n|><&";  // list of delimiters
    char* tokens[50];
    int t_cnt = 0;              // stores number of tokens

    // split by delimiter chars into tokens array
    splt = strtok(cmd, delim);
    while (splt != NULL) {
        tokens[t_cnt] = splt;
        splt = strtok(NULL, delim);
        t_cnt++;
    }

    //stage1 testing // temp print tokens
    for (int i = 0; i<t_cnt; i++) {
        printf("[%d]: '%s'\n", i, tokens[i]);
    }

    /* While the command is a history invocation or alias then replace it with the 
        appropriate command from history or the aliased command respectively */


    if (t_cnt > 0) {
        /* If command is built-in invoke appropriate function */
        if (strcmp(tokens[0], "exit") == 0) return 70;

        /* Else execute command as an external process */

    }

    // Recurse if split by semicolon
    if ((cmd = strtok_r(rest, ";", &rest))) {
        printf("[;]\n"); //stage1 testing
        int exit_code = shell_exec(cmd, rest);
        if (exit_code != 0) return exit_code;
    }

    return 0;
}