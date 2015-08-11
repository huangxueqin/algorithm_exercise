#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *reverseList(struct ListNode *head) {
    struct ListNode *p = head->next;
    head->next = NULL;
    while(p != NULL) {
        struct ListNode *tmp = p->next;
        p->next = head;
        head = p;
        p = tmp;
    }
    return head;
}

void reorderList(struct ListNode *head) {
    struct ListNode *p = head, *pp = head;
    while(pp != NULL && pp->next != NULL) {
        p = p->next;
        pp = pp->next->next;
    }
    struct ListNode *p1 = head;
    struct ListNode *p2 = p != NULL && p->next != NULL ? reverseList(p->next) : NULL;
    if(p2 != NULL) {
        p->next = NULL;
        while(p2 != NULL) {
            struct ListNode *tmp1 = p1->next;
            struct ListNode *tmp2 = p2->next;
            p1->next = p2;
            p2->next = tmp1;
            p1 = tmp1;
            p2 = tmp2;
        }
    }
}
