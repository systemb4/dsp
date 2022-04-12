/*
 * nachtigal
 *
 * Author: Lukas Nitzsche
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef __NACHTIGAL_H__
#define __NACHTIGAL_H__

#define FOREACH_CHAR(CHAR) \
    CHAR(NUM)      \
    CHAR(LETTER)   \
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

#define FOREACH_KEYWORD(KEYWORD) \
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
        int val;
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
    enum keyWord type;
    struct Definition *defLink;
} Definition;

typedef struct Arithmetic {
    char op;
    double numVal;

    struct Arithmetic *list;
    struct Arithmetic *next;
} Arithmetic;

double strToDb(char *str) {
    double result;
    char *ptr_end;

    result = strtod(str, &ptr_end);

    return result;
}

void addArt(Arithmetic **head, char op, double numVal) {
    Arithmetic *result = malloc(sizeof(Arithmetic));
    Arithmetic *lastNode = *head;

    result->op = op;
    result->numVal = numVal;
    result->next = NULL;
    //result->list->next = NULL;

    if(*head == NULL) {
        *head = result;
    } else {
        while(lastNode->next != NULL) {
            lastNode = lastNode->next;
        }

        lastNode->next = result;
    }
}

void addName(Name **head, char **name, enum keyWord type) {
    Name *result = malloc(sizeof(Name));
    Name *lastNode = *head;

    result->type = type;
    result->name = *name;
    result->nameLink = NULL;
    result->defLink = NULL;

    if(*head == NULL) {
        *head = result;
    } else {
        while(lastNode->nameLink != NULL) {
            lastNode = lastNode->nameLink;
        }

        lastNode->nameLink = result;
    }
}

void addDefinition(Name **head, char **val, enum keyWord type) {
    Definition *result = malloc(sizeof(Definition));
    Name *lastNode = *head;
    Definition *place = NULL;

    result->type = type;
    result->defLink = NULL;

    /* be able to choose between actual number or string */
    result->stringVal = *val;

    if(*head == NULL) {
        fprintf(stderr, "Can not set definition equal to a name!");
    } else {
        while(lastNode->nameLink != NULL) {
            lastNode = lastNode->nameLink;
        }

        while(lastNode->defLink != NULL) {
            place = lastNode->defLink;
        }

        lastNode->defLink = result;
    }
}

char *sortTokens(Token *tokens, int pos) {
    char *result = malloc(sizeof(char) * 15);
    enum charType type;

    if(tokens[pos].type == LPAREN) {
        type = RPAREN;
    } else if(tokens[pos].type == LBRACKET) {
        type = RBRACKET;
    } else {
        type = SEMICOL;
    }

    for(int i = 0; tokens[pos].type != type; i++) {
        pos++;

        if(tokens[pos].type == type) {
            break;
        }

        if(tokens[pos].type == NUM) {
            result[i] = tokens[pos].val + '0';
        } else {
            result[i] = tokens[pos].symbol;
        }

        result[i+1] = '\0';

    }

    return result;
}

Arithmetic sortStack(Arithmetic **head) {
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

int namesLength(Name *names) {
    int i = 0;
    Name *tmp = names;

    while(tmp != NULL) {
        tmp = tmp->nameLink;
        i++;
    }

    return i;
}

size_t getSize (const char* s) {
    size_t size = 0;

    while (*s++) ++size;

    return size;
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

void printNames(Name *head) {
    Name *tmp = head;

    while(tmp != NULL) {
        printf("%d - ", getSize(tmp->defLink->stringVal));
        printf("%s - ", tmp->name);
        printf("%s\n", tmp->defLink->stringVal);
        tmp = tmp->nameLink;
    }
}

void printArt(Arithmetic *head) {
    Arithmetic *tmp = head;
    Arithmetic *tm = tmp->list;

    while(tmp != NULL) {
        while(tmp->list->next != NULL) {
            printf("%c = %lf\n", tmp->list->op, tmp->list->numVal);
            tm = tmp->list->next;
        }

        tmp = tmp->next;
        tm = tmp;
    }
}

Name *parser(Token *tokens) {
    int length = tokensLength(tokens);
    Name *head = NULL;

    char *tmp;
    for(int i = 0; i < length; i++) {
        if(tokens[i].type == LPAREN) {
            tmp = sortTokens(tokens, i);
            addName(&head, &tmp, NAME);
            i += strlen(tmp);
        } else if(tokens[i].type == LBRACKET) {
            tmp = sortTokens(tokens, i);
            addDefinition(&head, &tmp, DEF);
            i += strlen(tmp);
        }
    }

    return head;
}

char charCheck(char ch) {
    if(&ch == NULL) {
        return 'X';
    } else {
        return ch;
    }
}

Arithmetic *run(Name *head) {
    int length = namesLength(head);

    Name *tmp = head;
    Arithmetic *art = NULL;
    char *numVal, *end;

    for(int i = 0; i < length; i++) {
        int length_str = getSize(tmp->defLink->stringVal);
        for(int x = 0; x < length_str; x++) {
            if(tmp->defLink->stringVal[x] == '\'') {
                x++;
                numVal = malloc(sizeof(char) * 15);
                for(int y = 0; tmp->defLink->stringVal[x] != '\''; y++) {
                    numVal[y] = tmp->defLink->stringVal[x];
                    numVal[y+1] = '\0';
                    x++;
                }
                x++;
                //addArt(&art->list, charCheck(tmp->defLink->stringVal[x]), strtod(numVal, &end));
                addArt(&art, '+', strtod(numVal, &end));
            }
        }
        tmp = tmp->nameLink;
    }

    return art;
}

#endif
