#include "leetc.h"

using std::vector;
using std::string;
using std::printf;

class Solution {
    enum Direction {Right, Down, Left, Up};
    public:
        vector<vector<int>> generateMatrix(int n) {
            vector<vector<int>> result(n, vector<int>(n, 0));
            int i = 0, j = 0;
            int v = 1;
            Direction d = Right;
            while(v <= n*n) {
                result[i][j] = v;
                ++v;
                if(!valid_direction(d, i, j, n, result))
                    d = nextDirection(d);
                update_index_by_direction(d, i, j);
            }
            return result;
        }
    private:
        inline bool valid_direction(Direction d, int i, int j, int n, 
                vector<vector<int>> &mat) const {
            switch(d) {
                case Right: return j < n-1 && mat[i][++j] == 0;
                case Down:  return i < n-1 && mat[++i][j] == 0;
                case Left:  return j > 0 && mat[i][--j] == 0;
                case Up:    return i > 0 && mat[--i][j] == 0;
            }
        }
        inline void update_index_by_direction(Direction d, int &i, int &j) {
            switch(d) {
                case Right: ++j; break;
                case Down:  ++i; break;
                case Left:  --j; break;
                case Up:    --i; break;
            }
        }
        inline Direction nextDirection(Direction d) {
            switch(d) {
                case Right: return Down;
                case Down:  return Left;
                case Left:  return Up;
                case Up:    return Right;
            }
        }
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    int n = 3;
    vector<vector<int>> spiral_matrix = sol.generateMatrix(n);
    print_table(spiral_matrix);
    return 0;
}
