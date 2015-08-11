#include "leetc.h"

using namespace std;

int main(void) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    size_t n = 10;
    ListNode *head = deserialize_list(a, n);
    vector<int> result = serialize_list(head);
    print_vector(result);
    return 0;
}
