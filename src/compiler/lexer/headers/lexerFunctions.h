#ifndef LEXERFUNCTIONS_H
#define LEXERFUNCTIONS_H

int isNumeric(const char *str);
int isBoolean(const char *str);
int isAlphabetic(const char *str);
int startsWith(const char *str, const char *prefix);
int findNextCharacterPosition(const char* str, const char *searcher);
int startsEndsChar(char *data, char start, char end);
char **tokenizeWithoutQuotes(const char *input);
char* removeCommentsInsideStrings(const char* input);
char **tokenizeLines(char *str, int *numTokens);

#endif