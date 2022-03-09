/*
 * lexer.h
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef __LEXER_H__
#define __LEXER_H__

#define FOREACH_CHAR(CHAR) \
    CHAR(NUM)      \
    CHAR(LETTER)   \
    CHAR(END)      \
    CHAR(SPACE)    \
                   \
    CHAR(PLUS)     \
    CHAR(MINUS)    \
    CHAR(STAR)     \
    CHAR(FSLASH)   \
    CHAR(EXCL)     \
                   \
    CHAR(COL)      \
    CHAR(SEMICOL)  \
    CHAR(LPAREN)   \
    CHAR(RPAREN)   \
    CHAR(LBRACKET) \
    CHAR(RBRACKET) \
                   \
    CHAR(QUOTM)    \
    CHAR(QUOTEM)   \
    CHAR(DOT)      \
    CHAR(COMMA)    \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum charType {
    FOREACH_CHAR(GENERATE_ENUM)
};

static const char *CHAR_STRING[] = {
    FOREACH_CHAR(GENERATE_STRING)
};

typedef struct Token {
    int id;
    enum charType type;
    union {
        char symbol;
        int val;
    };
    int end;
} Token;

int charCount(FILE *fptr) {
    int chars = 0;

    if(fptr == NULL) {
        fprintf(stderr, "File does not exist!\n");
        exit(EXIT_SUCCESS);
    }

    while(fgetc(fptr) != EOF) {
        chars++;
    }

    return chars - 1;
}

void printTokens(Token *tokens) {
    int length = tokensLength(tokens);

    for(int i = 0; i < length; i++) {
        printf("ID: %d ", tokens[i].id);
        printf("Type: %s ", CHAR_STRING[tokens[i].type]);

        if(strcmp(CHAR_STRING[tokens[i].type], CHAR_STRING[NUM]) == 0)
            printf("Symbol: %f ", tokens[i].val);
        else
            printf("Symbol: %c ", tokens[i].symbol);

        printf("\n");
    }
}

Token *lexer(char name[]) {
    FILE *fileO = fopen(name, "r");
    int length = charCount(fileO);
    rewind(fileO);
    Token *tokens = malloc(sizeof(struct Token) * length);

    if(fileO == NULL) {
        fprintf(stderr, "File does not exist!\n");
        exit(EXIT_SUCCESS);
    }

    char c = fgetc(fileO);

    for(int i = 0; i < length; i++) {
        switch(c) {
            case '+':
                tokens[i].id = i;
                tokens[i].type = PLUS;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case '-':
                tokens[i].id = i;
                tokens[i].type = MINUS;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case '*':
                tokens[i].id = i;
                tokens[i].type = STAR;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case '/':
                tokens[i].id = i;
                tokens[i].type = FSLASH;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case '!':
                tokens[i].id = i;
                tokens[i].type = EXCL;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case ':':
                tokens[i].id = i;
                tokens[i].type = COL;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case ';':
                tokens[i].id = i;
                tokens[i].type = SEMICOL;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case '(':
                tokens[i].id = i;
                tokens[i].type = LPAREN;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case ')':
                tokens[i].id = i;
                tokens[i].type = RPAREN;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case '[':
                tokens[i].id = i;
                tokens[i].type = LBRACKET;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case ']':
                tokens[i].id = i;
                tokens[i].type = RBRACKET;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case '"':
                tokens[i].id = i;
                tokens[i].type = QUOTM;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case '\'':
                tokens[i].id = i;
                tokens[i].type = QUOTEM;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case '.':
                tokens[i].id = i;
                tokens[i].type = DOT;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case ',':
                tokens[i].id = i;
                tokens[i].type = COMMA;
                tokens[i].symbol = c;
                tokens[i].end = 0;
                break;
            case ' ':
                i--;
                break;
            case '\n':
                i--;
                break;
            default :
                if(isalpha(c)) {
                    tokens[i].id = i;
                    tokens[i].type = LETTER;
                    tokens[i].symbol = c;
                    tokens[i].end = 0;
                    break;
                } else if(isdigit(c)) {
                    tokens[i].id = i;
                    tokens[i].type = NUM;
                    tokens[i].val = c - '0';
                    tokens[i].end = 0;
                    break;
                } else if(c == EOF) {
                    tokens[i].id = i;
                    tokens[i].end = 1;
                    break;
                }
        }
        c = fgetc(fileO);
    }
    fclose(fileO);

    return tokens;
}

#endif
