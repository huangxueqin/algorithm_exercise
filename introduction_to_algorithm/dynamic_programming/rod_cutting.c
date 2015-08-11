#include <stdio.h>
#include <stdlib.h>

#define max(a, b) (a) >= (b) ? (a) : (b);
static int price[40] = {1, 7, 8, 9, 10, 17, 17, 20, 24, 30,
    35, 41, 55, 60, 68, 73, 85, 96, 100, 100,
    121, 125, 133, 147, 150, 168, 177, 189, 190, 199,
    208, 217, 250, 266, 289, 300, 311, 320, 322, 322};

//simple recursive method, not dynamic programming
int cut_rod_v1 (int price[], int n)
{
    int i;
    int r = 0;

    for(i=0;i<n;i++) {
        r = max(r, price[i] + cut_rod_v1(price, n-1-i)); 
    }
    return r;
}

//top-down recursive dynamic programming
int cut_rod_v2 (int price[], int revenue[], int n)
{
    int i;
    int r = 0;
    if(revenue[n-1] > 0)
        return revenue[n-1];
    else {
        for(i=0;i<n;i++)
            r = max(r, price[i] + cut_rod_v2(price, revenue, n-1-i));
    }
    revenue[n-1] = r;
    return r;
}

//bottom-up dynamic programming
int cut_rod_v3 (int price[], int revenue[], int n)
{
    int i, j;
    int r = 0;

    for(i=0;i<n;i++) {
        r = 0;
        for(j=0;j<=i;j++) {
            if(j == i) {
                r = max(r, price[j] + 0);
            }
            else
                r = max(r, price[j] + revenue[i-1-j]);
        }
        revenue[i] = r;
    }
    return revenue[n-1];
}

//bottom-up dynamic programming reconstructing solution
int cut_rod_v4 (int price[], int revenue[], int s[], int n)
{
    int i, j;
    int r = 0;

    for(i=0;i<n;i++) {
        r = 0;
        for(j=0;j<=i;j++) {
            int tmpr = i==j ? price[j] : price[j] + revenue[i-1-j];
            if(tmpr > r) {
                r = tmpr;
                s[i] = j;
            }
        }
        revenue[i] = r;
    }
    return revenue[n-1];

}

void print_cut_rod_solution (int s[], int n)
{
    int path = 0;

    printf("The max cutting method is :\n");
    while(s[n-path-1] != n-path-1) {
        path += s[n-1-path] + 1;
        printf("%d",path);
        if(s[n-path-1] != n-path-1)
            printf(" ");
    }
    printf("\n");
}

int main(void)
{
    int len = 8;
    int revenue[40];
    int s[40];
    int r;
    int i;
    for(i=0;i<40;i++){
        revenue[i] = -1;
        s[i] = i;
    }
    r = cut_rod_v4 (price, revenue, s, len);
    printf("The max revenue of a %d meters rod is: %d\n", len, r);
    print_cut_rod_solution(s, len);
}
