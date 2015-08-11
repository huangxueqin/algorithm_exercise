#include <stdio.h>
#include <stdbool.h>

#define MAX_LEN 10000001
char str[MAX_LEN];
int repeat;
typedef enum {NONE, ONE, TWO, THREE} state;

bool is_beautiful(char *str, int len) {
    repeat = 0;
    char *p = str;
    state s = NONE;
    char *savep = NULL;
    while((p-str) < len && s != THREE) {
        savep = p;
        while((p+1-str) < len && *(p+1) == *p) p++;
        p++;
        switch(s) {
            case NONE:
                if(p-str < len && *p == *(p-1) + 1) {
                    repeat = p - savep;
                    s = ONE;
                }
                break;
            case ONE:
                if(p-str < len && *(p-1)+1 == *p) {
                    if(p-savep <= repeat) {
                        repeat = p-savep;
                        s = TWO;
                    }
                    else {
                        repeat = p-savep;
                    }
                }
                else if(p-str < len) {
                    s = NONE;
                }
                break;
            case TWO:
                if(p-savep >= repeat) {
                    s = THREE;
                }
                else {
                    if(p-str < len && *(p-1)+1 == *p) {
                        if(p-savep < repeat) {
                            s = TWO;
                            repeat = p-savep;
                        }
                    }
                    else if(p-str < len) {
                        s = NONE;
                    }
                }
                break;
        }
    }
    return s == THREE;
}

int main(void) {
    int i, cases;
    scanf("%d", &cases);
    for(i = 0; i < cases; i++) {
        int len;
        scanf("%d", &len);
        scanf("%s", str);
        printf(is_beautiful(str, len) ? "YES\n" : "NO\n");
    }
    return 0;
}
