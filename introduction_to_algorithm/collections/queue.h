#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct __queue_node {
    void *content;
    struct __queue_node *next;
    struct __queue_node *prev;
} __queue_node;

typedef struct __queue {
    size_t count;
    __queue_node *head;
    __queue_node *tail;
} __queue;

#define INIT_QUEUE(name) \
    __queue name = { \
        .count = 0; \
        .head = NULL; \
        .tail = NULL; \
    }

__queue *init_queue();
size_t get_queue_size(const __queue *q);
_Bool is_queue_empty(const __queue *q);
void enqueue(__queue *q, void *e);
void *dequeue(__queue *q);
void destroy_queue(__queue *q);

#endif
