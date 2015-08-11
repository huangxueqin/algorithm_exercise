#include "leetc.h"
#include <algorithm>
#include <set>

using std::multiset;

class Solution {
public:
    vector<std::pair<int, int>> getSkyline(vector<vector<int>> &buildings) {
        vector<std::pair<int, int>> result, heights;
        for(const vector<int> &item : buildings) {
            heights.push_back(std::make_pair(item[0], item[2]));
            heights.push_back(std::make_pair(item[1],-item[2]));
        }
        std::sort(heights.begin(), heights.end(), [] (const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) -> 
                bool {
                    if(lhs.first != rhs.first) return lhs.first < rhs.first;
                    else return lhs.second > rhs.second;
                });
        std::multiset<int, std::greater<int>> heap;
        heap.insert(0);
        int pre = 0;
        for(const std::pair<int, int> &item : heights) {
            if(item.second > 0) {
                heap.insert(item.second);
            }
            else {
                heap.erase(heap.find(-item.second));
            }
            int cur = *(heap.begin());
            if(cur != pre) {
                result.push_back(std::make_pair(item.first, cur));
                pre = cur;
            }
        }
        return result;
    }

    /* Memory Excess Limit
    vector<std::pair<int, int>> getSkyline(vector<vector<int>> &buildings) {
        vector<std::pair<int, int>> histo;
        for(int i = 0; i < buildings.size(); i++) {
            int li = buildings[i][0];
            int ri = buildings[i][1];
            int hi = buildings[i][2];
            for(int k = li; k < ri; k++) {
                histo.push_back(std::make_pair(k, hi));
            }
        }
        std::sort(histo.begin(), histo.end(), [] (const std::pair<int, int> &lhs,
                    const std::pair<int, int> &rhs) -> bool { return lhs.first < rhs.first; });
        vector<std::pair<int, int>> merge;
        for(std::pair<int, int> &item : histo) {
            if(merge.empty() || item.first > merge.back().first) {
                merge.push_back(item);
            }
            else if(merge.back().second < item.second) {
                merge.back().second = item.second;
            }
        }
        vector<std::pair<int, int>> result;
        for(int i = 0; i < merge.size(); i++) {
            if(i == 0) {
                result.push_back(merge[0]);
            }
            else {
                if(result.back().second != merge[i].second) {
                    result.push_back(merge[i]);
                }
            }
            if(i == merge.size()-1 || merge[i].first+1 < merge[i+1].first) {
                result.push_back(std::make_pair(merge[i].first+1, 0));
            }
        }
        return result;
    }
    */
};

Solution sol;

int main(void) {
    vector<vector<int>> buildings = {{2,9,10}, {3,7,15}, {5,12,12}, {15,20,10}, {19,24,8}};
    vector<std::pair<int, int>> skyline = sol.getSkyline(buildings);
    cout << "[" ;
    for(int i = 0; i < skyline.size(); i++) {
        cout << "[" << skyline[i].first << " " << skyline[i].second << "]" ;
        if(i < skyline.size()-1) cout << ", " ;
    }
    cout << "]" << endl;
    return 0;
}
