#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        bool searchMatrix(vector<vector<int>> &matrix, int target) {
            size_t m = matrix.size();
            if(m < 1) return false;
            size_t n = matrix[0].size();
            if(n < 1) return false;
            vector<int> rowmax;
            for(size_t i = 0; i < m; i++)
                rowmax.push_back(matrix[i][n-1]);
            size_t target_row = find_nearest_index(rowmax, target);
            if((target_row) == m) return false;
            return find_target(matrix[target_row], target);
        }
    private:
        bool find_target(vector<int> &ivec, const int target) {
            size_t n = ivec.size();
            if(n < 1) return false;
            if(ivec[0] <= target && ivec[n-1] >= target) {
                if(ivec[0] == target || ivec[n-1] == target) return true;
                int s = 0, t = n-1;
                while(t > s + 1) {
                    if(ivec[t] == target || ivec[s] == target) return true;
                    else {
                        int mid = (s+t) >> 1;
                        if(ivec[mid] > target) t = mid;
                        else if(ivec[mid] < target) s = mid;
                        else return true;
                    }
                }
            }
            return false;
        }
        size_t find_nearest_index(vector<int> &ivec, int target) {
            size_t n = ivec.size();
            if(n < 1) return n;
            if(ivec[0] < target && ivec[n-1] >= target) {
                int s = 0, t = n-1;
                while(t > s+1) {
                    int mid = (t+s) >> 1;
                    if(ivec[mid] >= target) t = mid;
                    else s = mid;
                }
                return t;
            }
            else if(ivec[0] >= target) return 0;
            else return n;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int arr[] = {1,3};
    vector<vector<int>> matrix(1, vector<int>(arr, arr+2));
    bool found = sol.searchMatrix(matrix, 2);
    printf("%s\n", found ? "true" : "false");
    return 0;
}
