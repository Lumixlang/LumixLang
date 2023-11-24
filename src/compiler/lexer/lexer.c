#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#include "./headers/lexerFunctions.h"

#define MAX_LEN 50

struct Token {
    // Function
    struct Function {
        struct KeywordFunction {
            char value[MAX_LEN];
        } keywordFunction;
        struct InsideFunction {
            char value[MAX_LEN];
            char type[10];
        } insideFunction;
    } function;
    // Variable
    struct Variable {
        struct TypeVariable {
            char value[MAX_LEN];
        } typeVariable;
        struct NameVariable {
            char value[MAX_LEN];
        } nameVariable;
        struct Operator {
            char value[MAX_LEN];
        } OperatorVariable;
        struct InsideVariable {
            char value[MAX_LEN];
            char type[MAX_LEN];
        } insideVariable;
    } variable;
    // If Statement
    struct IfStatement {
        struct Statement {
            char value[MAX_LEN];
        } statementIfStatement;
        struct InsideIfStatement {
            char value[MAX_LEN];
        } insideIfStatement;
    } ifStatement;
    // Error
    struct Error {
            char message[100];
            char codePart[MAX_LEN];
    } error;
};

struct Token* lex(char *str) {
    str = removeCommentsInsideStrings(str);
    struct Token *token = malloc(sizeof(struct Token));
    if (token == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    char *line = strtok(str, ";\n");
    while (line != NULL) {

        // If statement
        char insideStatement[MAX_LEN];
        char codeInsideStatement[MAX_LEN];
        enum { START, INSIDE_IF, INSIDE_CONDITION, INSIDE_CODE, INSIDE_STRING } state = START;
        int insideIndex = 0;
        int codeIndex = 0;
        for (int i = 0; line[i] != '\0'; ++i) {
            switch (state) {
                case START:
                    if (line[i] == 'i' && strncmp(&line[i], "if", 2) == 0) {
                        state = INSIDE_IF;
                        i += 2;
                    }
                    break;
                case INSIDE_IF:
                    if (line[i] == '(') {
                        state = INSIDE_CONDITION;
                    } else if (line[i] == ' ') {
                    } else {
                        strcpy(token->error.codePart, line);
                        strcpy(token->error.message, "Missing the opening parenthesis.");
                        exit(1);
                    }
                    break;
                case INSIDE_CONDITION:
                    if (line[i] == ')') {
                        state = INSIDE_CODE;
                    } else {
                        insideStatement[insideIndex++] = line[i];
                    }
                    break;
                case INSIDE_CODE:
                    if (line[i] == '{') {
                        state = INSIDE_STRING;
                    }
                    break;
                case INSIDE_STRING:
                    if (line[i] == '}') {
                        state = START;
                    } else {
                        codeInsideStatement[codeIndex++] = line[i];
                    }
                    break;
            }
        }
        insideStatement[insideIndex] = '\0';
        codeInsideStatement[codeIndex] = '\0';
        strcpy(token->ifStatement.insideIfStatement.value, codeInsideStatement);
        strcpy(token->ifStatement.statementIfStatement.value, insideStatement);

        // Function
        char *keywordFunction = NULL;
        char *insideFunction = NULL;
        int lLength = 0;
        while (line[lLength] != '\0') {
            lLength++;
        }
        for (int i = 0; i < lLength; i++) {
            if (line[i] == '(') {
                keywordFunction = malloc((i + 1) * sizeof(char));
                for (int k = 0; k < i; k++) {
                    keywordFunction[k] = line[k];
                }
                keywordFunction[i] = '\0';

                int j = i + 1;
                int insideLength = 0;
                while (line[j] != ')' && line[j] != '\0') {
                    insideFunction = realloc(insideFunction, (insideLength + 1) * sizeof(char));
                    insideFunction[insideLength] = line[j];
                    insideLength++;
                    j++;
                }
            }
        }
        if (keywordFunction != NULL) {
            if (!startsWith(keywordFunction, "if")) { // Doesn't collide with the keywords
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
                } else if (token->function.insideFunction.value[0] == '/' && token->function.insideFunction.value[strlen(token->function.insideFunction.value) - 1] == '/') {
                    strcpy(token->function.insideFunction.type, "regular expression");
                } else if (isAlphabetic(token->function.insideFunction.value)) {
                    strcpy(token->function.insideFunction.type, "variable");
                    // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                } else {
                    strcpy(token->error.message, "Didn't find the type.");
                    strcpy(token->error.codePart, line);
                    exit(1);
                }
            }
            free(keywordFunction);
            free(insideFunction);
        }

        // Variable
        if (startsWith(line, "str") || startsWith(line, "int") || startsWith(line, "bool") || startsWith(line, "obj") || startsWith(line, "enum") || startsWith(line, "regex") || startsWith(line, "auto") || startsWith(line, "")) {
            char firstWord[MAX_LEN];
            char variableName[MAX_LEN];
            char equal[MAX_LEN];
            char *insideValue;
            if ((sscanf(line, "%s", firstWord) == 1 && strcmp(firstWord, "str") == 0) || strcmp(firstWord, "int") == 0 || strcmp(firstWord, "bool") == 0 || strcmp(firstWord, "obj") == 0 || strcmp(firstWord, "enum") == 0 || strcmp(firstWord, "regex") == 0 || strcmp(firstWord, "auto") == 0) {
                if (strcmp(firstWord, "str") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            char **tokens = tokenizeWithoutQuotes(line);

                            insideValue = tokens[3];
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
                            } else if (startsEndsChar(insideValue, '/', '/')) {
                                strcpy(token->error.message, "You can't assign a enumeration variable to a regular expression.");
                                strcpy(token->error.codePart, line);
                            } else if (isAlphabetic(insideValue)) {
                                strcpy(token->variable.insideVariable.type, "variable");
                                // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                            }
                            free(tokens);
                        }
                    }
                } else if (strcmp(firstWord, "int") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            char **tokens = tokenizeWithoutQuotes(line);

                            insideValue = tokens[3];
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
                            } else if (startsEndsChar(insideValue, '/', '/')) {
                                strcpy(token->error.message, "You can't assign a enumeration variable to a regular expression.");
                                strcpy(token->error.codePart, line);
                            } else if (isAlphabetic(insideValue)) {
                                strcpy(token->variable.insideVariable.type, "variable");
                                // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                            }
                            free(tokens);
                        }
                    }
                } else if (strcmp(firstWord, "bool") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            char **tokens = tokenizeWithoutQuotes(line);

                            insideValue = tokens[3];
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
                            } else if (startsEndsChar(insideValue, '/', '/')) {
                                strcpy(token->error.message, "You can't assign a enumeration variable to a regular expression.");
                                strcpy(token->error.codePart, line);
                            } else if (isAlphabetic(insideValue)) {
                                strcpy(token->variable.insideVariable.type, "variable");
                                // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                            }
                            free(tokens);
                        }
                    }
                } else if (strcmp(firstWord, "obj") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            char **tokens = tokenizeWithoutQuotes(line);

                            insideValue = tokens[3];
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
                            } else if (startsEndsChar(insideValue, '/', '/')) {
                                strcpy(token->error.message, "You can't assign a enumeration variable to a regular expression.");
                                strcpy(token->error.codePart, line);
                            } else if (isAlphabetic(insideValue)) {
                                strcpy(token->variable.insideVariable.type, "variable");
                                // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                            }
                            free(tokens);
                        }
                    }
                } else if (strcmp(firstWord, "enum") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            char **tokens = tokenizeWithoutQuotes(line);

                            insideValue = tokens[3];
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
                            } else if (startsEndsChar(insideValue, '/', '/')) {
                                strcpy(token->error.message, "You can't assign a enumeration variable to a regular expression.");
                                strcpy(token->error.codePart, line);
                            } else if (isAlphabetic(insideValue)) {
                                strcpy(token->variable.insideVariable.type, "variable");
                                // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                            }
                            free(tokens);
                        }
                    }
                } else if (strcmp(firstWord, "regex") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            char **tokens = tokenizeWithoutQuotes(line);

                            insideValue = tokens[3];
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
                                strcpy(token->error.message, "You can't assign a regular expression variable to a enumeration.");
                                strcpy(token->error.codePart, line);
                            } else if (startsEndsChar(insideValue, '/', '/')) {
                                strcpy(token->variable.insideVariable.type, "regular expression");
                                strcpy(token->variable.insideVariable.value, insideValue);
                                strcpy(token->variable.nameVariable.value, variableName);
                                strcpy(token->variable.OperatorVariable.value, equal);
                                strcpy(token->variable.typeVariable.value, "regex");
                            } else if (isAlphabetic(insideValue)) {
                                strcpy(token->variable.insideVariable.type, "variable");
                                // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                            }
                            free(tokens);
                        }
                    }
                } else if (strcmp(firstWord, "auto") == 0) {
                    if (sscanf(line, "%*s %255s", variableName) == 1) {
                        if (sscanf(line, "%*s %*s %255s", equal) == 1) {
                            char **tokens = tokenizeWithoutQuotes(line);

                            insideValue = tokens[3];
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
                                strcpy(token->variable.typeVariable.value, "auto");
                            } else if (startsEndsChar(insideValue, '/', '/')) {
                                strcpy(token->variable.insideVariable.type, "regular expression");
                                strcpy(token->variable.insideVariable.value, insideValue);
                                strcpy(token->variable.nameVariable.value, variableName);
                                strcpy(token->variable.OperatorVariable.value, equal);
                                strcpy(token->variable.typeVariable.value, "auto");
                            } else if (isAlphabetic(insideValue)) {
                                strcpy(token->variable.insideVariable.type, "variable");
                                // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                            }
                            free(tokens);
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
                        char **tokens = tokenizeWithoutQuotes(line);

                        insideValue = tokens[3];
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
                        } else if (startsEndsChar(insideValue, '/', '/')) {
                            strcpy(token->variable.insideVariable.type, "regular expression");
                            strcpy(token->variable.insideVariable.value, insideValue);
                            strcpy(token->variable.nameVariable.value, variableName);
                            strcpy(token->variable.OperatorVariable.value, equal);
                            strcpy(token->variable.typeVariable.value, "auto");
                        } else if (isAlphabetic(insideValue)) {
                            strcpy(token->variable.insideVariable.type, "variable");
                            // NEED TO CHECK IF THE VARIABLE SELECTED IS A TYPE STRING.
                        }
                        free(tokens);
                    }
                }
            }
            printf("Inside type: %s\n", token->variable.insideVariable.type);
            printf("Inside value: %s\n", token->variable.insideVariable.value);
            printf("Variable name: %s\n", token->variable.nameVariable.value);
            printf("Variable operator: %s\n", token->variable.OperatorVariable.value);
            printf("Variable type: %s\n", token->variable.typeVariable.value);
            printf("\nIf statement statement: %s\n", token->ifStatement.statementIfStatement.value);
            printf("If statement code: %s\n", token->ifStatement.insideIfStatement.value);
            printf("\nInside function: %s\n", token->function.insideFunction.value);
            printf("Inside function type: %s\n", token->function.insideFunction.type);
            printf("Function keyword: %s", token->function.keywordFunction.value);
        }

        line = strtok(NULL, ";\n");
    }
    free(str);

    return token;
}