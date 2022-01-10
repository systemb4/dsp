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

typedef struct llNode {
    char value;
    struct llNode *next;
} llNode;

typedef struct Node {
    struct llNode *name_value;
    struct llNode *def_value;
    struct Node *next;
} Node;

void insertEnd(llNode **head, char val) {
    llNode *result = malloc(sizeof(llNode));
    llNode *lastNode = *head;

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

void createNode(Node **head, llNode **name) {
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

void printLList(llNode *head) {
    llNode *tmp = head;

    while(tmp != NULL) {
        printf("%c", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

void printNode(Node *head) {
    llNode *name = head->name_value;
    llNode *def = head->def_value;

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

    int i = 1;
    while(c != EOF) {
        llNode *list = NULL;
        while(i != 0) {
            if(c == ';' || c == ':' || c == '"') {
                c = fgetc(fileO);
                i = 0;
            }
            insertEnd(&list, c);
            c = fgetc(fileO);
        }
        c = fgetc(fileO);
        createNode(head, &list);
        //printLList(list);
        i = 1;
        while(i != 0) {
            c = fgetc(fileO);
            if(c == '\n') {
                i = 0;
                c = fgetc(fileO);
            }
        }
    }
}

void llTransfer(llNode **head, char name[]) {
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

/*
void searchFor(llNode *head, char searchValue) {
    llNode *tmp = head;
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
*/

#endif /* end include */
