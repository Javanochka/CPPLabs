#include "stddef.h"

char * strcpy(char * destination, const char * source) {
  char * curd = destination;
  const char * curs = source;
  for(;*curs; curs++, curd++) {
    *curd = *curs;
  }
  *curd = '\0';
  return destination;
}

char * strcat(char * destination, const char * source) {
  char * curd = destination;
  const char * curs = source;
  for(;*curd; curd++);
  for(;*curs; curs++, curd++) {
    *curd = *curs;
  }
  *curd = '\0';
  return destination;
}

int strcmp(const char * str1, const char * str2) {
  const char * curs1 = str1;
  const char * curs2 = str2;
  for(; *curs1 && *curs2 && *curs1 == *curs2; curs1++, curs2++);
  return *curs1 - *curs2;
}

size_t strlen(const char * str) {
  const char * curs = str;
  for(; *curs; curs++);
  return curs - str;
}
