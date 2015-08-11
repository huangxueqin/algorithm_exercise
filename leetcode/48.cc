#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        void rotate(vector<vector<int>> &mat) {
            int n = mat.size();
            int l = n-1;
            vector<int> col(n);
            vector<int> row(n);
            for(int i = 0; i < n; i++) {
                for(int k = 0; k < n; k++)
                    col[k] = mat[k][l-i];
                for(int k = 0; k < n-i; k++)
                    row[k] = mat[i][k];
                for(int k = 0; k < i; k++)
                    row[n-i+k] = mat[i-k-1][l-i];
                for(int k = 0; k < n; k++)
                    mat[k][l-i] = row[k];
                for(int k = 0; k < l-i; k++)
                    mat[i][k] = col[l-k];
            }
        }
    private:
        inline void swap(int i, int j, int ii, int jj, vector<vector<int>> &mat) {
            int tmpi = mat[i][j];
            mat[i][j] = mat[ii][jj];
            mat[ii][jj] = tmpi;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    vector<vector<int>> mat{{4,2,1,3},{8,5,4,1},{2,3,9,6},{5,6,3,3}};
    print_table(mat);
    sol.rotate(mat);
    printf("----------after----------\n");
    print_table(mat);
    return 0;
}
