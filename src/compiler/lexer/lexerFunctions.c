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

char **tokenizeWithoutQuotes(const char *input) {
    char line[256];
    strncpy(line, input, sizeof(line));
    line[sizeof(line) - 1] = '\0';
    char **tokens = NULL;
    char *token;
    char *rest = line;
    int insideQuotes = 0;
    int count = 0;
    while ((token = strtok_r(rest, "\"'{}[]/", &rest))) {
        if (insideQuotes) {
            if (input[strpbrk(input, "\"'{}[]/") - input] == '"' && input[strlen(input) - strlen(rest) - 1] == '"') {
                tokens = realloc(tokens, (count + 1) * sizeof(char *));
                tokens[count] = malloc(strlen(token) + 3);
                sprintf(tokens[count], "\"%s\"", token);
                count++;
            } else if (input[strpbrk(input, "\"'{}[]/") - input] == '\'' && input[strlen(input) - strlen(rest) - 1] == '\'') {
                tokens = realloc(tokens, (count + 1) * sizeof(char *));
                tokens[count] = malloc(strlen(token) + 3);
                sprintf(tokens[count], "\'%s\'", token);
                count++;
            } else if (input[strpbrk(input, "\"'{}[]/") - input] == '{' && input[strlen(input) - strlen(rest) - 1] == '}') {
                tokens = realloc(tokens, (count + 1) * sizeof(char *));
                tokens[count] = malloc(strlen(token) + 3);
                sprintf(tokens[count], "{%s}", token);
                count++;
            } else if (input[strpbrk(input, "\"'{}[]/") - input] == '[' && input[strlen(input) - strlen(rest) - 1] == ']') {
                tokens = realloc(tokens, (count + 1) * sizeof(char *));
                tokens[count] = malloc(strlen(token) + 3);
                sprintf(tokens[count], "[%s]", token);
                count++;
            }  else if (input[strpbrk(input, "\"'{}[]/") - input] == '/' && input[strlen(input) - strlen(rest) - 1] == '/') {
                tokens = realloc(tokens, (count + 1) * sizeof(char *));
                tokens[count] = malloc(strlen(token) + 3);
                sprintf(tokens[count], "/%s/", token);
                count++;
            }
        } else {
            char *subtoken;
            char *subrest = token;
            while ((subtoken = strtok_r(subrest, " ", &subrest))) {
                tokens = realloc(tokens, (count + 1) * sizeof(char *));
                tokens[count] = strdup(subtoken);
                count++;
            }
        }
        insideQuotes = !insideQuotes;
    }
    return tokens;
}

/*To use the function
int numTokens;

char **tokens = tokenizeWithoutQuotes(line, &numTokens);

printf("Tokens:\n");
for (int i = 0; i < numTokens; i++) {
    printf("%d: %s\n", i + 1, tokens[i]);
}

// Free the allocated memory
for (int i = 0; i < numTokens; i++) {
    free(tokens[i]);
}
free(tokens);
*/

char* removeCommentsInsideStrings(const char* input) {
    char* result = malloc(strlen(input) + 1);
    if (!result) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    int insideQuotes = 0;
    int insideComment = 0;
    int resultIndex = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '"') {
            insideQuotes = !insideQuotes;
        } else if (input[i] == '#' && !insideQuotes) {
            if (input[i + 1] == '*' && !insideComment) {
                insideComment = 1;
                i++; // Skip the next '*'
                continue;
            }
        } else if (input[i] == '*' && input[i + 1] == '#' && insideComment) {
            insideComment = 0;
            i++; // Skip the next '/'
            continue;
        }

        if (!insideComment) {
            result[resultIndex++] = input[i];
        }
    }

    result[resultIndex] = '\0';
    return result;
}

char **tokenizeLines(char *str, int *numTokens) {
    char *line;
    int insideBraces = 0;
    int capacity = 10;  // Initial capacity for tokens array
    int count = 0;     // Number of tokens
    char **tokens = malloc(capacity * sizeof(char *));

    if (tokens == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    line = strtok(str, ";\n");
    while (line != NULL) {
        // Check if the line contains an opening brace '{'
        if (strchr(line, '{') != NULL) {
            insideBraces = 1;
        }

        // Tokenize the line if not inside braces
        if (!insideBraces) {
            tokens[count] = strdup(line);
            if (tokens[count] == NULL) {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }
            count++;

            // Resize tokens array if needed
            if (count >= capacity) {
                capacity *= 2;
                tokens = realloc(tokens, capacity * sizeof(char *));
                if (tokens == NULL) {
                    perror("Memory allocation failed");
                    exit(EXIT_FAILURE);
                }
            }
        }

        // Check if the line contains a closing brace '}'
        if (strchr(line, '}') != NULL) {
            insideBraces = 0;
        }

        line = strtok(NULL, ";\n");
    }

    *numTokens = count;
    return tokens;
}

char* trimString(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    size_t length = strlen(input);
    size_t start = 0;
    while (start < length && isspace(input[start])) {
        start++;
    }
    size_t end = length - 1;
    while (end > start && isspace(input[end])) {
        end--;
    }
    size_t trimmedLength = end - start + 1;
    char* result = (char*)malloc((trimmedLength + 1) * sizeof(char));
    if (result != NULL) {
        strncpy(result, input + start, trimmedLength);
        result[trimmedLength] = '\0';
    }
    return result;
}