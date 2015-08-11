#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N;
    cin >> N;
    vector<int> a(N);
    vector<int> b(1, N);
    for(int i = 0; i < N; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < N-1; i++) {
        b[0] *= b[i];
        b[i+1] = b[0];
    }
    b[0] = 1;
    for(int i = N-1; i > 1; i++) {
        b[0] *= a[i];
        b[i-1] *= b[0];
    }
    return 0;
}
