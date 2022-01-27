/*
 * Author: Lukas Nitzsche
 */

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <stdbool.h>

#ifndef __NACHTIGAL_H__
#define __NACHTIGAL_H__

#define FOREACH_TOKEN(TOKEN) \
    TOKEN(LPAREN)   \
    TOKEN(CHAR)     \
    TOKEN(NUM)      \
    TOKEN(RPAREN)   \
    TOKEN(SEMICOL)  \
    TOKEN(COL)      \
    TOKEN(COMMA)    \
    TOKEN(QUOTM)    \
    TOKEN(QUOTEM)   \
    TOKEN(LBRACKET) \
    TOKEN(RBRACKET) \
    TOKEN(PLUS)     \
    TOKEN(MINUS)    \
    TOKEN(FSLASH)   \
    TOKEN(STAR)     \
    TOKEN(DOT)      \
    TOKEN(EXCL)     \
    TOKEN(END)      \

#define FOREACH_KEYWORD(KEYWORD) \
    KEYWORD(IF) \
    KEYWORD(CONST) \
    KEYWORD(NAME) \
    KEYWORD(DEF) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum tokenType {
    FOREACH_TOKEN(GENERATE_ENUM)
};

static const char *TOKEN_STRING[] = {
    FOREACH_TOKEN(GENERATE_STRING)
};

enum keyWord {
    FOREACH_KEYWORD(GENERATE_ENUM)
};

static const char *KEYWORD_STRING[] = {
    FOREACH_KEYWORD(GENERATE_STRING)
};

typedef struct Token {
    int id;
    enum tokenType type;
    union {
        char symbol;
        double val;
    };
    bool end;
} Token;

typedef struct Ast {
    union {
        char *name;
        char *definition;
    };
    union {
        char *valC;
        double valN;
    };
    Token token;
    int id;
    struct Ast *nameLink;
    struct Ast *definitionLink;
    enum keyWord type;
} Ast;

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

int tokensLength(Token *tokens) {
    int i = 0;
    while(!tokens[i].end) {
        i++;
    }

    return i;
}

void printTokens(Token *tokens) {
    int length = tokensLength(tokens);

    for(int i = 0; i < length; i++) {
        printf("ID: %d ", tokens[i].id);
        printf("Type: %s ", TOKEN_STRING[tokens[i].type]);

        if(strcmp(TOKEN_STRING[tokens[i].type], TOKEN_STRING[NUM]) == 0)
            printf("Symbol: %f ", tokens[i].val);
        else
            printf("Symbol: %c ", tokens[i].symbol);

        printf("\n");
    }
    // free(tokens);
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
            case '.':
                tokens[i].id = i;
                tokens[i].type = DOT;
                tokens[i].symbol = c;
                break;
            case '\'':
                tokens[i].id = i;
                tokens[i].type = QUOTEM;
                tokens[i].symbol = c;
                break;
            case '!':
                tokens[i].id = i;
                tokens[i].type = EXCL;
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
                } else if(isdigit(c)) {
                    tokens[i].id = i;
                    tokens[i].type = NUM;
                    tokens[i].val = c - '0';
                    break;
                } else if(c == EOF) {
                    tokens[i].id = i;
                    tokens[i].end = true;
                }
        }
        c = fgetc(fileO);
    }
    fclose(fileO);

    return tokens;
}

Ast *parser(Token *tokens) {
    int length = tokensLength(tokens);
    printf("%d\n", length);
    Ast *nodes = malloc(sizeof(struct Ast) * length);

    /* -- experimental -- */

    int i = 0;
    while(!tokens[i].end) {
        printf("%d\n", tokens[i].id);

        i++;
    }

    /* -- -- */

    free(tokens);
    return nodes;
}

#endif
