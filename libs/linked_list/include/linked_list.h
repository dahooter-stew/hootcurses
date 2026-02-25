#ifndef LINKED_LIST
#define LINKED_LIST

#define LIST_START 0
#define LIST_END -1

typedef struct node_int 
{
  struct node_int* next;
  int data;
} node_int;

node_int* create_list_node(int);

node_int* list_at(node_int*, int);

node_int* list_middle(node_int*);

int list_length(node_int*);

int list_insert(node_int**, int, int);

node_int* list_delete(node_int**, int);

int print_list(node_int*);

node_int* list_reverse(node_int*);

node_int* number_to_list(int);

node_int* add_lists(node_int*, node_int*);

node_int* add_linked_numbers(node_int*, node_int*);

void print_linked_num(node_int*);

#endif
