#include<stdio.h>
#include<stdlib.h>
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* creatlist() {
    int a;
    struct ListNode *p, *q, *head;
    head = (struct ListNode*)malloc(sizeof(struct ListNode));
    p = head;
    scanf("%d", &a);
    while(a != -1) {
        q = (struct ListNode*)malloc(sizeof(struct ListNode));
        q->val = a;
        p->next = q;
        p = q;
        scanf("%d",&a);
    }
    p->next = '\0';
    return head;
}


struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *p = NULL, *q = head, *nexttmp = NULL;
    while(q) {
        nexttmp = q->next;
        q->next = p;
        p = q;
        q = nexttmp;
    }
    return p;
}
