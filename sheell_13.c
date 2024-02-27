#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_ALIASES 128
#define MAX_ALIAS_LEN 128

struct alias {
    char name[MAX_ALIAS_LEN];
    char value[MAX_ALIAS_LEN];
};

static struct alias aliases[MAX_ALIASES];
static int num_aliases = 0;

void define_alias(const char *name, const char *value) {
    if (num_aliases >= MAX_ALIASES) {
        fprintf(stderr, "Too many aliases\n");
        return;
    }
    strncpy(aliases[num_aliases].name, name, MAX_ALIAS_LEN);
    strncpy(aliases[num_aliases].value, value, MAX_ALIAS_LEN);
    num_aliases++;
}

void replace_alias(char **args) {
    int i;
    for (i = 0; i < num_aliases; i++) {
        if (strcmp(aliases[i].name, args[1]) == 0) {
            args[0] = strdup(aliases[i].value);
            args[1] = NULL;
            return;
        }
    }
}

void print_aliases(void) {
    int i;
    for (i = 0; i < num_aliases; i++) {
        printf("%s=%s\n", aliases[i].name, aliases[i].value);
    }
}
