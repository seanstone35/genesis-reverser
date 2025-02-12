#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024  // Maximum line length

// Function to reverse a string
void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Function to reverse the entire file content
void reverse_entire_file(const char *input_file, const char *output_file) {
    FILE *fp = fopen(input_file, "r");
    if (!fp) {
        perror("Error opening input file");
        return;
    }

    // Get file size
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    // Read entire content
    char *content = (char *)malloc(size + 1);
    if (!content) {
        perror("Memory allocation failed");
        fclose(fp);
        return;
    }

    fread(content, 1, size, fp);
    fclose(fp);
    content[size] = '\0';  // Null-terminate

    // Reverse content
    reverse_string(content);

    // Write reversed content to output file
    fp = fopen(output_file, "w");
    if (!fp) {
        perror("Error opening output file");
        free(content);
        return;
    }

    fprintf(fp, "%s", content);
    fclose(fp);
    free(content);
}

// Function to reverse each line while keeping paragraph order
void reverse_lines(const char *input_file, const char *output_file) {
    FILE *fp = fopen(input_file, "r");
    if (!fp) {
        perror("Error opening input file");
        return;
    }

    FILE *out_fp = fopen(output_file, "w");
    if (!out_fp) {
        perror("Error opening output file");
        fclose(fp);
        return;
    }

    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, fp)) {
        size_t len = strlen(line);
        
        // Remove newline for proper reversing
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        reverse_string(line);
        fprintf(out_fp, "%s\n", line); // Write reversed line
    }

    fclose(fp);
    fclose(out_fp);
}

int main() {
    const char *input_filename = "genesis.txt";
    const char *output_full_reverse = "genesis_reversed.txt";
    const char *output_line_reverse = "genesis_line_reversed.txt";

    // Generate both reversed files
    reverse_entire_file(input_filename, output_full_reverse);
    reverse_lines(input_filename, output_line_reverse);

    printf("Files generated successfully!\n");

    return 0;
}
