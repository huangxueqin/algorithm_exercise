#include "leetc.h"

using std::vector;
using std::string;

void print_list(ListNode *l) {
    while(l != NULL) {
        std::printf("%d ", l->val);
        l = l->next;
    }
    std::printf("\n");
}

class Solution {
    public:
        ListNode *sortList(ListNode *head) {
            if(head == NULL || head->next == NULL) return head;
            ListNode **tail = &head, **mid = &head;
            while((*tail)->next != NULL && (*tail)->next->next != NULL) {
                mid = &((*mid)->next);
                tail = &((*tail)->next->next);
            }
            if((*tail)->next != NULL) tail = &((*tail)->next);
            ListNode *l2_head = (*mid)->next;
            (*mid)->next = NULL;
            ListNode *l1 = sortList(head);
            ListNode *l2 = sortList(l2_head);
            return merge_lists(l1, l2);
        }
    private:

        ListNode *merge_lists(ListNode *l1, ListNode *l2) {
            if(l1 == NULL) return l2;
            else if(l2 == NULL) return l1;

            ListNode *head = l1->val < l2->val ? l1 : l2;
            if(l1->val < l2->val) l1 = l1->next;
            else l2 = l2->next;

            ListNode *sorted = head;
            ListNode *sorted_prev = NULL;
            while(l1 != NULL && l2 != NULL) {
                sorted->next = l1->val < l2->val ? l1 : l2;
                sorted_prev = sorted;
                sorted = sorted->next;
                if(l1->val < l2->val) l1 = l1->next;
                else l2 = l2->next;
            }
            if(l1 == NULL) {
                l1 = l2;
            }
            while(l1 != NULL) {
                sorted->next = l1;
                sorted = sorted->next;
                l1 = l1->next;
            }
            return head;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int arr[] = {2,1,3,5,4,1,3,3,1,3,1,3,3,2,3,2,2,1,1,1,3,2,2,1,1,2,2,2,3,3,
        1,1,2,2,2,1,2,1,1,2,3,3,2,2,3,2,3,2,2,2,1,1,3,2,3,3,1,1,1,2,2,1,2,2,2,
        2,3,1,3,1,1,1,2,1,2,2,2,1,3,2,2,2,3,3,2,3,3,1,1,2,2,1,2,1,3,2,1,3,3,1,
        2,1,1,1,1,1,2,1,2,2,2,2,3,3,3,1,1,3,2,1,1,2,1,3,3,2,2,1,3,1,3,1,3,2,2,
        3,2,3,2,2,1,2,3,1,3,1,2,3,3,2,3,3,3,1,1,2,3,1,2,3,2,1,1,2,3,1,1,3,1,2,
        2,3,2,1,3,1,2,1,3,2,1,1,2,2,2,1,3,1,3,2,3,3,1,1,3,1,2};
    ListNode *head = deserialize_list(arr, 788/4);  
    head = sol.sortList(head); 
    vector<int> sel = serialize_list(head); 
    print_vector(sel);   
    delete head;
    return 0;
}
