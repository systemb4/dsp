#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char value;
    struct Node* next;
} Node;

static Node *insertEnd(Node **head, char value) {
    Node *result = malloc(sizeof(Node));

    result->value = value;
    result->next = NULL;

    if(*head == NULL) {
        *head = result;
    } else {
        Node *lastNode = *head;

        while(lastNode->next != NULL) {
            lastNode = lastNode->next;
        }
        lastNode->next = result;
    }
}

static void printList(Node *head) {
    Node *tmp = head;

    while(tmp != NULL) {
        printf("%c", tmp->value);
        tmp = tmp->next;
    }
}

static void *transfer(Node *head, char name[]) {
    FILE *fileO = fopen(name, "r");

    if(fileO == NULL) {
        fprintf(stderr, "File does not exist!\n");
        exit(EXIT_SUCCESS);
    }

    char c = fgetc(fileO);
    while(c != EOF) {
        insertEnd(&head, c);
        c = fgetc(fileO);
    }

    fclose(fileO);
}

static void searchFor(Node *head, char searchValue) {
    Node *tmp = head;
    char data[30];

    while(tmp != NULL) {
        if(tmp->value == searchValue) {
            tmp = tmp->next->next;
            while(tmp->value != ':') {
                strncat(data, &tmp->value, 1);
                tmp = tmp->next;
            }
            break;
        }
        tmp = tmp->next;
    }

    printf("%s\n", data);
}

int main(int argc, char *argv[]) {
    Node *head = NULL;

    if(argc <= 1) {
        fprintf(stderr, "You must give an input file!\n");
        return 0;
    } else {
        transfer(head, argv[1]);
    }

    printList(head);
    searchFor(head, ',');

    return 0;
}
