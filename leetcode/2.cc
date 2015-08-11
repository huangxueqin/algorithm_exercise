#include "leetc.h"

class Solution {
    public:
        ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
            if(l1 == NULL) return cloneList(l2);
            else if(l2 == NULL) return cloneList(l1);
            ListNode *sum = new ListNode((l1->val+l2->val)%10);
            bool carry = l1->val + l2->val >= 10;
            ListNode *p = sum;
            l1 = l1->next;
            l2 = l2->next;
            while(l1 != NULL && l2 != NULL) {
                int newval = l1->val + l2->val + (carry ? 1 : 0);
                if(newval >= 10) {
                    newval -= 10;
                    carry = true;
                }
                else
                    carry = false;
                p->next = new ListNode(newval);
                p = p->next;
                l1 = l1->next;
                l2 = l2->next;
            }
            ListNode *ll = l1 == NULL ? l2 : l1;
            while(carry && ll != NULL) {
                p->next = new ListNode((1+ll->val)%10);
                p = p->next;
                carry = 1 + ll->val >= 10;
                ll = ll->next;
            }
            if(carry) {
                    p->next = new ListNode(1);
                    p = p->next;
            }
            p->next = cloneList(ll);
            return sum;
        }
    private:
        ListNode *cloneList(ListNode *l) {
            if(l == NULL)
                return NULL;
            ListNode *lc = new ListNode(l->val);
            ListNode *lcc = lc;
            l = l->next;
            while(l != NULL) {
                lcc->next = new ListNode(l->val);
                l = l->next;
                lcc = lcc->next;
            }
            return lc;
        }
};
