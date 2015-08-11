#include "leetc.h"

using namespace std;

class Solution {
    public:
        vector<string> restoreIpAddresses(string s) {
            vector<string> result;
            vector<vector<int>> all_splits = get_all_possible_splits(s);
            for(auto it = all_splits.begin(); it != all_splits.end(); it++) {
                result.push_back(construct_ip_address(s, *it));
            }
            return result;
        }
    private:
        string construct_ip_address(const string &s, vector<int> &split) {
            string ipaddr;
            for(size_t i = 0; i < 4; i++) {
                size_t startp = split[i];
                size_t endp = i < 3 ? split[i+1] : s.size();
                ipaddr.append(s.substr(startp, endp-startp));
                if(i < 3) ipaddr.push_back('.');
            }
            return ipaddr;
        }
        vector<vector<int>> get_all_possible_splits(const string &s) {
            vector<vector<int>> splits;
            vector<int> ivec;
            get_possible_splits_from(s, 0, splits, ivec);
            return splits;
        }
        void get_possible_splits_from(const string &s, const int start, 
                vector<vector<int>> &splits, vector<int> &ivec) {
            if(ivec.size() == 4 && start == s.size()) {
                splits.push_back(ivec);
            }
            else if(ivec.size() < 4 && start < s.size()){
                ivec.push_back(start);
                size_t i = start + 1;
                while( i <= s.size()) {
                    if(!is_valid_ip_seg(s, start, i)) break;
                    get_possible_splits_from(s, i, splits, ivec);
                    i++;
                }
                ivec.pop_back();
            }
        }
        inline bool is_valid_ip_seg(const string &s, const int i, const int j) {
            int len = j-i;
            switch(len) {
                case 1:
                    return true;
                case 2:
                    return s[i] != '0';
                case 3:
                    return (s[i] > '0' && s[i] < '2') || 
                        (s[i] == '2' && s[i+1] < '5') ||
                        (s[i] == '2' && s[i+1] =='5' && s[i+2] <= '5');
                default:
                    return false;
            }
        }
};

Solution sol;

int main(void) {
    printf("----------Test----------\n");
    string ipstr = "172162541";
    printf("%s\n", ipstr.c_str());
    vector<string> ipaddrs = sol.restoreIpAddresses(ipstr);
    print_vector(ipaddrs);
    return 0;
}
