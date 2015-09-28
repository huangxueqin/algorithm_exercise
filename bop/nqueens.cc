#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline bool valid_pos(vector<int> &ivec, int r, int c) {
    for(int i = 0; i < ivec.size(); i++) {
        int j = ivec[i];
        if(c == j || i-r == j-c || i-r == c-j)
            return false;
    }
    return true;
}

void solve(const int n, const int row, vector<int> &ivec, vector<vector<int>> &result) {
    if(row == n) {
        result.push_back(ivec);
        return;
    }
    int nn = row == 0 ? (n+1) / 2 : n;
    for(int i = 0; i < nn; i++) {
        if(valid_pos(ivec, row, i)) {
            ivec.push_back(i);
            solve(n, row+1, ivec, result);
            ivec.pop_back();
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<unsigned> table(n, (1 << n) - 1);
    vector<vector<int>> result;
    vector<int> ivec;
    solve(n, 0, ivec, result);
    vector<vector<string>> sresult;
    vector<string> svec(n, string(n, '.'));
    for(vector<int> &r : result) {
        for(int i = 0; i < r.size(); i++) {
            svec[i][r[i]] = 'Q';
        }
        sresult.push_back(svec);
        for(int i = 0; i < r.size(); i++) {
            svec[i][r[i]] = '.';
        }
        if(!((n&1) && (r[0] == (n-1)/2))) {
            for(int i = 0; i < r.size(); i++) {
                svec[i][n-1-r[i]] = 'Q';
            }
            sresult.push_back(svec);
            for(int i = 0; i < r.size(); i++) {
                svec[i][n-1-r[i]] = '.';
            }
        }
    }
    return sresult;
}
