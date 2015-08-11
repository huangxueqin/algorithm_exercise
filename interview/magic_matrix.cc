#include <iostream>
#include <vector>

using namespace std;

void print_matrix(vector<vector<int>> &mat) {
    for(int i = 0; i < mat.size(); i++) {
        for(int j = 0; j < mat[i].size(); j++) {
            cout << mat[i][j];
            if(j < mat[i].size()-1) cout << " ";
        }
        cout << endl;
    }
}

int main(void) {
    int n;
    cin >> n;
    if(!(n & 1)) {
        cout << "n must be odd" << endl;
        return -1;
    }
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    int i = 0, j = n/2;
    for(int k = 1; k <= n*n; k++) {
        matrix[i][j] = k;
        int ni, nj;
        if(i == 0) {
            ni = j == n-1 ? i : n-1;
            nj = j == n-1 ? j : j+1;
        }
        else {
            ni = i - 1;
            nj = j == n-1 ? 0 : j+1;
        }
        i = matrix[ni][nj] ? i + 1 : ni;
        j = matrix[ni][nj] ? j : nj;
    }
    print_matrix(matrix);
    return 0;
}

