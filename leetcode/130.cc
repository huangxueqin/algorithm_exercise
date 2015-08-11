#include "leetc.h"
#include <vector>

using namespace std;

class Solution {
    public:
        void solve(vector<vector<char>> &board) {
            int n = board.size();
            vector<vector<bool>> visited(n, vector<bool>(n, false));
            for(int j=0;j<n;j++)
                if(board[0][j] == 'O' && !visited[0][j])
                    mark(board, visited, 0, j);
            for(int i=1;i<n;i++)
                if(board[i][n-1] == 'O' && !visited[i][n-1])
                    mark(board, visited, i, n-1);
            for(int j=n-2;j>=0;j--)
                if(board[n-1][j] == 'O' && !visited[n-1][j])
                    mark(board, visited, n-1, j);
            for(int i=n-2;i>0;i--)
                if(board[i][0] == 'O' && !visited[i][0])
                    mark(board, visited, i, 0);
            for(int i=0;i<n;i++)
                for(int j=0;j<n;j++)
                    if(board[i][j] == 'O' && !visited[i][j])
                        board[i][j] = 'X';
        }
    private:
        void mark(vector<vector<char>> &board, vector<vector<bool>> &visited, int i, int j) {
            if(visited[i][j])
                return;
            int n = board.size();
            visited[i][j] = true;
            if(i > 0 && board[i-1][j] == 'O')
                mark(board, visited, i-1, j);
            if(i < n-1 && board[i+1][j] == 'O')
                mark(board, visited, i+1, j);
            if(j > 0 && board[i][j-1] == 'O')
                mark(board, visited, i, j-1);
            if(j < n-1 && board[i][j+1] == 'O')
                mark(board, visited, i, j+1);
        }
};

int main(void) {
    vector<vector<char>> board;
    int n;
    cin >> n; 
    for(int i=0;i<n;i++) {
        vector<char> row;
        for(int j=0;j<n;j++) {
            char c;
            cin >> c;
            row.push_back(c);
        }
        board.push_back(row);
    }
    Solution s;
    s.solve(board);
    print_table(board);
    return 0;
}
