#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *lex(char *code) {
    char *str = strdup(code);
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    char *token;

    token = strtok(str, ";");

    while (token != NULL) {
        char length = 0;
        while (token[length] != '\0') {
            length++;
        }

        for (int i = 0; i < length; i++) {

            // I need to find a way to access and create the tokens, like in YAML or JSON kind. (An abstract syntax tree)

            printf("%c\n", token[i]);

        }
        printf("\n"); // Seperator between all lines and token lines.
        token = strtok(NULL, ";");
    }

    free(str);

    return code;
}