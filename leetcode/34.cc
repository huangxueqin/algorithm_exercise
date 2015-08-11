#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        vector<int> searchRange(int a[], int n, int target) {
            vector<int> error(2, -1);
            if(n < 1) return error;
            if(a[0] > target || a[n-1] < target) return error;
            int index = find_target(a, 0, n-1, target);
            printf("index = %d\n", index);
            if(index == -1) return error;
            else {
                int i = index, j = index;
                while(i > 0 && a[i] == target) i--;
                while(j < n-1 && a[j] == target) j++;
                return make_result(a[i] == target ? i : i+1, 
                        a[j] == target ? j : j-1);
            }
        }
    private:
        int find_target(int a[], int i, int j, int target) {
            if(a[i] == target) return i;
            if(a[j] == target) return j;
            if(i+1 >= j) return -1;
            int mid = (i+j) / 2;
            if(a[mid] > target) return find_target(a, i, mid, target);
            else if(a[mid] < target) return find_target(a, mid, j, target);
            else return mid;
        }
        inline vector<int> make_result(int i, int j) {
            vector<int> result;
            result.push_back(i);
            result.push_back(j);
            return result;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int a[] = {0,0,0,1,2,3};
    int target = 0;
    vector<int> result = sol.searchRange(a, sizeof(a) / sizeof(int), target);
    print_vector(result);
    return 0;
}
