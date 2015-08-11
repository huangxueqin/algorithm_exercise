#include "leetc.h"

class Solution {
public:
    void solveSudoku(vector<vector<char>> &board) {
        SolveSudokuOneStep(board);
    }
private:

    bool SolveSudokuOneStep(vector<vector<char>> &board) {
        int i = -1, j = -1;
        GetEmptyCell(board, i, j);
        if(i == -1) {
            return true;
        }
        else {
            vector<int> possible;
            possible.reserve(9);
            GetPossibleFillIns(i, j, board, possible);
            if(possible.size() == 0) {
                return false;
            }
            else {
                for(int k = 0; k < possible.size(); k++) {
                    board[i][j] = i2c(possible[k]);
                    if(SolveSudokuOneStep(board)) {
                        return true;
                    }
                }
                board[i][j] = '.';
                return false;
            }
        }
    }

    void GetPossibleFillIns(const int i, const int j, const vector<vector<char>> &board, vector<int> &ivec) {
        std::memset(visit, 0, sizeof(visit));
        for(int k = 0; k < 9; k++) {
            char c1 = board[i][k];
            char c2 = board[k][j];
            if(c1 != '.') {
                visit[c2i(c1)-1] = true;
            }
            if(c2 != '.') {
                visit[c2i(c2)-1] = true;
            }
        }
        int offsetY = (j / 3) * 3;
        int offsetX = (i / 3) * 3;
        for(int k1 = 0; k1 < 3; k1++) {
            for(int k2 = 0; k2 < 3; k2++) {
                char c = board[offsetX+k1][offsetY+k2];
                if(c != '.') {
                    visit[c2i(c)-1] = true;
                }
            }
        }
        for(int k = 1; k <= 9; k++) {
            if(!visit[k-1]) {
                ivec.push_back(k);
            }
        }
    }

    void GetEmptyCell(const vector<vector<char>> &board, int &i, int &j) {
        for(int k1 = 0; k1 < 9; k1++) {
            for(int k2 = 0; k2 < 9; k2++) {
                if(board[k1][k2] == '.') {
                    i = k1;
                    j = k2;
                    return;
                }
            }
        }
    }

    inline int c2i(char c) { return c - '0'; }
    inline char i2c(int i) { return '0' + i; }
private:
    bool visit[9];
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
