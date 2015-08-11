#include "leetc.h"
#include <algorithm>

using namespace std;

class Solution {
    public:
        int minimumTotal(vector<vector<int>> &triangle) {
            int rows = triangle.size();
            if(rows == 0)
                return 0;
            int *pstate = new int[rows]();
            int *cstate = new int[rows]();
            for(int i=0;i<rows;i++) {
                vector<int> &crow = triangle[i];
                for(int j=0;j<=i;j++) {
                    int left = j > 0 ? j-1 : j;
                    int right = j < i ? j : j-1;
                    cstate[j] = std::min(pstate[left], pstate[right]) + crow[j];
                }
                std::swap(pstate, cstate);
                // std::memcpy((char *)pstate, (char *)cstate , sizeof(int) * rows);
            }
            int min_path = pstate[0];
            for(int i=1;i<rows;i++) {
                if(pstate[i] < min_path) {
                    min_path = pstate[i];
                }
            }
            delete pstate;
            delete cstate;
            return min_path;
        }
};

int main(void) {
    vector<vector<int>> t;
    int r1[] = {2}; vector<int> v1(r1, r1+1); t.push_back(v1);
    int r2[] = {3, 4}; vector<int> v2(r2, r2+2); t.push_back(v2);
    int r3[] = {5, 6, 7}; vector<int> v3(r3, r3+3); t.push_back(v3);
    int r4[] = {4, 1, 8, 3}; vector<int> v4(r4, r4+4); t.push_back(v4);
    Solution s;
    printf("%d\n", s.minimumTotal(t));
    return 0;
}
