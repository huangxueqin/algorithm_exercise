#include "cleetc.h"

#define DEFAULT_STACK_SIZE 100

struct stack {
    int *array;
    int array_size;
    int top;
};

struct stack *create_stack() {
    struct stack *stk = (struct stack *) malloc(sizeof(struct stack));
    stk->array = (int *) malloc(sizeof(int) * DEFAULT_STACK_SIZE);
    memset(stk->array, 0, sizeof(int) * DEFAULT_STACK_SIZE);
    stk->array_size = DEFAULT_STACK_SIZE;
    stk->top = 0;
    return stk;
}

void resize(struct stack *stk, int new_size) {
    int *new_array = (int *) malloc(sizeof(int) * new_size);
    memcpy(new_array, stk->array, sizeof(int) * stk->top);
    free(stk->array);
    stk->array = new_array;
    stk->array_size = new_size;
}

int top(struct stack *stk) {
    return stk->array[stk->top-1];
}

void pop(struct stack *stk) {
    stk->top -= 1;
    if(stk->array_size >= DEFAULT_STACK_SIZE * 2 && stk->array_size / 4 >= stk->top) {
        int new_size = stk->array_size / 2;
        resize(stk, new_size);
    }
}

void push(struct stack *stk, int x) {
    if(stk->top == stk->array_size) {
        int new_size = stk->array_size * 2 + 1;
        resize(stk, new_size);
    }
    stk->array[stk->top] = x;
    stk->top += 1;
}

// lazy clear
void clear(struct stack *stk) {
    stk->top = 0;
}

bool is_empty(struct stack *stk) {
    return stk->top <= 0;
}

void free_stack(struct stack *stk) {
    free(stk->array);
    free(stk);
    stk = NULL;
}
