#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/dsp.h"

int main(int argc, char *argv[]) {
    //Node *head = NULL;

    /*
    if(argc <= 1) {
        fprintf(stderr, "You must give an input file!\n");
        return 0;
    } else {
        transfer(head, argv[1]);
    }
    */

    //printList(head);
    //searchFor(head, ',');

    Node *test1;
    Node *test2;
    Node *test3;

    test1->value = 'a';
    test1->next = test2;

    test2->value = 'b';
    test2->next = test3;

    test3->value = 'c';
    test3->next = NULL;

    //printList(test1);
    printf("%c\n", test1->value);
    printf("%c\n", test2->value);
    printf("%c\n", test3->value);

    return 0;
}
