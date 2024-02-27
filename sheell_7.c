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

        tokens = custom_tokenize(lineptr, ' ');
        argv_copy = malloc(MAX_ARGS * sizeof(char *));
        int i = 0;
        while (tokens[i] != NULL) {
            argv_copy[i] = tokens[i];
            i++;
        }
        argv_copy[i] = NULL;

        execute_command(argv_copy);

        for (int j = 0; tokens[j] != NULL; j++) {
            free(tokens[j]);
        }
        free(tokens);
        free(argv_copy);
    }

    free(lineptr);
    return 0;
}
