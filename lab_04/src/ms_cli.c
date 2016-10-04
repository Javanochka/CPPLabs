#include "stdio.h"
#include "stddef.h"
#include "stdlib.h"
#include "mergesort.h"
#include "str.h"

int comparInt(const void* a, const void* b) {
  const int* pa = a;
  const int* pb = b;
  return (*pa - *pb);
}

int comparChr(const void* a, const void* b) {
  const char* pa = a;
  const char* pb = b;
  return (*pa - *pb);
}

int comparStr(const void* a, const void* b) {
  const char* const* pa = a;
  const char* const* pb = b;
  return strcmp(*pa, *pb);
}

int makeInt(char* str){
  int sign = 1;
  if(*str == '-') {
    *str++;
    sign *= -1;
  }
  int res = 0;
  for(; *str; str++) {
    res *= 10;
    res += (*str-'0');
  }
  return res * sign;
}

int main(int argc, char* argv[]){
  if(argc <= 3) {
    return 0;
  }
  if(strcmp(argv[1], "int") == 0) {
    int* arr = malloc((argc - 2) * sizeof(*arr));
    int i;
    for(i = 0; i < argc - 2; i++) {
      arr[i] = makeInt(argv[i + 2]);
    }
    mergesort(arr, argc - 2, sizeof(*arr), comparInt);
    for(i = 0; i < argc - 2; i++) {
      printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
  } else if(strcmp(argv[1], "char") == 0) {
    char* arr = malloc((argc - 2) * sizeof(*arr));
    int i;
    for(i = 0; i < argc - 2; i++) {
      arr[i] = *argv[i + 2];
    }
    mergesort(arr, argc - 2, sizeof(*arr), comparChr);
    for(i = 0; i < argc - 2; i++) {
      printf("%c ", arr[i]);
    }
    printf("\n");
    free(arr);
  } else if(strcmp(argv[1], "str") == 0) {
    char** arr = malloc((argc - 2) * sizeof(*arr));
    int i;
    for(i = 0; i < argc - 2; i++) {
      arr[i] = argv[i + 2];
    }
    mergesort(arr, argc - 2, sizeof(*arr), comparStr);
    for(i = 0; i < argc - 2; i++) {
      printf("%s ", arr[i]);
    }
    printf("\n");
    free(arr);
  }
  return 0;
}


