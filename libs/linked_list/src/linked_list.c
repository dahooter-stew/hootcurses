#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

node_int* create_list_node(int val)
{
  node_int* node = malloc(sizeof(node_int));

  *node = (node_int) {
    .next = NULL,
    .data = val,
  };

  return node;
}

node_int* list_at(node_int* root, int at)
{
  if (root == NULL)
    return NULL;

  for (int i = 0; i < at; i++)
  {
    root = root->next;
  }

  return root;
}

node_int* list_middle(node_int* root)
{
  node_int* slow = root;
  node_int* fast = root;

  while(fast && fast->next)
  {
    fast = fast->next->next;
    slow = slow->next;
  }

  return slow;
}

int list_length(node_int* root)
{
  if (root == NULL)
    return -1;

  int count = 1;

  while (root->next != NULL)
  {
    count++;
    root = root->next;
  }

  return count;
}

int list_insert(node_int** root, int val, int at)
{
  if (root == NULL)
    return -1;

  node_int* curr = *root;
  node_int* prev = NULL;
  int i = 0;

  if (at == LIST_START)
  {
    node_int* temp = create_list_node(val);
    temp->next = *root;
    *root = temp;

    return 0;
  }

  while (curr != NULL)
  {
    if (curr->next == NULL && at == LIST_END)
    {
      curr->next = create_list_node(val);

      return 0;
    }

    if (i == at)
    {
      node_int* temp = create_list_node(val);
      prev->next = temp;
      temp->next = curr;

      return 0;
    }

    i++;
    prev = curr;
    curr = curr->next;
  }

  return -1;
}

node_int* list_delete(node_int** root, int at)
{
  if (root == NULL)
    return NULL;

  node_int* curr = *root;
  node_int* prev = NULL;
  int i = 0;

  if (at == LIST_START)
  {
    node_int* temp = *root;
    *root = (*root)->next;
    
    return temp;
  }

  if (at == LIST_END) 
    at = list_length(*root) - 1;

  while (curr != NULL)
  {
    if (i == at)
    {
      prev->next = curr->next;
      free(curr);
      curr = NULL;

      return 0;
    }

    i++;
    prev = curr;
    curr = curr->next;
  }

  return NULL;
}

int print_list(node_int* root)
{
  if (root == NULL)
    return -1;

  while (root != NULL)
  {
    printf("( %d )->", root->data);
    root = root->next;
  }
  printf("\n");

  return 0;
}

node_int* list_reverse(node_int* root)
{
  node_int* next = root->next;
  root->next = NULL;
  node_int* prev = root;
  node_int* curr = next;

  while(curr != NULL)
  {
    next = curr->next;

    curr->next = prev;

    prev = curr;
    curr = next;
  }

  return prev;
}

node_int* number_to_list(int number)
{
  node_int* root = create_list_node(0);
  node_int* curr = root;

  while (number)  
  {
    curr->next = create_list_node(number % 10);
    curr = curr->next;
    number /= 10;
  }

  curr = root->next;
  free(root);

  return curr;
  
}

node_int* add_linked_numbers(node_int* a, node_int* b)
{
  node_int* out = create_list_node(0);
  node_int* curr = out;
  int carry = 0;

  while (a || b)
  {
    int sum = 0;
    if (a) sum += a->data;
    if (b) sum += b->data;
    sum += carry;
    carry = sum / 10;
    sum %= 10;

    curr->next = create_list_node(sum);
    curr = curr->next;
    a = a->next;
    b = b->next;

    if (!curr->next && carry > 0)
    {
      curr->next = create_list_node(carry);
    }
  }

  curr = out->next;
  free(out);

  return curr;
}

void print_linked_num(node_int* root)
{
  node_int* reversed = list_reverse(root);
  print_list(reversed);
  free(reversed);
}
