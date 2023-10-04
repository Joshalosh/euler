#if !defined(NAME_SCORES_H)

struct File_Content 
{
    char *data;
    size_t size;
};

struct Tokeniser
{
    char *at;
};

struct Token
{
    char  *name;
    size_t name_length;
};

enum Token_Type
{
    TokenType_Unknown,
    TokenType_String,

    TokenType_EndOfStream,
};

#define NAME_SCORES_H
#endif
