#include "leetc.h"

using namespace std;

class Solution {
    public:
        ListNode *swapPairs(ListNode *head) {
            return swapNextPairs(head);
        }
    private:
        ListNode *swapNextPairs(ListNode *head) {
            if(head == NULL || head->next == NULL) return head;
            ListNode *new_head = head->next;
            ListNode *node = new_head->next;
            new_head->next = head;
            head->next = swapNextPairs(node);
            return new_head;
        }
};

Solution sol;
