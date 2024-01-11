#define DELIMETER ","
#define DAT_LEN 30

struct Person {
    char name[DAT_LEN];
    char surname[DAT_LEN];
    char email[DAT_LEN];
    char number[DAT_LEN];
    struct Person *next;
};

struct Person* create_node(char *name, char *surname, char *email, char *number);
struct Person* create_address_node(char *address_line);
void add_to_list(struct Person **list, struct Person *node);
void print_list(struct Person *list);
void delete_list(struct Person **list);
void load_addresses(FILE *file, struct Person **list);
void delete_from_list_nr(struct Person **list, int pos_nr, int *error);
void input_search_querry(char *name, int *trait_nr);
void input_person_data(char *name, char *surname, char *email, char *number, int buf_sz);
void add_to_list_nr(struct Person **list, struct Person *person, int pos_nr, int *error);
void person_at_pos(struct Person **list, int pos_nr, int *error);
void person_by_trait(struct Person **list, char *trait, int trait_nr, int *error);
