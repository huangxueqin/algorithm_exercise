#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

#define PARAM 256
#define NUM 257
#define ID 258
#define OPT 259
#define ENDOFFILE 260
#define SUBCKT 261
#define ENDS 263
#define XFUN 263


unordered_map<string, int> params;

class Token {
    public:
        int tag;
        Token(int t) : tag(t) {}
        virtual string to_string() {
            return string(1, this->tag);
        }
};


class Opt : public Token {
    public:
        char op;
        Opt(char o) : Token(OPT), op(o) {}
};

class Num : public Token{
    public:
        int value;
        Num(int v) : Token(NUM), value(v) {}
        string to_string() {
            return itoa(this->value);
        }

    private:
        string itoa(int num) {
            string s = "";
            if(num > 0) {
                int digit = num % 10;
                num /= 10;
                s += itoa(num);
                s += ('0'+digit);
            }
            return s;
        }
};

class Id : public Token{
    public:
        string lexeme;
        Id(int t, string s) : Token(t), lexeme(s) {} 
        string to_string() {
            return lexeme;
        }
};

int get_param_num(Token *param) {
    string key = param->to_string();
    return params.find(key)->second;
}

int parse_expression(int index, vector<Token *>::iterator current) {
    if((*current)->tag == '[') current++;
    stack<Token *> infix;
    queue<Token *> postfix;
    while((*current)->tag != ':' && (*current)->tag != ']') {
        if((*current)->tag == NUM) {
            Num *num = (Num *)(*current);
            postfix.push(new Num(num->value));
        }
        else if((*current)->tag == PARAM) {
            postfix.push(new Num(get_param_num(*current)));
        }
        else if((*current)->tag == '+' || (*current)->tag == '-') {
            while(!infix.empty()) {
                postfix.push(new Token(infix.top()->tag));
                infix.pop();
            }
            infix.push(new Token((*current)->tag));
        }
        else if((*current)->tag == '*' || (*current)->tag == '/') {
            while(!infix.empty()) {
                Token *t = infix.top();
                if(t->tag == '+' || t->tag == '-')
                    break;
                postfix.push(new Token(t->tag));
                infix.pop();
            }
            infix.push(new Token((*current)->tag));
        }
        else if((*current)->tag == ID) {
            Id *id = (Id *)(*current);
            if(id->lexeme == "i") {
                postfix.push(new Num(index));
            }
        }
        current++;
    }
    while(!infix.empty()) {
        postfix.push(infix.top());
        infix.pop();
    }
    stack<int> s_int; 
    while(!postfix.empty()) {
        Token *t = postfix.front();
        if(t->tag == NUM) {
            Num *num = (Num *)t;
            s_int.push(num->value);
        }
        else {
            if(s_int.size() < 2)
                return -1;
            int a = s_int.top(); s_int.pop();
            int b = s_int.top(); s_int.pop();
            if(t->tag == '+')
                s_int.push(a+b);
            else if(t->tag == '-')
                s_int.push(a-b);
            else if(t->tag == '*')
                s_int.push(a*b);
            else if(t->tag == '/')
                s_int.push(a/b);
            else
                return -1;
        }
        postfix.pop();
    }
    if(s_int.size() != 1)
        return -1;
    else 
        return s_int.top();
}

int ez_log2(int num) {
    if(num == 0)
        return 0;
    int t = 2, result = 1;
    while(t < num) {
        t *= 2;
        result++;
    }
    return result;
}

int ez_pow2(int t) {
    int i;
    int result = 1;
    for(i=0;i<t;i++) {
        result *= 2;
    }
    return result;
}


int main(void) {
    int Bits = 8;
    int CMUX = 2;
    int WORDS = 16;

    int ADR = ez_log2(WORDS);
    ADR = ez_pow2(ADR) < WORDS ? ADR + 1 : ADR;
    int ADR_CMUX = ez_log2(CMUX);
    int Rows = WORDS / CMUX;
    int cols = Bits * CMUX;
    int cols_half = cols / 2;
    int cols_num = cols_half / 4;

    cout << ADR << endl;
    cout << ADR_CMUX << endl;
    cout << Rows << endl;
    cout << cols << endl;
    cout << cols_half << endl;
    cout << cols_num << endl;

    params.insert(std::make_pair("Bits", Bits));
    params.insert(std::make_pair("CMUX", CMUX));
    params.insert(std::make_pair("WORDS", WORDS));
    params.insert(std::make_pair("ADR", ADR));
    params.insert(std::make_pair("ADR_CMUX", ADR_CMUX));
    params.insert(std::make_pair("Rows", Rows));
    params.insert(std::make_pair("cols", cols));
    params.insert(std::make_pair("cols_half", cols_half));
    params.insert(std::make_pair("cols_num", cols_num));

    vector<Token *> tokens;
    tokens.push_back(new Token('['));
    tokens.push_back(new Num(Rows));
    tokens.push_back(new Token('/'));
    tokens.push_back(new Id(PARAM, "16"));
    tokens.push_back(new Token('-'));
    tokens.push_back(new Num(1));
    tokens.push_back(new Token(':'));
    tokens.push_back(new Token(']'));

    cout << parse_expression(0, tokens.begin()) << endl;
    return 0;
}

