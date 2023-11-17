#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fileReader(const char *filename);
struct Token* lex(char *str);

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    char *str = fileReader(filename);

    struct Token *myToken = lex(str);

    free(myToken);

    return 0;
}