#include "leetc.h"

class Solution {
public:
    bool isPalindrome(ListNode *head) {
        if(!head) return true;
        ListNode *slow = head, *fast = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *mid = slow;
        ListNode *pp = mid, *p = mid->next;
        mid->next = NULL;
        while(p) {
            ListNode *tmp = p->next;
            p->next = pp;
            pp = p;
            p = tmp;
        }
        bool result = true;
        ListNode *tail = pp;
        ListNode *l1 = head, *l2 = tail;
        while(l1 && l2 ) {
            if(l1->val != l2->val) {
                result = false;
                break;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        pp = tail;
        p = tail->next;
        tail->next = NULL;
        while(p) {
            ListNode *tmp = p->next;
            p->next = pp;
            pp = p;
            p = tmp;
        }
        return result;
    }
};
