#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/dsp.h"

int main(int argc, char *argv[]) {
    Node *head = NULL;

    if(argc <= 1) {
        fprintf(stderr, "You must give an input file!\n");
        return 0;
    } else {
        transfer(head, argv[1]);
    }

    printList(head);
    //searchFor(head, ',');

    return 0;
}
