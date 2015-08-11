#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#define BASIC_LEN   10

typedef int E;

struct priority_queue_entry;
typedef struct priority_queue_entry entry;
struct priority_queue ;
typedef struct priority_queue queue;

queue *init_priority_queue ();

queue *build_priority_queue (E arr[], int key_array[], int len);

_Bool is_empty(queue *p_queue);

void insert (queue *p_queue, E data, int k);

E maximum(queue *p_queue);

E extract_max(queue *p_queue);

//void increase_key(queue *p_queue, E data, int k);


#endif
