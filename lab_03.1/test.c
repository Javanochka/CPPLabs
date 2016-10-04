#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"

int main() {

  int* a = malloc(10 * sizeof(*a));
  int n;
  scanf("%d", &n);
  if(n % 2 == 0) {
    printf("OK");
  }else {
    for(int i = 0; i < 10; i++) {
      a[i] = n *6 + i;
    }
    printf("%d", a[4]+a[6]);
    free(a);
  }
  return 0;
}
