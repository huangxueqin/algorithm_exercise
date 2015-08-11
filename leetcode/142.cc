#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        ListNode *detectCycle(ListNode *head) {
            ListNode *slow = head, *fast = head;
            while(slow && fast && fast->next) {
                slow = slow->next;
                fast = fast->next->next;
                if(slow == fast)
                    break;
            }
            if(fast == NULL || fast->next == NULL)
                return NULL;
            while(head != slow) {
                head = head->next;
                slow = slow->next;
            }
            return head;
        }
    private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
