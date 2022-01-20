/*
 * Author: Lukas Nitzsche
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef __LEXER_H__
#define __LEXER_H__

#define FOREACH_TOKEN(TOKEN) \
    TOKEN(LPAREN)   \
    TOKEN(CHAR)     \
    TOKEN(NUM)      \
    TOKEN(RPAREN)   \
    TOKEN(SEMICOL)  \
    TOKEN(COL)      \
    TOKEN(COMMA)    \
    TOKEN(QUOTM)    \
    TOKEN(LBRACKET) \
    TOKEN(RBRACKET) \
    TOKEN(PLUS)     \
    TOKEN(MINUS)    \
    TOKEN(FSLASH)   \
    TOKEN(STAR)     \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum tokenType {
    FOREACH_TOKEN(GENERATE_ENUM)
};

static const char *TOKEN_STRING[] = {
    FOREACH_TOKEN(GENERATE_STRING)
};

typedef struct Token {
    int id;
    enum tokenType type;
    union {
        char symbol;
        long int val;
    };
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

void printTokens(Token tokens[]) {
    for(int i = 0; i < 100; i++) {
        printf("ID: %d ", tokens[i].id);
        printf("Type: %s ", TOKEN_STRING[tokens[i].type]);

        if(strcmp(TOKEN_STRING[tokens[i].type], TOKEN_STRING[NUM]) == 0)
            printf("Symbol: %ld ", tokens[i].val);
        else
            printf("Symbol: %c ", tokens[i].symbol);

        printf("\n");
    }
    free(tokens);
}

void *threadTokenCheck(char c, Token tokens[]) {
}

Token *lexer(char name[]) {
    FILE *fileO = fopen(name, "r");
    int chars = charCount(fileO);
    rewind(fileO);
    Token *tokens = malloc(sizeof(struct Token) * chars);

    if(fileO == NULL) {
        fprintf(stderr, "File does not exist!\n");
        exit(EXIT_SUCCESS);
    }

    char c = fgetc(fileO);

    for(int i = 0; i < chars; i++) {
        switch(c) {
            case '(':
                tokens[i].id = i;
                tokens[i].type = LPAREN;
                tokens[i].symbol = c;
                break;
            case ')':
                tokens[i].id = i;
                tokens[i].type = RPAREN;
                tokens[i].symbol = c;
                break;
            case ';':
                tokens[i].id = i;
                tokens[i].type = SEMICOL;
                tokens[i].symbol = c;
                break;
            case ':':
                tokens[i].id = i;
                tokens[i].type = COL;
                tokens[i].symbol = c;
                break;
            case '"':
                tokens[i].id = i;
                tokens[i].type = QUOTM;
                tokens[i].symbol = c;
                break;
            case '[':
                tokens[i].id = i;
                tokens[i].type = LBRACKET;
                tokens[i].symbol = c;
                break;
            case ']':
                tokens[i].id = i;
                tokens[i].type = RBRACKET;
                tokens[i].symbol = c;
                break;
            case '+':
                tokens[i].id = i;
                tokens[i].type = PLUS;
                tokens[i].symbol = c;
                break;
            case '-':
                tokens[i].id = i;
                tokens[i].type = MINUS;
                tokens[i].symbol = c;
                break;
            case '/':
                tokens[i].id = i;
                tokens[i].type = FSLASH;
                tokens[i].symbol = c;
                break;
            case '*':
                tokens[i].id = i;
                tokens[i].type = STAR;
                tokens[i].symbol = c;
                break;
            case ',':
                tokens[i].id = i;
                tokens[i].type = COMMA;
                tokens[i].symbol = c;
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
                    tokens[i].type = CHAR;
                    tokens[i].symbol = c;
                    break;
                } else if(isdigit(c)) {
                    tokens[i].id = i;
                    tokens[i].type = NUM;
                    tokens[i].val = c - '0';
                    break;
                }
        }
        c = fgetc(fileO);
    }
    fclose(fileO);

    return tokens;
}

#endif /* end include */
