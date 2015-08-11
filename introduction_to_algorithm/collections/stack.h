#ifndef _STACK_H_
#define _STACK_H_

struct __node {
    void *content;
    struct __node *prev;
};
typedef struct __node __node;

struct __stack {
    size_t count;
    __node *top;
};
typedef struct __stack __stack;

#define INIT_STACK(name) \
    __stack name = { \
        .count = 0, \
        .top = NULL \
    }


__stack *init_stack();
size_t get_stack_size(const __stack *s);
_Bool is_stack_empty(__stack *s);
void push(__stack *s, void *e);
void *pop(__stack *s);
void destroy_stack(__stack *s);
#endif
