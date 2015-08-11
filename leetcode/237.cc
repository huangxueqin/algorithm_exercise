#include "leetc.h"

class Solution {
public:
    void deleteNode(ListNode *node) {
        ListNode *p = node;
        ListNode *pp = p->next;
        while(pp) {
            p->val = pp->val;
            if(pp->next) {
                p = pp;
                pp = pp->next;
            }
            else {
                p->next = NULL;
                pp = NULL;
            }
        }
    }
};
