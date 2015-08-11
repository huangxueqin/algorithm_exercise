#include "leetc.h"

using namespace std;

class Solution {
    public:
        vector<int> grayCode(int n) {
            vector<int> result;
            if(n < 1) {
                result.push_back(0);
                return result;
            }
            result.push_back(0);
            result.push_back(1);
            int pow = 2;
            for(int i=2;i<=n;i++) {
                for(size_t j=result.size();j>0;j--)
                    result.push_back(result[j-1] + pow);
                pow *= 2;
            }
            return result;
        }
};

int main(void) {
    int n = 2;
    Solution s;
    vector<int> graycode = s.grayCode(n);
    print_vector(graycode);
    return 0;
}
