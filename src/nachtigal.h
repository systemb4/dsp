/*
 * Author: Lukas Nitzsche
 */

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

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
    KEYWORD(HEAD)   \
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
    int end;
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
    /*struct Name *nameLink;
    struct Definition *defLink;*/
} Definition;

typedef union struLink {
    struct Name *nameLink;
    struct Definition *defLink;
} struLink;

void addName(Name *head, char *name, enum keyWord type) {
    Name *result = malloc(sizeof(Name));
    Name *lastNode = head;

    result->type = type;
    result->name = name;
    result->nameLink = NULL;
    result->defLink = NULL;

    if(head == NULL) {
        head = result;
    } else {
        while(lastNode->nameLink != NULL) {
            lastNode = lastNode->nameLink;
        }

        lastNode->nameLink = result;
    }

    free(result);
}

void addDefinition(struLink *ptr, void *val) {
}

char *sort(Token *tokens, int pos) {
    char *result = malloc(sizeof(char) * 15);
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

    for(int i = 0; tokens[pos].type != type; i++) {
        pos++;

        if(tokens[pos].type == type) {
            break;
        }

        result[i] = tokens[pos].symbol;
        result[i+1] = '\0';
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
    while(tokens[i].end != 1) {
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

Name *parser(Token *tokens) {
    int length = tokensLength(tokens);
    Name *head = NULL;

    char *tmp;
    for(int i = 0; i < 141; i++) {
        if(tokens[i].type == LPAREN) {
            tmp = sort(tokens, i);
            addName(head, tmp, NAME);
            i += strlen(tmp);
            free(tmp);
        }
    }

    return head;
}

#endif
