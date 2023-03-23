/* list.h */

typedef struct node{
  char *value;
  struct node *next;
} Node;

typedef Node** List;

List new_list();

void push(List list, char* value);

char* pop(List list);

void print_list(List list);

char* peek(List list);

void add(List list, char* val);

char* rem(List list);

int is_empty(List list);

int size(List list);

void clear(List list);

int index_of(List list, char* val);

int contains(List list, char* val);

char* get_at(List list, int index);

int replace_at(List list, int index, char* value);

int insert_at(List list, int index, char*value);

char* remove_at(List list, int index);

List copy_list(List list);

List sublist(List list, int start, int end);
