#include "../ita.h"
#include "wdgraph.h"
#include <stdbool.h>


void flush_input() {
    char c;
    while((c = getchar()) != EOF && c != '\n');
}

int main(void) {
    PWdgraph wdg = init_graph(fopen("input", "r"));
    if(wdg == NULL) {
        printf("init graph failed\n");
        return EXIT_FAILURE;
    }
    printf("The graph's structure is:\n");
    print_graph(wdg);
    
    if(contains_loop(wdg))
        printf("The graph contains loop\n");
    else
        printf("The graph does not contains loop\n");

    size_t v, w;
    printf("please input 2 vertices: \n");
    
    while(EOF != (scanf("%zu%zu", &v, &w))) {
        double sp = shortest_path(wdg, v, w);
        printf("Shortest path from %zu to %zu is: %lf\n", v, w, sp);
        flush_input();        
    } 
    destroy_graph(wdg);
    return 0;
}
