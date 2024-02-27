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
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            if (strchr(args[0], '&') == NULL && strchr(args[0], '|') == NULL) {
                return;
            }
        }
        if (strchr(args[0], '&') == NULL && strchr(args[0], '|') == NULL) {
            return;
        }
        if (strchr(args[0], '&') != NULL) {
            args[strcspn(args[0], "&")] = '\0';
        }
        if (strchr(args[0], '|') != NULL) {
            args[strcspn(args[0], "|")] = '\0';
        }
        if (strchr(args[0], '&') != NULL) {
            args[strcspn(args[0], "&")] = '\0';
            child_pid = fork();
            if (child_pid < 0) {
                perror("Fork failed");
                return;
            } else if (child_pid == 0) {
                // Child process
                if (execvp(args[1], args + 1) < 0) {
                    perror("Command not found");
                    exit(1);
                }
            } else {
                // Parent process
                waitpid(child_pid, &status, 0);
            }
        } else if (strchr(args[0], '|') != NULL) {
            args[strcspn(args[0], "|")] = '\0';
            int pipefd[2];
            if (pipe(pipefd) < 0) {
                perror("Pipe failed");
                return;
            }
            child_pid = fork();
            if (child_pid < 0) {
                perror("Fork failed");
                return;
            } else if (child_pid == 0) {
                // Child process
                close(pipefd[0]);
                if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
                    perror("Dup2 failed");
                    exit(1);
                }
                close(pipefd[1]);
                if (execvp(args[0], args) < 0) {
                    perror("Command not found");
                   
