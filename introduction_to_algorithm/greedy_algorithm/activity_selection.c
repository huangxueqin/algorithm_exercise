#include "../ita.h"

static int s[] = {0, 1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12, 17};
static int f[] = {0, 4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16, 17};

//dynamic programming solution
int actv_sel_v1 (int s[], int f[], int n, int b[][n])
{
    int i, l, j, k;
    int c[n][n];
    
    for(i=0;i<n;i++) {
        c[i][i] = 0;
        b[i][i] = -1;
    }

    for(l=1;l<n;l++)
        for(i=0;i<n-l;i++) {
            j = i+l;
            c[i][j] = 0;
            b[i][j] = -1;
            for(k=i+1;k<j;k++) {
                if(s[k] >= f[i] && f[k] < s[j])
                    if(c[i][j] < c[i][k] + c[k][j] + 1) {
                        c[i][j] = c[i][k] + c[k][j] + 1;
                        b[i][j] = k;
                    }
            }
        }
    return c[0][n-1];
}

void print_resolution (int i, int j, int n, int b[][n])
{
    if(b[i][j] != -1) {
        print_resolution(i, b[i][j], n, b);
        printf("T%d", b[i][j]);
        print_resolution(b[i][j], j, n, b);
    }
}

//greedy algorithm solution
void actv_sel_preprocess (int s[], int f[], int n, int b[])
{
    int i;
    int g = f[0];
    b[0] = -1;
    for(i=1;i<n;i++) {
        if(s[i] >= g) {
            b[i] = 1;
            g = f[i];
        }
        else
            b[i] = -1;
    }
}

void actv_sel_v2 (int s[], int f[], int n, int b[])
{
    int ret = 0;
    int i;
    actv_sel_preprocess(s, f, n, b);
    for(i=0;i<n;i++)
        if(b[i] == 1) {
            ret++;
            printf("T%d", i);
        }
    printf("\nmaximum task number is %d\n", ret);
}

int main (void)
{
    int n = 13;
    int b[n];
    actv_sel_v2(s, f, n, b);
    exit(EXIT_SUCCESS);
}
