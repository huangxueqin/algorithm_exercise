#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "_c_graph.h"

#define DEBUG 0
#if DEBUG
#define log(fmt, x...) do{\
    printf("%s,%d: "fmt"\n", __func__, __LINE__, ##x);\
}while(0)
#else
#define log(fmt, x...) {}
#endif

inline AdjNode *_malloc_node(int v) {
    AdjNode *node = (AdjNode *)malloc(sizeof(AdjNode));
    if(node == NULL) {
        fprintf(stderr, "malloc failed in malloc_node\n");
        return NULL;
    }
    memset(node, 0, sizeof(AdjNode));
    node->u = v;
    return node;
}

inline AdjNode *_malloc_wnode(int v, int weight)
{
    AdjNode *node = _malloc_node(v);
    node->weight = weight;
    return node;
}

inline Graph *_malloc_graph()
{
    Graph *g = (Graph *)malloc(sizeof(Graph));
    if(g == NULL) {
        fprintf(stderr, "malloc failed in malloc_graph\n");
        return NULL;
    }
    memset(g, 0, sizeof(Graph));
    return g;
}

Graph *init_graph_no_edge(const int vNum)
{
    Graph *g = _malloc_graph();
    int adjs_size = vNum * sizeof(AdjNode *);
    if(g == NULL) {
        fprintf(stderr, "malloc failed in malloc_node\n");
        return NULL;
    }
    g->vertexNum = vNum;
    g->edgeNum = 0;
    g->adjs = (AdjNode **)malloc(adjs_size);
    if(g->adjs == NULL)
    {
        fprintf(stderr, "malloc failed in malloc adjs\n");
        return NULL;
    }
    memset((void *)g->adjs, 0, adjs_size);
    return g;
}

inline _Bool is_empty(Graph *g)
{
    return g->vertexNum == 0;
}

Graph *init_graph(const int vNum, const int eNum, AdjNode **adjs)
{
    Graph *g = _malloc_graph();
    g->vertexNum = vNum;
    g->edgeNum = eNum;
    g->adjs = adjs;
    return g;
}

int _get_next_line(FILE *fp, char buf[], int buf_len)
{
    if(fgets(buf, buf_len, fp) != NULL)
    {
        int len = strlen(buf);
        if(buf[len-1] == '\n')
        {
            buf[--len] = '\0';
        }
        return len;    
    }
    return 0;
}

void _add_edge_to_adjs(AdjNode **adjs, int v, int w)
{
    AdjNode *node = _malloc_node(w);
    AdjNode *adj = adjs[v];
    if(adj != NULL)
        node->next = adj;
    adjs[v] = node;
}

#define false 0
#define true 1
_Bool _parse_edge(char buf[], int len, AdjNode **adjs, int maxNum, _Bool is_directed)
{
    int v = 0, w = 0, i = 0;
    while(isspace(buf[i])) 
    {
        i++;
        if(i >= len)
            return false;
    }
    while(!isspace(buf[i]))
    {
        if(buf[i] <= '9' && buf[i] >= '0')
            v = 10 * v + (buf[i] - '0');
        else
            return false;
        i++;
        if(i > len-2)
            return false;
    }
    if(v >= maxNum)
        return false;
    while(isspace(buf[i]))
    {
        i++;
        if(i >= len)
            return false;
    }
    while(i<len && !isspace(buf[i]))
    {
        if(buf[i] <= '9' && buf[i] >= '0')
            w = 10 * w + (buf[i] - '0');
        else 
            return false;
        i++;
    }
    if(w >= maxNum)
        return false;

    _add_edge_to_adjs(adjs, v, w);
    if(!is_directed)
        _add_edge_to_adjs(adjs, w, v);
    return true;

}

#define BUF_SIZE 42
Graph *init_graph_from_file(const char *path)
{
    FILE *fp;
    _Bool is_directed = false;
    int vertexNum, edgeNum;
    AdjNode **adjs;
    Graph *g;
    char buf[BUF_SIZE];
    int read_len, edge_count = 0;
    if((fp = fopen(path, "r")) == NULL)
    {
        fprintf(stderr, "can't open file with path %s\n", path);
        return NULL;
    }
    if((read_len = _get_next_line(fp, buf, BUF_SIZE)) > 0)
    {
        is_directed = atoi(buf) > 0;
    }
    else
    {
        fprintf(stderr, "no direct info\n");
        return NULL;
    }

    if((read_len = _get_next_line(fp, buf, BUF_SIZE)) > 0)
    {
        vertexNum = atoi(buf);
    }
    else
    {
        fprintf(stderr, "no vertexNum info\n");
        return NULL;
    }

    if((read_len = _get_next_line(fp, buf, BUF_SIZE)) > 0)
    {
        edgeNum = atoi(buf);
    }
    else
    {
        fprintf(stderr, "no edgeNum info\n");
        return NULL;
    }

    adjs = (AdjNode **)malloc(vertexNum * sizeof(AdjNode *));
    if(adjs == NULL)
    {
        fprintf(stderr, "malloc adjs failed\n");
        return NULL;
    }
    memset(adjs, 0, vertexNum * sizeof(AdjNode *));
    while((read_len = _get_next_line(fp, buf, BUF_SIZE)) > 0)
    {
        if(!_parse_edge(buf, read_len, adjs, vertexNum, is_directed)){
            return NULL;
        }
        edge_count++;
    }
    if(!is_directed) edge_count *= 2;
    if(edge_count != edgeNum)
    {
        return NULL;
    }
    g = init_graph(vertexNum, edgeNum, adjs);
    return g;

}

