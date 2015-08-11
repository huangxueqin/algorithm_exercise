#include "leetc.h"
#include <stack>

using std::stack;

class Queue {
    stack<int> s1;
    stack<int> s2;
public:
    // Push element x to the back of queue.
    void push(int x) {
        if(s1.empty()) {
            flop();
        }
        s1.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        if(s2.empty()) {
            flop();
        }
        if(!s2.empty()) {
            s2.pop();
        }
    }

    // Get the front element.
    int peek(void) {
        if(s2.empty()) {
            flop();
        }
        if(!s2.empty()) {
            return s2.top();
        }
        return 0;
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return s1.empty() && s2.empty();
    }

private:
    void flop() {
        if(s1.empty() && !s2.empty()) {
            while(!s2.empty()) {
                int t = s2.top();
                s1.push(t);
                s2.pop();
            }
        }
        else if(!s1.empty() && s2.empty()) {
            while(!s1.empty()) {
                int t = s1.top();
                s2.push(t);
                s1.pop();
            }
        }
    }
};
