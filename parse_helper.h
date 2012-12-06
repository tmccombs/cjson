/****************************************************************************************
*  Copyright 2012 Thayne McCombs
* 
*  This file is part of cjson.
*  
*      cjson is free software: you can redistribute it and/or modify
*      it under the terms of the GNU General Public License as published by
*      the Free Software Foundation, either version 3 of the License, or
*      (at your option) any later version.
*  
*      cjson is distributed in the hope that it will be useful,
*      but WITHOUT ANY WARRANTY; without even the implied warranty of
*      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*      GNU General Public License for more details.
*  
*      You should have received a copy of the GNU General Public License
*      along with cjson.  If not, see <http://www.gnu.org/licenses/>.
*/
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
