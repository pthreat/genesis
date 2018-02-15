#include "../../include/util/list.h"

void list_new(List *list, unsigned long int elementSize, freeFunction freeFn)
{
	assert(elementSize > 0);
	list->length = 0;
	list->elementSize = elementSize;
	list->head = list->tail = NULL;
	list->freeFn = freeFn;
}

void list_destroy(List *list)
{
	listNode *current;
	while(list->head != NULL) {
		current = list->head;
		list->head = current->next;

		if(list->freeFn) {
			list->freeFn(current->data);
		}

		free(current->data);
		free(current);
	}
}

unsigned int list_prepend(List *list, void *element)
{
	listNode *node = malloc(sizeof(listNode));

	if(node == NULL){
		return LIST_MALLOC_ERROR;
	}

	node->data = malloc(list->elementSize);

	if(node->data == NULL){
		return LIST_MALLOC_ERROR;
	}

	memcpy(node->data, element, list->elementSize);

	node->next = list->head;
	list->head = node;

	// first node?
	if(!list->tail) {
		list->tail = list->head;
	}

	list->length++;

	return LIST_OK;
}

unsigned int list_append(List *list, void *element)
{
	listNode *node = malloc(sizeof(listNode));

	if(node == NULL){
		return LIST_MALLOC_ERROR;
	}

	node->data = malloc(list->elementSize);

	if(node->data == NULL){
		return LIST_MALLOC_ERROR;
	}

	node->next = NULL;

	memcpy(node->data, element, list->elementSize);

	if(list->length == 0) {
		list->head = list->tail = node;
	} else {
		list->tail->next = node;
		list->tail = node;
	}

	list->length++;

	return LIST_OK;
}

void list_foreach(List *list, listIterator iterator)
{
	assert(iterator != NULL);

	listNode *node = list->head;

	bool result = true;

	while(node != NULL && result) {
		result = iterator(node->data);
		node = node->next;
	}
}

void list_head(List *list, void *element, bool removeFromList)
{
	assert(list->head != NULL);

	listNode *node = list->head;
	memcpy(element, node->data, list->elementSize);

	if(removeFromList) {
		list->head = node->next;
		list->length--;

		free(node->data);
		free(node);
	}
}

void list_tail(List *list, void *element)
{
	assert(list->tail != NULL);
	listNode *node = list->tail;
	memcpy(element, node->data, list->elementSize);
}

unsigned long int list_size(List *list)
{
	return list->length;
}
