
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct File_Content 
{
    char *data;
    size_t size;
};

static File_Content ReadEntireFileAndNullTerminate(char *filename) 
{
    FILE *file = fopen(filename, "r");
    File_Content result;

    if (file) {
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

int main()
{
    File_Content file = ReadEntireFileAndNullTerminate("names.txt");
}
