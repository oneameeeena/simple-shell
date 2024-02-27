#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#include "getline.h"
#include "tokenize.h"
#include "cd.h"
#include "exit.h"
#include "setenv.h"
#include "unsetenv.h"

void process_command(char **args) {
    pid_t child_pid;
    int status;

    if (strcmp(args[0], "exit") == 0) {
        exit_shell(args);
        return;
    } else if (strcmp(args[0], "setenv") == 0) {
        setenv_shell(args + 1);
        return;
    } else if (strcmp(args[0], "unsetenv") == 0) {
        unsetenv_shell(args + 1);
        return;
    } else if (strcmp(args[0], "cd") == 0) {
        cd_shell(args);
        return;
    }

    child_pid = fork();
    if (child_pid < 0) {
        perror("Fork failed");
        return;
    } else if (child_pid == 0) {
        // Child process
        if (execvp(args[0], args) < 0) {
            perror("Command not found");
            exit(1);
        }
    } else {
        // Parent process
        waitpid(child_pid, &status, 0);
    }
}

int main() {
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    char **tokens;
    int i;

    while (1) {
        printf("#cisfun$ ");
        linelen = getline(&line, &linecap, stdin);
        if (linelen <= 0) {
            break;
        }

        // Tokenize the input line
        tokens = tokenize(line, ";");

        // Process each command separately
        for (i = 0; tokens[i] != NULL; i++) {
            char **command_args = tokenize(tokens[i], " \t\r\n\a");
            process_command(command_args);
            free(command_args);
        }

        free(tokens);
    }

    free(line);
    return 0;
}
