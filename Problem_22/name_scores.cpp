
#include <stdlib.h>
#include <stdio.h>

struct File_Content {
    char *data;
    size_t size;
};

static FileContent ReadEntireFileAndNullTerminate(char *filename) {
    FILE file;
    File_Content result;

    if (file) {
        fopen(file, "r");
        fseek(file, 0, SEEK_END);
        result.size = ftell(file);
        fseek(file, 0, SEEK_SET);

        result.data = (char *)malloc(result.size + 1);
        fread(result.data, result.size, 1, file);
        fclose(file);

        result.data[result.size] = '\0';
    }

    return result;
}
