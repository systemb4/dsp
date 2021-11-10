#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char value;
    struct node* next;
};
typedef struct node node_t;

node_t *cNode(char value) {
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;
    return result;
}

node_t *insertEnd(node_t **head, char value) {
    node_t *result = malloc(sizeof(node_t));
    result->value = value;
    result->next = NULL;

    if(*head == NULL) {
        *head = result;
    } else {
        node_t *lastNode = *head;

        while(lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = result;
    }
}

void printList(node_t *head) {
    node_t *tmp = head;

    while(tmp != NULL) {
        printf("%c ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

/*
void transfer(char name[]) {
    // check if file in dir and if not printf
    FILE *fptr;
    fptr = fopen(name, "r");
    char c = fgetc(fptr);
    while(c != EOF) {
        strncat(data, &c, 1);
        c = fgetc(fptr);
    }

    fclose(fptr);
}*/

int main(int argc, char *argv[]) {
    node_t *head = NULL;
    node_t *tmp;

    insertEnd(&head, 'A');
    insertEnd(&head, 'B');
    insertEnd(&head, 'C');

    printList(head);

    return 0;
}
