#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
        std::sort(nums1.begin(), nums1.end());
        std::sort(nums2.begin(), nums2.end());
        vector<int> result;
        int i = 0, j = 0;
        while(true) {
            if(i >= nums1.size() || j >= nums2.size()) break;
            if(nums1[i] == nums2[j]) {
                if(result.size() == 0 || result.back() != nums1[i]) {
                    result.push_back(nums1[i]);
                }
                i++; j++;
            }
            else if(nums1[i] > nums2[j]) j++;
            else i++;

        }
        return result;
    }
};

Solution sol;

int main(void) {

}
