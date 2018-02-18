#ifndef __LIST_H
#define __LIST_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define LIST_MALLOC_ERROR 1
#define LIST_OK 0

// a common function used to free malloc'd objects
typedef void (*freeFunction)(void *);
 
typedef bool (*listIterator)(void *);
 
typedef struct _listNode {
  void *data;
  struct _listNode *next;
} listNode;
 
typedef struct List {
  int length;
  int elementSize;
  listNode *head;
  listNode *tail;
  freeFunction freeFn;
} List;
 
void list_new(List *list, unsigned long int elementSize, freeFunction freeFn);
void list_destroy(List *list);
 
unsigned int list_prepend(List *list, void *element);
unsigned int list_append(List *list, void *element);
unsigned long int list_size(List *list);
 
void list_foreach(List *list, listIterator iterator);
void list_head(List *list, void *element, bool removeFromList);
void list_tail(List *list, void *element);
 
#endif
