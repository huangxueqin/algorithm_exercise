#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
    int val;
    struct list *next;
};

struct list *create_list(int val, struct list *next) {
    struct list *l = (struct list *) malloc(sizeof(struct list));
    l->val = val;
    l->next = next;
    return l;
}

void dfs(const int s, const int numCourses, int *degrees, struct list **adjlists, int *num, int *out_seq) {
    out_seq[*num] = s;
    degrees[s] = -1;
    *num += 1;
    struct list *adj = adjlists[s];
    while(adj) {
        int v = adj->val;
        degrees[v]--;
        if(degrees[v] == 0) {
            dfs(v, numCourses, degrees, adjlists, num, out_seq);
        }
    }
}

int *findOrder(int numCourses, int **prerequisites, int prerequisitesRowSize, int prerequisitesColSize, int *returnSize) {
    int i;
    struct list **adjlists = (struct list **) malloc(sizeof(char *) * numCourses);
    memset(adjlists, 0, sizeof(char *) * numCourses);
    int *degrees = (int *) malloc(sizeof(int) * numCourses);
    memset(degrees, 0, sizeof(int) * numCourses);

    for(i = 0; i < prerequisitesRowSize; i++) {
        int from = prerequisites[i][1];
        int to = prerequisites[i][0];
        degrees[to]++;
        adjlists[from] = create_list(to, adjlists[from]);
    }

    int num = 0;
    int *out_seq = (int *) malloc(sizeof(int) * numCourses);
    for(i = 0; i < numCourses; i++) {
        if(degrees[i] == 0) {
            dfs(i, numCourses, degrees, adjlists, &num, out_seq);
        }
    }

    for(i = 0; i < numCourses; i++) {
        struct list *adj = adjlists[i];
        while(adj) {
            struct list *tmp = adj;
            adj = adj->next;
            free(tmp);
        }
    }
    free(adjlists);
    free(degrees);

    *returnSize = numCourses;
    if(num != numCourses) {
        free(out_seq);
        out_seq = NULL;
        *returnSize = 0;
    }

    return out_seq;
}

int main(void) {
    int numCourses = 10;
    int outSize = 0;
    int **p = NULL;
    int *seq = findOrder(numCourses, p, 0, 0, &outSize);
    for(int i = 0; i < outSize; i++) {
        printf("%d", seq[i]);
        if(i < outSize-1) printf(" ");
        else printf("\n");
    }
    if(seq != NULL) free(seq);
    return 0;
}
