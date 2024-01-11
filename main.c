#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include "address_book.h"

struct Person *list = NULL;
FILE *address_file = NULL;

void sig_handler(int signum){
    delete_list(&list);
    fclose(address_file);
    exit(0);
}

void error_handler(char *success,int *error){
    switch(*error) {
    case 0 :
        if (success != "")
            printf("\n%s\n\n",success);
        break;
    case 1 :
        printf("\nPosition does not exist (too high)\n\n");
        *error = 0;
        break;
    case 2 :
        printf("\nPosition does not exist (too low)\n\n");
        *error = 0;
        break;
    case 3 :
        printf("\nList is empty\n\n");
        *error = 0;
        break;
    case 4 :
        printf("\nTrait not found\n\n");
        *error = 0;
        break;
    }
}

int main(void)
{
    signal(SIGINT,sig_handler); // Register signal handler
    signal(SIGQUIT,sig_handler);
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

    address_file = fopen(address_file_path, "r");

    if( address_file == NULL) {
        printf("Unable to open file\nProceding with an empty list\n");
    }
    if( address_file != NULL) {
        load_addresses(address_file, &list); //uzloadinam adresus is failo
    }
    while(run == 1){
        int c;
        char user_input[30];
        printf("Enter 'a' to print list\n");
        printf("Enter 'b' to add a new item at the end\n");
        printf("Enter 'c' to add a new item in a defined position\n");
        printf("Enter 'd' to delete a list item at a defined position\n");
        printf("Enter 'e' to delete the entire list\n");
        printf("Enter 'f' to print a list item at a defined position\n");
        printf("Enter 'g' to search for a list item by trait and print it\n");
        printf("Enter 'q' to quit\n\n");
        fscanf(stdin, " %29[^\n]", user_input);
        while ((c = getchar()) != '\n' && c != EOF); //stdin flush
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
            break;
        case 'c':
            input_person_data(&name[0],&surname[0],&email[0],&number[0],DAT_LEN);
            printf("position: ");
            fscanf(stdin, " %i", &pos_nr);
            add_to_list_nr(&list,create_node(name, surname, email, number), pos_nr, &error);
            error_handler("Added",&error);
            break;
        case 'd':
            printf("Delete position: ");
            fscanf(stdin, " %i", &pos_nr);
            delete_from_list_nr(&list, pos_nr, &error);
            error_handler("Deleted",&error);
            break;
        case 'e':
            delete_list(&list);
            printf("\nDeleted entire list\n\n");
            break;
        case 'f':
            printf("Print position: ");
            fscanf(stdin, " %i", &pos_nr);
            person_at_pos(&list, pos_nr, &error);
            error_handler("",&error);
            break;
        case 'g' :
            input_search_querry(&name[0],&trait_nr);
            person_by_trait(&list, &name[0] ,trait_nr, &error);
            error_handler("",&error);
            break;
        case 'q':
            run = 0;
        }
    }
    delete_list(&list);
    fclose(address_file);
    return 0;
}