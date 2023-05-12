/*
 * nachtigal
 * See LICENSE file for copyright and license details
 * Author: Lukas Nitzsche
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "std.h"

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
    enum keyWord type;
    struct Definition *defLink;
} Definition;

typedef struct Arithmetic {
    char op;
    enum charType type;
    int pos; /* use to show which
                nodes are on the same line for sort and order of ops */
    union {
        char *str;
        double numVal;
    };

    struct Arithmetic *prev;
    struct Arithmetic *next;
} Arithmetic;

typedef union Values {
    char *str;
    double numVal;
} Values;

Arithmetic *addArt(char op, char *value, int numPos, enum charType type);
void addArtHead(Arithmetic **head, char op, char *value, int numPos, enum charType type);
void insertArtHead(Arithmetic *head, Arithmetic *node);
void addArtEnd(Arithmetic **head, char op, char *value, int numPos, enum charType type);
void insertArt(Arithmetic *node, char op, char *value, int numPos, enum charType type);
void deleteArt(Arithmetic *node);
Arithmetic *sortStackOps(Arithmetic **head);
void addName(Name **head, char **name, enum keyWord type);
void addDefinition(Name **head, char **val, enum keyWord type);
char *sortTokens(Token *tokens, int pos);
int charCount(FILE *fptr);
int tokensLength(Token *tokens);
int namesLength(Name *names);
size_t getSize (const char* s);
char charCheck(char ch);
void printTokens(Token *tokens);
void printArt(Arithmetic *head);
Token *lexer(char name[]);
Name *parser(Token *tokens);


Arithmetic *addArt(char op, char *value, int numPos, enum charType type) {
    Arithmetic *tmp = malloc(sizeof(Arithmetic));
    char *end;

    if(CHAR_STRING[type] == CHAR_STRING[NUM]) {
        tmp->numVal = strtod(value, &end);
    } else {
        tmp->str = value;
    }

    /*
     * use this in both addEnd and addFront to make easier
     */

    tmp->type = type;
    tmp->op = op;
    tmp->pos = numPos;
    tmp->next = NULL;
    tmp->prev = NULL;

    return tmp;
}

void addArtHead(Arithmetic **head, char op, char *value, int numPos, enum charType type) {
    Arithmetic *result = addArt(op, value, numPos, type);

    result->next = *head;
    *head = result;

    /*
     * for sortStack so that * and / can be added the front
     *  so that they are chosen first when sorted through in a linear
     *  sense
     */
}

void insertArtHead(Arithmetic *head, Arithmetic *node) {
    node->next = head;
    head->prev = node;
    head = node;
}

void addArtEnd(Arithmetic **head, char op, char *value, int numPos, enum charType type) {
    Arithmetic *result = addArt(op, value, numPos, type);
    Arithmetic *lastNode = *head;

    if(*head == NULL) {
        *head = result;
    } else {
        while(lastNode->next != NULL) {
            lastNode = lastNode->next;
        }

        result->prev = lastNode;
        lastNode->next = result;
    }
}

void insertArt(Arithmetic *node, char op, char *value, int numPos, enum charType type) {
    Arithmetic *tmp = addArt(op, value, numPos, type);

    if(node->prev == NULL) {
        fprintf(stderr, "Can not insert node at head! Try using 'addArtHead' instead of 'insertArt'\n");
        return;
    }

    Arithmetic *norm = node;
    Arithmetic *swap = node->prev;

    norm->prev = tmp;
    swap->next = tmp;
    tmp->prev = swap;
    tmp->next = norm;

}

void deleteArt(Arithmetic *node) {
    Arithmetic *tmp = node;
    Arithmetic *tmp_prev = node->prev;

    tmp_prev->next = tmp->next;
    tmp->next->prev = tmp_prev;

    free(tmp);
    tmp = NULL;

    /*
     * delete node from art
     * will be used to move over nodes
     */
}

Arithmetic *sortStackOps(Arithmetic **head) {
    /*
     * for sort through Definition by order of operations
     * this is basically insertion sort where a value is compared
     *  to something and if true just puts it in front
     */

    Arithmetic *tmp = *head;
    int currPos = 0;
    tmp = tmp->next;
    tmp = tmp->next;

    while(tmp == NULL) {
        if(tmp->op == '*' || tmp->op == '/') {
            insertArtHead(*head, tmp);
            //deleteArt(tmp);
        }

        tmp = tmp->next;
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

char charCheck(char ch) {
    if(ch == 0) {
        return 'X';
    } else {
        return ch;
    }
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

    while(tmp != NULL) {
        if(tmp->type == NUM) {
            printf("%c = %.2lf ! %d\n", tmp->op, tmp->numVal, tmp->pos);
        } else if(tmp->type == LETTER) {
            printf("%c = %s ! %d\n", tmp->op, tmp->str, tmp->pos);
        }
        tmp = tmp->next;
    }

    //tmp = tmp->prev;

    /*
    while(tmp != NULL) {
        while(tmp->list->next != NULL) {
            printf("%c = %lf\n", tmp->list->op, tmp->list->numVal);
            tm = tmp->list->next;
        }

        tmp = tmp->next;
        tm = tmp;
    }*/
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

    /*
     * make sure file is of type .nagl
     */
    if(strcmp(strrchr(name, '\0') - 5, ".nagl")) {
        fprintf(stderr, "File needs to be of type '.nagl'!\n");
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

Arithmetic *run(Name *head) {
    int length = namesLength(head);

    Name *tmp = head;
    Arithmetic *art = NULL;
    char *cVal, *end;
    enum charType typeCheck;

    for(int i = 0; i < length; i++) {
        int length_str = getSize(tmp->defLink->stringVal);
        for(int x = 0; x < length_str; x++) {
            if(tmp->defLink->stringVal[x] == '\'') {
                typeCheck = NUM;
                x++;
                cVal = malloc(sizeof(char) * 15);
                for(int y = 0; tmp->defLink->stringVal[x] != '\''; y++) {
                    cVal[y] = tmp->defLink->stringVal[x];
                    cVal[y+1] = '\0';
                    x++;
                }
                x++;
                addArtEnd(&art, charCheck(tmp->defLink->stringVal[x]), cVal, i, typeCheck);
            } else if(tmp->defLink->stringVal[x] == '"') {
                typeCheck = LETTER;
                x++;
                cVal = malloc(sizeof(char) * 100);
                for(int y = 0; tmp->defLink->stringVal[x] != '"'; y++) {
                    cVal[y] = tmp->defLink->stringVal[x];
                    cVal[y+1] = '\0';
                    x++;
                }
                x++;
                addArtEnd(&art, charCheck(tmp->defLink->stringVal[x]), cVal, i, typeCheck);
            }
        }
        tmp = tmp->nameLink;
    }

    return art;
}

#endif
