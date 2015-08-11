#include "../ita.h"
#include <math.h>
void lu_decomposition(int n, double A[][n], double L[][n], double U[][n])
{
    int i, j, k;
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            L[i][j] = 0;
    for(i=0;i<n;i++)
        L[i][i] = 1;

    for(i=0;i<n;i++)
        for(j=0;j<i;j++)
            U[i][j] = 0;
    
    for(k=0;k<n;k++){
        U[k][k] = A[k][k];
        for(i=k+1;i<n;i++){
            L[i][k] = A[i][k]/A[k][k];
            U[k][i] = A[k][i];
        }
        for(i=k+1;i<n;i++)
            for(j=k+1;j<n;j++){
                A[i][j] = A[i][j] - L[i][k]*U[k][j];               
            }

    }
}

void swap_element(int pi[], int i, int j)
{
    int temp = pi[i];
    pi[i] = pi[j];
    pi[j] = temp;
}

void swap_row(int n, double a[][n], int i, int j)
{
    int k;
    for(k=0;k<n;k++) {
        double temp = a[i][k];
        a[i][k] = a[j][k];
        a[j][k] = temp;
    }
}

double abs_double(double d)
{
    if(d >= 0)
        return d;
    else
        return 0-d;
}

void lup_decomposition(int n, double a[][n], int pi[])
{
    int i, j, k;
    for(i=0;i<n;i++)
        pi[i] = i;
    for(k=0;k<n;k++){
        int max = k;
        for(i=k+1;i<n;i++)
            if(abs_double(a[i][k]) > abs_double(a[k][k])){
                max = i;
            }
        if(a[max][k] == 0){
            fprintf(stderr, "singular matrix\n");
            return;
        }

        swap_element(pi, max, k);
        swap_row(n, a, max, k);
        for(i=k+1;i<n;i++)
            a[i][k] = a[i][k]/a[k][k];
        for(i=k+1;i<n;i++)
            for(j=k+1;j<n;j++)
                a[i][j] = a[i][j] - a[i][k]*a[k][j];
    }
}
