#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

void cd_shell(char **args) {
    if (args[1] == NULL) {
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
            return;
        }
        int ret = chdir(home);
        if (ret != 0) {
            perror("cd");
        }
    } else if (strcmp(args[1], "-") == 0) {
        char *oldpwd = getenv("OLDPWD");
        if (oldpwd == NULL) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return;
        }
        int ret = chdir(oldpwd);
        if (ret != 0) {
            perror("cd");
        }
    } else {
        int ret = chdir(args[1]);
        if (ret != 0) {
            perror("cd");
        }
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        setenv("PWD", cwd, 1);
    } else {
        perror("getcwd");
    }

    if (getenv("OLDPWD") == NULL) {
        char *cwd_copy = strdup(cwd);
        if (cwd_copy == NULL) {
            perror("strdup");
            return;
        }
        setenv("OLDPWD", cwd_copy, 1);
    }
}
