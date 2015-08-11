#include <stdio.h>
#include <stdlib.h>

#define INF 0x7FFFFFFF

static int p[7] = {30, 35, 15, 5, 10, 20, 25};

int matrix_chain_mul (int p[], int n, int s[][n+1])
{
    int m[n+1][n+1];
    int i,k,l;

    for(i=1;i<=n;i++)
        m[i][i] = 0;

    for(l=2;l<=n;l++) {
        for(i=1;i<=n-l+1;i++) {
            int j = i+l-1;
            m[i][j] = INF;
            for(k=i;k<j;k++) {
                int temp = m[i][k] + m[k+i][j] + p[i-1]*p[k]*p[j];
                if(m[i][j] < temp) {
                    m[i][j] = temp;
                    s[i][j] = k;
                }
            }
        }
    }
    return m[1][n];
}

void print_solution (int n, int s[][n+1], int i, int j)
{
     if(i == j)
        printf("A%d",i);
     else {
         printf("(");
         print_solution(n, s, i, s[i][j]);
         print_solution(n, s, s[i][j]+1, j);
         printf(")");
     }
}

int main (void)
{
    int s[7][7];
    int ret;
    ret = matrix_chain_mul(p, 6, s);
    printf("min multiply times is: %d\n", ret);
    print_solution(6, s, 1, 6);
}
