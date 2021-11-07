#include <stdio.h>
#include <string.h>

#define MAX 3072

char data[MAX];

void transfer(char name[]) {
    /*
     * check if file in dir and if not printf
     */
    FILE *fptr;
    fptr = fopen(name, "r");
    char c = fgetc(fptr);
    while(c != EOF) {
        strncat(data, &c, 1);
        c = fgetc(fptr);
    }

    fclose(fptr);
}

int main(int argc, char *argv[]) {
    transfer(argv[1]);

    printf("%s\n", data);

    return 0;
}
