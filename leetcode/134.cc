#include "leetc.h"

using namespace std;

class Solution {
    public:
        int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
            vector<int> gas_left(gas);
            int max_index = gas.size();
            for(int i=0;i<max_index;i++)
                gas_left[i] = gas_left[i] - cost[i];
            int start_pos = 0;
            while(gas_left[start_pos] < 0) start_pos++;
            int left_gas = gas_left[start_pos];
            int i = start_pos < max_index-1 ? start_pos+1 : 0;
            while(i != start_pos) {
                left_gas += gas_left[i];
                if(left_gas < 0) {
                    start_pos = start_pos == 0 ? max_index-1 : start_pos-1;
                    while(start_pos != i) {
                        left_gas += gas_left[start_pos];
                        if(left_gas >= 0) break;
                        start_pos = start_pos == 0 ? max_index-1 : start_pos-1;
                    }
                    if(start_pos == i)
                        return -1;
                }
                i = i < max_index-1 ? i+1 : 0;
            }
            return left_gas >= 0 ? start_pos : -1;
        }
};

int main(void) {
    int a[] = {1, 2, 3, 3};
    int b[] = {2, 1, 5, 1};
    vector<int> gas(a, a+4);
    vector<int> cost(b, b+4);
    Solution s;
    printf("%d\n", s.canCompleteCircuit(gas, cost));

}
