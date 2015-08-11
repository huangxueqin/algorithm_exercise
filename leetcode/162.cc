#include "leetc.h"

using namespace std;

class Solution {
    public:
        int findPeakElement(const vector<int> &num) {
            return findPeakElement(num, 0, num.size()-1);
        }
        int findPeakElement(const vector<int> &num, size_t startp, size_t endp) {
            if(startp == endp) return startp;
            else if(startp + 1 == endp) return num[startp] > num[endp] ? startp : endp;
            else {
                int midp = (startp + endp) >> 1;
                if(num[midp] > num[midp-1] && num[midp] > num[midp+1]) return midp;
                else if(num[midp] > num[midp-1]) {
                    return num[endp] > num[endp-1] ? endp : findPeakElement(num, midp, endp);
                }
                else
                    return num[startp] > num[startp+1] ? startp : findPeakElement(num, startp, midp);
            }
        }
};
