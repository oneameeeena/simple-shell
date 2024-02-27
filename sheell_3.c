#include "SHELL.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "path.h"

#define MAX_LINE_LENGTH 1024
#define MAX_ARGS 64

void execute_command(char *arguments[]) {
    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(arguments[0], arguments) == -1) {
            perror("Error executing command");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("Error forking");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char *line;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        read = getline(&line, &len, stdin);
        if (read == -1) {
            break;
        }

        if (strcmp(line, "exit\n") == 0) {
            break;
        }

        char *arguments[MAX_ARGS];
        char *token = strtok(line, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            arguments[i++] = token;
            token = strtok(NULL, " ");
        }
        arguments[i] = NULL;

        char *path = get_path();
        if (path == NULL) {
            perror("Error getting PATH environment variable");
            continue;
        }

        char *full_path = find_command_in_path(path, arguments[0]);
        if (full_path == NULL) {
            printf("Command not found: %s\n", arguments[0]);
            continue;
        }

        char *arguments_with_path[MAX_ARGS + 1];
        arguments_with_path[0] = full_path;
        for (int j = 1; j < i; j++) {
            arguments_with_path[j] = arguments[j - 1];
        }
        arguments_with_path[i + 1] = NULL;

        execute_command(arguments_with_path);
    }

    free(line);
    return 0;
}
