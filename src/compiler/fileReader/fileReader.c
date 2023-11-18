#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fileReader(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    size_t str_size = 1024;
    char *str = malloc(str_size);
    if (str == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }

    char buffer[1024];
    strcpy(str, "");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        size_t buffer_len = strlen(buffer);
        size_t str_len = strlen(str);
        if (str_len + buffer_len >= str_size - 1) {
            str_size *= 2;
            str = realloc(str, str_size);
            if (str == NULL) {
                perror("Memory reallocation error");
                fclose(file);
                return NULL;
            }
        }

        strcat(str, buffer);
    }

    fclose(file);
    return str;
}