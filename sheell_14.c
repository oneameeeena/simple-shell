#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This is a simple function that expands variables in a string.
// It only handles simple variables of the form $VAR, and does not
// handle more complex cases like ${VAR-default} or $(command).
char *expand_variables(char *input) {
  char *output = malloc(strlen(input) + 1);
  char *input_ptr = input;
  char *output_ptr = output;

  while (*input_ptr != '\0') {
    if (*input_ptr == '$') {
      // We have a potential variable.
      input_ptr++;
      if (*input_ptr == '\0') {
        // The variable is empty.
        *output_ptr++ = '$';
      } else if (*input_ptr == '{') {
        // The variable has a name in curly braces.
        char *brace_start = input_ptr;
        char *brace_end = strchr(brace_start, '}');
        if (brace_end == NULL) {
          // The variable name is not properly terminated.
          *output_ptr++ = '$';
          *output_ptr++ = *input_ptr;
        } else {
          // Expand the variable.
          char *var_name = brace_start + 1;
          char *var_value = getenv(var_name);
          if (var_value == NULL) {
            // The variable is not set.
            *output_ptr++ = '$';
            *output_ptr++ = *brace_start;
          } else {
            // Copy the variable value.
            while (var_name < brace_end) {
              *output_ptr++ = *var_name++;
            }
            input_ptr = brace_end + 1;
          }
        }
      } else {
        // The variable has a simple name.
        char *var_name = input_ptr;
        char *var_value = getenv(var_name);
        if (var_value == NULL) {
          // The variable is not set.
          *output_ptr++ = '$';
          *output_ptr++ = *input_ptr;
        } else {
          // Expand the variable.
          while (*var_name != '\0' && *var_name != '{') {
            *output_ptr++ = *var_name++;
          }
          input_ptr = var_name;
        }
      }
    } else {
      // This is not a variable, just copy the character.
      *output_ptr++ = *input_ptr++;
    }
  }

  *output_ptr = '\0';
  return output;
}

int main() {
  // This is a simple command loop that reads commands, expands variables,
  // and prints the result. In a real shell, you would need to tokenize
  // the command and arguments, and then execute the command with the
  // arguments.
  char line[1024];
  while (1) {
    printf("simple_shell> ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
      // End of file (Ctrl-D).
      break;
    }
    char *expanded_command = expand_variables(line);
    printf("expanded: %s", expanded_command);
    free(expanded_command);
  }

  return 0;
}
