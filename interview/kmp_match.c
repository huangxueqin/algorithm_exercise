#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gen_pat_array(char *pattern, const int len, int *pat_array) {
    int k = -1;
    for(int i = 0; i < len; i++) {
        while(k > -1 && pattern[k+1] != pattern[i]) k = pat_array[k];
        if(k+1 < i && pattern[k+1] == pattern[i]) ++k;
        pat_array[i] = k;
    }

    // debug
    printf("pi for \"%s\" is: ", pattern);
    for(int i = 0; i < len; i++) {
        printf("%d", pat_array[i]);
        if(i < len-1) printf(" ");
        else printf("\n");
    }
}

void kmp_match(char *src, char *pattern) {
    int src_len = strlen(src);
    int pat_len = strlen(pattern);
    int *pi = (int *)malloc(sizeof(int) * pat_len);
    memset(pi, 0, sizeof(int) * pat_len);
    gen_pat_array(pattern, pat_len, pi);
    int k = -1;
    for(int i = 0; i < src_len; i++) {
        while(k > -1 && pattern[k+1] != src[i]) k = pi[k];
        if(pattern[k+1] == src[i]) ++k;
        if(k == pat_len-1) {
            printf("%d\n", i);
            k = pi[k];
        }
    }
    free(pi);
}

int main(void) {
    char *src = "aaabaacaacaaa";
    char *pat = "aaa";
    kmp_match(src, pat);
    return 0;
}

