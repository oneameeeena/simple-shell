#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "path.h"
#include "exit.h"
#include "env.h"

#define MAX_LINE_LENGTH 1024
#define MAX_ARGS 64

void execute_command(char *arguments[]) {
    pid_t pid = fork();
    if (pid == 0) {
        if (strcmp(arguments[0], "exit") == 0) {
            exit_shell();
        } else if (strcmp(arguments[0], "env") == 0) {
            print_env();
            exit(EXIT_SUCCESS);
        } else {
            if (path_search(arguments[0]) == NULL) {
                fprintf(stderr, "%s: command not found\n", arguments[0]);
                exit(EXIT_FAILURE);
            }
            if (execvp(arguments[0], arguments) == -1) {
                perror("Error executing command");
                exit(EXIT_FAILURE);
            }
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
    char *arguments[MAX_ARGS];

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

        char *token = strtok(line, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            arguments[i++] = token;
            token = strtok(NULL, " ");
        }
        arguments[i] = NULL;

        execute_command(arguments);
    }

    free(line);
    return 0;
}
