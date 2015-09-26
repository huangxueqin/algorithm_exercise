#ifndef __MM_ALLOC__
#define __MM_ALLOC__

#include <stddef.h>

extern void *mm_alloc(size_t size);
extern void mm_free(void *ptr);

extern void mm_init();
extern void mm_destroy();

#endif
