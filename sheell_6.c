#include "getline.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

void execute_command(char **argv) {
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
        perror("Error forking");
        exit(1);
    } else if (pid == 0) {
        if (execvp(argv[0], argv) < 0) {
            printf("ERROR: exec child process failed\n");
            exit(1);
        }
    } else {
        while (wait(&status) != pid);
    }
}

int main(int ac, char *argv[]) {
    char *prompt = "(Eshell) $ ";
    char *lineptr = NULL;
    size_t n = 0;
    ssize_t bytes_read;
    char **tokens;
    char **argv_copy;

    while (1) {
        printf("%s", prompt);
        bytes_read = my_getline(&lineptr, &n, stdin);

        if (bytes_read < 0) {
            free(lineptr);
            break;
        }

        tokens = strtok(lineptr, " \n");
        argv_copy = malloc(MAX_ARGS * sizeof(char *));
        int i = 0;
        while (tokens != NULL) {
            argv_copy[i] = strdup(tokens);
            i++;
            tokens = strtok(NULL, " \n");
        }
        argv_copy[i] = NULL;

        execute_command(argv_copy);

        for (int j = 0; argv_copy[j] != NULL; j++) {
            free(argv_copy[j]);
        }
        free(argv_copy);
    }

    free(lineptr);
    return 0;
}
