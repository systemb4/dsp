/*
 * parser.h
 */

#ifndef __PARSER_H__
#define __PARSER_H__

#define FOREACH_KEYWORD(KEYWORD) \
    KEYWORD(HEAD)   \
    KEYWORD(CONST)  \
    KEYWORD(NAME)   \
    KEYWORD(DEF)    \

#define GENERATE_STRING(STRING) #STRING,
#define GENERATE_ENUM(ENUM) ENUM,

enum keyWord {
    FOREACH_KEYWORD(GENERATE_ENUM)
};

static const char *KEYWORD_STRING[] = {
    FOREACH_KEYWORD(GENERATE_STRING)
};

typedef struct Name {
    char *name;
    enum keyWord type;
    struct Name *nameLink;
    struct Definition *defLink;
} Name;

typedef struct DefNode {
    struct DefNode *next;
    char *val; /* will be something like "verb" and next node will be "adj" */
    char *type;
} DefNode;

typedef struct Definition {
    char op;
    enum keyWord type;
    struct Definition *defLink;
    struct DefNode *nodeLink;
} Definition;

double strToDb(char *str) {
    double result;
    char *ptr_end;

    result = strtod(str, &ptr_end);

    return result;
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

    DefNode *node = NULL;

    int i = 0;
    char curr = *val[i];
    for(i = 0; curr != ']' || curr != '+'; i++) {
        node->val[i] = curr;
    }
    node->val[i+1] = '\0';

    result->nodeLink = node;
    result->defLink = NULL;
    result->type = type;

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

char *sort(Token *tokens, int pos) {
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

int tokensLength(Token *tokens) {
    int i = 0;
    while(tokens[i].end != 1) {
        i++;
    }

    return i;
}

/*
void printNames(Name *head) {
    Name *tmp = head;

    while(tmp != NULL) {
        printf("%s - ", tmp->name);
        printf("%s\n", tmp->defLink->stringVal);
        tmp = tmp->nameLink;
    }
}*/

Name *parser(Token *tokens) {
    int length = tokensLength(tokens);
    Name *head = NULL;

    char *tmp;
    for(int i = 0; i < length; i++) {
        if(tokens[i].type == LPAREN) {
            tmp = sort(tokens, i);
            addName(&head, &tmp, NAME);
            i += strlen(tmp);
        } else if(tokens[i].type == LBRACKET) {
            tmp = sort(tokens, i);
            addDefinition(&head, &tmp, DEF);
            i += strlen(tmp);
        }
    }

    return head;
}

#endif
