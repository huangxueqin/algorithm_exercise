#include <algorithm>
#include "leetc.h"

class Solution {
public:
    vector<int> twoSum(const vector<int> &numbers, const int target) { 
        vector<int> indices;
        for(int i = 0; i < numbers.size(); i++) 
            indices.push_back(i);
        std::sort(indices.begin(), indices.end(), Compare(numbers));
        int i = 0, j = indices.size()-1;
        while(i < j) {
            int t = numbers[indices[i]] + numbers[indices[j]];
            if(t == target)
                break;
            else if(t < target)
                i++;
            else 
                j--;
        }
        return vector<int>{std::min(indices[i], indices[j]) + 1, std::max(indices[j], indices[i])+1};
    }
private:
    struct Compare{
        const vector<int> &numbers;
        Compare(const vector<int> &num) : numbers(num) {};
        bool operator() (int i, int j) { return numbers[i] <= numbers[j];}
    };
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
