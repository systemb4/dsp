#include <stdio.h>
#include <time.h>

#include "src/nachtigal.h"

int main(int argc, char *argv[]) {
    double timeSpent = 0.0;
    clock_t begin = clock();

    Token *tokens = lexer(argv[1]);
    //printTokens(tokens);
    Name *head = parser(tokens);
    free(head);

    clock_t end = clock();

    timeSpent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time: %f\n", timeSpent);

    return 0;
}
