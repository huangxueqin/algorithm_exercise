#include "leetc.h"

class Solution {
    public:
        bool isValidSudoku(vector<vector<char>> &board) {
            vector<bool> bvec(9, false);
            if(!check_rows(board, bvec))
                return false;
            if(!check_cols(board, bvec))
                return false;
            if(!check_blks(board, bvec))
                return false;
            return true;
        }
    private:
        bool check_rows(const vector<vector<char>> &board, vector<bool> &bvec) {
            for(size_t i = 0; i < 9; i++) {
                reset(bvec);
                for(size_t j = 0; j < 9; j++) {
                    if(board[i][j] != '.') {
                        if(bvec[char2int(board[i][j])])
                            return false;
                        else 
                            bvec[char2int(board[i][j])] = true;
                    }
                }
            }
            return true;
        }
        bool check_cols(const vector<vector<char>> &board, vector<bool> &bvec) {
            for(size_t j = 0; j < 9; j++) {
                reset(bvec);
                for(size_t i = 0; i < 9; i++) {
                    if(board[i][j] != '.') {
                        if(bvec[char2int(board[i][j])])
                            return false;
                        else
                            bvec[char2int(board[i][j])] = true;
                    }
                }
            }
            return true;
        }
        bool check_blks(const vector<vector<char>> &board, vector<bool> &bvec) {
            for(size_t i = 0; i < 9; i++) {
                reset(bvec);
                if(!check_blk(board, bvec, i))
                    return false;
            }
            return true;
        }
        bool check_blk(const vector<vector<char>> &board, vector<bool> &bvec, size_t i) {
            const vector<int> indices = mapfun(i);
            return check_blk(board, bvec, indices[0], indices[1]);
        }
        bool check_blk(const vector<vector<char>> &board, vector<bool> &bvec, 
                const size_t n, const size_t m) {
            for(size_t i = n; i < n+3; i++) {
                for(size_t j = m; j < m+3; j++) {
                    if(board[i][j] != '.') {
                        if(bvec[char2int(board[i][j])])
                            return false;
                        else 
                            bvec[char2int(board[i][j])] = true;
                    }
                }
            }
            return true;
        }
        inline vector<int> mapfun(size_t num) {
            const static vector<vector<int>> table{{0,0},{0,3},{0,6},
                {3,0},{3,3},{3,6},{6,0},{6,3},{6,6}};
            return table[num];
        }
        inline int char2int(char c) { return c - '1'; }
        inline void reset(vector<bool> &bvec) {
            for(size_t i = 0; i < bvec.size(); i++)
                bvec[i] = false;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    vector<vector<char>> board{
        {'.','.','4','.','.','.','6','3','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'5','.','.','.','.','.','.','.','9'},
        {'.','.','.','5','6','.','.','.','.'},
        {'4','.','3','.','.','.','.','.','1'},
        {'.','.','.','7','.','.','.','.','.'},
        {'.','.','.','5','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.','.'}
    };
    printf("%s\n", sol.isValidSudoku(board) ? "true" : "false");
    return 0;
}
