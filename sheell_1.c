#include "SHELL.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE_LENGTH 1024

void execute_command(char *command) {
    char *argv[MAX_LINE_LENGTH/2 + 1];
    int argc = 0;
    char *token = strtok(command, " ");

    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        if (execvp(argv[0], argv) == -1) {
            perror("Error executing command");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Error forking");
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

        execute_command(line);
    }

    free(line);
    return 0;
}

