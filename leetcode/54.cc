#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        vector<int> spiralOrder(vector<vector<int>> &mat) {
            vector<int> result;
            int m = mat.size();
            if(m == 0) return result;
            int n = mat[0].size();
            if(n == 0) return result;
            int i = 0;
            while(true) {
                if(i >= m-i) 
                    break;
                for(int k = i; k < n-i; k++)
                    result.push_back(mat[i][k]);
                if(n-1-i <= i-1)
                    break;
                for(int k = i+1; k < m-i; k++) 
                    result.push_back(mat[k][n-1-i]);
                if(i >= m-1-i)
                    break;
                for(int k = n-2-i; k >= i; k--) 
                    result.push_back(mat[m-1-i][k]);
                if(i >= n-1-i)
                    break;
                for(int k = m-i-2; k > i; k--) 
                    result.push_back(mat[k][i]);
                i++;
            }
            return result;
        }
    private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    vector<vector<int>> mat{{1,2,3,4,5,6,7,8,9,10}, {11,12,13,14,15,16,17,18,19,20}};
    print_table(mat);
    vector<int> result = sol.spiralOrder(mat);
    print_vector(result);
    return 0;
}
