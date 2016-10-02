#include "mergesort.h"
#include "stddef.h"
#include "stdlib.h"


void mem_cpy(void* dst, void* src, size_t size) {
  char* dstc = dst;
  char* srcc = src;
  int i = 0;
  for(; i < size; i++) {
    *(dstc+i) = *(srcc+i);
  }
}

int mergesort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*)) {
  if(num <= 1) return 0;
  size_t mid = num / 2;
  mergesort(base, mid, size, compar);
  mergesort((void*)((char*)base + mid * size), num - mid, size, compar);
  char* arr1 = base;
  char* arr2 = ((char*)base + mid * size);
  char* buf = malloc(num * size);
  int i = 0;
  int j = 0;
  while(i < mid*size && j < (num - mid)*size) {
    if(compar((void*)(arr1 + i), (void*)(arr2 + j)) < 0) {
      mem_cpy((void*)(buf + i + j), (void*)(arr1 + i), size);
      i+=size;
    } else {
      mem_cpy((void*)(buf + i + j), (void*)(arr2 + j), size);
      j+=size;
    }
  }
  while(i < mid*size) {
    mem_cpy((void*)(buf + i + j), (void*)(arr1 + i), size);
    i+=size;
  }
  while(j < (num - mid)*size) {
    mem_cpy((void*)(buf + i + j), (void*)(arr2 + j), size);
    j+=size;
  }
  mem_cpy(base, (void*)buf, num * size);
  free(buf);
  return 0;
}
