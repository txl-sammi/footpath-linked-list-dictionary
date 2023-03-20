#ifndef _LIST_H_
#define _LIST_H_
#include <stdio.h>

// type definitions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct list list_t;
typedef struct node node_t;


// creates & returns an empty linked list
list_t *listCreate();

// free the list, with the help of function "freeData" for freeind data component
void listFree(list_t *list, void (*dataFree)(void *));

// inserts a new node with value "data" to the end of "list" 
void listAppend(list_t *list, footpath_t *data); 

// performs linear search in "list", returns found data or NULL 
void *listSearch(list_t *list, char *query, FILE *infoFile);


#endif
