#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        void setZeroes(vector<vector<int>> &matrix) {
            set_zeroes_minimum_space(matrix);
        }
    private:
        // O(1) space
        void set_zeroes_minimum_space(vector<vector<int>> &mat) {
            size_t n = mat.size();
            if(n < 1) return;
            size_t m = mat[0].size();
            if(m < 1) return;
            bool first_row_got_zero = false;
            for(size_t j = 0; j < m; j++)
                if(mat[0][j] == 0) {
                    first_row_got_zero = true;
                    break;
                }
            bool first_col_got_zero = false;
            for(size_t i = 0; i < n; i++)
                if(mat[i][0] == 0) {
                    first_col_got_zero = true;
                    break;
                }

            for(size_t i = 1; i < n; i++) {
                for(size_t j = 1; j < m; j++) {
                    if(mat[i][j] == 0) {
                        mat[i][0] = 0;
                        mat[0][j] = 0;
                    }
                }
            }
            for(size_t i = 1; i < n; i++)
                if(mat[i][0] == 0)
                    set_row_zeroes(mat, i);
            for(size_t j = 1; j < m; j++)
                if(mat[0][j] == 0)
                    set_col_zeroes(mat, j);
            if(first_row_got_zero)
                for(size_t j = 0; j < m; j++)
                    mat[0][j] = 0;
            if(first_col_got_zero)
                for(size_t i = 0; i < n; i++)
                    mat[i][0] = 0;
        }
        // O(m+n) space
        void bf_set_zeroes_improve(vector<vector<int>> &matrix) {
            size_t n = matrix.size();
            if(n < 1) return;
            size_t m = matrix[0].size();
            if(m < 1) return;
            vector<bool> zero_rows(n, false);
            vector<bool> zero_cols(m, false);
            for(size_t i = 0; i < n; i++) {
                for(size_t j = 0; j < m; j++) {
                    if(matrix[i][j] == 0) {
                        zero_rows[i] = true;
                        zero_cols[j] = true;
                    }
                }
            }
            for(size_t i = 0; i < zero_rows.size(); i++)
                if(zero_rows[i]) set_row_zeroes(matrix, i);
            for(size_t j = 0; j < zero_cols.size(); j++)
                if(zero_cols[j]) set_col_zeroes(matrix, j);
        }
        inline void set_row_zeroes(vector<vector<int>> &mat, size_t i) {
            for(size_t k = 0; k < mat[i].size(); k++)
                    mat[i][k] = 0;
        }
        inline void set_col_zeroes(vector<vector<int>> &mat, size_t j) {
            for(size_t k = 0; k < mat.size(); k++)
                    mat[k][j] = 0;
        }
        // O(m*n) space
        void bf_set_zeroes(vector<vector<int>> &matrix) {
            size_t n = matrix.size();
            if(n < 1) return;
            size_t m = matrix[0].size();
            if(m < 1) return;
            vector<vector<bool>> mark(n, vector<bool>(m, true));
            for(size_t i = 0; i < n; i++)
                for(size_t j = 0;j < m; j++)
                    if(mark[i][j] && matrix[i][j] == 0)
                        set_row_col_zeroes(matrix, i, j, mark);
         }
        inline void set_row_col_zeroes(vector<vector<int>> &matrix, size_t i, size_t j, 
                vector<vector<bool>> &mark) {
            for(size_t k = 0; k < matrix[i].size(); k++) {
                if(matrix[i][k] != 0) {
                    matrix[i][k] = 0;
                    mark[i][k] = false;
                }
            }
            for(size_t k = 0; k < matrix.size(); k++) {
                if(matrix[k][j] != 0) {
                    matrix[k][j] = 0;
                    mark[k][j] = false;
                }
            }
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int a[][4] = 
        {{0,0,0,5},
         {4,3,1,4},
         {0,1,1,4},
         {1,2,1,3},
         {0,0,1,1}};
    vector<int> ivecs[] = {vector<int>(a[0],a[0]+4), vector<int>(a[1], a[1]+4), 
        vector<int>(a[2],a[2]+4), vector<int>(a[3], a[3]+4),  vector<int>(a[4],a[4]+4)}; 
    vector<vector<int>> mat(ivecs, ivecs+5);
    sol.setZeroes(mat);
    print_table(mat);
    return 0;
}
