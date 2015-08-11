#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

struct NODE {
    void *content;
    struct NODE *prev;
};
typedef struct NODE NODE;

struct Stack {
    StackInterface *iStack; 
    size_t count;
    size_t element_size;
    NODE *top;
};
typedef struct Stack Stack;

Stack *init_stack(size_t elmt_size);
void push(Stack *s, void *new_val);
void pop(Stack *s, void *container);
size_t get_size(Stack * const s);
bool is_empty_stack(Stack * const s);
void destroy_stack(Stack *s);

StackInterface iStack = {
    .init_stack = init_stack,
    .push = push,
    .pop = pop,
    .get_size = get_size,
    .is_empty = is_empty_stack,
    .destroy = destroy_stack
};


#define STDERR stderr

inline void malloc_error(FILE *stream) {
    fprintf(stream, "%s,%d: malloc failed\n", __func__, __LINE__);
}

inline void *malloc_block(size_t size) {
    char *p = (char *)malloc(size);
    if(p == NULL) {
        malloc_error(STDERR);
        return NULL;
    }
    memset(p, 0, size);
    return p;
}

NODE *malloc_node(void *src, size_t size) {
    NODE *n = (NODE *)malloc(sizeof(NODE));
    if(n == NULL) {
        malloc_error(STDERR);
        return NULL;
    }
    memset(n, 0, sizeof(NODE));
    void *p = malloc_block(size);
    if(p != NULL) {
        memcpy(p, src, size);
        n->content = p;
    }
    else {
        free(n);
        n = NULL;
    }
    return n;
}

Stack *init_stack(size_t elmt_size) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    if(s == NULL) {
        malloc_error(STDERR);
        return NULL;
    }
    memset(s, 0, sizeof(Stack));
    s->element_size = elmt_size;
    s->iStack = &iStack;
}

size_t get_size(Stack * const s) {
    return s->count;
}

bool is_empty_stack(Stack * const s) {
    return s->count == 0;
}

void push(Stack *s, void *new_val) {
    NODE *new_top = malloc_node(new_val, s->element_size);
    if(new_top == NULL)
        return;
    new_top->prev = s->top;
    s->top = new_top;
    s->count++;
}

void pop(Stack *s, void *container) {
    if(s->count == 0)
        return;
    void *content = s->top->content;
    memcpy(container, content, s->element_size);
    NODE *top = s->top;
    s->top = s->top->prev;
    free(top);
    free(content);
    s->count--;
}

void destroy_stack(Stack *s) {
    NODE *top = s->top;
    while(top != NULL) {
        NODE *tmp = top->prev;
        free(top->content);
        free(top);
        top = tmp;
    }
    free(s);
}
