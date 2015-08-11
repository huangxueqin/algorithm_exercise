#include "hihocode.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(int argc, char *argv[]) {
    char *pal = argv[1];
    int n = strlen(pal);
    int *p = (int *)malloc(sizeof(int) * (2*n+1));
    char *epal = (char *)malloc(sizeof(char) * (2*n+1));
    int i;
    for(i=0;i<n;i++) {
        epal[2*i] = '#';
        epal[2*i+1] = pal[i];
    }
    epal[2*n] = '#';
    int max = 0, max_p, result = 0;
    for(i=0;i<2*n+1;i++) {
        if(i < max)
            p[i] = MIN(p[2*max_p-i], (p[max_p]-(i-max_p)));
        else
            p[i] = 1;
        while(i-p[i]>=0 && i+p[i]<2*n+1 && epal[i-p[i] ] == epal[ i+p[i] ])
            p[i]++;
        if(max < i+p[i]) {
            max = i+p[i];
            max_p = i;
        }
        if(result < p[i])
            result = p[i];
    }
    printf("%d\n", result-1);
    /* for(i=0;i<2*n+1;i++)  */
        /* printf("%d, ", p[i]-1); */
    printf("\n");
    free(p);
    free(epal);
    return 0;
}
