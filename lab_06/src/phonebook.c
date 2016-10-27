#include "phonebook.h"
#include "names.h"
#include "expat.h"
#include "stdio.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
#define BUFF_SIZE 4096

static bool IF_STARTED_PHONE;

void start_element(void *data, const char *element, const char **attribute) {
    if (strcmp(element, "human") != 0) return;
    phonebook_t *book = data;
    human_t human;
    char * copy_attr = malloc(sizeof(human)*(strlen(attribute[1]) + 1));
    strcpy(copy_attr, attribute[1]);
    strcpy(human.name, strtok(copy_attr, " "));
    strcpy(human.middle_name, strtok(NULL, " "));
    strcpy(human.family_name, strtok(NULL, " "));
    human.phones_num = 0;
    push_back_human(book, &human);
    IF_STARTED_PHONE = false;
    free(copy_attr);
}

void end_element(void *data, const char *element) {
    //do nothing
}

void handle_data(void *data, const char *content, int length) {
    char *tmp = malloc(length+1);
    strncpy(tmp, content, length);
    tmp[length] = '\0';
    if(tmp[0] >= '0' && tmp[0] <= '9') {
        phonebook_t *book = data;
        human_t *cur_human = &(book->humans[book->size - 1]);
        if(!IF_STARTED_PHONE) { 
            strcpy(cur_human->phones[cur_human->phones_num++], tmp);
        }else {
            strcat(cur_human->phones[cur_human->phones_num-1], tmp);
        }
        IF_STARTED_PHONE = true;
    }else {
        IF_STARTED_PHONE = false;
    }
    free(tmp);
}


int compare_humans(const void *a, const void *b) {
    human_t *ha = (human_t*)a;
    human_t *hb = (human_t*)b;
    return strcmp(ha->family_name, hb->family_name);
}

int load_phonebook_xml(const char *filename, phonebook_t *book) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    XML_Parser  parser = XML_ParserCreate(NULL);
    XML_SetElementHandler(parser, start_element, end_element);
    XML_SetCharacterDataHandler(parser, handle_data);
    XML_SetUserData(parser, book);
    char *buff = malloc(BUFF_SIZE);

    memset(buff, 0, BUFF_SIZE);

    size_t len = 0;
    int done = 0;
    do {
        len = fread(buff, sizeof(char), BUFF_SIZE, fp);
        done = len < BUFF_SIZE;

        if (XML_Parse(parser, buff, len, done) == XML_STATUS_ERROR) {
            printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(parser)));
            fclose(fp);
            free(buff);
            return 2;
        }
    } while (!done);

    XML_ParserFree(parser);
    fclose(fp);
    free(buff);
    qsort(book->humans, book->size, sizeof(human_t), compare_humans);
    return 0;
}

int save_phonebook_xml(const char *filename, phonebook_t *book) {
    FILE *fw = fopen(filename, "w");
    fprintf(fw, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fw, "<phonebook>\n");
    for(int i = 0; i < book->size; i++) {
        fprintf(fw, "    <human name=\"%s %s %s\">\n", book->humans[i].name, book->humans[i].middle_name, book->humans[i].family_name);
        for(int j = 0; j < book->humans[i].phones_num; j++) {
            fprintf(fw, "        <phone>%s</phone>\n", book->humans[i].phones[j]);
        }
        fprintf(fw, "    </human>\n");
    }
    fprintf(fw, "</phonebook>\n");
    fclose(fw);
}

void print_phonebook(phonebook_t *book) {
    printf("%zu\n", book->size);
    int i = 0;
    for(i = 0; i < book->size; i++) {
        printf("name: %s\n", book->humans[i].name);
        printf("middle name: %s\n", book->humans[i].middle_name);
        printf("family name: %s\n", book->humans[i].family_name);
        int j = 0;
        for(j = 0; j < book->humans[i].phones_num; j++) {
            printf("phone: %s\n", book->humans[i].phones[j]);
        }
        printf("\n");
    }
}

human_t gen_human() {
    human_t human;

    strcpy(human.name, kNames[rand() % NAMES_CNT]);
    strcpy(human.middle_name, kMiddleNames[rand() % MIDDLE_NAMES_CNT]);
    strcpy(human.family_name, kFamilyNames[rand() % FAMILY_NAMES_CNT]);

    human.phones_num = (rand() % 10) + 1;
    for (int i = 0; i < human.phones_num; i++) {
        int len = (rand() % 20) + 1;
	for (int j = 0; j < len; j++) {
            human.phones[i][j] = '0' + (rand() % 10);
        }    
        human.phones[i][len] = '\0';
    }
    return human;
}

void gen_phonebook(phonebook_t* book, size_t size) {
    for (; size > 0; size--) {
        human_t human = gen_human();
        push_back_human(book, &human);
    }
}

void init_phonebook(phonebook_t *book) {
    book->size = 0;
    book->capacity = 1;
    book->humans = malloc(sizeof(human_t));
}

void clear_phonebook(phonebook_t *book) {
    free(book->humans);
    book->size = 0;
    book->capacity = 0;
}


void push_back_human(phonebook_t *book, human_t *human) {
    if(book->size == book->capacity) {
        book->capacity *= 2;
        book->humans = realloc(book->humans, book->capacity * sizeof(human_t));
    }
    book->humans[book->size] = *human;
    book->size++;
}


