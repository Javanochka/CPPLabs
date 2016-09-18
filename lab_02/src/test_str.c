#include "str.h"
#include "stdio.h"
#include "stdarg.h"

void printRes(int res, const char * comment) {
  if(!res) {
    printf("OK, : ");
  }else {
    printf("WA, %d: ", res); 
  }
  printf(comment);
  printf("\n");
}

void test_strlen(){
  printRes(strlen("abacaba")!=7, "strlen abacaba = 7");
  printRes(strlen("")!=0, "strlen  = 0");
}


void test_strcmp() {
  printRes(strcmp("auto", "auto")!=0, "strcmp auto auto = 0");
  printRes(strcmp("abc", "a")<=0, "strcmp abc a > 0");
  printRes(strcmp("a", "abc")>=0, "strcmp a abc < 0");
  printRes(strcmp("everyone", "everybody")<=0, "strcmp everyone everybody > 0");
  printRes(strcmp("everybody", "everyone")>=0, "strcmp everybody everyone < 0");
  printRes(strcmp("","")!=0, "strcmp   == 0");
}

void test_strcat() {
  {
  char a[10] = "";
  char b[10] = "";
  printf("Look at res: strcat ");
  printf("%s %s ", a, b);
  printf("%s\n", strcat(a,b));
  }
  {
  char a[10] = "aba";
  char b[10] = "";
  printf("Look at res: strcat ");
  printf("%s %s ", a, b);
  printf("%s\n", strcat(a,b));
  }
  {
  char a[10] = "";
  char b[10] = "aba";
  printf("Look at res: strcat ");
  printf("%s %s ", a, b);
  printf("%s\n", strcat(a,b));
  }
  {
  char a[10] = "aba";
  char b[10] = "cdc";
  printf("Look at res: strcat ");
  printf("%s %s ", a, b);
  printf("%s\n", strcat(a,b));
  }
}

void test_strcpy() {
  {
  char a[10] = "";
  char b[10] = "";
  printf("Look at res: strcpy ");
  printf("%s %s ", a, b);
  printf("%s %s\n", strcpy(a,b), a);
  }
  {
  char a[10] = "aba";
  char b[10] = "";
  printf("Look at res: strcpy ");
  printf("%s %s ", a, b);
  printf("%s %s\n", strcpy(a,b), a);
  }
  {
  char a[10] = "";
  char b[10] = "aba";
  printf("Look at res: strcpy ");
  printf("%s %s ", a, b);
  printf("%s %s\n", strcpy(a,b), a);
  }
  {
  char a[10] = "aba";
  char b[10] = "cdc";
  printf("Look at res: strcpy ");
  printf("%s %s ", a, b);
  printf("%s %s\n", strcpy(a,b), a);
  }
}
