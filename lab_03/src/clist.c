#include "clist.h"
#include "stddef.h"
#include "stdlib.h"
#include "stdio.h"


void init_list(struct intrusive_list *l) {
  //l = malloc(sizeof(struct intrusive_list));
  l->head = NULL;
}
void add_node(struct intrusive_list *l, struct intrusive_node *node) {
  node->prev = NULL;
  node->next = NULL;
  if(l->head == NULL) {
    l->head = node;
    return;
  }
  l->head->prev = node;
  node->next = l->head;
  l->head = node;
}
void remove_node(struct intrusive_list *l, struct intrusive_node *node) {
  if(node->prev == NULL) { //if the node is a head of the list
    l->head = node->next;
    node = node->next;
    if(node != NULL) { //it can be both a head and a tail
      node->prev = NULL;
    }
    return;
  }
  if(node->next == NULL) { //if a node is a tail of the list
    node->prev->next = NULL;
    return;
  }
  node->prev->next = node->next;
  node->next->prev = node->prev;
  node->next = NULL;
  node->prev = NULL;
}

int get_length(struct intrusive_list *l) {
  int len = 0;
  struct intrusive_node *cur = l->head;
  for(;cur != NULL; cur = cur->next, len++);
  return len;
}
