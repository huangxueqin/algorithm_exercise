#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

struct SegComp {
    bool operator() (const PII &ths, const PII &rhs) {
        return ths.first < rhs.first;
    }
};

int computeOverlap(PII &lhs, PII &rhs) {
    if(rhs.first < lhs.second) {
        if(rhs.second > lhs.second) {
            return lhs.second - rhs.first;
        }
        else {
            return rhs.second - rhs.first;
        }
    }
    return 0;
}

int main(void) {
    vector<PII> segments;
    int N;
    cin >> N;
    for(int i = 0; i < N; i++) {
        int s, e;
        cin >> s >> e;
        segments.push_back(std::make_pair(s, e));
    }
    std::sort(segments.begin(), segments.end(), SegComp());
    int maxOverlap = 0, candidatei, candidatej;
    for(int i = 1; i < segments.size(); i++) {
        for(int j = 0; j < i; j++) {
            if(computeOverlap(segments[i], segments[j]) > maxOverlap) {
                maxOverlap = computeOverlap(segments[i], segments[j]);
                candidatei = i;
                candidatej = j;
            }
        }
    }
    cout << segments[candidatej].first << " " << segments[candidatej].second << endl;
    cout << segments[candidatei].first << " " << segments[candidatei].second << endl;
    return 0;
}
