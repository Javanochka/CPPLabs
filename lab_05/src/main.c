#include "position.h"
#include "stdio.h"
#include "string.h"

void print(position_node * node, void* extra) {
    const char * params = (const char *)extra;
    printf(params, node->x, node->y);
}

void count(position_node * node, void* extra) {
    int * counter = (int *)extra;
    (*counter)++;
}

void apply(intrusive_list *lst, void (*op)(position_node*, void *), void * extra) {
    intrusive_node *head = &lst->head;
    intrusive_node *node = head->next;
    while(node != head) {
        op(get_position(node), extra);
        node = node->next;
    }
}

int make_signed(int x) {
    if(x < (1 << 23)) return x;
    return -((1 << 24) - x);
}

void loadtext(intrusive_list *lst, FILE * f) {
    while(1) {
        int x, y;
        int res = fscanf(f, "%d%d", &x, &y);
        x = make_signed(x);
        y = make_signed(y);
        if(res != 2) break;
        add_position(lst, x, y);
    }
}

int loadint(FILE * f) {
    unsigned char cur;
    int x = 0;
    for(int i = 0; i < 3 && !feof(f); i++) {
        int res = fread(&cur, sizeof(cur), 1, f);
        if (res != 1) return -1;
        x += cur << (8*i);
    }
    return x;
}

void loadbin(intrusive_list *lst, FILE * f) {
    while(1) {
        int x = loadint(f);
        int y = loadint(f);
        if(x == -1 || y == -1) break;
        x = make_signed(x);
        y = make_signed(y);
        add_position(lst, x, y);
    }
}

int make_unsigned(int x) {
    if(x >= 0) return x;
    return x + (1 << 24);
}

void savetext(intrusive_list *lst, FILE * f) {
    intrusive_node *head = &lst->head;
    intrusive_node *node = head->next;
    while(node != head) {
        position_node* cur = get_position(node);
        fprintf(f, "%d %d\n", cur->x, cur->y);
        node = node->next;
    }
}

void saveint(FILE * f, int x) {
    x = make_unsigned(x);
    unsigned char x1 = (x >> 16) & ((1 << 8)-1);
    unsigned char x2 = (x >> 8) & ((1 << 8)-1);
    unsigned char x3 = (x) & ((1 << 8)-1);
    fwrite(&x3, sizeof(x3), 1, f);
    fwrite(&x2, sizeof(x2), 1, f);
    fwrite(&x1, sizeof(x1), 1, f);
}

void savebin(intrusive_list *lst, FILE * f) {
    intrusive_node *head = &lst->head;
    intrusive_node *node = head->next;
    while(node != head) {
        position_node* cur = get_position(node);
        saveint(f, cur->x);
        saveint(f, cur->y);
        node = node->next;
    }
}

int main(int argc, char* argv[]) {
    if(argc < 4) return 0;
    intrusive_list list;
    init_list(&list);
    FILE* f = fopen(argv[2], "r");
    if(strcmp(argv[1], "loadtext") == 0) {
        loadtext(&list, f);
    }else {
        loadbin(&list, f);
    }
    fclose(f);
    if(strcmp(argv[3], "print") == 0) {
        const char * fmt = argv[4];
        apply(&list, print, (void *)fmt);
        remove_all(&list);
        return 0;
    }
    if(strcmp(argv[3], "count") == 0) {
        int ans = 0;
        apply(&list, count, (void *)(&ans));
        printf("%d\n", ans);
        remove_all(&list);
        return 0;
    }
    f = fopen(argv[4], "w");
    if(strcmp(argv[3], "savetext") == 0) {
        savetext(&list, f);
    }else {
        savebin(&list, f);
    }
    fclose(f);
    remove_all(&list);
    return 0;
}
