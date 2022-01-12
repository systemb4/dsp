#include <stdio.h>
#include <stdlib.h>

enum tokenType {ENDL, IDEN, LPAREN, RPAREN, COL} tokenType;

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

Token lexer(char name[]) {
    FILE *fileO = fopen(name, "r");
    int chars = lexer(fileO);
    rewind(fileO);
    Token tokens[sizeof(fileO)];

    if(fileO == NULL) {
        fprintf(stderr, "File does not exist!\n");
        exit(EXIT_SUCCESS);
    }

    char c = fgetc(fileO);

    for(int i = 0; i < chars; i++) {
        //token[i]->id = i;
        if(c == ' ') {
            continue;
        } else if(c == ) {
        }
        tokens[i]->tokenType =
        c = fgetc(fileO);
    }

    fclose(fileO);
}

int main(int argc, char *argv[]) {
    lexer(argv[1]);

    return 0;
}
