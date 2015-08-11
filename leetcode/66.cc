#include "leetc.h"

class Solution {
    public:
        vector<int> plusOne(vector<int> &digits) {
            int i = digits.size()-1;
            while(i >= 0 && digits[i] == 9) {
                digits[i] = 0;
                --i;
            }
            if(i >= 0)
                ++digits[i];
            else {
                digits[0] = 1;
                digits.push_back(0);
            }
            return digits;
        }
    private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
