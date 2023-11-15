#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int isNumeric(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int isBoolean(const char *str) {
    char lowerStr[50];
    strcpy(lowerStr, str);
    for (int i = 0; lowerStr[i]; i++) {
        lowerStr[i] = tolower(lowerStr[i]);
    }
    return (strcmp(lowerStr, "true") == 0 || strcmp(lowerStr, "false") == 0);
}

int isAlphabetic(const char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int startsWith(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

int findNextCharacterPosition(const char* str, const char *searcher) {
    int xPos = -1;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == searcher[0]) {
            xPos = i;
            break;
        }
    }
    if (xPos == -1) {
        return -1;
    }
    for (int i = xPos + 1; str[i] != '\0'; ++i) {
        return i;
    }
    return -1;
}

int startsEndsChar(char *data, char start, char end) {
    return data[0] == start && data[strlen(data) - 1] == end;
}

struct Token {
    struct Function {
        struct KeywordFunction {
            char value[50];
        } keywordFunction;
        struct InsideFunction {
            char value[50];
            char type[10];
        } insideFunction;
    } function;
    struct Variable {
        struct TypeVariable {
            char value[50];
        } typeVariable;
        struct NameVariable {
            char value[50];
        } nameVariable;
        struct Operator {
            char value[50];
        } OperatorVariable;
        struct Inside {
            char value[50];
            char type[50];
        } insideVariable;
    } variable;
    struct Error {
            char message[100];
            char codePart[50];
    } error;
};

