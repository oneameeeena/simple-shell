#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"

void exit_shell(char **args) {
    if (args[1] == NULL) {
        exit(EXIT_SUCCESS);
    }

    int status;
    if (sscanf(args[1], "%d", &status) != 1) {
        fprintf(stderr, "exit: %s: numeric argument required\n", args[1]);
        exit(EXIT_FAILURE);
    }

    if (status < 0 || status > 255) {
        fprintf(stderr, "exit: %d: numeric argument out of range\n", status);
        exit(EXIT_FAILURE);
    }

    exit(status);
}
