/*
 *test graph utils
 * 0. print graph
 * 1. test dfs
 * 2. test bfs
 * 3. test top-sort
 * 4. test strong-component
 * 5. print reverse graph
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "_c_graph.h"
#include "_c_graph_utils.h"

void print_graph(Graph *g);
void test_dfs(Graph *g);
void test_bfs(Graph *g);
void test_top_sort(Graph *g);
void test_strong_component(Graph *g);
void print_reverse_graph(Graph *g);

void clean_stdin();
int main(int argc, char *argv[])
{
    Graph *g;
    int test_num;
    char continue_run;
    char rebuild_graph;
    char *path = (char *)malloc(256 * sizeof(char));
    
    int opt;
    while((opt = getopt(argc, argv, "p:")) > 0) {
        switch(opt) {
            case 'p':
                g = init_graph_from_file(optarg);
                break;
            default:
                break;
        }
    }

    printf("Enter test unit? y or n: ");
    scanf("%c", &continue_run);
    clean_stdin();
    while(continue_run == 'y' || continue_run == 'Y') {
        printf("Need rebuild graph? y or n: ");
        scanf("%c", &rebuild_graph);
        clean_stdin();
        if(rebuild_graph == 'y' || rebuild_graph == 'Y') {
            size_t n = 255;
            int byte_read;
            printf("Input source file path: ");
            byte_read = getline(&path, &n, stdin);
            if(byte_read == -1) {
                printf("ERROR");
            }
            if(path[byte_read-1] == '\n')
                path[byte_read-1] = '\0';
            if(g != NULL)
                destroy(g);
            g = init_graph_from_file(path);
        }

        if(g == NULL) {
            printf("The test graph is NULL\n");
            exit(EXIT_FAILURE);
        }

        printf("Input a number to choose test functions: ");
        scanf("%d", &test_num);
        clean_stdin();
        switch(test_num) {
            case 0:
                print_graph(g);
                break;
            case 1:
                test_dfs(g);
                break;
            case 2:
                test_bfs(g);
                break;
            case 3:
                test_top_sort(g);
                break;
            case 4:
                test_strong_component(g);
                break;
            case 5:
                print_reverse_graph(g);
                break;
            default:
                break;
        }

        printf("Continue test? y or n: ");
        scanf("%c", &continue_run);
        clean_stdin();
    }
    if(path != NULL)
        free(path);
    destroy(g);
    return 0;
}
void print_graph(Graph *g) {
    char *s = to_string(g);
    printf("graph content:\n%s\n", s);
    free(s);
}

void print_reverse_graph(Graph *g) {
    Graph *rg = reverse(g);
    print_graph(rg);
    destroy(rg);
}

void print_int_array(int array[], int len) {
    int i;
    printf("[");
    for(i=0;i<len;i++) {
        printf("%d", array[i]);
        if(i < len-1)
            printf(", ");
    }
    printf("]");
}

int print_path(int start, int end, int edgeTo[])
{
    int root;
    if(edgeTo[end] != -1 && end != start) {
        root = print_path(start, edgeTo[end], edgeTo);
        printf("->");
    }
    else {
        root = end;
    }
    printf("%d", end);
    return root;
}

void find_path(Graph *g, int v, int w) {
    int arr_len = g->vertexNum, i, root;
    int *edgeTo = (int *)malloc(sizeof(int) * arr_len);
    if(edgeTo == NULL)
        return;
    for(i=0;i<arr_len;i++) {
        edgeTo[i] = -1;
    }
    dfs(g, v, edgeTo);
    root = print_path(v, w, edgeTo);
    printf("\n");
    if(root != v) {
        printf("No exist path\n");
    }
}

void test_dfs(Graph *g)
{
    int v, w;
    printf("Test DFS, Graph g has %d nodes\n", g->vertexNum);
    printf("Input start and end node: ");
    scanf("%d %d", &v, &w);
    find_path(g, v, w);
}


void test_bfs(Graph *g) {
    int *dist = (int *)malloc(g->vertexNum * sizeof(int));
    int v, w;
    printf("Test BFS, Graph g has %d nodes\n", g->vertexNum);
    printf("Input two node: ");
    scanf("%d %d", &v, &w);
    bfs(g, v, dist);
    print_int_array(dist, g->vertexNum);
    printf("\n");
    printf("The shortest dist from node %d to node %d is %d\n", v, w, dist[w]);
}

void test_top_sort(Graph *g) {
    int s;
    int i, j;
    int len = g->vertexNum;
    int *result = (int *)malloc(len * sizeof(int));
    if(result == NULL) {
        printf("malloc failed\n");
        return;
    }
    memset(result, 0, len * sizeof(int));
    printf("Input a suggest first node: ");
    scanf("%d", &s);
    top_sort(g, s, result);
    for(i=0;i<len;i++) {
        for(j=0;j<len;j++) {
            if(result[j] == i)
                printf("%d", j);
        }
        if(i < len -1)
            printf("->");
    }
    printf("\n");
    free(result);
}

void test_strong_component(Graph *g) {
    int *group = (int *)malloc(sizeof(int) * g->vertexNum);
    if(group == NULL)
        return;
    strong_component(g, group);
    printf("group info is: \n");
    print_int_array(group, g->vertexNum);
    printf("\n");
}

void clean_stdin() {
    char ch;
    do {
        ch = getchar();
    }while(ch != '\n' && ch != EOF);
}
