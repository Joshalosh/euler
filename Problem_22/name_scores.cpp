
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "name_scores.h"

#define ASSERT(expression) if(!(expression)) {*(int *)0 = 0;}

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

static int AddTokensToArrayAndGetCount(Tokeniser *tokeniser, Token **token_array)
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
static void BubbleSortArray(Token **token_array, int token_count)
{
    for (int outer = 0; outer < token_count - 1; outer++) {
        for (int inner = 0; inner < token_count - outer - 1; inner++) {
            if (token_array[inner]->name[0] > token_array[inner + 1]->name[0]) {
                Token *temp            = token_array[inner];
                token_array[inner]     = token_array[inner + 1];
                token_array[inner + 1] = temp;
            } else if (token_array[inner]->name[0] == token_array[inner + 1]->name[0]) {
                size_t smallest_length = token_array[inner]->name_length < token_array[inner + 1]->name_length ? token_array[inner]->name_length : token_array[inner + 1]->name_length;
                bool   identical_up_to_smallest_length = 1;
                for (int current_letter = 1; current_letter < smallest_length; current_letter++) {
                    if (token_array[inner]->name[current_letter] > token_array[inner+1]->name[current_letter]) {
                        Token *temp                     = token_array[inner];
                        token_array[inner]              = token_array[inner + 1];
                        token_array[inner + 1]          = temp;
                        identical_up_to_smallest_length = 0;
                        break;
                    } else if (token_array[inner]->name[current_letter] < token_array[inner+1]->name[current_letter]) {
                        identical_up_to_smallest_length = 0;
                        break;
                    }
                }

                if (identical_up_to_smallest_length) {
                    if (token_array[inner]->name_length > token_array[inner+1]->name_length) {
                        Token *temp                     = token_array[inner];
                        token_array[inner]              = token_array[inner + 1];
                        token_array[inner + 1]          = temp;
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

static void MergeSort(Token **first, Token **temp_array, int count) {
    if (count <= 1) {
        return;  // Array of size 1 or 0 is always sorted.
    } else if (count == 2) {
        if (strcmp(first[0]->name, first[1]->name) > 0) {
            Token *temp = first[0];
            first[0] = first[1];
            first[1] = temp;
        }
        return;
    }
    
    int half_0_count = count / 2;
    int half_1_count = count - half_0_count;

    Token **in_half_0 = first;
    Token **in_half_1 = first + half_0_count;

    MergeSort(in_half_0, temp_array, half_0_count);
    MergeSort(in_half_1, temp_array, half_1_count);

    Token **read_half_0 = in_half_0;
    Token **read_half_1 = in_half_1;
    Token **end_half_0 = in_half_1;
    Token **end = first + count;
    Token **out = temp_array;

    while (read_half_0 < end_half_0 && read_half_1 < end) {
        if (strcmp((*read_half_0)->name, (*read_half_1)->name) < 0) {
            *out++ = *read_half_0++;
        } else {
            *out++ = *read_half_1++;
        }
    }

    // Copy any remaining items from the halves, if any.
    while (read_half_0 < end_half_0) {
        *out++ = *read_half_0++;
    }
    while (read_half_1 < end) {
        *out++ = *read_half_1++;
    }

    // Copy the merged items back to the original array.
    for (int i = 0; i < count; i++) {
        first[i] = temp_array[i];
    }
}

#if 0
static void MergeSort(Token **first, Token **temp_array, int count)
{
    if (count == 1) {
        // NOTE: Do nothing
    }
    else if (count == 2) {
        Token **entry_a  = first;
        Token **entry_b  = first + 1;
        if (strcmp((*entry_a)->name, (*entry_b)->name) > 0) {
            Token *temp   = *entry_a;
            *entry_a      = *entry_b;
            *entry_b      = temp;
        }
    } else {
        
        int half_0_count = count / 2;
        int half_1_count = count - half_0_count;

        ASSERT(half_0_count >= 1);
        ASSERT(half_1_count >= 1);

        Token **in_half_0   = first;
        Token **in_half_1   = first + half_0_count;
        Token **end         = first + count;

        MergeSort(in_half_0, temp_array, half_0_count);
        MergeSort(in_half_1, temp_array, half_1_count);

        Token **read_half_0 = in_half_0;
        Token **read_half_1 = in_half_1;

        Token **out = temp_array;
        for (int index = 0; index < count; index++) {
            if (read_half_0 == in_half_1) {
                **out++ = **read_half_1++;
            } else if (read_half_1 == end) {
                **out++ = **read_half_0++;
            } else if (strcmp((*read_half_0)->name, (*read_half_1)->name) < 0) {
                **out++ = **read_half_0++;
            } else {
                **out++ = **read_half_1++;
            }
        }
        ASSERT(out == (temp_array + count));
        ASSERT(read_half_0 == in_half_1);
        ASSERT(read_half_1 == end);

        for (int index = 0; index < count; index++) {
            first[index] = temp_array[index];
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
    Token *temp_array[5200];

    long long token_count = AddTokensToArrayAndGetCount(&tokeniser, token_array);
    //BubbleSortArray(token_array, token_count);
    MergeSort(token_array, temp_array, token_count);

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
