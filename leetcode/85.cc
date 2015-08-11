#include "leetc.h"
#include <stack>

using std::stack;

class Solution {
public:
    int maximalRectangle(vector<vector<char>> &matrix) {
        int nr = matrix.size();
        if(nr == 0) return 0;
        int nc = matrix[0].size();

        vector<vector<int>> heights(nr, vector<int>(nc+2));
        for(int i = 0; i < nc+2; i++)
            heights[0][i] = i > 0 && i < nc+1 && matrix[0][i-1] == '1' ? 1 : 0;
        for(int i = 1; i < nr; i++)
            for(int j = 0; j < nc+2; j++)
                heights[i][j] = j > 0 && j < nc+1 && matrix[i][j-1] == '1' ? heights[i-1][j]+1 : 0;
        int mr = 0;
        for(int i = 0; i < nr; i++) {
            int a = largestRectangleArea(heights[i]);
            if(a > mr) mr = a;
        }
        return mr;
    }
private:
    /*
     * when we want to computer result for height = {h1, h2, h3, h4, h5, ... ,hn}
     * actually we must make sure the parameter is height = {0, h1, h2, h3, ... ,hn, 0}
     */
    int largestRectangleArea(const vector<int> &height) {
        stack<int> is;
        int mr = 0;
        int n = height.size();
        for(int i = 0; i < n; i++) {
            int h = height[i];
            if(is.empty() || h > height[is.top()])
                is.push(i);
            else
                while(!is.empty() && h <= height[is.top()]) {
                    int iph = is.top(); is.pop();
                    if(h == height[iph]) continue;
                    int ipph = is.top();
                    int a = height[iph] * (i - ipph - 1);
                    if(mr < a) mr = a;
                }
            is.push(i);
        }
        return mr;
    }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    /* vector<vector<char>> matrix = {
     *     {'0','0','1','0','0','0'},
     *     {'1','1','1','1','0','0'},
     *     {'0','1','0','1','0','0'},
     *     {'0','1','1','1','1','0'},
     *     {'0','1','1','1','1','1'},
     *     {'0','0','0','0','0','0'}
     * }; */
    vector<vector<char>> matrix = {{'0', '1'}};
    cout << sol.maximalRectangle(matrix) << endl;
    return 0;
}
