#include "leetc.h"
#include <stack>

using std::vector;
using std::string;
using std::printf;

class Solution {
    public:
        string simplifyPath(string path) {
            string compressed_path = "/";
            if(path.size() < 1) return compressed_path;
            vector<string> svec;
            int pos = 0;
            while(pos < path.size()) {
                string next_dir = get_next_dir(path, pos);
                if(next_dir.size() == 0) break;
                else if(is_prev_dir(next_dir)) {
                    if(!svec.empty())
                        svec.pop_back();
                }
                else if(is_cur_dir(next_dir)) continue;
                else svec.push_back(next_dir);
            }
            for(auto it = svec.begin(); it != svec.end(); it++) {
                compressed_path.append(*it);
                if(it+1 != svec.end())
                    compressed_path.push_back('/');
            }
            return compressed_path;
        }
    private:
        inline bool is_prev_dir(string &path) const {
            return path.size() == 2 && path[0] == '.' && path[1] == '.';
        }
        inline bool is_cur_dir(string &path) const {
            return path.size() == 1 && path[0] == '.';
        }
        string get_next_dir(const string &path, int &s) {
            string dir;
            while(s < path.size() && path[s] == '/') s++;
            while(s < path.size() && path[s] != '/') {
                dir.push_back(path[s]);
                s++;
            }
            return dir;
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
