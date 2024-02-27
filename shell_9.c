#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

void unsetenv_shell(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "unsetenv: too few arguments\n");
        return;
    }

    int ret = unsetenv(args[1]);
    if (ret != 0) {
        fprintf(stderr, "unsetenv: %s: variable not set\n", args[1]);
    }
}
