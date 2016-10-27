#include "stdlib.h"
#include "stddef.h"
#include "phonebook.h"

int main(int argc, char* argv[]) {
    if(argc < 3) {
        return -1;
    }
    phonebook_t book;
    init_phonebook(&book);
    int t = (load_phonebook_xml(argv[1], &book));
    if(t != 0) return t;
    print_phonebook(&book);
    clear_phonebook(&book);
    init_phonebook(&book);
    gen_phonebook(&book, rand() % 100 + 1);
    save_phonebook_xml(argv[2], &book);
    clear_phonebook(&book);
    return 0;
}
