#include <stdio.h>
#include <stdlib.h>

struct node {
    char value;
    struct node* next;
};

typedef struct node node_c;

node_c *head = NULL;

node_c *insertEnd(node_c **head, char value) {
    node_c *result = malloc(sizeof(node_c));
    result->value = value;
    result->next = NULL;

    if(*head == NULL) {
        *head = result;
    } else {
        node_c *lastNode = *head;

        while(lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = result;
    }
}

void printList(node_c *head) {
    node_c *tmp = head;

    while(tmp != NULL) {
        printf("%c", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

void transfer(char name[]) {
    FILE *fptr;
    fptr = fopen(name, "r");
    char c = fgetc(fptr);
    while(c != EOF) {
        insertEnd(&head, c);
        c = fgetc(fptr);
    }
    fclose(fptr);
}

int main(int argc, char *argv[]) {
    transfer(argv[1]);
    printList(head);

    return 0;
}
