#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) (a) >= (b) ? (a) : (b)

int lcs_length (char *x, char *y, int m, int n, int *b)
{
    int i, j, k;
    int offset = m+1;
    int c[m+1][n+1];
    for(i=0;i<=m;i++) {
        c[i][0] = 0;
    }
    for(i=0;i<=n;i++) {
        c[0][i] = 0;
    }

    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++) {
            if(*(x+i-1) == *(y+j-1)){
                c[i][j] = c[i-1][j-1] + 1;
                *(b+i*offset+j) = 0;
            }
            else if (c[i-1][j] >= c[i][j-1]) {
                c[i][j] = c[i-1][j];
                *(b+i*offset+j) = 1;
            }
            else {
                c[i][j] = c[i][j-1];
                *(b+i*offset+j)   = -1;
            }
        }
    return c[m][n];
}
void print_lcs (char *s, int *b, int m, int n)
{
    int offset = m+1;
    int c;
    if(m == 0 || n == 0)
        return;
    c = *(b+m*offset+n);
    if(c == 0){
        print_lcs(s, b, m-1, n-1);
        printf("%c", *(s+m-1));
    }
    else if(c == 1)
        print_lcs(s, b, m-1, n);
    else
        print_lcs(s, b, m, n-1);
}

int main (int argc, char *argv[])
{
    int m, n, length;
    int *b;
    if(argc < 3) {
        fprintf(stderr, "not enough parameters\n");
        exit(EXIT_FAILURE);
    }
    m = strlen(argv[1]);
    n = strlen(argv[2]);

    b = (int *)malloc(sizeof(int)*(m+1)*(n+1));

    length = lcs_length(argv[1], argv[2], m, n, b);
    printf("%s\n%s\n", argv[1], argv[2]);
    printf("lcs length is: %d\n", length);
    printf("lcs is: ");
    print_lcs(argv[1], b, m, n);
    printf("\n");
    exit(EXIT_SUCCESS);
}
