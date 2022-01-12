/*
 * dsp.h
 * Data Sorting and Processing Library
 * Author: Lukas Nitzsche
 */

#ifndef __DSP_H__
#define __DSP_H__

#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a ## b
#define NAME(base) CONCAT(base, __COUNTER__)

typedef struct List {
    char value;
    struct List *next;
} List;

typedef struct Node {
    struct List *name_value;
    struct List *def_value;
    struct Node *next;
} Node;

void insertEnd(List **head, char val) {
    List *result = malloc(sizeof(List));
    List *lastNode = *head;

    result->value = val;
    result->next = NULL;

    if(*head == NULL) {
        *head = result;
    } else {
        while(lastNode->next != NULL) {
            lastNode = lastNode->next;
        }

        lastNode->next = result;
    }
}

void createNode(Node **head, List **name) {
    Node *result = malloc(sizeof(Node));
    Node *lastNode = *head;

    result->name_value = *name;
    result->next = NULL;

    if(*head == NULL) {
        *head = result;
    } else {
        while(lastNode->next != NULL) {
            lastNode = lastNode->next;
        }

        lastNode->next = result;
    }
}

void printList(List *head) {
    List *tmp = head;

    while(tmp != NULL) {
        printf("%c", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

void printNode(Node *head) {
    List *name = head->name_value;
    List *def = head->def_value;

    while(name != NULL) {
        printf("%c", name->value) ;
        name = name->next;
    }
    printf("\n");

    while(def != NULL) {
        printf("%c", def->value) ;
        def = def->next;
    }
    printf("\n");


}

void transfer(Node **head, char name[]) {
    FILE *fileO = fopen(name, "r");

    if(fileO == NULL) {
        fprintf(stderr, "File does not exist!\n");
        exit(EXIT_SUCCESS);
    }

    char c = fgetc(fileO);

    while(c != EOF) {
        List *name = NULL;
        List *def= NULL;

        // get name
        while(1) {
            insertEnd(&name, c);
            c = fgetc(fileO);
            if(c == ';' || c == ':' || c == '"') {
                c = fgetc(fileO);
                break;
            }
        }

        c = fgetc(fileO);

        // get def
        while(1) {
            if(c == ':' || c == ';') {
                break;
            }
            insertEnd(&def, c);
            c = fgetc(fileO);
        }

        createNode(head, &name);
        printList(name);
        printList(def);

        // go to next line
        if(c == ';') {
            while(1) {
                if(c =='\n') {
                    c = fgetc(fileO);
                    break;
                }
                c = fgetc(fileO);
            }
        }
    }
    fclose(fileO);
}

void llTransfer(List **head, char name[]) {
    FILE *fileO = fopen(name, "r");

    if(fileO == NULL) {
        fprintf(stderr, "File does not exist!\n");
        exit(EXIT_SUCCESS);
    }

    char c = fgetc(fileO);

    while(c != EOF) {
        insertEnd(head, c);
        c = fgetc(fileO);
    }

    fclose(fileO);
}

void llSearchFor(List *head, char searchValue) {
    List *tmp = head;
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

#endif /* end include */
