#ifndef __MERGESORT_H_
#define __MERGESORT_H_
#include "stddef.h"
int mergesort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));
void mem_cpy(void* a, void* b, size_t size);
#endif
