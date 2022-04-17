#include <stdio.h>
#include <time.h>

#include "src/nachtigal.h"

int main(int argc, char *argv[]) {
    double timeSpent = 0.0;
    clock_t begin = clock();

    Token *tokens = lexer(argv[1]);
    Name *names = parser(tokens);

    //printTokens(tokens);
    printNames(names);

    printf("\n");
    Arithmetic *art = run(names);
    //addArtHead(&art, '$', 3.2, 0);
    printArt(art);

    /*
    printf("\n");
    art = sortStack(art);
    printArt(art);
    */

    free(tokens);
    free(names);
    free(art);

    clock_t end = clock();

    timeSpent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time: %f\n", timeSpent);

    return 0;
}
