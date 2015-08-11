#include "leetc.h"

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
        vector<Interval> result;
        int ns = newInterval.start;
        int ne = newInterval.end;
        int i = 0;
        while(i < intervals.size() && intervals[i].end < ns) {
            result.push_back(intervals[i]);
            i++;
        }
        if(i < intervals.size() && ns > intervals[i].start) {
            ns = intervals[i].start;
        }
        while(i < intervals.size() && intervals[i].start <= ne) {
            i++;
        }
        if (i > 0 && ne < intervals[i-1].end) {
            ne = intervals[i-1].end;
        }
        result.push_back(Interval(ns, ne));
        while(i < intervals.size()) {
            result.push_back(intervals[i]);
            i++;
        }
        return result;
    }
private:
};

Solution sol;

int main(int argc, char *argv[]) {
    printf("----------Test----------\n");
    return 0;
}
