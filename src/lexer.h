/*
 * Author: Lukas Nitzsche
 */

#ifndef __LEXER_H__
#define __LEXER_H__

enum tokenType {IDEN, NUM, LPAREN, RPAREN, SEMICOL, COL, QUOTM} tokenType;

typedef struct Token {
    int id;
    char symbol;
    enum tokenType tokenType;
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

void printTokens(Token tokens[], int length) {
    for(int i = 0; i < length; i++) {
        printf("ID: %d ", tokens[i].id);
        printf("Symbol: %c ", tokens[i].symbol);
        printf("\n");
    }
}

Token lexer(char name[]) {
    FILE *fileO = fopen(name, "r");
    int chars = charCount(fileO);
    rewind(fileO);
    Token tokens[chars];

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
            case '"':
                tokens[i].id = i;
                tokens[i].tokenType = QUOTM;
                tokens[i].symbol = c;
            default :
                tokens[i].id = i;
                tokens[i].tokenType = IDEN;
                tokens[i].symbol = c;
        }
        c = fgetc(fileO);
    }

    fclose(fileO);

    /*Token *ptrtokens = malloc(chars * sizeof(Token));
    return ptrtokens;*/

    printTokens(tokens, chars);
}

#endif /* end include */
