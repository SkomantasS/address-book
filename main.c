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

int main(void)
{
    char name[DAT_LEN];
    char surname[DAT_LEN];
    char email[DAT_LEN];
    char number[DAT_LEN];
    struct Person *temp = NULL;
    int pos_nr;
    int trait_nr;
    bool run = 1;
    int error = 0; //0 - no err; 1 - too high; 2 - too low

    char address_file_path[30];
    char address_file_name[30] = "/addresses.csv";

    strcpy(address_file_path, getenv("HOME"));
    strcat(address_file_path,address_file_name);
    // printf("%s\n",address_file_path);

    struct Person *list = NULL;
    FILE *address_file = NULL;

    address_file = fopen(address_file_path, "r");

    if( address_file == NULL) {
        printf("Unable to open file\nProceding with an empty list\n");
    }
    if( address_file != NULL) {
        load_addresses(address_file, &list); //uzloadinam adresus is failo
    }
    while(run == 1){
        char user_input[128];
        printf("Enter 'a' to print list\n");
        printf("Enter 'b' to add a new item at the end\n");
        printf("Enter 'c' to add a new item in a defined position\n");
        printf("Enter 'd' to delete a list item at a defined position\n");
        printf("Enter 'e' to delete the entire list\n");
        printf("Enter 'f' to print a list item at a defined position\n");
        printf("Enter 'g' to search for a list item by trait and print it\n");
        printf("Enter 'q' to quit\n\n");
        fscanf(stdin, " %[^\n]", user_input);

        char first_letter = user_input[0];

        printf("\nYour input %c\n\n", first_letter);

        switch(first_letter) {
        case 'a':
            print_list(list);
            break;
        case 'b':
            input_person_data(&name[0],&surname[0],&email[0],&number[0],DAT_LEN);
            add_to_list(&list,create_node(name, surname, email, number));
            printf("\nAdded\n\n");
            // print_list(list);
            break;
        case 'c':
            input_person_data(&name[0],&surname[0],&email[0],&number[0],DAT_LEN);
            printf("position: ");
            fscanf(stdin, " %i", &pos_nr);
            add_to_list_nr(&list,create_node(name, surname, email, number), pos_nr, &error);
            switch(error) {
            case 0 :
                printf("\nAdded\n\n");
                break;
            case 1 :
                printf("\nPosition does not exist (too high)\n\n");
                error = 0;
                break;
            case 2 :
                printf("\nPosition does not exist (too low)\n\n");
                error = 0;
                break;
            case 3 :
                printf("\nList is empty, adding at position 1\n\n");
                error = 0;
            }
            // print_list(list);
            break;
        case 'd':
            printf("Delete position: ");
            fscanf(stdin, " %i", &pos_nr);
            delete_from_list_nr(&list, pos_nr, &error);
            switch(error) {
            case 0 :
                printf("\nDeleted\n\n");
                break;
            case 1 :
                printf("\nPosition does not exist (too high)\n\n");
                error = 0;
                break;
            case 2 :
                printf("\nPosition does not exist (too low)\n\n");
                error = 0;
                break;
            case 3 :
                printf("\nList is empty\n\n");
                error = 0;
                break;
            }
            // print_list(list);
            break;
        case 'e':
            delete_list(&list);
            printf("\nDeleted\n\n");
            // print_list(list);
            break;
        case 'f':
            if(list == NULL){
                error = 3;
            } else {
                printf("Print position: ");
                fscanf(stdin, " %i", &pos_nr);
                temp = person_at_pos(&list, pos_nr, &error);
            }
            switch(error) {
            case 0:
                printf("\n%s %s %s %s\n\n",temp->name,temp->surname,temp->email,temp->number);
                break;
            case 1:
                printf("\nPosition does not exist (too high)\n\n");
                error = 0;
                break;
            case 2:
                printf("\nPosition does not exist (too low)\n\n");
                error = 0;
                break;
            case 3 :
                printf("\nList is empty\n\n");
                error = 0;
                break;
            }
            break;
        case 'g' :
            printf("Enter '1' to search by name\n");
            printf("Enter '2' to search by surname\n");
            printf("Enter '3' to search by email\n");
            printf("Enter '4' to search by phone number\n\n");
            fscanf(stdin, " %i", &trait_nr);
            printf("\n");
            switch(trait_nr){
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
            }
            fscanf(stdin, " %[^\n]s", &name[0]);
            // printf("%s",name);
            temp = person_by_trait(&list, &name[0] ,trait_nr, &error);
            printf("\n%s %s %s %s\n\n",temp->name,temp->surname,temp->email,temp->number);
            break;
        case 'q':
            run = 0;
        }
    }
    delete_list(&list);
    fclose(address_file);
    return 0;
}