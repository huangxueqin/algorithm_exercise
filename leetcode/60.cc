#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        string getPermutation(int n, int k) {
            vector<int> num_pmtts(n+1, 1);
            for(int i = 1; i <= n; i++)
                num_pmtts[i] = i * num_pmtts[i-1];
            if(num_pmtts[n] < k) return "";
            return get_permutation(n, k, num_pmtts);
        }
    private:
        string get_permutation(const int n, int k, const vector<int> &num_pmtts) {
            vector<bool> used(n+1, false);
            string pmtt;
            for(int i = 1; i <= n; i++) {
                int t = n, cnt = n-i+1;
                while(t >= 1 && (used[t] || (cnt-1) * num_pmtts[n-i] >= k)) {
                    if(!used[t])
                        --cnt;
                    --t;
                }
                printf("k = %d, t = %d\n", k, t);
                k -= (cnt-1) * num_pmtts[n-i];
                used[t] = true;
                pmtt.push_back(int2char(t));
            }
            return pmtt;
        }
        inline char int2char(const int i) { return '0'+i; }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int n = 3, k = 3;
    string perm = sol.getPermutation(n, k);
    printf("%s\n", perm.c_str());
    return 0;
}
