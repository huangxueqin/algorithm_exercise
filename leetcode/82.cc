#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        ListNode *deleteDuplicates(ListNode *head) {
            if(head == NULL) return head;
            ListNode *pp = NULL;
            ListNode *p = head;
            while(p != NULL && p->next != NULL) {
                if(p->val == p->next->val) {
                    ListNode *tmpln = p;
                    while(p->next != NULL && p->val == p->next->val)
                        p = p->next;
                    if(pp == NULL) {
                        head = p->next;
                    }
                    else {
                        pp->next = p->next;
                    }
                    p->next = NULL;
                    delete tmpln;
                    // because I defined the destructor of ListNode so following code
                    // is unessisary
                    /* while(tmpln != NULL) {
                     *     ListNode *tmptmpln = tmpln;
                     *     tmpln = tmpln->next;
                     *     delete(tmptmpln);
                     * } */
                    p = pp == NULL ? head : pp->next;
                }
                else {
                    pp = p;
                    p = p->next;
                }
            }
            return head;
        }
    private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int arr[] = {2,2,3,3,4,4,4};
    ListNode *head = deserialize_list(arr, 7);
    head = sol.deleteDuplicates(head);
    ListNode::print_list(head);
    delete head;
    return 0;
}
