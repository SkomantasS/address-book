#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address_book.h"

static char* return_trait_by_trait_nr(struct Person *person, int trait_nr)
{
    switch (trait_nr) {
    case 1 :
        return(person->name);
        break;
    case 2 :
        return(person->surname);
        break;
    case 3 :
        return(person->email);
        break;
    case 4 :
        return(person->number);
        break;
    }
    return(person->name);
}

static void removeNewLineChar(char *ptr)
{
    while((ptr != NULL) && (*ptr != '\n'))
    {
        ++ptr;
    }
    *ptr = '\0';
}

void load_addresses(FILE *file, struct Person **list)
{
    char line[128];
    while (fgets(line, sizeof(line), file)) {
        struct Person *person = NULL;
        if(strcmp(line, "\n") == 0) {
            continue;
        }
        person = create_address_node(line);
        if (person != NULL) {
            add_to_list(list, person);
        }
    }
}

struct Person* create_address_node(char *address_line)
{
    struct Person *person = NULL;
    char *name;
    char *surname;
    char *email;
    char *number;

    name = strtok(address_line, DELIMETER);
    surname = strtok(NULL, DELIMETER);
    email = strtok(NULL, DELIMETER);
    number = strtok(NULL, DELIMETER);
    removeNewLineChar(number); //remove new line character
    
    person = create_node(name, surname, email, number);
    
    return person;
}

struct Person* create_node(char *name, char *surname, char *email, char *number)
{
    struct Person *person = NULL;
    person = (struct Person*) malloc(sizeof(struct Person));
    if (person == NULL) {
        return NULL;
    }
    strcpy(person->name, name);
    strcpy(person->surname, surname);
    strcpy(person->email, email);
    strcpy(person->number, number);
    person->next = NULL;
    return person;
}

void add_to_list(struct Person **list, struct Person *person)
{
    struct Person* temp = *list;
    if (temp == NULL) {
        *list = person;
        return; 
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = person;
}

void print_list(struct Person *list)
{
    struct Person *temp = list;
    while (temp != NULL) {
        printf("%s %s %s %s\n", temp->name, temp->surname, temp->email, temp->number);
        temp = temp->next;
    }
    printf("\n");
}

void delete_list(struct Person **list)
{
    struct Person *to_delete = *list; //list should be a pointer
    while (*list != NULL) {
        *list = (*(list))->next;
        free(to_delete);
        to_delete = *list;
    }
}

int add_to_list_nr(struct Person **list, struct Person *person, int pos_nr)
{
    if (pos_nr<=0) {
        return(-2);
    }
    if (*list == NULL) {
        *list = person;
        return(-3); 
    }
    struct Person *temp = *list;
    if (pos_nr == 1) {
        person->next = *list;
        *list = person;
        return(0);
    }
    for (int i = 2; i < pos_nr; i++) {
        if (temp->next != NULL){
            temp = temp->next;
        }else if (i<pos_nr) {
            return(75);
        }
    }
    person->next = temp->next;
    temp->next = person;
    return(0);
}

int delete_from_list_nr(struct Person **list, int pos_nr)
{
    if (pos_nr <= 0) {
        return(-2);
    }
    if (*list == NULL) {
        return(-3); 
    }
    struct Person *temp = *list;
    if (pos_nr == 1) {
        *list = (*(list))->next;
        free(temp);  
        return(0);
    }
    for (int i = 2; i < pos_nr; i++) {
        if (temp->next->next != NULL){
            temp = temp->next;
        }else if (i < pos_nr) {
            return(75); 
        }
    }
    struct Person *to_delete = (temp->next);
    temp->next = temp->next->next;
    free(to_delete);
    return(0);
}

int person_at_pos(struct Person **list, int pos_nr)
{
    if (pos_nr <= 0){
        return(-2);
    }
    if (*list == NULL){
        return(-3);
    }
    struct Person *temp = *list;
    for (int i = 1; i < pos_nr; i++) {
        if (temp->next != NULL){
            temp = temp->next;
        } else if (i < pos_nr) {
            return(75);
        }
    }
    printf("\n%s %s %s %s\n\n",temp->name,temp->surname,temp->email,temp->number);
    return(0);
}

int person_by_trait(struct Person **list, char *trait, int trait_nr)
{
    if (*list == NULL){
        return(-3);
    }
    int ptr_ls_cur = 0;
    struct Person *temp = *list;
    char *to_compare_with = NULL;
    printf("\n");
    while ((temp->next) != NULL) {
        to_compare_with = return_trait_by_trait_nr(temp,trait_nr);
        if (strcmp(to_compare_with,trait) == 0){
            printf("%s %s %s %s\n",temp->name,temp->surname,temp->email,temp->number);
            ptr_ls_cur++;
        }
        temp = temp->next;
    }
    if (strcmp(to_compare_with,trait) == 0) {
        printf("%s %s %s %s\n",temp->name,temp->surname,temp->email,temp->number);
    } else if (ptr_ls_cur == 0){
        return(-4);
    }
    printf("\n");
    return(0);
}
