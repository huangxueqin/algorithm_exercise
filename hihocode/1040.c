#include "hihocode.h"

typedef struct point {
    int x;
    int y;
} Point, Vector;

// line make sure that p[0].x <= p[1].x
typedef struct line {
    Point p[2];
    Vector v;
    int length_square;
} Line;

typedef struct rect {
    Point p[4];
} Rect;

Line lines[4];
Rect rect;

void init_line(Line *line, int x1, int y1, int x2, int y2) {
    line->p[0].x = x1 <= x2 ? x1 : x2;
    line->p[0].y = x1 <= x2 ? y1 : y2;
    line->p[1].x = x1 <= x2 ? x2 : x1;
    line->p[1].y = x1 <= x2 ? y2 : y1;
    line->v.x = line->p[1].x - line->p[0].x;
    line->v.y = line->p[1].y - line->p[0].y;
    line->length_square = line->v.x * line->v.x + line->v.y * line->v.y;
}

void print_line(Line *line) {
    printf("%d %d %d %d ----- %d %d %d\n",
            line->p[0].x, line->p[0].y, line->p[1].x, line->p[1].y, line->v.x, line->v.y, 
            line->length_square);
}

bool perpendicular(Point *a, Point *o, Point *b) {
    Vector v1, v2;
    v1.x = a->x - o->x;
    v1.y = a->y - o->y;
    v2.x = b->x - o->x;
    v2.y = b->y - o->y;
    return v1.x * v2.x + v1.y * v2.y == 0;
}

bool same_point(Point *p1, Point *p2) {
    return p1->x == p2->x && p1->y == p2->y;
}

bool is_valid_rect() {
    int i, k;
    bool marked[4];
    for(i=0;i<4;i++) {
        if(lines[i].length_square == 0) {
            printf("length_square == 0\n");
            return false;
        }
        marked[i] = false;
    }
    rect.p[0].x = lines->p[0].x;
    rect.p[0].y = lines->p[0].y;
    rect.p[1].x = lines->p[1].x;
    rect.p[1].y = lines->p[1].y;
    marked[0] = true;
    bool found;
    for(i=2;i<4;i++) {
        found = false;
        for(k=0;k<4;k++) {
            if(!marked[k]) {
                if(same_point(lines[k].p, rect.p+i-1)) {
                    found = true;
                    rect.p[i].x = lines[k].p[1].x;
                    rect.p[i].y = lines[k].p[1].y;
                    marked[k] = true;
                    break;
                }
                else if(same_point(lines[k].p+1, rect.p+i-1)) {
                    found = true;
                    rect.p[i].x = lines[k].p[0].x;
                    rect.p[i].y = lines[k].p[0].y;
                    marked[k] = true;
                    break;
                }
            }
        }
        if(!found) {
            return false;
        }
    }
    for(i=0;i<4;i++)
        if(!marked[i]) {
            if(same_point(lines[i].p, rect.p)) {
                if(!(same_point(lines[i].p+1, rect.p+3)))
                    return false;
            }
            else if(same_point(lines[i].p+1, rect.p)) {
                if(!(same_point(lines[i].p, rect.p+3)))
                    return false;
            }
            else
                return false;
            break;
        }
    for(i=0;i<4;i++) {
        Point *a = i == 0 ? rect.p+3 : rect.p+i-1;
        Point *o = rect.p+i;
        Point *b = i == 4 ? rect.p : rect.p+i+1;
        if(!perpendicular(a, o, b))
            return false;
    }
    return true;
}

int main(void) {
    int num_rect;
    scanf("%d", &num_rect);
    int x1, y1, x2, y2;
    int i, k;
    for(i=0;i<num_rect;i++) {
        for(k=0;k<4;k++) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            init_line(lines+k, x1, y1, x2, y2);
        }
        if(is_valid_rect())
            printf("YES");
        else 
            printf("NO");
        printf("\n");
    }
    return 0;
}
