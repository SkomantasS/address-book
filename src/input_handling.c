#include <stdio.h>

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

void input_person_data(char *name, char *surname, char *email, char *number)
{
    int c;
    printf("name: "); //how to use buf_sz variable
    scanf(" %29[^\n]s", name);
    while ((c = getchar()) != '\n' && c != EOF); //stdin flush
    printf("surname: ");
    scanf(" %29[^\n]s", surname);
    while ((c = getchar()) != '\n' && c != EOF); //stdin flush
    printf("email: ");
    scanf(" %59[^\n]s", email);
    while ((c = getchar()) != '\n' && c != EOF); //stdin flush
    printf("phone number: ");
    scanf(" %29[^\n]s", number);
    while ((c = getchar()) != '\n' && c != EOF); //stdin flush
    printf("\n");
}