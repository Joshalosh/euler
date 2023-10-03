
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

static bool IsEndOfLine(char c) 
{
    bool   result = (c == '\n' || c == '\r');
    return result;
}

static bool IsWhitespace(char c) 
{
    bool   result = (c == ' ' || c == '\t' || c == '\v' || c == '\f' || IsEndOfLine(c));
    return result;
}

static bool IsAlpha(char c) 
{
    bool   result = ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    return result;
}

static bool IsNumber(char c) 
{
    bool   result = (c >= '0' && c <= '9');
    return result;
}

static void EatAllWhitespace(char *stream)
{
    while (stream[0]) {
        if (IsWhitespace(stream[0])) {
            stream++;
        } else if (stream[0] == '/' && stream[1] == '/') {
            while (stream[0] && !IsEndOfLine(stream[0])) {
                stream++;
            }
        } else if (stream[0] == '/' && stream[1] && stream[1] == '*') {
            while (stream[0] && stream[0] != '*' && stream[1] != '/') {
                stream++;
            }
            if (stream[0] == '*') {
                stream += 2;
            }
        } else {
            break;
        }
    }
}

int main()
{
    File_Content file = ReadEntireFileAndNullTerminate("names.txt");
}
