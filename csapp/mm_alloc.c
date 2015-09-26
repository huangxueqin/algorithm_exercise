/**
 * This little is used to simulating the functionality of malloc and free routin 
 * in c standard library
 * author: huangxueqin
 * data: 2015-09-21
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "mm_alloc.h"

#define MAX_HEAP_SIZE (1024*1024*10)    // 10MB
#define WRAP8(n) (((n) + 7u) & (~7u))

#define MAKE_TAG(size, alloc, alloc_prev) (((size) | ((alloc) ? 1u : 0u)) | ((alloc_prev) ? 2u : 0u))
#define END_TAG MAKE_TAG(0, 1, 1)

#define GET_TAG(ptr) (*((unsigned *) (ptr)))
#define SET_TAG(ptr, val) (GET_TAG(ptr) = (val))
#define GET_TAG_SIZE(ptr) (GET_TAG(ptr) & (~7u))
#define GET_TAG_ALLO(ptr) (GET_TAG(ptr) & 1u)
#define GET_PREV_TAG_ALLO(ptr) (GET_TAG(ptr) & 2u)

#define SET_TAG_SIZE(ptr, size) (GET_TAG(ptr) = MAKE_TAG(size, GET_TAG_ALLO(ptr), GET_PREV_TAG_ALLO(ptr)))
#define SET_TAG_ALLO(ptr) (GET_TAG(ptr) |= 1u)
#define CLEAR_TAG_ALLO(ptr) (GET_TAG(ptr) &= (~1u))
#define SET_PREV_TAG_ALLO(ptr) (GET_TAG(ptr) |= 2u)
#define CLEAR_PREV_TAG_ALLO(ptr) (GET_TAG(ptr) &= (~2u))
#define SET_END_TAG(ptr) (GET_TAG(ptr) = END_TAG)
#define IS_END(ptr) (GET_TAG(ptr) == END_TAG)

#define NEXT_TAG(ptr) ((ptr) + GET_TAG_SIZE(ptr))

static char *mem_heap;
static char *mem_brk;
static char *mem_start;
static char *mem_max_addr;

void mm_init() {
    mem_heap = (char *) malloc(sizeof(char) * MAX_HEAP_SIZE);
    // align mem_brk by 8 bytes
    uintptr_t start_addr = (uintptr_t) mem_heap;
    mem_start = mem_brk = (char *) WRAP8(start_addr);
    SET_END_TAG(mem_brk);
    mem_max_addr = (char *) (mem_heap + MAX_HEAP_SIZE);
}

void mm_destroy() {
    free(mem_heap);
    mem_heap = NULL;
    mem_brk = NULL;
    mem_start = NULL;
    mem_max_addr = NULL;
}

// merge any continuing neighbour blocks with find suitable block
void *mm_alloc(size_t size) {
    int as = WRAP8(size + 4);
    char *ptr = mem_start;
    while(!IS_END(ptr)) {
        size_t bs = 0;
        if(!GET_TAG_ALLO(ptr)) {
            char *saved_ptr = ptr;
            while(!IS_END(ptr) && !GET_TAG_ALLO(ptr)) {
                bs += GET_TAG_SIZE(ptr);
                ptr = NEXT_TAG(ptr);
            }
            ptr = saved_ptr;
            if(bs > GET_TAG_SIZE(ptr)) {
                SET_TAG_SIZE(ptr, bs);
            }
            if(bs >= as) {
                break;
            }
        }
        ptr += GET_TAG_ALLO(ptr);
    }
    if(IS_END(ptr)) {
        // can't find suitable block
        char *next_end = ptr + as;
        if(next_end >= mem_max_addr) {
            ptr = NULL;
        }
        else {
           *((unsigned *) ptr) = MAKE_TAG(as, 1, 0);
           SET_END_TAG(next_end);
        }
    }
    return ptr == NULL ? NULL : ptr + 4;
}

void mm_free(void *ptr) {
    char *tag_ptr = (char *) ((char *) ptr - 4);
    CLEAR_TAG_ALLO(tag_ptr);
}
