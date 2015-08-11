#include "leetc.h"

using std::vector;
using std::string;

class Solution {
    public:
        ListNode *insertionSortList(ListNode *head) {
            ListNode *pinsn = NULL;
            ListNode *insn = head;
            while(insn != NULL) {
                ListNode *ptmpn = NULL;
                ListNode *tmpn = head;
                while(tmpn != insn && tmpn->val < insn->val) {
                    ptmpn = tmpn;
                    tmpn = tmpn->next;
                }
                ListNode *ninsn = insn->next;
                if(tmpn != insn) {
                    if(ptmpn != NULL)
                        ptmpn->next = insn;
                    else
                        head = insn;
                    insn->next = tmpn;
                }
                else {
                    pinsn = insn;
                }
                pinsn->next = ninsn;
                insn = ninsn;
            }
            return head;
        }
    private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int arr[] = {9,8,7,6,5,4,3,2,1};
    ListNode *head = deserialize_list(arr, 9);
    head = sol.insertionSortList(head);
    ListNode::print_list(head);
    delete head;
    return 0;
}
