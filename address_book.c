#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "address_book.h"
#define DELIMETER ","
#define DAT_LEN 30

struct Person {
    char name[DAT_LEN];
    char surname[DAT_LEN];
    char email[DAT_LEN];
    char number[DAT_LEN];
    struct Person *next;
};

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

void input_person_data(char *name, char *surname, char *email, char *number, int buf_sz)
{
    printf("name: "); //how to use buf_sz variable
    scanf(" %29[^\n]s", name);
    printf("surname: ");
    scanf(" %29[^\n]s", surname);
    printf("email: ");
    scanf(" %29[^\n]s", email);
    printf("phone number: ");
    scanf(" %29[^\n]s", number);
    printf("\n");
}

void add_to_list_nr(struct Person **list, struct Person *person, int pos_nr, int *error)
{
    *error = 0;
    if (pos_nr<=0) {
        *error = 2;
        return;
    }
    if (*list == NULL) {
        *error = 3;
        *list = person;
        return; 
    }
    struct Person *temp = *list;
    if (pos_nr == 1) {
        person->next = *list;
        *list = person;
        return;
    }
    for (int i = 2; i < pos_nr; i++) {
        if (temp->next != NULL){
            temp = temp->next;
        }else if (i<pos_nr) {
            *error = 1;
            return; 
        }
    }
    if (*error == 0) {
        person->next = temp->next;
        temp->next = person;
    }
}

void delete_from_list_nr(struct Person **list, int pos_nr, int *error)
{
    *error = 0;
    if (pos_nr <= 0) {
        *error = 2;
        return;
    }
    if (*list == NULL) {
        *error = 3;
        return; 
    }
    struct Person *temp = *list;
    if (pos_nr == 1) {
        *list = (*(list))->next;
        free(temp);  
        return;
    }
    for (int i = 2; i < pos_nr; i++) {
        if (temp->next->next != NULL){
            temp = temp->next;
        }else if (i < pos_nr) {
            *error = 1;
            return; 
        }
    }
    if (*error == 0){
        struct Person *to_delete = (temp);
        temp->next = temp->next->next;
        temp = temp->next;
        free(to_delete);
    }
}

struct Person* person_at_pos(struct Person **list, int pos_nr, int *error)
{
    *error = 0;
    if (pos_nr <= 0)
        *error = 2;
    if (*list == NULL)
        *error = 3; //how to handle
    struct Person *temp = *list;
    for (int i = 1; i < pos_nr; i++) {
        if (temp->next != NULL)
            temp = temp->next;
        if ((temp->next == NULL) && (i<pos_nr-1))
            *error = 1;
    }
    return(temp);
}

struct Person* person_by_trait(struct Person **list, char *trait, int trait_nr, int *error)
{
    struct Person *temp = *list;
    switch(trait_nr) {
    case 1:
        while ((temp->next) != NULL) {
            if (strcmp(temp->name,trait)==0)
                break;
            temp = temp->next;
        }
        break;
    case 2:
        while ((temp->next) != NULL) {
            if (strcmp(temp->surname,trait)==0)
                break;
            temp = temp->next;
        }
        break;
    case 3:
        while ((temp->next) != NULL) {
            if (strcmp(temp->email,trait)==0)
                break;
            temp = temp->next;
        }
        break;
    case 4:
        while ((temp->next) != NULL) {
            if (strcmp(temp->number,trait)==0)
                break;
            temp = temp->next;
        }
        break;
    }
    return(temp);
}

void removeNewLineChar(char *ptr)
{
    while((ptr != NULL) && (*ptr != '\n'))
    {
        ++ptr;
    }
    *ptr = '\0';
}