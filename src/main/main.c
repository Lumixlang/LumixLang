#include <stdio.h>

#include "../cli/cli.c"
#include "../lexer/lexer.c"

int main(int argc, char *argv[]) {
    printf("%s", lex(cli(argc, argv)));
    return 0;
}