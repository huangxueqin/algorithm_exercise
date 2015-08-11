#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

int main(int argc, char *argv[])
{
    __queue *q = init_queue();
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i;
    
    for(i=0;i<9;i++)
    {
        enqueue(q, array+i);
    }

    printf("queue size is %zu\n", get_queue_size(q));
    while(!is_queue_empty(q))
    {
        int *p = (int *)dequeue(q);
        printf("%d\n", *p);
    }
    destroy_queue(q);
    return 0;
}
