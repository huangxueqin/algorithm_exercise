#include "leetc.h"
#include <assert.h>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
    private:
        const int dna_chain_mask = (1 << 20) - 1;

        inline int DNA_BIT(char db) { return ((db >> 1) & 0b11); }
        inline void append_by_dnabit(int &bits, const char dnabit) { 
            bits = (((bits<<2) | DNA_BIT(dnabit))) & dna_chain_mask;
        }
    public:
        vector<string> findRepeatedDnaSequences(string s) {
            return findRepeatedDnaSequences_v2(s);
        }

        vector<string> findRepeatedDnaSequences_v2(const string& s) {
            vector<string> result;
            if(s.size() >= 10) {
                unordered_set<int> iset;
                unordered_set<string> sset;
                int bits = init_chain_bits(s);
                iset.insert(bits);
                for(size_t i = 10; i < s.size(); i++) {
                    append_by_dnabit(bits, s.at(i));
                    if(iset.find(bits) != iset.end()) {
                        sset.insert(s.substr(i-9, 10));
                    }
                    else 
                        iset.insert(bits);
                }
                for(auto it = sset.begin(); it != sset.end(); it++) {
                    result.push_back(*it);
                }
            }
            return result;
        }
        vector<string> findRepeatedDnaSequences_v1(const string& s) {
            vector<string> result;
            if(s.size() >= 10) {
                unordered_map<int, int> iimap;
                int bits = init_chain_bits(s);
                iimap.insert(std::make_pair(bits, 1));
                for(size_t i = 10; i < s.size(); i++) {
                    append_by_dnabit(bits, s.at(i));
                    auto it = iimap.find(bits);
                    if(it == iimap.end())
                        iimap.insert(std::make_pair(bits, 1));
                    else {
                        if(it->second == 1) {
                            result.push_back(s.substr(i-9, 10));
                            it->second++;
                        }
                    }
                }
            }
            return result;
        }

    private:
        int init_chain_bits(const string &s) {
            int bits = 0x00;
            for(size_t i = 0; i < 10; i++) {
                append_by_dnabit(bits, s.at(i));
            }
            return bits;
        }
};

Solution sol;

int main(void) {
    string s1 = "TGCTCCTGTCACAACTTCTTTACCAGCCTGTTTTTCTAGAGTCGGCTCAAAACCTGCCTTTATGCGCAGCTGTCCACGAGAATTTCATGTTATCGAGGACCGCGATATACCCAATCGCGCGCCCCAGAAAAAAGAGTCTTACCAGATGTATACGGTGACGACCCAGTGGGTAAGACCGCTCTGCTCAGCGACCCGTCCATACCCACAGTCAGCCATGTGTGACATATCAGCGTGCATTCTTGATCTGTATGGGTGCGCTGCCCCCGCACTTGATGGGGTATGTGATGACTCCGCTCGGTAAGCAAGACCCTGGGGGTTCGGACGTAGGGTATACCCGAACTTCACGTATGCGGACACCAACGCACGTGCCAATTTATCTAACGTATGTCTCCATGCCGCCCAGAAGGTTAAAGTGGACCGCCGTTCGTATACTGTTTCTGCAATTGTGTGCGGCAGCACCAGGTAGAGAGCATTCTATTTCGCTAGCTAGTAAATCTACTTCACCGAGTCTGGAAGCTCCAATCGCTGTTTACAAACTTTTTGCCCCTGCGTGGGTCAGGCCATGTCCCGTTCCCGAGGATTCTAGCACTGACCTAGCCCTATATCACGAGCCGGGTTTTCTTAAAATAGAGATCGGGACGTTAAGGTCTTATGAACGGCTTCAGCTATCTTCCGCTTACCAACTGAGCCGAACTATCTCCGGGTGTTACATGGATCCTAAAATGCTCTCCAATTTTGCCCCTGCATGGTATTTCTCTTGAGACTACTGGATCTACCTGGGTTGTGCATGTTTCGTGTCTCTTCCGACGTTCGACAATTGGGGGCGACGCTTTAAGTTCTACTACGGTGAGATGCACATCCCACGGACGCCCTTTTCCTTTGGCTCTTCCTACGTTCGCGAGCGGTCCTGTAGGACAGTTGCTTTATGCCAACTTTTACGAGGGTGGAATACAGTATCGCCATGACACTCTGAAAAAGGATGGAAGACCTGAGATTCACC";
    string s2 = "TTTTTTTTTTT";
    string s3 = "AAAAAAAAAAAA";
    vector<string> result = sol.findRepeatedDnaSequences(s3);
    print_vector(result);
    return 0;
}
