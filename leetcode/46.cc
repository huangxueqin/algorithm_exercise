#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        vector<vector<int>> permute(vector<int> &num) {
            vector<vector<int>> result;
            vector<int> ivec;
            vector<bool> added(num.size(), false);
            permute(result, ivec, num, added);
            return result;
        }
    private:
        void permute(vector<vector<int>> &result, vector<int> &ivec, 
                const vector<int> &num, vector<bool> &added) {
            if(ivec.size() == num.size()) {
                result.push_back(ivec);
                return;
            }
            for(size_t i = 0; i < num.size(); i++) {
                if(!added[i]) {
                    added[i] = true;
                    ivec.push_back(num[i]);
                    permute(result, ivec, num, added);
                    added[i] = false;
                    ivec.pop_back();
                }
            }
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    vector<int> num{1,2,3,4};
    vector<vector<int>> pmtts = sol.permute(num);
    print_table(pmtts);
    return 0;
}
