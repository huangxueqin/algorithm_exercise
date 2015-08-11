#include "leetc.h"

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        for(int i = 0; i < 32; i++) {
            if(((n >> i) & 0x1) > 0) 
                count++;
        }
        return count;
    }
private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
