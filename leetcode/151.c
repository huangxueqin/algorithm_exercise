#include <stdio.h>

char *remove_extra_space(char *s) {
    char *p1 = s, *p2 = s;
    while(*p2) {
        if(*p2 == ' ') {
            if(p2 > s && *(p2-1) != ' ')
                *p1++ = *p2;
        }
        else {
            *p1++ = *p2;
        }
        p2++;
    }
    if(p1 > s && *(p1-1) == ' ') {
        *(p1-1) = 0;
        return p1-1;
    }
    else {
        *p1 = 0;
        return p1;
    }
}

void first2last(const char *s, char *first, char *last) {
    if(last <= first) return;
    char *efirst = first;
    char *slast = last;
    while((efirst+1) <= last && *(efirst+1) != ' ') efirst++;
    while((slast-1) >= first && *(slast-1) != ' ') slast--;
    if(efirst >= slast) return;
    else {
        first2last(s, efirst+2, slast-2);
        int flen = efirst - first + 1;
        int llen = last - slast + 1;
        int len = flen < llen ? flen : llen;
        for(size_t i=0;i < len; i++) {
            char temp = *(slast+i);
            *(slast+i) = *(first+i);
            *(first+i) = temp;
        }
        if(flen > llen) {
            for(size_t i = 0; i < flen - llen; i++) {
                char *j = first+len;
                char c = *j;
                for(;j < last;j++)
                    *j = *(j+1);
                *j = c;
            }
        }
        else if(llen > flen) {
            for(size_t i = 0; i < llen - flen; i++) {
                char *j = slast+len+i;
                char c = *j;
                for(; j > first+flen+i; j--)
                    *j = *(j-1);
                *j = c;
            }
        }
    }
}

void reverseWords(char *s) {
    char *end = remove_extra_space(s);
    first2last(s, s, end-1);
}

int main(void) {
    char string[] = {' ',' ',' ',' ',' ',
        'b','o','y','c','o','t','t',' ',' ','b','e','e',' ',
        'I',' ','l','i','k','e',' ',' ','s','o',' ','b','e','a','u','t','i','f','u','l',' ',
        't','h','e',' ','s','k','y',' ',' ','i','s',' ',' ',' ','b','l','u','e',
        ' ',' ',' ',' ','\0' };
    char *s = string;
    printf("origin string: |%s|\n", s);
    reverseWords(s);
    printf("after reverse: |%s|\n", s);
    return 0;
}
