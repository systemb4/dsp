/*
 * parSort.h
 */

#ifndef __PARSORT_H__
#define __PARSORT_H__

int namesLength(Name *names) {
    int i = 0;
    Name *tmp = names;

    while(tmp != NULL) {
        tmp = tmp->nameLink;
        i++;
    }

    return i;
}

Name *sortNames(Name *head) {
    int length = namesLength(head);

    for(int i = 0; i < length; i++) {
    }

    return head;
}

#endif
