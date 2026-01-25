#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Read the given `.env` file and load each values in the environement 
int load_env_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Cannot open .env file");
        return -1;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        // Ignore comments and empty lines
        if (line[0] == '#' || line[0] == '\n') continue;

        // Remove trailing newline
        line[strcspn(line, "\n")] = 0;

        // Find '='
        char *eq = strchr(line, '=');
        if (!eq) continue; // skip malformed lines

        *eq = 0; // split into key and value
        char *key = line;
        char *value = eq + 1;

        // Optionally trim spaces (left/right)
        while (*key == ' ') key++;
        while (*value == ' ') value++;

        // Set environment variable
        setenv(key, value, 1);
    }

    fclose(file);
    return 0;
}