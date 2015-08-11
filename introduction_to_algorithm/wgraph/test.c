#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "wgraph.h"

int main(int argc, char *argv[])
{
    wGraph *wg = NULL;
    PEdge *edges = NULL;
    int opt;
    while((opt = getopt(argc, argv, "p:")) > 0) {
        switch(opt) {
            case 'p':
                wg = init_graph_from_file(optarg);
                break;
            default:
                break;
        }
    }
    
    if(wg == NULL) {
        printf("default parameters\n");
        if(argc > 1) {
            wg = init_graph_from_file(argv[1]);
        }
        if(wg == NULL) {
            printf("NO input file\n");
            exit(EXIT_FAILURE);
        }
    }
    
    edges = prim_mst(wg);
    if(edges != NULL)
        free(edges);
    destroy_graph(wg);
    return 0;
}

