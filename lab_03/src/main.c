#include "clist.h"
#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "string.h"

#define container_of(ptr, type, member) ((type*)( (char*)(ptr) - offsetof(type, member) ))

struct position_node {
  int x, y;
  struct intrusive_node node;
};

void remove_position(struct intrusive_list *l, int x, int y) { // removes all (x, y) pairs
  struct intrusive_node *cur = l->head;
  while(cur != NULL) {
    struct position_node *cont = container_of(cur, struct position_node, node);
    if(cont->x == x && cont->y == y) { //we should delete it
      struct intrusive_node *next = cur->next;
      remove_node(l, cur);
      free(cont);
      cur = next;
    }else {
      cur = cur->next;
    }
  }
}

void add_position(struct intrusive_list *l, int x, int y) {
  struct position_node *cur = malloc(sizeof(struct position_node));
  cur->x = x;
  cur->y = y;
  add_node(l, &(cur->node));
}

void show_all_positions(struct intrusive_list *l) {
  struct intrusive_node *cur = l->head;
  while(cur != NULL) {
    struct position_node *cont = container_of(cur, struct position_node, node);
    printf("(%d %d) ", cont->x, cont->y);
    cur = cur->next;
  }
  printf("\n");
}

void remove_all_positions(struct intrusive_list *l) {
  while(l->head != NULL) {
    struct position_node *cont = container_of(l->head, struct position_node, node);
    struct intrusive_node * cur = l->head;
    remove_node(l, cur);
    free(cont);
  }
}

int main() {
  struct intrusive_list l;
  init_list(&l);
  char s[100];
  while(1) {
    scanf("%s", s);
    if(strcmp(s,"add") == 0) {
      int x, y;
      scanf("%d %d", &x, &y);
      add_position(&l, x, y);
    }else if(strcmp(s,"rm") == 0) {
      int x, y;
      scanf("%d %d", &x, &y);
      remove_position(&l, x, y);
    }else if(strcmp(s,"print") == 0) {
      show_all_positions(&l);
    }else if(strcmp(s,"rma") == 0) {
      remove_all_positions(&l);
    }else if(strcmp(s,"len") == 0) {
      printf("%d\n", get_length(&l));
    }else if(strcmp(s,"exit") == 0) {
      break;
    }else {
      printf("Unknown command\n");
    }
  }
  remove_all_positions(&l);
 // free(&l);
  return 0;
}
