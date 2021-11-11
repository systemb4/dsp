#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void searchFor(node_c *head, char searchValue) {
    node_c *tmp = head;
    char data[30];

    while(tmp != NULL) {
        //printf("%c", tmp->value);
        if(tmp->value == searchValue) {
            tmp = tmp->next;
            while(tmp->value != ':') {
                strncat(data, &tmp->value, 1);
                tmp = tmp->next;
            }
        }
        tmp = tmp->next;
    }
    printf("%s\n", data);
}

int main(int argc, char *argv[]) {
    if(argc <= 1) {
        printf("You must give an input file!\n");
        return 0;
    } else {
        transfer(argv[1]);
    }

    printList(head);
    searchFor(head, ',');

    return 0;
}
