#include "leetc.h"
#include <algorithm>

using namespace std;

class Solution {
    public:
        int threeSumClosest(vector<int> &num, int target) {
            std::sort(num.begin(), num.end());
            int result = num[0]+num[1]+num[2];
            for(int i=0;i<num.size()-2;i++) {
                if(result == target)
                    break;
                int temp = find_closest(num, i, target, result);
                if(result != temp)
                    result = temp;
                int cur = num[i];
                while(num[i+1] == cur) i++;
            }
            return result;
        }
    private:
        int find_closest(vector<int> &num, int i, int target, int last_closest) {
            int first_num = num[i];
            int start = i+1, end = num.size()-1;
            int result = last_closest;
            while(start < end) {
                int temp = first_num + num[start] + num[end];
                if(std::abs(temp-target) < std::abs(result-target)) result = temp;
                if(temp < target)
                    start++;
                else if(temp > target)
                    end--;
                else
                    break;
            }
            return result;
        }
};
