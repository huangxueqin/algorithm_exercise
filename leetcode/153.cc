#include "leetc.h"

using namespace std;

class Solution {
    public:
        int findMin(vector<int> &num) {
            if(num.size() == 1 || num[0] < num[num.size()-1])
                return num[0];
            return findMin(num, 0, num.size()-1);
        }
    private:
        int findMin(vector<int> &num, int startp, int endp) {
            if(endp - startp <= 1)
                return num[endp] < num[startp] ? num[endp] : num[startp];
            int mid = (startp + endp) >> 1;
            if(num[mid] > num[startp])
                return findMin(num, mid, endp);
            else
                return findMin(num, startp, mid);
        }
};
