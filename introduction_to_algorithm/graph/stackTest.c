#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char *argv[]) {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    STACK s = iStack.init_stack(sizeof(int));
    int i;
    for(i=0;i<10;i++) {
        iStack.push(s, array+i);
    }
    while(!iStack.is_empty(s)) {
        int num;
        iStack.pop(s, &num);
        printf("%d ", num);
    }
    printf("\n");
    iStack.destroy(s);
    return 0;
}
