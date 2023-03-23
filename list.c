/* list.c */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node * new_node(char* value) {
  Node* a = malloc(sizeof(Node));
  a->value = value;
  a->next = NULL;
  return a;
}

void delete_node(Node* pnode){
  free(pnode);
  pnode = NULL;
}

List new_list(){
  List list = malloc(sizeof(List));
  *list = NULL;
  return list;
}

void push(List list, char* value){
  if(*list == NULL){
    *list = new_node(value);
  }else{
    Node *current = *list;
    while(current->next != NULL){
      current = current->next;
    }
    current->next = new_node(value);
  }
}

char* pop(List list){
  if(*list == NULL){
    return NULL;
  }
  if((*list)->next == NULL){
    char *value = (*list)->value;
    free(*list);
    *list = NULL;
    return value;
  }
  Node *last = *list;
  Node *curr = last->next;
  while(curr->next != NULL){
    last = curr;
    curr = curr->next;
  }
  char *value = curr->value;
  free(curr);
  last->next = NULL;
  return value;
}

char* peek(List list){
  if(*list == NULL){
    return NULL;
  }
  if((*list)->next == NULL){
    return (*list)->value;
  }
  Node *last = *list;
  Node *curr = last->next;
  while(curr->next != NULL){
    last = curr;
    curr = curr->next;
  }
  return curr->value;
}

void print_list(List list){
  if(*list == NULL){
    printf("[]\n");
  }else{
    Node *curr = *list;
    printf("[");
    while (curr->next != NULL){
      printf("\"%s\", ", curr->value);
      curr = curr->next;
    }
    printf("\"%s\"", curr->value);
    printf("]\n");
  }
}

void add(List list, char *value){
  if(*list == NULL){
    *list = new_node(value);
  }else{
    Node *node = new_node(value);
    node->next = *list;
    *list = node;
  }
}

char* rem(List list){
  if(*list == NULL){
    return NULL;
  }
  Node *curr = *list;
  Node *next = curr->next;
  char *value = curr->value;
  free(curr);
  *list = next;
  return value;
}

int is_empty(List list){
  if(*list != NULL){
    return 0;
  }
  return 1;
}

int size(List list){
  int count = 0;
  Node *curr = *list;
  while(curr != NULL){
    count ++;
    curr = curr->next;
  }
  return count;
}

void clear(List list){
  while(*list!=NULL){
    rem(list);
  }
}

int index_of(List list, char* val){
  Node *curr = *list;
  if(curr == NULL){
    return -1;
  }
  int index = 0;
  while(curr != NULL){
    if(curr->value == val){
      return index;
    }
    curr = curr->next;
    index ++;
  }
  return -1;
}

int contains(List list, char* val){
  int bool = index_of(list, val);
  if(bool == -1){
    return 0;
  }
  return 1;
}

char* get_at(List list, int index){
  Node *node = *list;
  
  if(node==NULL){
    return NULL;
  }
  
  for(int i = 0; i < index; i++){
    if(node->next == NULL){
      return NULL;
    }
    node = node->next;
  }
  return node->value;
}

int replace_at(List list, int index, char* value){
  Node *node = *list;
  if(node == NULL){
    return 0;
  }
  
  for(int i = 0; i < index; i++){
    if(node->next == NULL){
      return 0;
    }
    node = node->next;
  }
  node->value = value;
  return 1;
}

int insert_at(List list, int index, char* value){
  if(*list == NULL || index == 0){
    add(list, value);
    return 1;
  }
  if(index < 0){
    return 0;
  }
  Node *prev = *list;
  if(prev->next == NULL && index == 1){
    push(list, value);
    return 1;
  }
  Node *next = prev->next;
  Node *new = new_node(value);
  
  for(int i = 0; i < (index-1); i++){
    if(prev->next == NULL){
      return 0;
    }
    prev = prev->next;
    next = prev->next;
  }
  prev->next = new;
  new->next = next;
  return 1;
}

char* remove_at(List list, int index){
  if(*list == NULL || index < 0){
    return NULL;
  }
  Node *prev = *list;
  if(index == 0){
      char* value = rem(list);
      return value;
  }
  if(prev->next == NULL){
      return NULL;
  }
  Node *curr = prev->next;
  if(curr->next == NULL){
    if(index == 1){
      char* value = pop(list);
      return value;
    }
    return NULL;
  }
  Node *next = curr->next;
  
  for(int i = 0; i < (index-1); i++){
      prev = prev->next;
      if(curr->next == NULL){
          return NULL;
      }
      curr = prev->next;
      if(curr->next == NULL){
          next = NULL;
      }else{
        next = curr->next;
      }
  }
  if(next != NULL){
      prev->next = next;
      char* value = curr->value;
      delete_node(curr);
      return value;
  }
  char* value = pop(list);
  return value;
}

List copy_list(List list){
  if(*list == NULL){
    return NULL;
  }
  Node *node = *list;
  List copy = new_list();
  int i = 0;
  while(node != NULL){
    push(copy, get_at(list, i));
    node = node->next;
    i++;
  }
  return copy;
}

List sublist(List list, int start, int end){
  List sublist = new_list();
  if(*list == NULL){
    return NULL;
  }
  
  if(end < start || start < 0 || end > size(list)){
    return NULL;
  }
  
  for(int i = start; i < end; i++){
    push(sublist, get_at(list, i));
  }
  return sublist;
}