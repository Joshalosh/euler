
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "name_scores.h"

static File_Content ReadEntireFileAndNullTerminate(char *filename) 
{
    FILE *file = fopen(filename, "r");
    File_Content result = {};

    if (file) {
        fseek(file, 0, SEEK_END);
        result.size = ftell(file);
        fseek(file, 0, SEEK_SET);

        result.data = (char *)malloc(result.size + 1);

        if (result.data) {
            fread(result.data, result.size, 1, file);
            fclose(file);

            result.data[result.size] = '\0';
        } else {
            fprintf(stderr, "Memory allocation failed\n");
            fclose(file);
        }
    } else {
        fprintf(stderr, "Failed to open file\n");
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
    bool   result = (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == ',' || IsEndOfLine(c));
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

static void EatWhitespaceAndComments(Tokeniser *tokeniser)
{
    char *stream = tokeniser->at;

    while (stream[0]) {
        if (IsWhitespace(stream[0])) {
            stream++;
        } else if (stream[0] == '/' && stream[1] == '/') {
            while (stream[0] && !IsEndOfLine(stream[0])) {
                stream++;
            }
        } else if (stream[0] == '/' && stream[1] == '*') {
            while (stream[0] && !(stream[0] == '*' && stream[1] == '/')) {
                stream++;
            }
            if (stream[0] == '*') {
                stream += 2;
            }
        } else {
            break;
        }
    }

    tokeniser->at = stream;
}

static void AddTokenToArray(Tokeniser *tokeniser, Token **token_array)
{
    int index = 0;
    while(tokeniser->at[0])
    {
        EatWhitespaceAndComments(tokeniser);

        Token *token = (Token *)malloc(sizeof(Token));
        switch(tokeniser->at[0]) {
            case '"': {
            tokeniser->at++;
            token->name = tokeniser->at;
            while (tokeniser->at[0] != '"') {
                tokeniser->at++;
            }

            token->name_length = tokeniser->at - token->name;

            token_array[index] = token;
            index++;
            tokeniser->at++;
            }
        }
    }
}

int main()
{
    File_Content file = ReadEntireFileAndNullTerminate("names.txt");

    Tokeniser tokeniser;
    tokeniser.at = file.data;

    Token *token_array[5000];

    AddTokenToArray(&tokeniser, token_array);

    for(int i = 0; i < 5000; i++)
    {
        printf("%.*s\n", (int)token_array[i]->name_length, token_array[i]->name);
    }
}
