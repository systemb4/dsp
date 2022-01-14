#include <stdio.h>

#include "src/lexer.h"

int main(int argc, char *argv[]) {
    printTokens(lexer(argv[1]));

    return 0;
}
