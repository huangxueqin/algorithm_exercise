#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

__stack *init_stack()
{
    __stack *s = (__stack *)malloc(sizeof(__stack));
    memset(s, 0, sizeof(__stack));
    return s;
}

void push(__stack *s, void *e)
{
    __node *node = (__node *)malloc(sizeof(__node));
    node->content = e;
    if(s->top != NULL)
    {
        node->prev = s->top;
    }
    s->top = node;
    s->count++;
}

void *pop(__stack *s)
{
    if(s->count == 0)
    {
        fprintf(stderr, "stack is empty\n");
        return NULL;
    }
    void *result = s->top->content;
    __node *top = s->top;
    s->top = s->top->prev;
    s->count--;
    free(top);
    return result;
}

size_t get_stack_size(const __stack *s)
{
    return s->count;
}

void destroy_stack(__stack *s)
{
    __node *top = s->top;
    while(top != NULL)
    {
        __node *tmp = top->prev;
        free(top);
        top = tmp;
    }
    s->count = 0;
    free(s);
}

_Bool is_stack_empty(__stack *s)
{
    return s->count == 0;
}
