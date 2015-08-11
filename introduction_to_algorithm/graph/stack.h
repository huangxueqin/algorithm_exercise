#ifndef _STACK_H_
#define _STACK_H_

#include <stdbool.h>

typedef struct Stack *STACK;

struct StackInterface {
    STACK (*init_stack) (size_t elmt_size);
    void (*push) (STACK s, void *new_val);
    void (*pop) (STACK s, void *container);
    size_t (*get_size) (const STACK s);
    bool (*is_empty) (const STACK s);
    void (*destroy) (STACK s);
};
typedef struct StackInterface StackInterface;

extern StackInterface iStack;
#endif
