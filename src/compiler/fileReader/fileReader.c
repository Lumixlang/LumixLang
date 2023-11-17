#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *fileReader(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Allocate initial memory for str
    size_t str_size = 1024; // or any other initial size
    char *str = malloc(str_size);
    if (str == NULL) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }

    // Read file line by line
    char buffer[1024];
    strcpy(str, ""); // Initialize str as an empty string
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Resize str if necessary
        size_t buffer_len = strlen(buffer);
        size_t str_len = strlen(str);
        if (str_len + buffer_len >= str_size - 1) {
            str_size *= 2; // Double the size (you can adjust this logic as needed)
            str = realloc(str, str_size);
            if (str == NULL) {
                perror("Memory reallocation error");
                fclose(file);
                return NULL;
            }
        }

        // Concatenate the line to str
        strcat(str, buffer);
    }

    fclose(file);
    return str;
}