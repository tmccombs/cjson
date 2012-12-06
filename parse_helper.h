#ifndef PARSE_HELPER_H
#define PARSE_HELPER_H

#include <stdlib.h>
#include <stdbool.h>

#include "json_types.h"

/* Linked list used to build an array for JSON */
struct json_llist_node; // a node of a linked list
typedef struct json_llist_node json_llist_node;

typedef json_llist_node *JSON_llist; //a linked list


struct json_llist_node{
    size_t index;
    JSON value;
    JSON_llist next;
};

#endif
