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

#define FOREACH_CHAR(CHAR) \
    CHAR(NUM)      \
    CHAR(LETTER)   \
    CHAR(END)      \
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

#define FOREACH_KEYWORD(KEYWORD) \
    KEYWORD(IF)     \
    KEYWORD(CONST)  \
    KEYWORD(NAME)   \
    KEYWORD(DEF)    \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum charType {
    FOREACH_CHAR(GENERATE_ENUM)
};

static const char *CHAR_STRING[] = {
    FOREACH_CHAR(GENERATE_STRING)
};

enum keyWord {
    FOREACH_KEYWORD(GENERATE_ENUM)
};

static const char *KEYWORD_STRING[] = {
    FOREACH_KEYWORD(GENERATE_STRING)
};

typedef struct Token {
    int id;
    enum charType type;
    union {
        char symbol;
        double val;
    };
    bool end;
} Token;

typedef struct Name {
    char *name;
    enum keyWord type;
    struct Name *nameLink;
    struct Definition *defLink;
} Name;

typedef struct Definition {
    union {
        double numVal;
        char *stringVal;
    };
    struct Name *nameLink;
    struct Definition *defLink;
} Definition;

typedef union struLink {
    struct Name *nameLink;
    struct Definition *defLink;
} struLink;

void addName(Name *ptr, char *name, enum keyWord type) {
    struLink *args = (struLink *)ptr;
    Name *result = malloc(sizeof(Name));

    result->type = type;
    result->name = name;

    ptr->nameLink = result;
}

void addDefinition(struLink *ptr, void *val) {
}

char *sort(Token *tokens, int pos) {
    char *result;
    enum charType type;

    if(tokens[pos].type == LPAREN) {
        type = RPAREN;
    } else if(tokens[pos].type == LBRACKET) {
        type = RBRACKET;
    } else if(tokens[pos].type == QUOTM) {
        type = QUOTM;
    } else if(tokens[pos].type == QUOTEM) {
        type = QUOTEM;
    } else {
        type = SEMICOL;
    }

    pos++;
    for(int i = 1; tokens[pos].type != type; i++) {
        result[i] = tokens[pos].symbol;
        pos++;
    }

    return result;
}

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
        printf("Type: %s ", CHAR_STRING[tokens[i].type]);

        if(strcmp(CHAR_STRING[tokens[i].type], CHAR_STRING[NUM]) == 0)
            printf("Symbol: %f ", tokens[i].val);
        else
            printf("Symbol: %c ", tokens[i].symbol);

        printf("\n");
    }
    //free(tokens);
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
                break;
            case '-':
                tokens[i].id = i;
                tokens[i].type = MINUS;
                tokens[i].symbol = c;
                break;
            case '*':
                tokens[i].id = i;
                tokens[i].type = STAR;
                tokens[i].symbol = c;
                break;
            case '/':
                tokens[i].id = i;
                tokens[i].type = FSLASH;
                tokens[i].symbol = c;
                break;
            case '!':
                tokens[i].id = i;
                tokens[i].type = EXCL;
                tokens[i].symbol = c;
                break;
            case ':':
                tokens[i].id = i;
                tokens[i].type = COL;
                tokens[i].symbol = c;
                break;
            case ';':
                tokens[i].id = i;
                tokens[i].type = SEMICOL;
                tokens[i].symbol = c;
                break;
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
            case '"':
                tokens[i].id = i;
                tokens[i].type = QUOTM;
                tokens[i].symbol = c;
                break;
            case '\'':
                tokens[i].id = i;
                tokens[i].type = QUOTEM;
                tokens[i].symbol = c;
                break;
            case '.':
                tokens[i].id = i;
                tokens[i].type = DOT;
                tokens[i].symbol = c;
                break;
            case ',':
                tokens[i].id = i;
                tokens[i].type = COMMA;
                tokens[i].symbol = c;
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

Name *parser(Token *tokens) {
    int length = tokensLength(tokens);
    Name *head;

    /* -- experimental -- */

    char *hello = "Hello World!";
    addName(head, hello, NAME);

    head = head->nameLink;

    for(int i = 0; i < length; i++) {
        if(tokens[i].type == LPAREN) {
            char *check = sort(tokens, i);
            printf("%s\n", check);
        }
    }

    /* -- -- */

    free(tokens);
    return head;
}

#endif
