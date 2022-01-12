#include <stdio.h>

enum tokenType{NAME, ENDL, DEF};

struct typedef Token {
    int lineNum;
    int charNum;
    enum tokenType;
} Token;

int main() {
    printf("Hello World!");
    return 0;
}
