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

void input_search_querry(char *name, int *trait_nr)
{
    int c;
    printf("Enter '1' to search by name\n");
    printf("Enter '2' to search by surname\n");
    printf("Enter '3' to search by email\n");
    printf("Enter '4' to search by phone number\n\n");
    *trait_nr = 0;
    while ((*trait_nr > 4) || (*trait_nr < 1)){
        fscanf(stdin, " %i", trait_nr);
        while ((c = getchar()) != '\n' && c != EOF); //stdin flush
        printf("\n");
        switch (*trait_nr) {
        case 1 :
            printf("Enter name: ");
            break;
        case 2 :
            printf("Enter surname: ");
            break;
        case 3 :
            printf("Enter email: ");
            break;
        case 4 :
            printf("Enter phone number: ");
            break;
        default :
            printf("Invalid input, try again:");
        }
    }
    fscanf(stdin, " %29[^\n]s", &name[0]);
    while ((c = getchar()) != '\n' && c != EOF); //stdin flush
}

void input_person_data(char *name, char *surname, char *email, char *number, int buf_sz)
{
    int c;
    printf("name: "); //how to use buf_sz variable
    scanf(" %29[^\n]s", name);
    while ((c = getchar()) != '\n' && c != EOF); //stdin flush
    printf("surname: ");
    scanf(" %29[^\n]s", surname);
    while ((c = getchar()) != '\n' && c != EOF); //stdin flush
    printf("email: ");
    scanf(" %29[^\n]s", email);
    while ((c = getchar()) != '\n' && c != EOF); //stdin flush
    printf("phone number: ");
    scanf(" %29[^\n]s", number);
    while ((c = getchar()) != '\n' && c != EOF); //stdin flush
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
        struct Person *to_delete = (temp->next);
        temp->next = temp->next->next;
        free(to_delete);
    }
}

void person_at_pos(struct Person **list, int pos_nr, int *error)
{
    *error = 0;
    if (pos_nr <= 0){
        *error = 2;
        return;
    }
    if (*list == NULL){
        *error = 3; //how to handle
        return;
    }
    struct Person *temp = *list;
    for (int i = 1; i < pos_nr; i++) {
        if (temp->next != NULL){
            temp = temp->next;
        } else if (i < pos_nr) {
            *error = 1;
            return;
        }
    }
    printf("\n%s %s %s %s\n\n",temp->name,temp->surname,temp->email,temp->number);
    return;
}

void person_by_trait(struct Person **list, char *trait, int trait_nr, int *error)
{
    if (*list == NULL){
        *error = 3;
        return;
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
        *error = 4;
    }
    printf("\n");
    return;
}
