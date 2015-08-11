#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priority_queue.h"

struct priority_queue_entry {
    int key;
    E data;
};

struct priority_queue {
    entry *entrys;
    int capacity;
    int size;
};

void max_heapify(entry arr[], int len, int p)
{
    int left = 2*p;
    int right = 2*p + 1;
    int largest;

    if(left < len && arr[p].key < arr[left].key)
        largest = left;
    else
        largest = p;

    if(right < len && arr[largest].key < arr[right].key)
            largest = right;

    if(largest != p){
        entry temp = arr[p];
        arr[p] = arr[largest];
        arr[largest] = temp;
        max_heapify(arr, len, largest);
    }
}

queue *init_priority_queue()
{
    queue *p_queue;

    p_queue = (queue *)malloc(sizeof(queue));
    p_queue->entrys = (entry *)malloc(sizeof(entry)*(BASIC_LEN+1));
    bzero(p_queue->entrys, sizeof(entry)*(BASIC_LEN+1));
    p_queue->capacity = BASIC_LEN;
    p_queue->size = 0;

    return p_queue;
}

queue *build_priority_queue (E E_arr[], int key_arr[], int len)
{
    int i;
    int m_capacity = len*2 + 1;
    queue *p_queue;
    entry *entrys = (entry *)malloc(sizeof(entry)*(m_capacity+1));
    bzero(entrys, sizeof(entry)*(m_capacity+1));
    
    for(i=0;i<len;i++){
        entrys[i+1].key = key_arr[i];
        entrys[i+1].data = E_arr[i];
        //printf("%d\n",entrys[i+1].data);
    }
    for(i=(len-1)/2;i>0;i--){
        max_heapify(entrys, len+1, i);
    }
    
    /* for(i=1;i<len;i++){
     *     printf("%d\n",entrys[i].data);
     * } */
    
    p_queue = (queue *)malloc(sizeof(queue));
    p_queue->entrys = entrys;
    p_queue->capacity = m_capacity;
    p_queue->size = len;

    return p_queue;
}

E maximum(queue *p_queue)
{
    return (p_queue->entrys)[1].data;
}

E extract_max(queue *p_queue)
{
    E ret;
    entry *entrys;

    entrys = p_queue->entrys;
    ret = entrys[1].data;
    entrys[1] = entrys[p_queue->size];
    max_heapify(entrys, p_queue->size, 1);
    p_queue->size -= 1;

    return ret;
}

void ensure_capacity (queue *p_queue)
{
    entry *new_entrys;
    int new_capacity;
    new_capacity = p_queue->capacity*2 + 1;
    new_entrys = (entry *)malloc(sizeof(entry)*(new_capacity+1));
    bzero(new_entrys, sizeof(entry)*(new_capacity+1));
    memcpy(new_entrys, p_queue->entrys, sizeof(entry)*(p_queue->capacity+1));

    free(p_queue->entrys);
    p_queue->entrys = new_entrys;
    p_queue->capacity = new_capacity;
}

void flowup (entry arr[], int p)
{
    int up = p/2;
    int smaller;

    if(up > 0 && arr[up].key < arr[p].key)
        smaller = up;
    else 
        smaller = p;

    if(smaller!=p){
        entry tmp = arr[p];
        arr[p] = arr[smaller];
        arr[smaller] = tmp;
        flowup(arr, smaller);
    }
}

void insert (queue *p_queue, E data, int k)
{
    entry *entrys;
    int size;
    if(p_queue->size == p_queue->capacity)
        ensure_capacity(p_queue);
    entrys = p_queue->entrys;
    size = p_queue->size;
    entrys[++size].data = data;
    entrys[size].key = k;
    flowup(entrys, size);
    p_queue->size += 1;
}

_Bool is_empty(queue *p_queue)
{
    return p_queue == NULL || p_queue->size == 0;
}
