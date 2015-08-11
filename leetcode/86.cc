#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        ListNode *partition(ListNode *head, int x) {
            ListNode *insertpp = NULL;
            ListNode *insertp = head;
            while(insertp != NULL && insertp->val < x) {
                insertpp = insertp;
                insertp = insertp->next;
            }
            ListNode *scanpp = insertpp;
            ListNode *scanp = insertp;
            while(scanp != NULL) {
                ListNode *scanpn = scanp->next;
                if(scanp->val < x) {
                    if(scanpp == NULL) {
                        scanpp = scanp;
                    }
                    else {
                        scanpp->next = scanpn;
                        scanp->next = insertp;
                        if(insertpp == NULL) {
                            head = scanp;
                        }
                        else {
                            insertpp->next = scanp;
                        }
                        insertpp = scanp;
                    }
                }
                else {
                    scanpp = scanp;
                }
                scanp = scanpn;
            }
            return head;
        }
    private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int arr[] = {4,5,6,7,8,9,1,2,3};
    ListNode *head = deserialize_list(arr, 9);
    head = sol.partition(head, 4);
    vector<int> sel = serialize_list(head);
    print_vector(sel);
    delete head;
    return 0;
}
