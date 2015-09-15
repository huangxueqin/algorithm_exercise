#include "leetc.h"

class Solution {
public:
    int hIndex(vector<int> &citations) {
        int n = citations.size();
        if(n == 0) return 0;
        int i = 0;
        int j = n;
        while(i < j-1) {
            if(citations[n-j] >= j) break;
            else {
                int mid = (i + j) >> 1;
                if(citations[n-mid] >= mid) i = mid;
                else j = mid;
            }
        }
        return j;
    }
};
