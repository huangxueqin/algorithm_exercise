#include "leetc.h"
#include <algorithm>
#include <climits>

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        void nextPermutation(vector<int> &num) {
            if(num.size() <= 1) return;
            auto it = num.end()-2;
            auto swap_it = num.end();
            while(it >= num.begin() && (swap_it = find_next_larger_elmt(num, it)) == num.end())
                it--;
            if(it >= num.begin()) {
                int temp = *it;
                *it = *swap_it;
                *swap_it = temp;
                std::sort(it+1, num.end());
            }
            else 
                std::sort(num.begin(), num.end());
        }
    private:
        vector<int>::iterator find_next_larger_elmt(vector<int> &num, 
                vector<int>::iterator it) {
            auto result = num.end();
            int t = *it;
            int idea = INT_MAX;
            for(++it; it != num.end(); it++) {
                if(*it > t) {
                    if(idea > *it) {
                        result = it;
                        idea = *it;
                    }
                }
            }
            return result;
        }

};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int arr[] = {1,2,3,4,5};
    vector<int> num(arr, arr+5);
    for(int i = 0; i < 20; i++) {
        sol.nextPermutation(num);
        print_vector(num);
    }
    return 0;
}
