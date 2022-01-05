#include <stdio.h>
#include <stdlib.h>

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

    /*
    Node test1;
    Node test2;

    head = &test1;
    test1.value = 'a';
    test1.next = &test2;

    test2.value = 'b';
    test2.next = NULL;

    printList(head);
    printf("\n");

    insertEnd(&head, 'c');

    printList(head);
    printf("\n");
    */

    return 0;
}
