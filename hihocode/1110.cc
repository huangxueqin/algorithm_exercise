#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::printf;
using std::cout;
using std::cin;

class Terminal {
    public:
        static const int REGEX = 0x100;
        static const int REGEX_ = REGEX + 1;
        static const int EXPR = REGEX_ + 1;
        static const int EXPR_ = EXPR + 1;
        static const int TERM = EXPR + 1;
        static const int FACTOR = TERM + 1;
        static const int ID = FACTOR + 1;
        static inline bool is_terminal(int t) { return t >= REGEX && t <= ID; }
};
 
struct NonTerminal {
    static const int zero = '0';
    static const int one = '1';
    static const int left_parenthese = '(';
    static const int right_parenthese = ')';
    static const int alter = '|';
    static const int star = '*';
    static const int epsilon = 0;
};

bool regex(const string &input, size_t &pos);
bool regex_(const string &input, size_t &pos);
bool expr(const string &input, size_t &pos);
bool expr_(const string &input, size_t &pos);
bool term(const string &input, size_t &pos);
bool star(const string &, size_t &);
bool factor(const string &input, size_t &pos);
bool id(const string &input, size_t &pos);
bool parse_regex(const string &input, size_t &pos);

int main(void) {
    string s;
    while(cin >> s) {
        size_t pos = 0;
        bool result = parse_regex(s, pos) && pos == s.size();
        printf("%s:\t%s\n", s.c_str(), result ? "true" : "false");
    }  
    return 0;
}

bool parse_regex(const string &input, size_t &pos) {
    return regex(input, pos);
}

bool regex(const string &input, size_t &pos) {
    return expr(input, pos) && regex_(input, pos);
}

bool regex_(const string &input, size_t &pos) {
    size_t saved = pos;
    if(!regex(input, pos))
        pos = saved;
    return true;
}

bool nullable_regex(const string &input, size_t &pos) {
    size_t saved = pos;
    bool r = expr(input, pos) && regex(input, pos);
    if(!r)
        pos = saved;
    return true;
}

bool expr(const string &input, size_t &pos) {
    return term(input, pos) && expr_(input, pos);
}

bool expr_(const string &input, size_t &pos) {
    if(pos >= input.size()) 
        return true;
    size_t saved = pos;
    if(!(input[pos++] == NonTerminal::alter && term(input, pos) && expr_(input, pos)))
            pos = saved;
    return true;
}

bool term(const string &input, size_t &pos) {
    return factor(input, pos) && star(input, pos);
}

bool star(const string &input, size_t &pos) {
    if(pos >= input.size()) 
        return true;
    if(input[pos] == NonTerminal::star)
        pos++;
    return true;
}

bool factor(const string &input, size_t &pos) {
    size_t saved = pos;
    if(id(input, pos))
        return true;
    pos = saved;
    if(pos >= input.size())
        return false;
    if(input[pos++] == NonTerminal::left_parenthese) {
        bool r = regex(input, pos);
        if(r) {
            if(pos >= input.size())
                return false;
            return input[pos++] == NonTerminal::right_parenthese;
        }
        else 
            return false;
    }
    else 
        return false;
}

bool id(const string &input, size_t &pos) {
    if(pos >= input.size()) 
        return false;
    bool r = input[pos] == NonTerminal::zero || input[pos] == NonTerminal::one;
    if(r)
        pos++;
    return r;
}
