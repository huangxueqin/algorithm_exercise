#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        bool hasCycle(ListNode *head) {
            ListNode *slow = head, *fast = head;
            while(slow != NULL && fast != NULL && fast->next != NULL) {
                slow = slow->next;
                fast = fast->next->next;
                if(slow == fast) 
                    return true;
            }
            return false;
        }
    private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