void destroy(Graph *g)
{
    if(!is_empty(g))
    {
        AdjNode **adjs = g->adjs;
        int i;
        for(i=0;i<g->vertexNum;i++) {
            AdjNode *adj = adjs[i];
            while(adj != NULL) {
                AdjNode *node = adj;
                adj = adj->next;
                free(node);
            }
        }
        free(g->adjs);
    }
    free(g);
}

void add_edge(Graph *g, int v, int w)
{
    AdjNode *node = _malloc_node(w);
    AdjNode *v_adj = g->adjs[v];
    if(v_adj != NULL)
    {
        node->next = v_adj;
    }
    g->adjs[v] = node;
    g->edgeNum++;
}

void add_2edge(Graph *g, int v, int w)
{
    add_edge(g, v, w);
    add_edge(g, w, v);
}

void add_wedge(Graph *g, int v, int w, int weight)
{
    AdjNode *node = _malloc_wnode(w, weight);
    AdjNode *v_adj = g->adjs[v];
    if(v_adj != NULL)
    {
        node->next = v_adj;
    }
    g->adjs[v] = node;
    g->edgeNum++;
}

void add_w2edge(Graph *g, int v, int w, int weight)
{
    add_wedge(g, v, w, weight);
    add_wedge(g, w, v, weight);
}

Graph *reverse(Graph *g)
{
    Graph *rg = init_graph_no_edge(g->vertexNum);
    if(rg == NULL)
        return;
    int i;
    for(i=0;i<g->vertexNum;i++)
    {
        AdjNode *adj = g->adjs[i];
        while(adj != NULL)
        {
            add_edge(rg, adj->u, i);
            adj = adj->next;
        }
    }
    return rg;
}


const int _NUM_DIGITS_TABLE[] = { 1, 10, 100, 1000, 10000, 100000, 1000000 };
const int _NUM_DIGITS_TABLE_SIZE = 7;
const char digits[] = "0123456789";

int _digit_length(int num)
{
    //int nDigits = floor(log10(abs(the_integer))) + 1;
    int i;
    for(i=0;i<_NUM_DIGITS_TABLE_SIZE;i++)
    {
        if(num < _NUM_DIGITS_TABLE[i])
        {
            break;
        }
    }
    return i;
}

//this calculation is not precise, maybe 2 times longer than actually require
int _cal_str_length(const Graph *g, int num_digits)
{
    return 2 * (num_digits + 1) + 
        g->vertexNum * (num_digits + 2 + 1) + 
        g->edgeNum * (num_digits + 1 + 1);
}

void _write_num_to_string(int num, char str[], int *start, int width)
{
    int p = 0, i;
    int shifter = num;
    do{
        p++;
        shifter /= 10;
    }while(shifter);
    for(i=0;i<width-p;i++)
    {
        str[*start + i] = ' ';
    }
    for(i=width-1;i>=width-p;i--)
    {
        str[*start+i] = digits[num%10];
        num /= 10;
    }
    (*start) += width;
}

//append "->" to string
inline void _append_arrow(char str[], int *start)
{
    str[*start] = '-';
    str[*start + 1] = '>';
    (*start) += 2;
}

inline void _append_comma(char str[], int *start)
{
    str[*start] = ',';
    (*start)++;
}

inline void _append_space(char str[], int *start)
{
    str[*start] = ' ';
    (*start)++;
}

inline void _append_newline(char str[], int *start)
{
    str[*start] = '\n';
    (*start)++;
}

char *to_string(const Graph *g)
{
    const int WIDTH = _digit_length(g->vertexNum > g->edgeNum ? g->vertexNum : g->edgeNum);
    log("WIDTH = %d", WIDTH);
    int len = _cal_str_length(g, WIDTH);
    log("len = %d", len);
    int write_pos, i;
    char *str = (char *)malloc((len + 1)*sizeof(char));
    if(str == NULL)
    {
        fprintf(stderr, "malloc failed in func to_string\n");
        return NULL;
    }
    memset(str, '\0', len+1);
    write_pos = 0;
    _write_num_to_string(g->vertexNum, str, &write_pos, WIDTH);
    _append_newline(str, &write_pos);
    _write_num_to_string(g->edgeNum, str, &write_pos, WIDTH);
    _append_newline(str, &write_pos);
    log("\n%s", str); 
    for(i=0;i<g->vertexNum;i++)
    {
        _write_num_to_string(i, str, &write_pos, WIDTH);
        _append_arrow(str, &write_pos);
        AdjNode *adj = g->adjs[i];
        log("\n%s", str); 
        while(adj != NULL)
        {
            _append_space(str, &write_pos);
            _write_num_to_string(adj->u, str, &write_pos, WIDTH);
            if (adj->next != NULL)
            {
                _append_comma(str, &write_pos);
            }
            adj = adj->next;
        }
        _append_newline(str, &write_pos);
    }
    log("write_pos = %d", write_pos);
    return str;
}
