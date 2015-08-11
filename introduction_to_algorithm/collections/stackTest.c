#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main(int argc, char *argv[])
{
    __stack *s = init_stack();
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i;
    
    for(i=0;i<9;i++)
    {
        push(s, array+i);
    }

    printf("stack size is %zu\n", get_stack_size(s));
    while(!is_stack_empty(s))
    {
        int *p = (int *)pop(s);
        printf("%d\n", *p);
    }
    destroy_stack(s);
    return 0;
}
