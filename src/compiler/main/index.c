#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Token* lex(char *str);

int main(int argc, char *argv[]) {
    FILE *file = fopen(argv[1], "r");

    char *str;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        str[sizeof(buffer)];
        strcpy(str, buffer);
    }

    struct Token *myToken = lex(str);

    free(myToken);

    return 0;
}