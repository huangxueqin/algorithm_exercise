#include "leetc.h"

using namespace std;

class Solution {
    public:
        ListNode *reverseBetween(ListNode *head, int m, int n) {
            ListNode *p = head, *pp = NULL;
            for(size_t i = 1; i < m; i++) {
                pp = p;
                p = p->next;
            }
            if(pp == NULL) return reverseList(p, n-m);
            else {
                pp->next = reverseList(p, n-m);
                return head;
            }

        }
    private:
        ListNode *reverseList(ListNode *head, size_t num) {
            if(num == 0) return head;
            ListNode *fnode = head, *lnode = head;
            ListNode *mnode = head->next;
            for(size_t i = 0; i < num; i++) {
                ListNode *node = mnode;
                mnode = mnode->next;
                node->next = fnode;
                fnode = node;
            }
            lnode->next = mnode;
            return fnode;
        }
};

Solution sol;

int main(void) {
    printf("----------Test----------\n");
    int a[] = {1, 2, 3};
    ListNode *head = deserialize_list(a, 3);
    vector<int> result2 = serialize_list(head);
    print_vector(result2);
    head = sol.reverseBetween(head, 3, 3);
    vector<int> result = serialize_list(head);
    print_vector(result);
    ListNode::destroy_list(head);
    return 0;
}
