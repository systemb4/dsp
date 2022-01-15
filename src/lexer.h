/*
 * Author: Lukas Nitzsche
 */

#include <stdlib.h>

#ifndef __LEXER_H__
#define __LEXER_H__

#define FOREACH_TOKEN(TOKEN) \
    TOKEN(LPAREN)  \
    TOKEN(IDEN)   \
    TOKEN(RPAREN)   \
    TOKEN(SEMICOL)  \
    TOKEN(COL)  \
    TOKEN(QUOTM)  \

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
    char symbol;
    enum tokenType type;
} Token;

int charCount(FILE *fptr) {
    int chars = 0;

    if(fptr == NULL) {
        fprintf(stderr, "File does not exist!\n");
        exit(EXIT_SUCCESS);
    }

    char c = fgetc(fptr);

    while(c != EOF) {
        chars++;
        c = fgetc(fptr);
    }

    return chars - 1;
}

void printTokens(Token tokens[]) {
    for(int i = 0; i < 20; i++) {
        printf("ID: %d ", tokens[i].id);
        printf("Type: %s ", TOKEN_STRING[tokens[i].type]);
        printf("Symbol: %c ", tokens[i].symbol);
        printf("\n");
    }
    free(tokens);
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
            default :
                tokens[i].id = i;
                tokens[i].type = IDEN;
                tokens[i].symbol = c;
                break;
        }
        c = fgetc(fileO);
    }
    fclose(fileO);

    return tokens;
}

#endif /* end include */
