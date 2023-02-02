#include <stdio.h>
#include <string.h>

int main ( int argc, char* argv[] ) {

    printf("$w4g$h311 initialised.\n\n");

    while(1) {
        printf("> ");
        char inp[512];
        char* splt; // token splitter
        char* tokens[256];
        int n = 0; // token count

        if (fgets(inp, 255, stdin) == NULL)
            break; // break if CTRL+D

        inp[strcspn(inp, "\n")] = 0; // removes newline from end

        splt = strtok(inp, " \t|><&;"); // split by delimiter chars

        while (splt != NULL) {
            tokens[n] = splt;
            splt = strtok(NULL, " \t|><&;");
            n++;
        }

        for (int i = 0; i<n; i++) {
            printf("[%d]: '%s'\n", i, tokens[i]);
        }
    }

    return 0;
}