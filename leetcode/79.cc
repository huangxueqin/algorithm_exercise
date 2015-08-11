#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    struct Orient {
        static const int U = 0;
        static const int D = 1;
        static const int L = 2;
        static const int R = 3;
        static const int A = 4;
    };
    public:
        bool exist(vector<vector<char>> &board, string word) {
            size_t wn = word.size();
            if(wn == 0) return true;
            size_t bn = board.size();
            if(bn == 0) return false;
            size_t bnn = board[0].size();
            vector<vector<bool>> mark = vector<vector<bool>>(bn, vector<bool>(bnn, true));
            for(size_t i = 0; i < bn; i++) {
                for(size_t j = 0; j < bnn; j++) {
                    if(board[i][j] == word[0])
                        if(unrep_search(board, i, j, word, 0, mark)) 
                            return true;
                }
            }
            return false;
        }
    private:
        bool unrep_search(const vector<vector<char>> &board, const size_t i, const size_t j, 
                const string &word, const size_t sp, vector<vector<bool>> &mark) {
            if(sp+1 == word.size()) return true;
            mark[i][j] = false;
            int bn = board.size(), bnn = board[0].size();
            char ch = word[sp+1];
            if(i > 0 && mark[i-1][j] && board[i-1][j] == ch)
                if(unrep_search(board, i-1, j, word, sp+1, mark)) return true;
            if(i+1 < bn && mark[i+1][j] && board[i+1][j] == ch)
                if(unrep_search(board, i+1, j, word, sp+1, mark)) return true;
            if(j > 0 && mark[i][j-1] && board[i][j-1] == ch)
                if(unrep_search(board, i, j-1, word, sp+1, mark)) return true;
            if(j+1 < bnn && mark[i][j+1] && board[i][j+1] == ch)
                if(unrep_search(board, i, j+1, word, sp+1, mark)) return true;
            mark[i][j] = true;
            return false;
        }
        bool search(const vector<vector<char>> &board, const size_t i, const size_t j, 
                const string &word, const size_t sp, int orient) const {
            printf("(%zu, %zu)->", i, j);
            if(sp+1 == word.size()) return true;
            int bn = board.size();
            int bnn = board[0].size();
            char ch = word[sp+1];
            if(orient != Orient::D && i > 0 && board[i-1][j] == ch)
                if(search(board, i-1, j, word, sp+1, Orient::U))
                    return true;
            if(orient != Orient::U && i+1 < bn && board[i+1][j] == ch)
                if(search(board, i+1, j, word, sp+1, Orient::D))
                    return true;
            if(orient != Orient::L && j+1 < bnn && board[i][j+1] == ch)
                if(search(board, i, j+1, word, sp+1, Orient::R))
                    return true;
            if(orient != Orient::R && j > 0 && board[i][j-1] == ch)
                if(search(board, i, j-1, word, sp+1, Orient::L))
                    return true;
            printf("\n");
            return false;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    char b1[][4] =  {{'A','B','C','E'},
                        {'S','F','C','S'},
                        {'A','D','E','E'}};
    char b2[][3] = {{'C','A','A'},
                    {'A','A','A'},
                    {'B','C','D'}};
    vector<vector<char>> board1;
    board1.push_back(vector<char>(b1[0], b1[0]+4));
    board1.push_back(vector<char>(b1[1], b1[1]+4));
    board1.push_back(vector<char>(b1[2], b1[2]+4));
    vector<vector<char>> board2;
    board2.push_back(vector<char>(b2[0], b2[0]+3));
    board2.push_back(vector<char>(b2[1], b2[1]+3));
    board2.push_back(vector<char>(b2[2], b2[2]+3));

    string s1 = "ABCCED";
    printf("%s\n", sol.exist(board1, s1) ? "true" : "false");
    string s2 = "SEE";
    printf("%s\n", sol.exist(board1, s2) ? "true" : "false");
    string s3 = "ABCB";
    printf("%s\n", sol.exist(board1, s3) ? "true" : "false");
    string s4 = "AAB";
    printf("%s\n", sol.exist(board2, s4) ? "true" : "false");
    return 0;
}
