#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_t {
    struct node_t *prior, *next;
    void *key;
};

// This func will never called outside, only called by struct lru_cache
struct node_t *init_node_t(void *key, struct node_t *prior, struct node_t *next) {
    struct node_t *node = (struct node_t *) malloc(sizeof(struct node_t));
    node->key = key;
    node->prior = prior;
    node->next = next;
    return node;
}

/*
#define INIT_NODE_T(name, p_key, p_prior, p_next) \
    struct node_t name = { \
        .key = p_key, \
        .prior = p_prior, \
        .next = p_next};
*/

// hooks
typedef void (*remove_func) (void *key);
typedef void (*add_func) (void *key, void *data);
typedef void *(*get_func) (const void *key);
typedef int (*key_comp_func) (const void *lkey, const void *rkey);
typedef void *(*key_cpy_func) (const void *key);
typedef void *(*key_dealloc_func) (void *key);

struct lru_cache {
    remove_func remove;
    add_func add;
    get_func get;
    key_comp_func key_comp; 
    key_cpy_func key_cpy;
    key_dealloc_func key_dealloc;

    size_t cache_size;
    size_t cache_count;
    struct node_t *first, *last;
};

struct lru_cache *init_lru_cache(const size_t cache_size, 
        remove_func remove, 
        add_func add, 
        get_func get,
        key_comp_func key_comp, 
        key_cpy_func key_cpy, 
        key_dealloc_func key_dealloc) {
    struct lru_cache *cache = (struct lru_cache *) malloc(sizeof(struct lru_cache));
    memset(cache, 0, sizeof(struct lru_cache));
    cache->cache_size = cache_size;
    cache->remove = remove;
    cache->add = add;
    cache->get = get;
    cache->key_comp = key_comp;
    cache->key_cpy = key_cpy;
    cache->key_dealloc = key_dealloc;
    return cache;
}

int is_cache_empty(struct lru_cache *cache) {
    return cache->last == NULL;
}

int is_cache_full(struct lru_cache *cache) {
    return cache->cache_count == cache->cache_size;
}

void cache_pop(struct lru_cache *cache) {
    if(is_cache_empty(cache)) return;
    struct node_t *tmp = cache->last;

    // check if cache->first == cache->last
    if(cache->first == cache->last) {
        cache->first = NULL;
    }

    cache->last = cache->last->prior;
    if(cache->last != NULL) {
        cache->last->next = NULL;
    }

    void *key = tmp->key;
    cache->remove(key);
    cache->key_dealloc(key);
    free(tmp);
    cache->cache_count -= 1;
}

void cache_put(struct lru_cache *cache, void *key, void *data) {
    void *key_cpy = cache->key_cpy(key);
    struct node_t *node = init_node_t(key_cpy, NULL, NULL);
    if(is_cache_empty(cache)) {
        cache->first = cache->last = node;
    }
    else {
        node->next = cache->first;
        cache->first->prior = node;
        cache->first = node;
    }
    cache->cache_count += 1;
}

void *cache_get(struct lru_cache *cache, const void *key) {
    struct node_t *ndt = cache->first;
    void *data = NULL;
    while(ndt && cache->key_comp(key, ndt->key) != 0) {
        ndt = ndt->next;
    }
    if(ndt != NULL) {
        data = cache->get(key);
        // adjust the node to cache->first
        if(ndt != cache->first) {
            struct node_t *pndt = ndt->prior;
            pndt->next = ndt->next;
            if(ndt != cache->last) {
                ndt->next->prior = pndt;
            }
            else {
                cache->last = pndt;
            }
            // move ndt to head
            ndt->prior = NULL;
            ndt->next = cache->first;
            cache->first = ndt;
        }
    }
    return data;
}