struct Token* lex(char *str) {
    struct Token *token = malloc(sizeof(struct Token));
    if (token == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    char *line = strtok(str, ";\n");
    while (line != NULL) {
        char keywordFunction[50];
        char insideFunction[50];

        // Function
        if (sscanf(line, "%49[^(\n] (%49[^)\n]", keywordFunction, insideFunction) == 2) {
            strcpy(token->function.keywordFunction.value, keywordFunction);
            strcpy(token->function.insideFunction.value, insideFunction);
            if (startsEndsChar(token->function.insideFunction.value, '\'', '\'') || startsEndsChar(token->function.insideFunction.value, '"', '"')) {
                strcpy(token->function.insideFunction.type, "string");
            } else if (isNumeric(token->function.insideFunction.value)) {
                strcpy(token->function.insideFunction.type, "integer");
            } else if (isBoolean(token->function.insideFunction.value)) {
                strcpy(token->function.insideFunction.type, "boolean");
            } else if (token->function.insideFunction.value[0] == '{' && token->function.insideFunction.value[strlen(token->function.insideFunction.value) - 1] == '}') {
                strcpy(token->function.insideFunction.type, "object");
            } else if (token->function.insideFunction.value[0] == '[' && token->function.insideFunction.value[strlen(token->function.insideFunction.value) - 1] == ']') {
                strcpy(token->function.insideFunction.type, "enumeration");
            } else if (isAlphabetic(token->function.insideFunction.value)) {
                strcpy(token->function.insideFunction.type, "variable");
                // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
            } else {
                strcpy(token->error.message, "Didn't find the type.");
                strcpy(token->error.codePart, line);
                exit(1);
            }
            printf("Function keyword: %s\n", token->function.keywordFunction.value);
            printf("Inside value: %s\n", token->function.insideFunction.value);
            printf("Inside type: %s\n", token->function.insideFunction.type);
        }

        // Variable
        if (startsWith(line, "str") || startsWith(line, "int") || startsWith(line, "bool") || startsWith(line, "obj") || startsWith(line, "auto") || startsWith(line, "enum") || startsWith(line, "")) {
            char firstWord[50];
            char variableName[50];
            char equal[50];
            char insideValue[50];
            if (sscanf(line, "%s", firstWord) == 1 && strcmp(firstWord, "str") == 0 || strcmp(firstWord, "int") == 0 || strcmp(firstWord, "bool") == 0 || strcmp(firstWord, "obj") == 0 || strcmp(firstWord, "auto") == 0 || strcmp(firstWord, "enum") == 0) {
                if (strcmp(firstWord, "str") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            if (sscanf(line, "%s %s %s %255s", firstWord, variableName, equal, insideValue) == 4) {
                                if (startsEndsChar(insideValue, '\'', '\'') || startsEndsChar(insideValue, '"', '"')) {
                                    strcpy(token->variable.insideVariable.type, "string");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "str");
                                } else if (isNumeric(insideValue)) {
                                    strcpy(token->error.message, "You can't assign a string variable to a integer.");
                                    strcpy(token->error.codePart, line);
                                } else if (isBoolean(insideValue)) {
                                    strcpy(token->error.message, "You can't assign a string variable to a boolean.");
                                    strcpy(token->error.codePart, line);
                                } else if (insideValue[0] == '{' && insideValue[strlen(insideValue) - 1] == '}') {
                                    strcpy(token->error.message, "You can't assign a string variable to a object.");
                                    strcpy(token->error.codePart, line);
                                } else if (insideValue[0] == '[' && insideValue[strlen(insideValue) - 1] == ']') {
                                    strcpy(token->error.message, "You can't assign a string variable to a enumeration.");
                                    strcpy(token->error.codePart, line);
                                } else if (isAlphabetic(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "variable");
                                    // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                                }
                            }
                        }
                    }
                } else if (strcmp(firstWord, "int") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            if (sscanf(line, "%s %s %s %255s", firstWord, variableName, equal, insideValue) == 4) {
                                if (startsEndsChar(insideValue, '\'', '\'') || startsEndsChar(insideValue, '"', '"')) {
                                    strcpy(token->error.message, "You can't assign a integer variable to a string.");
                                    strcpy(token->error.codePart, line);
                                } else if (isNumeric(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "integer");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "int");
                                } else if (isBoolean(insideValue)) {
                                    strcpy(token->error.message, "You can't assign a integer variable to a boolean.");
                                    strcpy(token->error.codePart, line);
                                } else if (insideValue[0] == '{' && insideValue[strlen(insideValue) - 1] == '}') {
                                    strcpy(token->error.message, "You can't assign a integer variable to a object.");
                                    strcpy(token->error.codePart, line);
                                } else if (insideValue[0] == '[' && insideValue[strlen(insideValue) - 1] == ']') {
                                    strcpy(token->error.message, "You can't assign a integer variable to a enumeration.");
                                    strcpy(token->error.codePart, line);
                                } else if (isAlphabetic(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "variable");
                                    // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                                }
                            }
                        }
                    }
                } else if (strcmp(firstWord, "bool") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            if (sscanf(line, "%s %s %s %255s", firstWord, variableName, equal, insideValue) == 4) {
                                if (startsEndsChar(insideValue, '\'', '\'') || startsEndsChar(insideValue, '"', '"')) {
                                    strcpy(token->error.message, "You can't assign a boolean variable to a string.");
                                    strcpy(token->error.codePart, line);
                                } else if (isNumeric(insideValue)) {
                                    strcpy(token->error.message, "You can't assign a boolean variable to a integer.");
                                    strcpy(token->error.codePart, line);
                                } else if (isBoolean(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "boolean");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "bool");
                                } else if (insideValue[0] == '{' && insideValue[strlen(insideValue) - 1] == '}') {
                                    strcpy(token->error.message, "You can't assign a boolean variable to a object.");
                                    strcpy(token->error.codePart, line);
                                } else if (insideValue[0] == '[' && insideValue[strlen(insideValue) - 1] == ']') {
                                    strcpy(token->error.message, "You can't assign a boolean variable to a enumeration.");
                                    strcpy(token->error.codePart, line);
                                } else if (isAlphabetic(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "variable");
                                    // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                                }
                            }
                        }
                    }
                } else if (strcmp(firstWord, "obj") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            if (sscanf(line, "%s %s %s %255s", firstWord, variableName, equal, insideValue) == 4) {
                                if (startsEndsChar(insideValue, '\'', '\'') || startsEndsChar(insideValue, '"', '"')) {
                                    strcpy(token->error.message, "You can't assign a object variable to a string.");
                                    strcpy(token->error.codePart, line);
                                } else if (isNumeric(insideValue)) {
                                    strcpy(token->error.message, "You can't assign a object variable to a integer.");
                                    strcpy(token->error.codePart, line);
                                } else if (isBoolean(insideValue)) {
                                    strcpy(token->error.message, "You can't assign a object variable to a boolean.");
                                    strcpy(token->error.codePart, line);
                                } else if (insideValue[0] == '{' && insideValue[strlen(insideValue) - 1] == '}') {
                                    strcpy(token->variable.insideVariable.type, "object");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "obj");
                                } else if (insideValue[0] == '[' && insideValue[strlen(insideValue) - 1] == ']') {
                                    strcpy(token->error.message, "You can't assign a object variable to a enumeration.");
                                    strcpy(token->error.codePart, line);
                                } else if (isAlphabetic(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "variable");
                                    // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                                }
                            }
                        }
                    }
                } else if (strcmp(firstWord, "enum") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            if (sscanf(line, "%s %s %s %255s", firstWord, variableName, equal, insideValue) == 4) {
                                if (startsEndsChar(insideValue, '\'', '\'') || startsEndsChar(insideValue, '"', '"')) {
                                    strcpy(token->error.message, "You can't assign a enumeration variable to a string.");
                                    strcpy(token->error.codePart, line);
                                } else if (isNumeric(insideValue)) {
                                    strcpy(token->error.message, "You can't assign a enumeration variable to a integer.");
                                    strcpy(token->error.codePart, line);
                                } else if (isBoolean(insideValue)) {
                                    strcpy(token->error.message, "You can't assign a enumeration variable to a boolean.");
                                    strcpy(token->error.codePart, line);
                                } else if (insideValue[0] == '{' && insideValue[strlen(insideValue) - 1] == '}') {
                                    strcpy(token->error.message, "You can't assign a enumeration variable to a object.");
                                    strcpy(token->error.codePart, line);
                                } else if (insideValue[0] == '[' && insideValue[strlen(insideValue) - 1] == ']') {
                                    strcpy(token->variable.insideVariable.type, "enumeration");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "enum");
                                } else if (isAlphabetic(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "variable");
                                    // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                                }
                            }
                        }
                    }
                } else if (strcmp(firstWord, "enum") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            if (sscanf(line, "%s %s %s %255s", firstWord, variableName, equal, insideValue) == 4) {
                                if (startsEndsChar(insideValue, '\'', '\'') || startsEndsChar(insideValue, '"', '"')) {
                                    strcpy(token->error.message, "You can't assign a enumeration variable to a string.");
                                    strcpy(token->error.codePart, line);
                                } else if (isNumeric(insideValue)) {
                                    strcpy(token->error.message, "You can't assign a enumeration variable to a integer.");
                                    strcpy(token->error.codePart, line);
                                } else if (isBoolean(insideValue)) {
                                    strcpy(token->error.message, "You can't assign a enumeration variable to a boolean.");
                                    strcpy(token->error.codePart, line);
                                } else if (insideValue[0] == '{' && insideValue[strlen(insideValue) - 1] == '}') {
                                    strcpy(token->error.message, "You can't assign a enumeration variable to a object.");
                                    strcpy(token->error.codePart, line);
                                } else if (insideValue[0] == '[' && insideValue[strlen(insideValue) - 1] == ']') {
                                    strcpy(token->variable.insideVariable.type, "enumeration");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "enum");
                                } else if (isAlphabetic(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "variable");
                                    // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                                }
                            }
                        }
                    }
                } else if (strcmp(firstWord, "auto") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            if (sscanf(line, "%s %s %s %255s", firstWord, variableName, equal, insideValue) == 4) {
                                if (startsEndsChar(insideValue, '\'', '\'') || startsEndsChar(insideValue, '"', '"')) {
                                    strcpy(token->variable.insideVariable.type, "string");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "auto");
                                } else if (isNumeric(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "integer");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "auto");
                                } else if (isBoolean(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "boolean");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "auto");
                                } else if (insideValue[0] == '{' && insideValue[strlen(insideValue) - 1] == '}') {
                                    strcpy(token->variable.insideVariable.type, "object");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "auto");
                                } else if (insideValue[0] == '[' && insideValue[strlen(insideValue) - 1] == ']') {
                                    strcpy(token->variable.insideVariable.type, "enumeration");
                                    strcpy(token->variable.insideVariable.value, insideValue);
                                    strcpy(token->variable.nameVariable.value, variableName);
                                    strcpy(token->variable.OperatorVariable.value, equal);
                                    strcpy(token->variable.typeVariable.value, "enum");
                                } else if (isAlphabetic(insideValue)) {
                                    strcpy(token->variable.insideVariable.type, "variable");
                                    // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                                }
                            }
                        }
                    }
                } else {
                    strcpy(token->error.message, "This type of variable doesn't exist.");
                    strcpy(token->error.codePart, line);
                    exit(1);
                }
            } else {
                if (sscanf(line, "%255s", variableName) == 1) {
                    if (sscanf(line, "%*s %255s", equal) == 1) {
                        if (sscanf(line, "%s %s %255s", variableName, equal, insideValue) == 3) {
                            if (startsEndsChar(insideValue, '\'', '\'') || startsEndsChar(insideValue, '"', '"')) {
                                strcpy(token->variable.insideVariable.type, "string");
                                strcpy(token->variable.insideVariable.value, insideValue);
                                strcpy(token->variable.nameVariable.value, variableName);
                                strcpy(token->variable.OperatorVariable.value, equal);
                                strcpy(token->variable.typeVariable.value, "auto");
                            } else if (isNumeric(insideValue)) {
                                strcpy(token->variable.insideVariable.type, "integer");
                                strcpy(token->variable.insideVariable.value, insideValue);
                                strcpy(token->variable.nameVariable.value, variableName);
                                strcpy(token->variable.OperatorVariable.value, equal);
                                strcpy(token->variable.typeVariable.value, "auto");
                            } else if (isBoolean(insideValue)) {
                                strcpy(token->variable.insideVariable.type, "boolean");
                                strcpy(token->variable.insideVariable.value, insideValue);
                                strcpy(token->variable.nameVariable.value, variableName);
                                strcpy(token->variable.OperatorVariable.value, equal);
                                strcpy(token->variable.typeVariable.value, "auto");
                            } else if (insideValue[0] == '{' && insideValue[strlen(insideValue) - 1] == '}') {
                                strcpy(token->variable.insideVariable.type, "object");
                                strcpy(token->variable.insideVariable.value, insideValue);
                                strcpy(token->variable.nameVariable.value, variableName);
                                strcpy(token->variable.OperatorVariable.value, equal);
                                strcpy(token->variable.typeVariable.value, "auto");
                            } else if (insideValue[0] == '[' && insideValue[strlen(insideValue) - 1] == ']') {
                                strcpy(token->variable.insideVariable.type, "enumeration");
                                strcpy(token->variable.insideVariable.value, insideValue);
                                strcpy(token->variable.nameVariable.value, variableName);
                                strcpy(token->variable.OperatorVariable.value, equal);
                                strcpy(token->variable.typeVariable.value, "enum");
                            } else if (isAlphabetic(insideValue)) {
                                strcpy(token->variable.insideVariable.type, "variable");
                                // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                            }
                        }
                    }
                }
            }
            printf("Inside type: %s\n", token->variable.insideVariable.type);
            printf("Inside value: %s\n", token->variable.insideVariable.value);
            printf("Variable name: %s\n", token->variable.nameVariable.value);
            printf("Variable operator: %s\n", token->variable.OperatorVariable.value);
            printf("Variable type: %s\n", token->variable.typeVariable.value);
        }

        line = strtok(NULL, ";\n");
    }

    return token;
}