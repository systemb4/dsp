/*
 * Author: Lukas Nitzsche
 */

#include "lexer.h"

#ifndef __PARSER_H__
#define __PARSER_H__

typedef struct Ast {
    Token token;
    int id;
    union {
        char *name;
        char *def;
    };
    union {
        char *valC;
        double valN;
    };
} Ast;

Ast *parser(Token *tokens) {
}

#endif
