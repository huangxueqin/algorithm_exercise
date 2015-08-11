#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

__queue *init_queue()
{
    __queue *q = (__queue *)malloc(sizeof(__queue));
    memset(q, 0, sizeof(__queue));
    return q;
}

size_t get_queue_size(const __queue *q)
{
    return q->count;
}

_Bool is_queue_empty(const __queue *q)
{
    return q->count == 0;
}

void enqueue(__queue *q, void *e)
{
    __queue_node *newtail = (__queue_node *)malloc(sizeof(__queue_node));
    memset(newtail, 0, sizeof(__queue_node));
    newtail->content = e;
    if(q->count == 0)
    {
        q->head = q->tail = newtail;
    }
    else
    {
        q->tail->next = newtail;
        newtail->prev = q->tail;
        q->tail = newtail;
    }
    q->count++;
}

void *dequeue(__queue *q)
{
    void *content;
    if(q->count == 0)
    {
        fprintf(stderr, "try to get elements from empty queue\n");
        return NULL;
    }
    __queue_node *head = q->head;
    content = head->content;
    q->head = head->next;
    if(q->tail == head)
    {
        q->tail = q->head;
    }
    q->count--;
    free(head);
    return content;
}

void destroy_queue(__queue *q)
{
    __queue_node *node = q->head;
    while(node != NULL)
    {
        __queue_node *next = node->next;
        free(node);
        node = next;
    }
    free(q);
}
