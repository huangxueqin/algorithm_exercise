#include "leetc.h"

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<int>> solutions;
        vector<int> solution;
        solveNQueens(n, solutions, solution, 0);
        return constructSolutions(n, solutions);
    }
private:
    void solveNQueens(const int n, vector<vector<int>> &solutions, vector<int> &solution, int i) {
        if(i >= n) {
            solutions.push_back(solution);
            return;
        }
        int end = (i > 0 ? n : (n/2 + (n&0x1)));
        for(int k = 0; k < end; k++) {
            if(valid(solution, i, k)) {
                solution.push_back(k);
                solveNQueens(n, solutions, solution, i+1);
                solution.pop_back();
            }
        }
    }

    bool valid(const vector<int> &part_of_sol, int i, int k) {
        for(int row = 0; row < i; row++) {
            if(k == part_of_sol[row]) return false;
            if(std::abs(k - part_of_sol[row]) == i - row) return false;
        }
        return true;
    }

    vector<vector<string>> constructSolutions(const int n, const vector<vector<int>> solutions) {
        vector<vector<string>> result;
        for(int i = 0; i < solutions.size(); i++) {
            vector<string> svec;
            for(int j = 0; j < n; j++) {
                svec.push_back(string(n, '.'));
                svec[j][solutions[i][j]] = 'Q';
            }
            result.push_back(svec);
            if(n-1-solutions[i][0] != solutions[i][0]) {
                vector<string> svec;
                for(int j = 0; j < n; j++) {
                    svec.push_back(string(n, '.'));
                    svec[j][n-1-solutions[i][j]] = 'Q';
                }
                result.push_back(svec);
            }
        }
        return result;
    }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int n;
    cin >> n;
    vector<vector<string>> result = sol.solveNQueens(n);
    cout << result.size() << endl;
    for(int i = 0; i < result.size(); i++) {
        vector<string> svec = result[i];
        for(int j = 0; j < svec.size(); j++) {
            cout << svec[j] << endl;
        }
        cout << "--------------------" << endl;
    } 
    return 0;
}
