#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "data.h"
#include "list.h"

// a list node 
struct node {
	footpath_t *data;              // points to the data element of the node
	node_t *next;            // points to the next node in the list
};

// a linked list is defined as a couple of pointers
struct list {
	node_t *head;  // points to the first node of the list
	node_t *tail;  // points to the last node of the list 
	size_t n;               // number of element in the list
};

// creates & returns an empty linked list
list_t *listCreate() {
	list_t *list = malloc(sizeof(*list));
	assert(list);
	list->head = list->tail = NULL;
	list->n = 0;
	return list;
}

// free the list
void listFree(list_t *list, void (*dataFree)(void *)) {
	assert(list != NULL);
	node_t *curr = list->head; // curr points to the first node
	while (curr) {             // while curr not reaching the end of list
		node_t *tmp = curr;
		curr = curr->next;     // advance curr to the next next node 
		dataFree(tmp->data);       // frees the previous node including
		free(tmp);             //    freeing the space used by data
	}
	free(list);                // free the list itself
} 

// inserts a new node with value "data" to the end of "list" 
void listAppend(list_t *list, footpath_t *data) {
	assert(list);

	// creates a new node and set data 
	node_t *new = malloc(sizeof(*new));
	assert(new);
	new->data = data;
	new->next = NULL;

	// FILL IN
	if (list->tail == NULL){
		list->head = new;
		list->tail = new;
	} 
	else {
		node_t *old = list->tail;
		old->next = new;
		list->tail = new;
	}
	(list->n)++;
}

// performs linear search in "list", returns found data or NULL 
void *listSearch(list_t *list, char *query, FILE *infoFile) {
	node_t* current = list->head;
	int found=0;
	int count=0;
    while (current != NULL) {
		footpath_t *p = current->data;
        if (addresscmp(query, p) == 0) {
            found=1;
			count++;
            footpathPrint(infoFile, p);
        }
        current = current->next;
    }
	if (found == 0) {
		fprintf(stdout, "%s --> NOTFOUND\n", query);
	} else{
		fprintf(stdout, "%s --> %d\n", query, count);
	}
}


