#include "leetc.h"

using namespace std;

class Solution {
    public:
        int maxProduct(const int a[], const int n) {
            return maxProduct_dp(a, n);
        }
    private:
        inline int Max(const int &a, const int &b) {
            return a > b ? a : b;
        }

        inline int Min(const int &a, const int &b) {
            return a < b ? a : b;
        }

        int maxProduct_dp(const int a[], const int n) {
            int *pmin = new int[n];
            int *pmax = new int[n];
            int max_product = a[0];
            pmin[0] = pmax[0] = a[0];
            for(int i = 1; i < n; i++) {
                pmax[i] = Max(a[i], Max(a[i] * pmin[i-1], a[i] * pmax[i-1]));
                if(pmax[i] > max_product) max_product = pmax[i];
                pmin[i] = Min(a[i], Min(a[i] * pmin[i-1], a[i] * pmax[i-1]));
            }
            return max_product;
        }

        int maxProduct_nondp(const int a[], const int n) {
            bool contains_zero = false;
            vector<vector<int>> sub_groups;
            vector<int> group;
            for(int i=0;i<n;i++) {
                if(a[i] != 0)
                    group.push_back(a[i]);
                else {
                    contains_zero = true;
                    if(!group.empty()) {
                        sub_groups.push_back(group);
                        group.clear();
                    }
                }
            }
            if(!group.empty())
                sub_groups.push_back(group);
            int Max = maxProduct_nondp(sub_groups, contains_zero ? 0 : a[0]);
            return Max;
        }
        int maxProduct_nondp(const vector<vector<int>> &num_groups, const int suggestive_max) {
            int Max = suggestive_max;
            for(auto it=num_groups.begin(); it!=num_groups.end(); it++) {
                int temp = maxProduct_nondp(*it);
                Max = Max > temp ? Max : temp;
            }
            return Max;
        }
        int maxProduct_nondp(const vector<int> &nums) {
            if(nums.size() == 1)
                return nums[0];
            int p_prefix = 1, p_posfix = 1, p_all;
            int Max;
            auto preit = nums.begin();
            while(preit != nums.end() && *preit > 0) p_prefix *= *preit++;
            p_all = p_prefix;
            for(auto it = preit; it != nums.end(); it++) p_all *= *it;
            if(p_all > 0) return p_all;

            if(preit == nums.begin())
                Max = p_all / *preit;
            else {
                int temp = p_all / (*preit * p_prefix);
                Max = temp > p_prefix ? temp : p_prefix;
            }

            auto postit = nums.rbegin();
            while(postit != nums.rend() && *postit > 0) p_posfix *= *postit++;
            if(postit == nums.rbegin())
                Max = Max > p_all / *postit ? Max : p_all / *postit;
            else {
                int temp = p_all / (*postit * p_posfix);
                temp = temp > p_posfix ? temp : p_posfix;
                Max = Max > temp ? Max : temp;
            }
            return Max;
        }
};

int main(void) {
    int array[] = {-2, 0, -1};
    Solution s;
    printf("%d\n", s.maxProduct(array, sizeof(array) / sizeof(int)));
    return 0;
}
