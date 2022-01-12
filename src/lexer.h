/*
 * Author: Lukas Nitzsche
 */

#include <ctype.h>

#ifndef __LEXER_H__
#define __LEXER_H__

enum tokenType {IDEN, NUM, LPAREN, RPAREN, SEMICOL, COL} tokenType;

typedef struct Token {
    int id;
    enum tokenType tokenType;
    char symbol;
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

    return chars;
}

void printTokens(Token tokens[]) {
}

Token lexer(char name[]) {
    FILE *fileO = fopen(name, "r");
    int chars = charCount(fileO);
    rewind(fileO);
    Token tokens[sizeof(fileO)];

    if(fileO == NULL) {
        fprintf(stderr, "File does not exist!\n");
        exit(EXIT_SUCCESS);
    }

    char c = fgetc(fileO);

    for(int i = 0; i < chars; i++) {
        switch(c) {
            case '(':
                tokens[i].id = i;
                tokens[i].tokenType = LPAREN;
                tokens[i].symbol = c;
            case ')':
                tokens[i].id = i;
                tokens[i].tokenType = RPAREN;
                tokens[i].symbol = c;
            case ';':
                tokens[i].id = i;
                tokens[i].tokenType = SEMICOL;
                tokens[i].symbol = c;
            case ':':
                tokens[i].id = i;
                tokens[i].tokenType = COL;
                tokens[i].symbol = c;
            case :
                tokens[i].id = i;
                tokens[i].tokenType = IDEN;
                tokens[i].symbol = c;
            default :
        }
        c = fgetc(fileO);
    }

    fclose(fileO);
}

#endif /* end include */
