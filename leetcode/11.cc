#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        int maxArea(vector<int> &heights) {
            return max_area(heights, 0, heights.size()-1);   
            /* return bf_max_area(heights); */
            /* return dp_max_area(heights); */
        }
    private:
        int max_area(const vector<int> &heights, size_t i, size_t j) {
            if(j <= i) return 0;
            int minh = std::min(heights[i], heights[j]);
            int maxa = minh * (j-i);
            while(j > i) {
                while(j > i && heights[j] <= minh) j--;
                while(j > i && heights[i] <= minh) i++;
                if(j > i) {
                    int h = std::min(heights[i], heights[j]);
                    int area = h * (j-i);
                    if(area > maxa) {
                        maxa = area;
                    }
                    minh = h;
                }
            }
            return maxa;
        }
        // Memory Limit Excess
        int dp_max_area(const vector<int> &heights) {
            size_t n = heights.size();
            if(n < 2) return 0;
            vector<vector<int>> dp(n, vector<int>(n, -1));
            return dp_max_area(heights, 0, n-1, dp);
        }
        int dp_max_area(const vector<int> &heights, 
                size_t i, size_t j, vector<vector<int>> &dp) {
            if(i == j) {
                dp[i][j] = 0;
            }
            else {
                if(dp[i][j] != -1)
                    return dp[i][j];
                int area1 = std::min(heights[i], heights[j]) * (j-i);
                int area2 = std::max(dp_max_area(heights, i, j-1, dp), 
                        dp_max_area(heights, i+1, j, dp));
                dp[i][j] = std::max(area1, area2);
            }
            return dp[i][j];
        }
        // time limit excess
        int bf_max_area(const vector<int> &heights) {
            int maxa = 0;
            size_t n = heights.size();
            if(n < 2) return maxa;
            for(size_t i = 0; i < n; i++) {
                for(size_t j = i+1; j < n; j++) {
                    int h = std::min(heights[i], heights[j]);
                    int w = j-i;
                    maxa = std::max(maxa, h*w);
                }
            }
            return maxa;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int arr[] = {1,2,4,3};
    vector<int> heights(arr, arr+4);
    printf("max area = %d\n", sol.maxArea(heights));
    return 0;
}
