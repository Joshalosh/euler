
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

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

static int AddTokenToArray(Tokeniser *tokeniser, Token **token_array)
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
            //printf("%.*s\n", (int)token->name_length, token->name);
            index++;
            tokeniser->at++;
            }
        }
    }

    return index;
}

#if 1
#define MAX_ARRAY_ENTRIES 5200
#else
#define MAX_ARRAY_ENTRIES 15
#endif

#if 0
static void BubbleSortArray(Token **token_array, int token_count)
{
    for (int outer = 0; outer < token_count - 1; outer++) {
        for (int inner = 0; inner < token_count - outer - 1; inner++) {
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
#else
static void BubbleSortArray(Token **token_array, int token_count)
{
    for (int outer = 0; outer < token_count - 1; outer++) {
        for (int inner = 0; inner < token_count - outer - 1; inner++) {
            if (strcmp(token_array[inner]->name, token_array[inner+1]->name) > 0) {
                Token *temp          = token_array[inner];
                token_array[inner]   = token_array[inner+1];
                token_array[inner+1] = temp;
            }
        }
    }
}

#endif

static void FreeTokens(Token **token_array, int token_count)
{
    for(int i = 0; i < token_count; i++) {
        free(token_array[i]);
    }
}

int main()
{
    File_Content file = ReadEntireFileAndNullTerminate("names.txt");

    Tokeniser tokeniser;
    tokeniser.at = file.data;

    Token *token_array[5200];

    long long token_count = AddTokenToArray(&tokeniser, token_array);
    //token_count = 15;
    //printf("Total tokens: %d\n", token_count);
    BubbleSortArray(token_array, token_count);

    int total_score = 0;
    for(int i = 0; i < token_count; i++) {
        long long num = 0;
        for(int current_letter = 0; current_letter < token_array[i]->name_length; current_letter++) {
            num += token_array[i]->name[current_letter] - 64;
        }
        num *= (i + 1);
        total_score += num;
        printf("%.*s -> %lld\n", (int)token_array[i]->name_length, token_array[i]->name, num);
    }

    printf("The total score is: %d\n", total_score);

    FreeTokens(token_array, token_count);
}
