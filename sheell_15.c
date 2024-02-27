#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void read_line(char **line) {
    char buffer[BUFFER_SIZE];
    char *line_ptr = NULL;
    size_t line_size = 0;
    ssize_t bytes_read;

    while ((bytes_read = getline(&line_ptr, &line_size, stdin)) != -1) {
        // Check if the line is a comment
        if (bytes_read > 0 && line_ptr[0] == '#') {
            // Skip the comment line
            continue;
        }

        // Copy the line to the buffer
        strncpy(buffer, line_ptr, bytes_read);
        buffer[bytes_read - 1] = '\0';

        // Allocate memory for the line and copy it
        *line = malloc(bytes_read);
        strncpy(*line, buffer, bytes_read);

        // Break the loop
        break;
    }
}

int main() {
    char *line;

    while (1) {
        printf("simple_shell> ");
        read_line(&line);

        if (line == NULL) {
            // End of file (Ctrl-D)
            break;
        }

        printf("expanded: %s", line);
        free(line);
    }

    return 0;
}
