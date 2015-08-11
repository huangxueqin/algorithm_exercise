#include "leetc.h"
#include <queue>

using std::queue;

class Stack {
private:
    queue<int> q1;
    queue<int> q2;

public:
    // Push element x onto stack.
    void push(int x) {
        if(q1.empty()) {
            q1.push(x);
        }
        else {
            while(!q1.empty()) {
                int t = q1.front(); q1.pop();
                q2.push(t);
            }
            q1.push(x);
        }
        while(!q2.empty()) {
            int t = q2.front(); q2.pop();
            q1.push(t);
        }
    }

    // Removes the element on top of the stack.
    void pop() {
        q1.pop();
    }

    // Get the top element.
    int top() {
        return q1.front();
    }

    // Return whether the stack is empty.
    bool empty() {
        return q1.empty();
    }
};
