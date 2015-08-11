#include "leetc.h"
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
    private:
        string pre_process(long long &numerator, long long &denominator) {
            string result = "";
            bool positive = true;
            if(numerator < 0) {
                positive = !positive;
                numerator = -numerator;
            }
            if(denominator < 0) {
                positive = !positive;
                denominator = -denominator;
            }
            if(!positive)
                result += '-';
            return result;
        }

        bool find_loop(string &result, const int pointp, const int curp,
                const long long& num, unordered_map<int, int> &mMap) {
            auto it = mMap.find(num);
            if(it == mMap.end()) {
                mMap.insert(std::make_pair(num, curp));
                return false;
            }
            else {
                result = result.substr(0, pointp+it->second) + '(' + 
                        result.substr(pointp+it->second, curp-it->second) + ')';
                return true;
            }
        }
    public:
        string fractionToDecimal(int inumerator, int idenominator) {
            long long numerator = inumerator;
            long long denominator = idenominator;
            if(numerator == 0)
                return "0";
            string result = pre_process(numerator, denominator);
            result += std::to_string(numerator / denominator);
            numerator %= denominator;
            if(numerator == 0)
                return result;
            unordered_map<int, int> mMap;
            result += '.';
            int index_after_point = result.size();
            int i = 0;
            while(numerator != 0) {
                numerator *= 10;
                while(numerator < denominator) {
                    if(find_loop(result, index_after_point, i, numerator, mMap))
                        return result;
                    numerator *= 10;
                    result += '0';
                    i++;
                }
                if(find_loop(result, index_after_point, i, numerator, mMap))
                    return result;
                result += ('0' + numerator / denominator);
                numerator %= denominator;
                i++;
            }
            return result;
        }
};

int main(int argc, char *argv[]) {
    int numerator = std::atoi(argv[1]);
    int denominator = std::atoi(argv[2]);
    Solution s;
    printf("%s\n", s.fractionToDecimal(numerator, denominator).c_str());
    return 0;
}
