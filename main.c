#include <stdio.h>
#include <time.h>

#include "src/nachtigal.h"

int main(int argc, char *argv[]) {
    double timeSpent = 0.0;
    clock_t begin = clock();

    Token *tokens = lexer(argv[1]);
    Name *names = parser(tokens);
    Arithmetic *art = run(names);

    printTokens(tokens);
    printf("\n");
    printNames(names);
    printf("\n");
    printArt(art);
    printf("\n");

    Arithmetic *tmp = sortStackOps(&art);
    printArt(tmp);

    free(tokens);
    free(names);
    free(art);

    clock_t end = clock();

    timeSpent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time: %f\n", timeSpent);

    return 0;
}
