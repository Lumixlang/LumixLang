#include <stdio.h>
#include <stdlib.h>


char *cli(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return NULL; // Return NULL to indicate an error
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", argv[1]);
        return NULL; // Return NULL to indicate an error
    }

    // Determine the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file contents
    char *file_contents = (char *)malloc(file_size + 1);
    if (file_contents == NULL) {
        fclose(file);
        printf("Error: Memory allocation failed\n");
        return NULL; // Return NULL to indicate an error
    }

    // Read the contents of the file
    size_t bytes_read = fread(file_contents, 1, file_size, file);
    if (bytes_read != file_size) {
        fclose(file);
        free(file_contents);
        printf("Error: Failed to read file %s\n", argv[1]);
        return NULL; // Return NULL to indicate an error
    }

    // Null-terminate the string
    file_contents[file_size] = '\0';

    // Close the file
    fclose(file);

    // Return the file contents
    return file_contents;
}