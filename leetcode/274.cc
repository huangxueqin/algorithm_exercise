#include "leetc.h"
#include <algorithm>

class Solution {
public:
    int hIndex(vector<int> &citations) {
        std::sort(citations.begin(), citations.end(), std::greater<int>());
        int h = 0;
        while(h < citations.size() && citations[h] > h) h++;
        return h;
    }
};


