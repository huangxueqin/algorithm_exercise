#include "hihocode.h"

void compute_prefix_function(char *patt, int pi[], int m) {
    pi[0] = 0;
    int k = 0, i;
    for(i=1;i<m;i++) {
        while( k != 0 && patt[k] != patt[i])
            k = pi[k-1];
        if(patt[k] == patt[i])
            ++k;
        pi[i] = k;
    }
}

int kmp_matcher(char *source, int n, char *patt, int m) {
    int *pi = (int *)malloc(sizeof(int) * m);
    compute_prefix_function(patt, pi, m);
    int count = 0;
    int i, k = 0;

    for(i=0;i<n;i++) {
        while(k!=0 && patt[k] != source[i])
            k = pi[k-1];
        if(patt[k] == source[i]) {
            if(++k >= m) {
                count++;
                k = pi[k-1];
            }
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    int N;
    scanf("%d", &N);
    __clear_input_buf();
    int *result = (int *)malloc(sizeof(int) * N);
    char *source = NULL;
    char *patt = NULL;
    size_t n;
    int i;
    for(i=0;i<N;i++) {
        __getline(&patt, &n, stdin);
        __getline(&source, &n, stdin);
        result[i] = kmp_matcher(source, strlen(source), patt, strlen(patt));
    }
    for(i=0;i<N;i++)
        printf("%d\n", result[i]);
    free(source);
    free(patt);
    free(result);
    return 0;
}
