
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

#if 0
#define MAX_ARRAY_ENTRIES 5000
#else
#define MAX_ARRAY_ENTRIES 15
#endif

#if 1
static void BubbleSortArray(Token **token_array)
{
    for (int outer = 0; outer < MAX_ARRAY_ENTRIES; outer++) {
        for (int inner = 0; inner < MAX_ARRAY_ENTRIES; inner++) {
            if (token_array[inner]->name[0] > token_array[inner + 1]->name[0]) {
                Token *temp = token_array[inner];
                token_array[inner] = token_array[inner + 1];
                token_array[inner + 1] = temp;
            } else if (token_array[inner]->name[0] == token_array[inner + 1]->name[0]) {
                size_t smallest_length = token_array[inner]->name_length < token_array[inner + 1]->name_length ? token_array[inner]->name_length : token_array[inner + 1]->name_length;
                for (int current_letter = 1; current_letter < smallest_length; current_letter++) {
                    if (token_array[inner]->name[current_letter] > token_array[inner+1]->name[current_letter]) {
                        Token *temp = token_array[inner];
                        token_array[inner] = token_array[inner + 1];
                        token_array[inner + 1] = temp;
                        break;
                    } else if (token_array[inner]->name[current_letter] < token_array[inner+1]->name[current_letter]) {
                        break;
                    }
                }
            }
        }
    }
}
#endif

int main()
{
    File_Content file = ReadEntireFileAndNullTerminate("names.txt");

    Tokeniser tokeniser;
    tokeniser.at = file.data;

    Token *token_array[5000];

    AddTokenToArray(&tokeniser, token_array);
    BubbleSortArray(token_array);

    for(int i = 0; i < MAX_ARRAY_ENTRIES; i++)
    {
        printf("%.*s\n", (int)token_array[i]->name_length, token_array[i]->name);
    }

    int num = 'z' + 'a';

    printf("%d\n", num);
}
